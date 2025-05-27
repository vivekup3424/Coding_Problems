"""
Configuration and fixtures for pytest tests.
"""
import pytest
import os
from typing import Generator
from unittest.mock import Mock, patch

from src.graph.database import GraphDatabase
from src.graph.operations import KnowledgeGraphManager
from src.graph.models import Person, Organization, Concept, Skill


@pytest.fixture(scope="session")
def test_db_config():
    """Test database configuration."""
    return {
        "uri": os.getenv("NEO4J_TEST_URI", "bolt://localhost:7687"),
        "username": os.getenv("NEO4J_TEST_USERNAME", "neo4j"),
        "password": os.getenv("NEO4J_TEST_PASSWORD", "test_password"),
        "database": "neo4j"
    }


@pytest.fixture(scope="session")
def mock_db() -> Generator[Mock, None, None]:
    """Mock database for unit tests that don't require real Neo4j."""
    with patch('src.graph.database.GraphDatabase') as mock:
        mock_instance = Mock()
        mock_instance.is_connected.return_value = True
        mock_instance.execute_query.return_value = []
        mock_instance.get_statistics.return_value = {
            "node_count": 0,
            "relationship_count": 0,
            "node_labels": [],
            "relationship_types": []
        }
        mock.return_value = mock_instance
        yield mock_instance


@pytest.fixture(scope="function")
def real_db(test_db_config) -> Generator[GraphDatabase, None, None]:
    """Real database connection for integration tests."""
    db = None
    try:
        db = GraphDatabase(**test_db_config)
        
        # Clear test data before each test
        db.execute_query("MATCH (n) DETACH DELETE n")
        
        yield db
    except Exception as e:
        pytest.skip(f"Neo4j not available for integration tests: {e}")
    finally:
        if db:
            # Clean up after test
            try:
                db.execute_query("MATCH (n) DETACH DELETE n")
                db.close()
            except:
                pass


@pytest.fixture(scope="function")
def kg_manager(mock_db) -> KnowledgeGraphManager:
    """Knowledge graph manager with mocked database."""
    return KnowledgeGraphManager(mock_db)


@pytest.fixture(scope="function")
def real_kg_manager(real_db) -> KnowledgeGraphManager:
    """Knowledge graph manager with real database for integration tests."""
    return KnowledgeGraphManager(real_db)


@pytest.fixture
def sample_person():
    """Sample person node for testing."""
    return Person(
        name="John Doe",
        age=30,
        email="john.doe@example.com",
        location="New York",
        bio="Software engineer with expertise in Python and machine learning."
    )


@pytest.fixture
def sample_organization():
    """Sample organization node for testing."""
    return Organization(
        name="Tech Corp",
        industry="Technology",
        size="Large",
        location="San Francisco",
        website="https://techcorp.com",
        description="Leading technology company focused on AI and machine learning."
    )


@pytest.fixture
def sample_concept():
    """Sample concept node for testing."""
    return Concept(
        name="Machine Learning",
        category="Technology",
        description="A subset of artificial intelligence focused on algorithms that learn from data."
    )


@pytest.fixture
def sample_skill():
    """Sample skill node for testing."""
    return Skill(
        name="Python Programming",
        category="Programming Language",
        level="Advanced",
        description="High-level programming language known for its simplicity and versatility."
    )


# Test markers
pytest_plugins = []

def pytest_configure(config):
    """Configure pytest markers."""
    config.addinivalue_line(
        "markers", "unit: Unit tests that don't require external dependencies"
    )
    config.addinivalue_line(
        "markers", "integration: Integration tests that require Neo4j database"
    )
    config.addinivalue_line(
        "markers", "slow: Slow tests that take more than a few seconds"
    )
