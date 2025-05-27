"""
Knowledge Graph Database Connection and Management

This module provides the core database connection and management functionality
for the knowledge graph application.
"""

from typing import Dict, List, Optional, Any, Tuple
import os
from dataclasses import dataclass
from neo4j import GraphDatabase, Driver, Transaction
from dotenv import load_dotenv
import logging

# Load environment variables
load_dotenv()

# Configure logging
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)


@dataclass
class GraphConfig:
    """Configuration for graph database connection."""
    uri: str = "bolt://localhost:7687"
    username: str = "neo4j"
    password: str = "password"
    database: str = "neo4j"
    
    @classmethod
    def from_env(cls) -> 'GraphConfig':
        """Create configuration from environment variables."""
        return cls(
            uri=os.getenv("NEO4J_URI", "bolt://localhost:7687"),
            username=os.getenv("NEO4J_USERNAME", "neo4j"),
            password=os.getenv("NEO4J_PASSWORD", "password"),
            database=os.getenv("NEO4J_DATABASE", "neo4j")
        )


class GraphDatabase:
    """
    Knowledge Graph Database Manager
    
    This class handles all database operations for the knowledge graph,
    including connection management, node/relationship creation, and querying.
    """
    
    def __init__(self, config: Optional[GraphConfig] = None):
        """
        Initialize the graph database connection.
        
        Args:
            config: Database configuration. If None, loads from environment.
        """
        self.config = config or GraphConfig.from_env()
        self._driver: Optional[Driver] = None
        
    def connect(self) -> None:
        """Establish connection to the Neo4j database."""
        try:
            self._driver = GraphDatabase.driver(
                self.config.uri,
                auth=(self.config.username, self.config.password)
            )
            # Test connection
            self._driver.verify_connectivity()
            logger.info(f"Connected to Neo4j at {self.config.uri}")
        except Exception as e:
            logger.error(f"Failed to connect to Neo4j: {e}")
            raise
    
    def close(self) -> None:
        """Close the database connection."""
        if self._driver:
            self._driver.close()
            logger.info("Database connection closed")
    
    def __enter__(self):
        """Context manager entry."""
        self.connect()
        return self
    
    def __exit__(self, exc_type, exc_val, exc_tb):
        """Context manager exit."""
        self.close()
    
    @property
    def driver(self) -> Driver:
        """Get the Neo4j driver instance."""
        if not self._driver:
            raise RuntimeError("Database not connected. Call connect() first.")
        return self._driver
    
    def execute_query(self, query: str, parameters: Optional[Dict[str, Any]] = None) -> List[Dict[str, Any]]:
        """
        Execute a Cypher query and return results.
        
        Args:
            query: Cypher query string
            parameters: Query parameters
            
        Returns:
            List of result records as dictionaries
        """
        with self.driver.session(database=self.config.database) as session:
            result = session.run(query, parameters or {})
            return [record.data() for record in result]
    
    def execute_write_query(self, query: str, parameters: Optional[Dict[str, Any]] = None) -> List[Dict[str, Any]]:
        """
        Execute a write query in a transaction.
        
        Args:
            query: Cypher query string
            parameters: Query parameters
            
        Returns:
            List of result records as dictionaries
        """
        def _write_tx(tx: Transaction) -> List[Dict[str, Any]]:
            result = tx.run(query, parameters or {})
            return [record.data() for record in result]
        
        with self.driver.session(database=self.config.database) as session:
            return session.execute_write(_write_tx)
    
    def create_constraints(self) -> None:
        """Create database constraints and indexes for better performance."""
        constraints = [
            "CREATE CONSTRAINT person_id IF NOT EXISTS FOR (p:Person) REQUIRE p.id IS UNIQUE",
            "CREATE CONSTRAINT organization_id IF NOT EXISTS FOR (o:Organization) REQUIRE o.id IS UNIQUE",
            "CREATE CONSTRAINT concept_id IF NOT EXISTS FOR (c:Concept) REQUIRE c.id IS UNIQUE",
            "CREATE CONSTRAINT document_id IF NOT EXISTS FOR (d:Document) REQUIRE d.id IS UNIQUE",
            "CREATE INDEX person_name IF NOT EXISTS FOR (p:Person) ON (p.name)",
            "CREATE INDEX organization_name IF NOT EXISTS FOR (o:Organization) ON (o.name)",
            "CREATE INDEX concept_name IF NOT EXISTS FOR (c:Concept) ON (c.name)"
        ]
        
        for constraint in constraints:
            try:
                self.execute_write_query(constraint)
                logger.info(f"Created constraint/index: {constraint}")
            except Exception as e:
                logger.warning(f"Constraint/index already exists or failed: {e}")
    
    def clear_database(self) -> None:
        """Clear all nodes and relationships from the database. Use with caution!"""
        query = "MATCH (n) DETACH DELETE n"
        self.execute_write_query(query)
        logger.info("Database cleared")
    
    def get_database_stats(self) -> Dict[str, Any]:
        """Get basic statistics about the database."""
        queries = {
            "node_count": "MATCH (n) RETURN count(n) as count",
            "relationship_count": "MATCH ()-[r]->() RETURN count(r) as count",
            "node_labels": "CALL db.labels() YIELD label RETURN collect(label) as labels",
            "relationship_types": "CALL db.relationshipTypes() YIELD relationshipType RETURN collect(relationshipType) as types"
        }
        
        stats = {}
        for key, query in queries.items():
            try:
                result = self.execute_query(query)
                if key in ["node_labels", "relationship_types"]:
                    stats[key] = result[0][key.split("_")[0] + "s"]
                else:
                    stats[key] = result[0]["count"]
            except Exception as e:
                logger.error(f"Failed to get {key}: {e}")
                stats[key] = 0
        
        return stats
    
    def health_check(self) -> bool:
        """Check if the database is healthy and responsive."""
        try:
            result = self.execute_query("RETURN 1 as health")
            return len(result) == 1 and result[0]["health"] == 1
        except Exception as e:
            logger.error(f"Health check failed: {e}")
            return False


# Example usage and testing
if __name__ == "__main__":
    # This section demonstrates basic usage
    print("Knowledge Graph Database Manager")
    print("=" * 40)
    
    # Create configuration (you can modify these values)
    config = GraphConfig(
        uri="bolt://localhost:7687",
        username="neo4j",
        password="password"
    )
    
    try:
        # Test database connection
        with GraphDatabase(config) as db:
            if db.health_check():
                print("✓ Database connection successful")
                
                # Create constraints and indexes
                db.create_constraints()
                print("✓ Constraints and indexes created")
                
                # Get database stats
                stats = db.get_database_stats()
                print(f"✓ Database stats: {stats}")
                
            else:
                print("✗ Database health check failed")
                
    except Exception as e:
        print(f"✗ Database connection failed: {e}")
        print("\nTo set up Neo4j:")
        print("1. Install Neo4j Desktop or Docker")
        print("2. Start a database instance")
        print("3. Update the connection settings above")
        print("4. Or set environment variables:")
        print("   NEO4J_URI=bolt://localhost:7687")
        print("   NEO4J_USERNAME=neo4j")
        print("   NEO4J_PASSWORD=your_password")
