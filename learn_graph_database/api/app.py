"""
Knowledge Graph API

This module provides a REST API for interacting with the knowledge graph
using Flask. It includes endpoints for nodes, relationships, and visualizations.
"""

from typing import Dict, List, Any, Optional
from flask import Flask, request, jsonify, render_template_string
from flask.wrappers import Response
import json
import sys
from pathlib import Path

# Add src to path for imports
sys.path.append(str(Path(__file__).parent.parent / "src"))

from src.graph.database import GraphDatabase, GraphConfig
from src.graph.operations import KnowledgeGraphManager
from src.graph.models import (
    Person, Organization, Concept, Document, Location, Event, Skill, Project,
    GraphRelationship, RelationshipType, create_node, NodeType
)
from src.data.generator import SampleDataGenerator
from src.visualization.graph_viz import GraphVisualizer


app = Flask(__name__)
app.config['JSON_SORT_KEYS'] = False

# Global database connection
_db_instance = None
_kg_manager = None


def get_db_connection():
    """Get or create database connection."""
    global _db_instance, _kg_manager
    
    if _db_instance is None:
        config = GraphConfig.from_env()
        _db_instance = GraphDatabase(config)
        _db_instance.connect()
        _kg_manager = KnowledgeGraphManager(_db_instance)
    
    return _db_instance, _kg_manager


def handle_error(error: Exception) -> Response:
    """Handle API errors consistently."""
    return jsonify({
        "success": False,
        "error": str(error),
        "message": "An error occurred while processing your request"
    }), 500


# API Routes
@app.route('/')
def index():
    """API documentation."""
    html = """
    <!DOCTYPE html>
    <html>
    <head>
        <title>Knowledge Graph API</title>
        <style>
            body { font-family: Arial, sans-serif; margin: 40px; }
            .endpoint { margin: 20px 0; padding: 15px; border: 1px solid #ddd; border-radius: 5px; }
            .method { color: white; padding: 2px 8px; border-radius: 3px; font-weight: bold; }
            .get { background-color: #61affe; }
            .post { background-color: #49cc90; }
            .put { background-color: #fca130; }
            .delete { background-color: #f93e3e; }
            code { background-color: #f5f5f5; padding: 2px 4px; border-radius: 3px; }
        </style>
    </head>
    <body>
        <h1>Knowledge Graph API</h1>
        <p>RESTful API for interacting with the knowledge graph database.</p>
        
        <h2>Available Endpoints</h2>
        
        <div class="endpoint">
            <h3><span class="method get">GET</span> /api/health</h3>
            <p>Check API and database health status</p>
        </div>
        
        <div class="endpoint">
            <h3><span class="method get">GET</span> /api/stats</h3>
            <p>Get comprehensive graph statistics</p>
        </div>
        
        <div class="endpoint">
            <h3><span class="method get">GET</span> /api/nodes</h3>
            <p>Get all nodes with optional filtering</p>
            <p>Parameters: <code>label</code>, <code>limit</code></p>
        </div>
        
        <div class="endpoint">
            <h3><span class="method get">GET</span> /api/nodes/{node_id}</h3>
            <p>Get specific node by ID</p>
        </div>
        
        <div class="endpoint">
            <h3><span class="method get">GET</span> /api/nodes/{node_id}/relationships</h3>
            <p>Get relationships for a specific node</p>
            <p>Parameters: <code>direction</code> (incoming/outgoing/both)</p>
        </div>
        
        <div class="endpoint">
            <h3><span class="method get">GET</span> /api/search</h3>
            <p>Search nodes by name</p>
            <p>Parameters: <code>q</code> (required), <code>limit</code></p>
        </div>
        
        <div class="endpoint">
            <h3><span class="method post">POST</span> /api/nodes</h3>
            <p>Create a new node</p>
            <p>Body: Node data with <code>type</code> field</p>
        </div>
        
        <div class="endpoint">
            <h3><span class="method post">POST</span> /api/relationships</h3>
            <p>Create a new relationship</p>
            <p>Body: Relationship data</p>
        </div>
        
        <div class="endpoint">
            <h3><span class="method get">GET</span> /api/visualize/network</h3>
            <p>Get network visualization data</p>
            <p>Parameters: <code>limit</code></p>
        </div>
        
        <div class="endpoint">
            <h3><span class="method post">POST</span> /api/generate-sample-data</h3>
            <p>Generate sample data for learning</p>
            <p>Body: Generation parameters (optional)</p>
        </div>
        
        <h2>Example Usage</h2>
        <pre>
# Get all people
curl http://localhost:5000/api/nodes?label=Person

# Search for nodes
curl http://localhost:5000/api/search?q=Alice

# Get node details
curl http://localhost:5000/api/nodes/{node-id}

# Create a person
curl -X POST http://localhost:5000/api/nodes \\
  -H "Content-Type: application/json" \\
  -d '{"type": "Person", "first_name": "John", "last_name": "Doe", "email": "john@example.com"}'
        </pre>
    </body>
    </html>
    """
    return html


@app.route('/api/health')
def health_check():
    """Check API and database health."""
    try:
        db, kg_manager = get_db_connection()
        healthy = db.health_check()
        
        return jsonify({
            "success": True,
            "api_status": "healthy",
            "database_status": "healthy" if healthy else "unhealthy",
            "message": "API is running"
        })
    except Exception as e:
        return handle_error(e)


@app.route('/api/stats')
def get_statistics():
    """Get graph statistics."""
    try:
        db, kg_manager = get_db_connection()
        stats = kg_manager.get_graph_statistics()
        
        return jsonify({
            "success": True,
            "data": stats
        })
    except Exception as e:
        return handle_error(e)


@app.route('/api/nodes')
def get_nodes():
    """Get nodes with optional filtering."""
    try:
        db, kg_manager = get_db_connection()
        
        label = request.args.get('label')
        limit = int(request.args.get('limit', 100))
        
        if label:
            nodes = kg_manager.find_nodes_by_label(label, limit)
        else:
            # Get all nodes (limited)
            query = "MATCH (n) RETURN n LIMIT $limit"
            result = db.execute_query(query, {"limit": limit})
            nodes = [dict(record['n']) for record in result]
        
        return jsonify({
            "success": True,
            "data": nodes,
            "count": len(nodes)
        })
    except Exception as e:
        return handle_error(e)


@app.route('/api/nodes/<node_id>')
def get_node(node_id: str):
    """Get specific node by ID."""
    try:
        db, kg_manager = get_db_connection()
        node = kg_manager.get_node_by_id(node_id)
        
        if not node:
            return jsonify({
                "success": False,
                "message": "Node not found"
            }), 404
        
        return jsonify({
            "success": True,
            "data": node
        })
    except Exception as e:
        return handle_error(e)


@app.route('/api/nodes/<node_id>/relationships')
def get_node_relationships(node_id: str):
    """Get relationships for a specific node."""
    try:
        db, kg_manager = get_db_connection()
        direction = request.args.get('direction', 'both')
        
        relationships = kg_manager.get_node_relationships(node_id, direction)
        
        return jsonify({
            "success": True,
            "data": relationships,
            "count": len(relationships)
        })
    except Exception as e:
        return handle_error(e)


@app.route('/api/search')
def search_nodes():
    """Search nodes by name."""
    try:
        db, kg_manager = get_db_connection()
        
        query = request.args.get('q')
        if not query:
            return jsonify({
                "success": False,
                "message": "Query parameter 'q' is required"
            }), 400
        
        limit = int(request.args.get('limit', 20))
        results = kg_manager.search_nodes_by_name(query, limit)
        
        return jsonify({
            "success": True,
            "data": results,
            "count": len(results),
            "query": query
        })
    except Exception as e:
        return handle_error(e)


@app.route('/api/nodes', methods=['POST'])
def create_node():
    """Create a new node."""
    try:
        db, kg_manager = get_db_connection()
        data = request.get_json()
        
        if not data or 'type' not in data:
            return jsonify({
                "success": False,
                "message": "Node type is required"
            }), 400
        
        node_type_str = data.pop('type')
        
        # Map string to NodeType enum
        node_type_map = {
            'Person': NodeType.PERSON,
            'Organization': NodeType.ORGANIZATION,
            'Concept': NodeType.CONCEPT,
            'Document': NodeType.DOCUMENT,
            'Location': NodeType.LOCATION,
            'Event': NodeType.EVENT,
            'Skill': NodeType.SKILL,
            'Project': NodeType.PROJECT
        }
        
        if node_type_str not in node_type_map:
            return jsonify({
                "success": False,
                "message": f"Invalid node type: {node_type_str}"
            }), 400
        
        node_type = node_type_map[node_type_str]
        node = create_node(node_type, **data)
        node_id = kg_manager.create_node(node)
        
        return jsonify({
            "success": True,
            "data": {"id": node_id, "type": node_type_str},
            "message": "Node created successfully"
        }), 201
        
    except Exception as e:
        return handle_error(e)


@app.route('/api/relationships', methods=['POST'])
def create_relationship():
    """Create a new relationship."""
    try:
        db, kg_manager = get_db_connection()
        data = request.get_json()
        
        required_fields = ['from_node_id', 'to_node_id', 'relationship_type']
        for field in required_fields:
            if field not in data:
                return jsonify({
                    "success": False,
                    "message": f"Field '{field}' is required"
                }), 400
        
        relationship = GraphRelationship(
            from_node_id=data['from_node_id'],
            to_node_id=data['to_node_id'],
            relationship_type=data['relationship_type'],
            properties=data.get('properties', {})
        )
        
        success = kg_manager.create_relationship(relationship)
        
        if success:
            return jsonify({
                "success": True,
                "message": "Relationship created successfully"
            }), 201
        else:
            return jsonify({
                "success": False,
                "message": "Failed to create relationship"
            }), 500
            
    except Exception as e:
        return handle_error(e)


@app.route('/api/visualize/network')
def get_network_data():
    """Get network visualization data."""
    try:
        db, kg_manager = get_db_connection()
        limit = int(request.args.get('limit', 50))
        
        # Get nodes
        nodes_query = "MATCH (n) RETURN n, labels(n) as labels LIMIT $limit"
        node_result = db.execute_query(nodes_query, {"limit": limit})
        
        nodes = []
        node_ids = set()
        
        for record in node_result:
            node_data = dict(record['n'])
            node_data['labels'] = record['labels']
            nodes.append(node_data)
            node_ids.add(node_data.get('id'))
        
        # Get relationships between these nodes
        if node_ids:
            rels_query = """
            MATCH (a)-[r]->(b)
            WHERE a.id IN $node_ids AND b.id IN $node_ids
            RETURN a.id as source, b.id as target, type(r) as type, r as properties
            """
            rel_result = db.execute_query(rels_query, {"node_ids": list(node_ids)})
            
            relationships = []
            for record in rel_result:
                rel_data = {
                    "source": record['source'],
                    "target": record['target'],
                    "type": record['type'],
                    "properties": dict(record['properties'])
                }
                relationships.append(rel_data)
        else:
            relationships = []
        
        return jsonify({
            "success": True,
            "data": {
                "nodes": nodes,
                "relationships": relationships
            }
        })
        
    except Exception as e:
        return handle_error(e)


@app.route('/api/generate-sample-data', methods=['POST'])
def generate_sample_data():
    """Generate sample data for learning."""
    try:
        db, kg_manager = get_db_connection()
        data = request.get_json() or {}
        
        # Get generation parameters
        people_count = data.get('people', 15)
        org_count = data.get('organizations', 8)
        concept_count = data.get('concepts', 12)
        skill_count = data.get('skills', 10)
        project_count = data.get('projects', 6)
        
        # Check if we should clear existing data
        clear_existing = data.get('clear_existing', False)
        if clear_existing:
            db.clear_database()
        
        generator = SampleDataGenerator(kg_manager)
        stats = generator.generate_complete_dataset(
            people_count=people_count,
            org_count=org_count,
            concept_count=concept_count,
            skill_count=skill_count,
            project_count=project_count
        )
        
        return jsonify({
            "success": True,
            "data": stats,
            "message": "Sample data generated successfully"
        })
        
    except Exception as e:
        return handle_error(e)


@app.route('/api/path/<from_id>/<to_id>')
def find_path(from_id: str, to_id: str):
    """Find shortest path between two nodes."""
    try:
        db, kg_manager = get_db_connection()
        max_hops = int(request.args.get('max_hops', 5))
        
        path = kg_manager.find_shortest_path(from_id, to_id, max_hops)
        
        if path:
            return jsonify({
                "success": True,
                "data": path
            })
        else:
            return jsonify({
                "success": False,
                "message": "No path found between the specified nodes"
            }), 404
            
    except Exception as e:
        return handle_error(e)


@app.route('/api/neighbors/<node_id>')
def get_neighbors(node_id: str):
    """Get neighbors of a specific node."""
    try:
        db, kg_manager = get_db_connection()
        hops = int(request.args.get('hops', 1))
        
        neighbors = kg_manager.get_node_neighbors(node_id, hops)
        
        return jsonify({
            "success": True,
            "data": neighbors,
            "count": len(neighbors)
        })
        
    except Exception as e:
        return handle_error(e)


@app.errorhandler(404)
def not_found(error):
    """Handle 404 errors."""
    return jsonify({
        "success": False,
        "message": "Endpoint not found"
    }), 404


@app.errorhandler(500)
def internal_error(error):
    """Handle 500 errors."""
    return jsonify({
        "success": False,
        "message": "Internal server error"
    }), 500


def create_app(config=None):
    """Application factory."""
    if config:
        app.config.update(config)
    return app


if __name__ == '__main__':
    import argparse
    
    parser = argparse.ArgumentParser(description='Knowledge Graph API Server')
    parser.add_argument('--host', default='localhost', help='Host to bind to')
    parser.add_argument('--port', type=int, default=5000, help='Port to bind to')
    parser.add_argument('--debug', action='store_true', help='Enable debug mode')
    
    args = parser.parse_args()
    
    print("Starting Knowledge Graph API Server...")
    print(f"Access the API documentation at: http://{args.host}:{args.port}")
    print(f"API endpoints available at: http://{args.host}:{args.port}/api/")
    
    try:
        # Test database connection on startup
        db, kg_manager = get_db_connection()
        if db.health_check():
            print("✅ Database connection successful")
        else:
            print("❌ Database connection failed")
            
        app.run(host=args.host, port=args.port, debug=args.debug)
        
    except Exception as e:
        print(f"❌ Failed to start server: {e}")
    finally:
        if _db_instance:
            _db_instance.close()
