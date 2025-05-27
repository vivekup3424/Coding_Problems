"""
Unit tests for knowledge graph operations.
"""
import pytest
from unittest.mock import Mock, patch, call
from datetime import datetime

from src.graph.operations import KnowledgeGraphManager
from src.graph.models import Person, Organization, Concept, Skill


@pytest.mark.unit
class TestKnowledgeGraphManager:
    """Test cases for KnowledgeGraphManager class."""

    def test_init(self, mock_db):
        """Test KnowledgeGraphManager initialization."""
        manager = KnowledgeGraphManager(mock_db)
        
        assert manager.db == mock_db

    def test_create_node_person(self, kg_manager, sample_person):
        """Test creating a person node."""
        kg_manager.db.execute_query.return_value = [{"id": "12345"}]
        
        result = kg_manager.create_node(sample_person)
        
        assert result == "12345"
        kg_manager.db.execute_query.assert_called_once()
        
        # Check the query contains the right data
        call_args = kg_manager.db.execute_query.call_args
        query, params = call_args[0], call_args[1] if len(call_args) > 1 else {}
        
        assert "CREATE" in query
        assert "Person" in query
        assert "RETURN" in query

    def test_create_node_organization(self, kg_manager, sample_organization):
        """Test creating an organization node."""
        kg_manager.db.execute_query.return_value = [{"id": "org123"}]
        
        result = kg_manager.create_node(sample_organization)
        
        assert result == "org123"
        kg_manager.db.execute_query.assert_called_once()

    def test_get_node_by_id(self, kg_manager):
        """Test getting a node by ID."""
        mock_result = [{
            "n": {
                "id": "12345",
                "name": "John Doe",
                "age": 30,
                "email": "john.doe@example.com"
            },
            "labels": ["Person"]
        }]
        kg_manager.db.execute_query.return_value = mock_result
        
        result = kg_manager.get_node_by_id("12345")
        
        assert result is not None
        assert result["n"]["name"] == "John Doe"
        kg_manager.db.execute_query.assert_called_once()

    def test_get_node_by_id_not_found(self, kg_manager):
        """Test getting a node that doesn't exist."""
        kg_manager.db.execute_query.return_value = []
        
        result = kg_manager.get_node_by_id("nonexistent")
        
        assert result is None

    def test_update_node(self, kg_manager):
        """Test updating a node."""
        kg_manager.db.execute_query.return_value = [{"updated": True}]
        
        updates = {"age": 31, "location": "San Francisco"}
        result = kg_manager.update_node("12345", updates)
        
        assert result is True
        kg_manager.db.execute_query.assert_called_once()

    def test_delete_node(self, kg_manager):
        """Test deleting a node."""
        kg_manager.db.execute_query.return_value = [{"deleted": 1}]
        
        result = kg_manager.delete_node("12345")
        
        assert result is True
        kg_manager.db.execute_query.assert_called_once()

    def test_delete_node_not_found(self, kg_manager):
        """Test deleting a node that doesn't exist."""
        kg_manager.db.execute_query.return_value = []
        
        result = kg_manager.delete_node("nonexistent")
        
        assert result is False

    def test_create_relationship(self, kg_manager):
        """Test creating a relationship between nodes."""
        kg_manager.db.execute_query.return_value = [{"relationship_created": True}]
        
        result = kg_manager.create_relationship(
            "person123", 
            "org456", 
            "WORKS_FOR",
            {"role": "Software Engineer", "since": "2023"}
        )
        
        assert result is True
        kg_manager.db.execute_query.assert_called_once()
        
        # Check query parameters
        call_args = kg_manager.db.execute_query.call_args
        query, params = call_args[0], call_args[1] if len(call_args) > 1 else {}
        
        assert "WORKS_FOR" in query or "WORKS_FOR" in str(params)

    def test_get_relationships(self, kg_manager):
        """Test getting relationships for a node."""
        mock_result = [
            {
                "r": {"type": "WORKS_FOR", "role": "Engineer"},
                "other": {"id": "org123", "name": "Tech Corp"}
            }
        ]
        kg_manager.db.execute_query.return_value = mock_result
        
        result = kg_manager.get_relationships("person123")
        
        assert len(result) == 1
        assert result[0]["r"]["type"] == "WORKS_FOR"
        kg_manager.db.execute_query.assert_called_once()

    def test_delete_relationship(self, kg_manager):
        """Test deleting a relationship."""
        kg_manager.db.execute_query.return_value = [{"deleted": 1}]
        
        result = kg_manager.delete_relationship("person123", "org456", "WORKS_FOR")
        
        assert result is True
        kg_manager.db.execute_query.assert_called_once()

    def test_search_nodes(self, kg_manager):
        """Test searching nodes by text."""
        mock_result = [
            {"n": {"id": "1", "name": "Machine Learning"}, "labels": ["Concept"]},
            {"n": {"id": "2", "name": "ML Engineer"}, "labels": ["Person"]}
        ]
        kg_manager.db.execute_query.return_value = mock_result
        
        result = kg_manager.search_nodes("machine learning")
        
        assert len(result) == 2
        assert result[0]["n"]["name"] == "Machine Learning"
        kg_manager.db.execute_query.assert_called_once()

    def test_get_nodes_by_type(self, kg_manager):
        """Test getting nodes by type/label."""
        mock_result = [
            {"n": {"id": "1", "name": "John Doe"}},
            {"n": {"id": "2", "name": "Jane Smith"}}
        ]
        kg_manager.db.execute_query.return_value = mock_result
        
        result = kg_manager.get_nodes_by_type("Person")
        
        assert len(result) == 2
        kg_manager.db.execute_query.assert_called_once()

    def test_get_neighbors(self, kg_manager):
        """Test getting neighboring nodes."""
        mock_result = [
            {
                "neighbor": {"id": "org1", "name": "Tech Corp"},
                "relationship": {"type": "WORKS_FOR"},
                "labels": ["Organization"]
            }
        ]
        kg_manager.db.execute_query.return_value = mock_result
        
        result = kg_manager.get_neighbors("person123")
        
        assert len(result) == 1
        assert result[0]["neighbor"]["name"] == "Tech Corp"
        kg_manager.db.execute_query.assert_called_once()

    def test_find_shortest_path(self, kg_manager):
        """Test finding shortest path between nodes."""
        mock_result = [
            {
                "path": {
                    "nodes": [
                        {"id": "person1", "name": "John"},
                        {"id": "org1", "name": "Tech Corp"},
                        {"id": "person2", "name": "Jane"}
                    ],
                    "relationships": [
                        {"type": "WORKS_FOR"},
                        {"type": "EMPLOYS"}
                    ]
                },
                "length": 2
            }
        ]
        kg_manager.db.execute_query.return_value = mock_result
        
        result = kg_manager.find_shortest_path("person1", "person2")
        
        assert result is not None
        assert result["length"] == 2
        kg_manager.db.execute_query.assert_called_once()

    def test_find_shortest_path_not_found(self, kg_manager):
        """Test finding shortest path when no path exists."""
        kg_manager.db.execute_query.return_value = []
        
        result = kg_manager.find_shortest_path("person1", "person2")
        
        assert result is None

    def test_get_graph_statistics(self, kg_manager):
        """Test getting graph statistics."""
        kg_manager.db.get_statistics.return_value = {
            "node_count": 100,
            "relationship_count": 150,
            "node_labels": ["Person", "Organization"],
            "relationship_types": ["WORKS_FOR", "KNOWS"]
        }
        
        # Mock additional queries for detailed stats
        def mock_execute_query(query, params=None):
            if "Person" in query and "count" in query:
                return [{"count": 50}]
            elif "Organization" in query and "count" in query:
                return [{"count": 25}]
            elif "WORKS_FOR" in query and "count" in query:
                return [{"count": 75}]
            elif "KNOWS" in query and "count" in query:
                return [{"count": 30}]
            else:
                return []
        
        kg_manager.db.execute_query.side_effect = mock_execute_query
        
        result = kg_manager.get_graph_statistics()
        
        assert result["total_nodes"] == 100
        assert result["total_relationships"] == 150
        assert "node_counts" in result
        assert "relationship_counts" in result

    def test_analyze_node_centrality(self, kg_manager):
        """Test analyzing node centrality."""
        mock_result = [
            {"node": {"id": "1", "name": "John"}, "degree": 5},
            {"node": {"id": "2", "name": "Jane"}, "degree": 3}
        ]
        kg_manager.db.execute_query.return_value = mock_result
        
        result = kg_manager.analyze_node_centrality()
        
        assert len(result) == 2
        assert result[0]["degree"] == 5
        kg_manager.db.execute_query.assert_called_once()

    def test_get_subgraph(self, kg_manager):
        """Test getting a subgraph around a node."""
        mock_result = [
            {
                "nodes": [
                    {"id": "1", "name": "John", "labels": ["Person"]},
                    {"id": "2", "name": "Tech Corp", "labels": ["Organization"]}
                ],
                "relationships": [
                    {"type": "WORKS_FOR", "start": "1", "end": "2"}
                ]
            }
        ]
        kg_manager.db.execute_query.return_value = mock_result
        
        result = kg_manager.get_subgraph("1", depth=2)
        
        assert "nodes" in result
        assert "relationships" in result
        assert len(result["nodes"]) == 2
        kg_manager.db.execute_query.assert_called_once()

    def test_find_communities(self, kg_manager):
        """Test finding communities in the graph."""
        mock_result = [
            {"community": 1, "members": ["person1", "person2", "org1"]},
            {"community": 2, "members": ["person3", "person4", "org2"]}
        ]
        kg_manager.db.execute_query.return_value = mock_result
        
        result = kg_manager.find_communities()
        
        assert len(result) == 2
        assert result[0]["community"] == 1
        kg_manager.db.execute_query.assert_called_once()


@pytest.mark.integration
class TestKnowledgeGraphManagerIntegration:
    """Integration tests that require a real Neo4j database."""

    def test_full_workflow(self, real_kg_manager, sample_person, sample_organization):
        """Test a complete workflow with real database."""
        # Create nodes
        person_id = real_kg_manager.create_node(sample_person)
        org_id = real_kg_manager.create_node(sample_organization)
        
        assert person_id is not None
        assert org_id is not None
        
        # Create relationship
        rel_created = real_kg_manager.create_relationship(
            person_id, org_id, "WORKS_FOR", {"role": "Engineer"}
        )
        assert rel_created is True
        
        # Get node by ID
        person_node = real_kg_manager.get_node_by_id(person_id)
        assert person_node is not None
        assert person_node["n"]["name"] == sample_person.name
        
        # Get relationships
        relationships = real_kg_manager.get_relationships(person_id)
        assert len(relationships) >= 1
        
        # Search nodes
        search_results = real_kg_manager.search_nodes(sample_person.name)
        assert len(search_results) >= 1
        
        # Update node
        update_result = real_kg_manager.update_node(person_id, {"age": 31})
        assert update_result is True
        
        # Verify update
        updated_node = real_kg_manager.get_node_by_id(person_id)
        assert updated_node["n"]["age"] == 31
        
        # Get neighbors
        neighbors = real_kg_manager.get_neighbors(person_id)
        assert len(neighbors) >= 1
        
        # Delete relationship
        rel_deleted = real_kg_manager.delete_relationship(person_id, org_id, "WORKS_FOR")
        assert rel_deleted is True
        
        # Delete nodes
        person_deleted = real_kg_manager.delete_node(person_id)
        org_deleted = real_kg_manager.delete_node(org_id)
        
        assert person_deleted is True
        assert org_deleted is True
