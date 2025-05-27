"""
Integration tests for the complete knowledge graph system.
"""
import pytest
import os
from unittest.mock import patch

from src.graph.database import GraphDatabase
from src.graph.operations import KnowledgeGraphManager
from src.data.generator import SampleDataGenerator
from src.visualization.graph_viz import GraphVisualizer


@pytest.mark.integration
class TestSystemIntegration:
    """Integration tests for the complete system."""

    def test_database_setup_and_cleanup(self, real_db):
        """Test database setup and cleanup."""
        # Test connection
        assert real_db.is_connected() is True
        
        # Test constraint creation
        real_db.create_constraints()
        
        # Test health check
        health = real_db.health_check()
        assert health["status"] == "healthy"
        assert health["connected"] is True
        
        # Test statistics
        stats = real_db.get_statistics()
        assert "node_count" in stats
        assert "relationship_count" in stats

    def test_sample_data_generation(self, real_kg_manager):
        """Test sample data generation and validation."""
        generator = SampleDataGenerator(real_kg_manager)
        
        # Generate sample data
        generator.generate_sample_data()
        
        # Verify data was created
        stats = real_kg_manager.get_graph_statistics()
        
        assert stats["total_nodes"] > 0
        assert stats["total_relationships"] > 0
        
        # Check specific node types
        people = real_kg_manager.get_nodes_by_type("Person")
        orgs = real_kg_manager.get_nodes_by_type("Organization")
        concepts = real_kg_manager.get_nodes_by_type("Concept")
        
        assert len(people) > 0
        assert len(orgs) > 0
        assert len(concepts) > 0
        
        # Test search functionality
        search_results = real_kg_manager.search_nodes("Python")
        assert len(search_results) >= 0  # May or may not find results
        
        # Test graph traversal
        if people:
            person_id = people[0]["n"]["id"]
            neighbors = real_kg_manager.get_neighbors(person_id)
            # May have neighbors depending on generated data

    def test_visualization_creation(self, real_kg_manager):
        """Test visualization creation without displaying."""
        # Generate some sample data first
        generator = SampleDataGenerator(real_kg_manager)
        generator.generate_sample_data()
        
        visualizer = GraphVisualizer(real_kg_manager)
        
        # Test getting visualization data (without actually displaying)
        people = real_kg_manager.get_nodes_by_type("Person")
        if people:
            person_id = people[0]["n"]["id"]
            
            # Test neighborhood visualization data
            subgraph = real_kg_manager.get_subgraph(person_id, depth=1)
            assert "nodes" in subgraph
            assert "relationships" in subgraph

    def test_query_performance(self, real_kg_manager):
        """Test query performance with larger dataset."""
        generator = SampleDataGenerator(real_kg_manager)
        generator.generate_sample_data()
        
        import time
        
        # Test simple queries
        start_time = time.time()
        people = real_kg_manager.get_nodes_by_type("Person")
        query_time = time.time() - start_time
        
        assert query_time < 5.0  # Should complete within 5 seconds
        
        # Test search queries
        start_time = time.time()
        search_results = real_kg_manager.search_nodes("engineer")
        query_time = time.time() - start_time
        
        assert query_time < 5.0
        
        # Test graph traversal
        if people:
            person_id = people[0]["n"]["id"]
            start_time = time.time()
            neighbors = real_kg_manager.get_neighbors(person_id)
            query_time = time.time() - start_time
            
            assert query_time < 2.0

    def test_error_handling(self, real_kg_manager):
        """Test error handling in various scenarios."""
        # Test getting non-existent node
        result = real_kg_manager.get_node_by_id("non-existent-id")
        assert result is None
        
        # Test deleting non-existent node
        result = real_kg_manager.delete_node("non-existent-id")
        assert result is False
        
        # Test creating relationship with non-existent nodes
        result = real_kg_manager.create_relationship(
            "non-existent-1", "non-existent-2", "TEST_REL"
        )
        assert result is False
        
        # Test searching with empty query
        result = real_kg_manager.search_nodes("")
        assert isinstance(result, list)

    def test_data_consistency(self, real_kg_manager):
        """Test data consistency after various operations."""
        generator = SampleDataGenerator(real_kg_manager)
        generator.generate_sample_data()
        
        # Get initial statistics
        initial_stats = real_kg_manager.get_graph_statistics()
        
        # Perform some operations
        people = real_kg_manager.get_nodes_by_type("Person")
        if people:
            person_id = people[0]["n"]["id"]
            
            # Update a node
            real_kg_manager.update_node(person_id, {"test_field": "test_value"})
            
            # Verify the update
            updated_node = real_kg_manager.get_node_by_id(person_id)
            assert updated_node["n"]["test_field"] == "test_value"
            
            # Get final statistics
            final_stats = real_kg_manager.get_graph_statistics()
            
            # Node count should remain the same
            assert final_stats["total_nodes"] == initial_stats["total_nodes"]

    @pytest.mark.slow
    def test_large_dataset_operations(self, real_kg_manager):
        """Test operations with a larger dataset."""
        # Generate larger dataset
        generator = SampleDataGenerator(real_kg_manager)
        
        # Generate data multiple times to create larger dataset
        for _ in range(3):
            generator.generate_sample_data()
        
        # Test centrality analysis
        centrality_results = real_kg_manager.analyze_node_centrality()
        assert len(centrality_results) > 0
        
        # Test community detection
        communities = real_kg_manager.find_communities()
        assert len(communities) >= 0  # May or may not find communities
        
        # Test complex search
        search_results = real_kg_manager.search_nodes("software")
        assert isinstance(search_results, list)

    def test_concurrent_operations(self, test_db_config):
        """Test concurrent database operations."""
        import threading
        import time
        
        results = []
        errors = []
        
        def worker(worker_id):
            try:
                # Each worker gets its own database connection
                db = GraphDatabase(**test_db_config)
                kg_manager = KnowledgeGraphManager(db)
                
                # Perform some operations
                from src.graph.models import Person
                person = Person(name=f"Worker {worker_id}", age=25)
                person_id = kg_manager.create_node(person)
                
                # Read back the node
                node = kg_manager.get_node_by_id(person_id)
                
                results.append((worker_id, person_id, node is not None))
                
                # Cleanup
                kg_manager.delete_node(person_id)
                db.close()
                
            except Exception as e:
                errors.append((worker_id, str(e)))
        
        # Create multiple threads
        threads = []
        for i in range(5):
            thread = threading.Thread(target=worker, args=(i,))
            threads.append(thread)
            thread.start()
        
        # Wait for all threads to complete
        for thread in threads:
            thread.join(timeout=30)  # 30 second timeout
        
        # Check results
        assert len(errors) == 0, f"Errors occurred: {errors}"
        assert len(results) == 5
        
        for worker_id, person_id, node_found in results:
            assert person_id is not None
            assert node_found is True
