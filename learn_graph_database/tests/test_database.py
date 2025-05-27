"""
Unit tests for graph database module.
"""
import pytest
from unittest.mock import Mock, patch, MagicMock
from neo4j import GraphDatabase as Neo4jGraphDatabase
from neo4j.exceptions import ServiceUnavailable, AuthError

from src.graph.database import GraphDatabase


@pytest.mark.unit
class TestGraphDatabase:
    """Test cases for GraphDatabase class."""

    def test_init_with_valid_params(self):
        """Test database initialization with valid parameters."""
        with patch.object(Neo4jGraphDatabase, 'driver') as mock_driver:
            mock_driver.return_value = Mock()
            
            db = GraphDatabase(
                uri="bolt://localhost:7687",
                username="neo4j",
                password="password"
            )
            
            assert db.uri == "bolt://localhost:7687"
            assert db.username == "neo4j"
            assert db.database == "neo4j"
            mock_driver.assert_called_once()

    def test_init_with_custom_database(self):
        """Test database initialization with custom database name."""
        with patch.object(Neo4jGraphDatabase, 'driver') as mock_driver:
            mock_driver.return_value = Mock()
            
            db = GraphDatabase(
                uri="bolt://localhost:7687",
                username="neo4j",
                password="password",
                database="custom_db"
            )
            
            assert db.database == "custom_db"

    def test_connection_failure(self):
        """Test handling of connection failures."""
        with patch.object(Neo4jGraphDatabase, 'driver') as mock_driver:
            mock_driver.side_effect = ServiceUnavailable("Connection failed")
            
            with pytest.raises(ServiceUnavailable):
                GraphDatabase(
                    uri="bolt://localhost:7687",
                    username="neo4j",
                    password="password"
                )

    def test_auth_failure(self):
        """Test handling of authentication failures."""
        with patch.object(Neo4jGraphDatabase, 'driver') as mock_driver:
            mock_driver.side_effect = AuthError("Authentication failed")
            
            with pytest.raises(AuthError):
                GraphDatabase(
                    uri="bolt://localhost:7687",
                    username="neo4j",
                    password="wrong_password"
                )

    def test_is_connected_true(self, mock_db):
        """Test is_connected when database is available."""
        mock_db.driver.verify_connectivity.return_value = None
        
        result = mock_db.is_connected()
        
        assert result is True
        mock_db.driver.verify_connectivity.assert_called_once()

    def test_is_connected_false(self, mock_db):
        """Test is_connected when database is not available."""
        mock_db.driver.verify_connectivity.side_effect = ServiceUnavailable("Not connected")
        
        result = mock_db.is_connected()
        
        assert result is False

    def test_execute_query_success(self, mock_db):
        """Test successful query execution."""
        # Mock session and result
        mock_session = Mock()
        mock_result = Mock()
        mock_result.data.return_value = [{"n.name": "test"}]
        
        mock_session.run.return_value = mock_result
        mock_db.driver.session.return_value.__enter__.return_value = mock_session
        
        result = mock_db.execute_query("MATCH (n) RETURN n.name")
        
        assert result == [{"n.name": "test"}]
        mock_session.run.assert_called_once_with("MATCH (n) RETURN n.name", {})

    def test_execute_query_with_parameters(self, mock_db):
        """Test query execution with parameters."""
        mock_session = Mock()
        mock_result = Mock()
        mock_result.data.return_value = []
        
        mock_session.run.return_value = mock_result
        mock_db.driver.session.return_value.__enter__.return_value = mock_session
        
        params = {"name": "John"}
        mock_db.execute_query("MATCH (n {name: $name}) RETURN n", params)
        
        mock_session.run.assert_called_once_with("MATCH (n {name: $name}) RETURN n", params)

    def test_execute_query_exception(self, mock_db):
        """Test query execution with exception."""
        mock_session = Mock()
        mock_session.run.side_effect = Exception("Query failed")
        mock_db.driver.session.return_value.__enter__.return_value = mock_session
        
        with pytest.raises(Exception, match="Query failed"):
            mock_db.execute_query("INVALID QUERY")

    def test_create_constraints(self, mock_db):
        """Test constraint creation."""
        mock_session = Mock()
        mock_result = Mock()
        mock_result.data.return_value = []
        
        mock_session.run.return_value = mock_result
        mock_db.driver.session.return_value.__enter__.return_value = mock_session
        
        mock_db.create_constraints()
        
        # Should call session.run multiple times for different constraints
        assert mock_session.run.call_count >= 5

    def test_get_statistics(self, mock_db):
        """Test getting database statistics."""
        mock_session = Mock()
        
        # Mock different query results
        def side_effect(query, params=None):
            mock_result = Mock()
            if "count(n)" in query:
                mock_result.data.return_value = [{"count(n)": 10}]
            elif "count(r)" in query:
                mock_result.data.return_value = [{"count(r)": 5}]
            elif "CALL db.labels()" in query:
                mock_result.data.return_value = [{"label": "Person"}, {"label": "Organization"}]
            elif "CALL db.relationshipTypes()" in query:
                mock_result.data.return_value = [{"relationshipType": "KNOWS"}, {"relationshipType": "WORKS_FOR"}]
            else:
                mock_result.data.return_value = []
            return mock_result
        
        mock_session.run.side_effect = side_effect
        mock_db.driver.session.return_value.__enter__.return_value = mock_session
        
        stats = mock_db.get_statistics()
        
        assert stats["node_count"] == 10
        assert stats["relationship_count"] == 5
        assert "Person" in stats["node_labels"]
        assert "KNOWS" in stats["relationship_types"]

    def test_health_check_healthy(self, mock_db):
        """Test health check when database is healthy."""
        mock_db.is_connected.return_value = True
        mock_db.get_statistics.return_value = {
            "node_count": 10,
            "relationship_count": 5,
            "node_labels": ["Person"],
            "relationship_types": ["KNOWS"]
        }
        
        health = mock_db.health_check()
        
        assert health["status"] == "healthy"
        assert health["connected"] is True
        assert health["statistics"]["node_count"] == 10

    def test_health_check_unhealthy(self, mock_db):
        """Test health check when database is unhealthy."""
        mock_db.is_connected.return_value = False
        
        health = mock_db.health_check()
        
        assert health["status"] == "unhealthy"
        assert health["connected"] is False

    def test_close_connection(self, mock_db):
        """Test closing database connection."""
        mock_db.close()
        
        mock_db.driver.close.assert_called_once()

    def test_context_manager(self):
        """Test using GraphDatabase as context manager."""
        with patch.object(Neo4jGraphDatabase, 'driver') as mock_driver:
            mock_driver_instance = Mock()
            mock_driver.return_value = mock_driver_instance
            
            with GraphDatabase("bolt://localhost:7687", "neo4j", "password") as db:
                assert db is not None
            
            mock_driver_instance.close.assert_called_once()
