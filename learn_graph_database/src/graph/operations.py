"""
Knowledge Graph Operations

This module provides high-level operations for managing nodes and relationships
in the knowledge graph, including CRUD operations and graph traversal.
"""

from typing import Dict, List, Optional, Any, Union, Tuple
from src.graph.database import GraphDatabase
from src.graph.models import (
    GraphNode, GraphRelationship, NodeType, RelationshipType,
    Person, Organization, Concept, Document, Location, Event, Skill, Project
)
import logging

logger = logging.getLogger(__name__)


class KnowledgeGraphManager:
    """
    High-level manager for knowledge graph operations.
    
    This class provides convenient methods for creating, reading, updating,
    and deleting nodes and relationships in the knowledge graph.
    """
    
    def __init__(self, database: GraphDatabase):
        """
        Initialize the knowledge graph manager.
        
        Args:
            database: Connected GraphDatabase instance
        """
        self.db = database
    
    # Node Operations
    def create_node(self, node: GraphNode) -> str:
        """
        Create a node in the graph database.
        
        Args:
            node: GraphNode instance to create
            
        Returns:
            The ID of the created node
        """
        node_data = node.to_dict()
        label = node.label
        
        # Remove None values and prepare properties
        properties = {k: v for k, v in node_data.items() if v is not None}
        
        # Create Cypher query
        query = f"""
        CREATE (n:{label} $properties)
        RETURN n.id as id
        """
        
        result = self.db.execute_write_query(query, {"properties": properties})
        
        if result:
            logger.info(f"Created {label} node with ID: {result[0]['id']}")
            return result[0]['id']
        else:
            raise RuntimeError(f"Failed to create {label} node")
    
    def get_node_by_id(self, node_id: str) -> Optional[Dict[str, Any]]:
        """
        Retrieve a node by its ID.
        
        Args:
            node_id: The ID of the node to retrieve
            
        Returns:
            Node data as dictionary or None if not found
        """
        query = """
        MATCH (n {id: $node_id})
        RETURN n, labels(n) as labels
        """
        
        result = self.db.execute_query(query, {"node_id": node_id})
        
        if result:
            node_data = dict(result[0]['n'])
            node_data['labels'] = result[0]['labels']
            return node_data
        return None
    
    def update_node(self, node_id: str, properties: Dict[str, Any]) -> bool:
        """
        Update a node's properties.
        
        Args:
            node_id: The ID of the node to update
            properties: Dictionary of properties to update
            
        Returns:
            True if successful, False otherwise
        """
        # Remove None values
        properties = {k: v for k, v in properties.items() if v is not None}
        
        query = """
        MATCH (n {id: $node_id})
        SET n += $properties
        RETURN count(n) as updated
        """
        
        result = self.db.execute_write_query(query, {
            "node_id": node_id,
            "properties": properties
        })
        
        success = result and result[0]['updated'] > 0
        if success:
            logger.info(f"Updated node {node_id}")
        return success
    
    def delete_node(self, node_id: str) -> bool:
        """
        Delete a node and all its relationships.
        
        Args:
            node_id: The ID of the node to delete
            
        Returns:
            True if successful, False otherwise
        """
        query = """
        MATCH (n {id: $node_id})
        DETACH DELETE n
        RETURN count(n) as deleted
        """
        
        result = self.db.execute_write_query(query, {"node_id": node_id})
        
        success = result and result[0]['deleted'] > 0
        if success:
            logger.info(f"Deleted node {node_id}")
        return success
    
    def find_nodes_by_label(self, label: str, limit: int = 100) -> List[Dict[str, Any]]:
        """
        Find all nodes with a specific label.
        
        Args:
            label: The node label to search for
            limit: Maximum number of nodes to return
            
        Returns:
            List of node data dictionaries
        """
        query = f"""
        MATCH (n:{label})
        RETURN n
        LIMIT $limit
        """
        
        result = self.db.execute_query(query, {"limit": limit})
        return [dict(record['n']) for record in result]
    
    def search_nodes_by_name(self, name: str, limit: int = 20) -> List[Dict[str, Any]]:
        """
        Search for nodes by name (case-insensitive partial match).
        
        Args:
            name: Name to search for
            limit: Maximum number of results
            
        Returns:
            List of matching nodes
        """
        query = """
        MATCH (n)
        WHERE toLower(n.name) CONTAINS toLower($name)
        RETURN n, labels(n) as labels
        LIMIT $limit
        """
        
        result = self.db.execute_query(query, {"name": name, "limit": limit})
        
        nodes = []
        for record in result:
            node_data = dict(record['n'])
            node_data['labels'] = record['labels']
            nodes.append(node_data)
        
        return nodes
    
    # Relationship Operations
    def create_relationship(self, relationship: GraphRelationship) -> bool:
        """
        Create a relationship between two nodes.
        
        Args:
            relationship: GraphRelationship instance
            
        Returns:
            True if successful, False otherwise
        """
        rel_data = relationship.to_dict()
        rel_type = relationship.relationship_type
        
        # Remove None values and prepare properties
        properties = {k: v for k, v in rel_data.items() 
                     if v is not None and k not in ['from_node_id', 'to_node_id', 'relationship_type']}
        
        query = f"""
        MATCH (a {{id: $from_id}}), (b {{id: $to_id}})
        CREATE (a)-[r:{rel_type} $properties]->(b)
        RETURN count(r) as created
        """
        
        result = self.db.execute_write_query(query, {
            "from_id": relationship.from_node_id,
            "to_id": relationship.to_node_id,
            "properties": properties
        })
        
        success = result and result[0]['created'] > 0
        if success:
            logger.info(f"Created {rel_type} relationship")
        return success
    
    def get_node_relationships(self, node_id: str, direction: str = "both") -> List[Dict[str, Any]]:
        """
        Get all relationships for a node.
        
        Args:
            node_id: The ID of the node
            direction: "incoming", "outgoing", or "both"
            
        Returns:
            List of relationship data
        """
        if direction == "outgoing":
            pattern = "(n)-[r]->(m)"
        elif direction == "incoming":
            pattern = "(m)-[r]->(n)"
        else:  # both
            pattern = "(n)-[r]-(m)"
        
        query = f"""
        MATCH {pattern}
        WHERE n.id = $node_id
        RETURN r, m, type(r) as rel_type
        """
        
        result = self.db.execute_query(query, {"node_id": node_id})
        
        relationships = []
        for record in result:
            rel_data = {
                "relationship": dict(record['r']),
                "related_node": dict(record['m']),
                "type": record['rel_type']
            }
            relationships.append(rel_data)
        
        return relationships
    
    def delete_relationship(self, from_node_id: str, to_node_id: str, 
                          relationship_type: Optional[str] = None) -> bool:
        """
        Delete relationship(s) between two nodes.
        
        Args:
            from_node_id: Source node ID
            to_node_id: Target node ID
            relationship_type: Specific relationship type to delete (optional)
            
        Returns:
            True if successful, False otherwise
        """
        if relationship_type:
            query = f"""
            MATCH (a {{id: $from_id}})-[r:{relationship_type}]->(b {{id: $to_id}})
            DELETE r
            RETURN count(r) as deleted
            """
        else:
            query = """
            MATCH (a {id: $from_id})-[r]-(b {id: $to_id})
            DELETE r
            RETURN count(r) as deleted
            """
        
        result = self.db.execute_write_query(query, {
            "from_id": from_node_id,
            "to_id": to_node_id
        })
        
        success = result and result[0]['deleted'] > 0
        if success:
            logger.info(f"Deleted relationship(s) between {from_node_id} and {to_node_id}")
        return success
    
    # Graph Traversal and Analysis
    def find_shortest_path(self, from_node_id: str, to_node_id: str, 
                          max_hops: int = 5) -> Optional[List[Dict[str, Any]]]:
        """
        Find the shortest path between two nodes.
        
        Args:
            from_node_id: Starting node ID
            to_node_id: Target node ID
            max_hops: Maximum number of hops to consider
            
        Returns:
            Path as list of nodes and relationships, or None if no path exists
        """
        query = f"""
        MATCH path = shortestPath((a {{id: $from_id}})-[*1..{max_hops}]-(b {{id: $to_id}}))
        RETURN nodes(path) as nodes, relationships(path) as relationships
        """
        
        result = self.db.execute_query(query, {
            "from_id": from_node_id,
            "to_id": to_node_id
        })
        
        if result:
            path_data = {
                "nodes": [dict(node) for node in result[0]['nodes']],
                "relationships": [dict(rel) for rel in result[0]['relationships']]
            }
            return path_data
        return None
    
    def get_node_neighbors(self, node_id: str, hops: int = 1, 
                          relationship_types: Optional[List[str]] = None) -> List[Dict[str, Any]]:
        """
        Get neighboring nodes within specified number of hops.
        
        Args:
            node_id: Center node ID
            hops: Number of hops to traverse
            relationship_types: Specific relationship types to follow
            
        Returns:
            List of neighboring nodes with distance information
        """
        rel_filter = ""
        if relationship_types:
            rel_types = "|".join(relationship_types)
            rel_filter = f":{rel_types}"
        
        query = f"""
        MATCH path = (center {{id: $node_id}})-[{rel_filter}*1..{hops}]-(neighbor)
        WHERE neighbor.id <> $node_id
        RETURN DISTINCT neighbor, length(path) as distance
        ORDER BY distance
        """
        
        result = self.db.execute_query(query, {"node_id": node_id})
        
        neighbors = []
        for record in result:
            neighbor_data = {
                "node": dict(record['neighbor']),
                "distance": record['distance']
            }
            neighbors.append(neighbor_data)
        
        return neighbors
    
    def get_graph_statistics(self) -> Dict[str, Any]:
        """Get comprehensive statistics about the knowledge graph."""
        stats = self.db.get_database_stats()
        
        # Add more detailed statistics
        additional_queries = {
            "most_connected_nodes": """
                MATCH (n)-[r]-()
                RETURN n.name as name, n.id as id, count(r) as connections
                ORDER BY connections DESC
                LIMIT 10
            """,
            "relationship_distribution": """
                MATCH ()-[r]->()
                RETURN type(r) as relationship_type, count(r) as count
                ORDER BY count DESC
            """,
            "node_label_distribution": """
                MATCH (n)
                RETURN labels(n)[0] as label, count(n) as count
                ORDER BY count DESC
            """
        }
        
        for key, query in additional_queries.items():
            try:
                result = self.db.execute_query(query)
                stats[key] = result
            except Exception as e:
                logger.error(f"Failed to get {key}: {e}")
                stats[key] = []
        
        return stats


# Example usage and demonstrations
if __name__ == "__main__":
    from src.graph.database import GraphConfig
    
    print("Knowledge Graph Operations Demo")
    print("=" * 35)
    
    # Initialize database connection
    config = GraphConfig()
    
    try:
        with GraphDatabase(config) as db:
            # Create knowledge graph manager
            kg_manager = KnowledgeGraphManager(db)
            
            # Create sample nodes
            alice = Person(
                first_name="Alice",
                last_name="Johnson",
                email="alice@techcorp.com",
                occupation="Data Scientist"
            )
            
            techcorp = Organization(
                name="TechCorp",
                organization_type="company",
                industry="Technology"
            )
            
            ml_concept = Concept(
                name="Machine Learning",
                description="Branch of AI focused on learning from data",
                category="Computer Science"
            )
            
            # Create nodes in database
            alice_id = kg_manager.create_node(alice)
            techcorp_id = kg_manager.create_node(techcorp)
            ml_id = kg_manager.create_node(ml_concept)
            
            # Create relationships
            works_for = GraphRelationship(
                from_node_id=alice_id,
                to_node_id=techcorp_id,
                relationship_type=RelationshipType.WORKS_FOR,
                properties={"position": "Senior Data Scientist"}
            )
            
            knows_concept = GraphRelationship(
                from_node_id=alice_id,
                to_node_id=ml_id,
                relationship_type=RelationshipType.RELATED_TO,
                properties={"expertise_level": "expert"}
            )
            
            kg_manager.create_relationship(works_for)
            kg_manager.create_relationship(knows_concept)
            
            print("✓ Created sample knowledge graph")
            
            # Demonstrate operations
            print("\nGraph Statistics:")
            stats = kg_manager.get_graph_statistics()
            print(f"Nodes: {stats['node_count']}")
            print(f"Relationships: {stats['relationship_count']}")
            
            # Search functionality
            print(f"\nSearching for 'Alice':")
            search_results = kg_manager.search_nodes_by_name("Alice")
            for node in search_results:
                print(f"Found: {node.get('name', 'Unknown')} ({node.get('labels', [])})")
            
            # Get relationships
            print(f"\nAlice's relationships:")
            alice_rels = kg_manager.get_node_relationships(alice_id)
            for rel in alice_rels:
                related_name = rel['related_node'].get('name', 'Unknown')
                rel_type = rel['type']
                print(f"Alice {rel_type} {related_name}")
            
    except Exception as e:
        print(f"Demo failed: {e}")
        print("Make sure Neo4j is running and accessible.")
