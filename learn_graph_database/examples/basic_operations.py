#!/usr/bin/env python3
"""
Basic Operations Example

This script demonstrates fundamental knowledge graph operations:
- Creating nodes and relationships
- Querying and searching
- Updating and deleting data
- Basic graph traversal

Run this after setting up the database and generating sample data.
"""

import sys
import os
from pathlib import Path

# Add the src directory to the path
sys.path.append(str(Path(__file__).parent.parent / "src"))

from graph.database import GraphDatabase
from graph.operations import KnowledgeGraphManager
from graph.models import Person, Organization, Concept, Skill


def main():
    """Demonstrate basic knowledge graph operations."""
    print("🚀 Knowledge Graph - Basic Operations Example")
    print("=" * 50)
    
    # Connect to database
    try:
        db = GraphDatabase(
            uri="bolt://localhost:7687",
            username="neo4j",
            password="knowledge_graph_password"
        )
        kg = KnowledgeGraphManager(db)
        print("✅ Connected to Neo4j database")
    except Exception as e:
        print(f"❌ Failed to connect to database: {e}")
        print("Make sure Neo4j is running (docker-compose up -d)")
        return
    
    print("\n1. Creating New Nodes")
    print("-" * 30)
    
    # Create a new person
    new_person = Person(
        name="Alice Johnson",
        age=28,
        email="alice.johnson@example.com",
        location="Seattle",
        bio="Data scientist specializing in machine learning and graph analytics"
    )
    
    person_id = kg.create_node(new_person)
    print(f"📄 Created person: {new_person.name} (ID: {person_id})")
    
    # Create a new organization
    new_org = Organization(
        name="Graph Analytics Inc",
        industry="Technology",
        size="Medium",
        location="Seattle",
        description="Specialized in graph database solutions and analytics"
    )
    
    org_id = kg.create_node(new_org)
    print(f"🏢 Created organization: {new_org.name} (ID: {org_id})")
    
    # Create a new skill
    new_skill = Skill(
        name="Graph Databases",
        category="Database Technology",
        level="Expert",
        description="Expertise in Neo4j, graph modeling, and Cypher queries"
    )
    
    skill_id = kg.create_node(new_skill)
    print(f"🎯 Created skill: {new_skill.name} (ID: {skill_id})")
    
    print("\n2. Creating Relationships")
    print("-" * 30)
    
    # Create relationships
    kg.create_relationship(
        person_id, org_id, "WORKS_FOR",
        {"role": "Senior Data Scientist", "start_date": "2023-01-15"}
    )
    print(f"🔗 Created WORKS_FOR relationship: {new_person.name} -> {new_org.name}")
    
    kg.create_relationship(
        person_id, skill_id, "HAS_SKILL",
        {"proficiency": "Expert", "years_experience": 5}
    )
    print(f"🔗 Created HAS_SKILL relationship: {new_person.name} -> {new_skill.name}")
    
    print("\n3. Querying Data")
    print("-" * 30)
    
    # Get node by ID
    retrieved_person = kg.get_node_by_id(person_id)
    if retrieved_person:
        print(f"👤 Retrieved person: {retrieved_person['n']['name']}")
        print(f"   Age: {retrieved_person['n'].get('age', 'N/A')}")
        print(f"   Location: {retrieved_person['n'].get('location', 'N/A')}")
    
    # Get relationships
    relationships = kg.get_relationships(person_id)
    print(f"\n🔗 {new_person.name} has {len(relationships)} relationships:")
    for rel in relationships:
        rel_type = rel['r']['type']
        other_name = rel['other'].get('name', 'Unknown')
        print(f"   - {rel_type}: {other_name}")
    
    print("\n4. Searching")
    print("-" * 30)
    
    # Search for nodes
    search_results = kg.search_nodes("graph")
    print(f"🔍 Found {len(search_results)} nodes containing 'graph':")
    for result in search_results[:3]:  # Show first 3 results
        node = result['n']
        labels = result['labels']
        print(f"   - {node.get('name', 'N/A')} ({', '.join(labels)})")
    
    # Get nodes by type
    all_people = kg.get_nodes_by_type("Person")
    print(f"\n👥 Total people in database: {len(all_people)}")
    
    print("\n5. Graph Traversal")
    print("-" * 30)
    
    # Get neighbors
    neighbors = kg.get_neighbors(person_id)
    print(f"🌐 {new_person.name}'s neighbors ({len(neighbors)}):")
    for neighbor in neighbors:
        neighbor_name = neighbor['neighbor'].get('name', 'Unknown')
        rel_type = neighbor['relationship']['type']
        labels = ', '.join(neighbor['labels'])
        print(f"   - {neighbor_name} ({labels}) via {rel_type}")
    
    # Find shortest path (if there are enough nodes)
    all_orgs = kg.get_nodes_by_type("Organization")
    if len(all_orgs) > 1:
        target_org_id = None
        for org in all_orgs:
            if org['n']['id'] != org_id:
                target_org_id = org['n']['id']
                break
        
        if target_org_id:
            path = kg.find_shortest_path(person_id, target_org_id)
            if path:
                print(f"\n🛤️  Shortest path found (length: {path['length']})")
            else:
                print(f"\n🛤️  No path found between nodes")
    
    print("\n6. Updating Data")
    print("-" * 30)
    
    # Update node
    update_success = kg.update_node(person_id, {
        "last_updated": "2024-01-20",
        "status": "Active"
    })
    
    if update_success:
        print(f"✏️  Updated {new_person.name}'s information")
        
        # Verify update
        updated_person = kg.get_node_by_id(person_id)
        if updated_person:
            print(f"   Status: {updated_person['n'].get('status', 'N/A')}")
    
    print("\n7. Statistics")
    print("-" * 30)
    
    # Get graph statistics
    stats = kg.get_graph_statistics()
    print(f"📊 Graph Statistics:")
    print(f"   Total nodes: {stats['total_nodes']}")
    print(f"   Total relationships: {stats['total_relationships']}")
    print(f"   Node types: {', '.join(stats.get('node_counts', {}).keys())}")
    
    print("\n8. Advanced Queries")
    print("-" * 30)
    
    # Analyze centrality
    centrality_results = kg.analyze_node_centrality(limit=5)
    print(f"🎯 Top 5 most connected nodes:")
    for result in centrality_results:
        node_name = result['node'].get('name', 'Unknown')
        degree = result['degree']
        print(f"   - {node_name}: {degree} connections")
    
    print("\n9. Cleanup (Optional)")
    print("-" * 30)
    
    response = input("Do you want to delete the created nodes? (y/n): ").lower()
    if response == 'y':
        # Delete relationships first (automatically handled by DETACH DELETE)
        kg.delete_node(person_id)
        kg.delete_node(org_id)
        kg.delete_node(skill_id)
        print("🗑️  Cleaned up created nodes")
    else:
        print("💾 Keeping created nodes for further exploration")
    
    print("\n✨ Basic operations example completed!")
    print("Next steps:")
    print("- Try the graph analysis example: python examples/graph_analysis.py")
    print("- Explore the Jupyter notebooks in the notebooks/ directory")
    print("- Use the interactive CLI: python main.py interactive")
    
    # Close database connection
    db.close()


if __name__ == "__main__":
    main()
