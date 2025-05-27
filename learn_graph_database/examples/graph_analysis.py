#!/usr/bin/env python3
"""
Graph Analysis Example

This script demonstrates advanced graph analysis techniques:
- Centrality analysis
- Community detection
- Network metrics
- Influence analysis
- Pattern recognition

Run this after setting up the database and generating sample data.
"""

import sys
import os
from pathlib import Path

# Add the src directory to the path
sys.path.append(str(Path(__file__).parent.parent / "src"))

from graph.database import GraphDatabase
from graph.operations import KnowledgeGraphManager


def analyze_network_structure(kg: KnowledgeGraphManager):
    """Analyze the overall network structure."""
    print("🕸️  Network Structure Analysis")
    print("-" * 30)
    
    stats = kg.get_graph_statistics()
    total_nodes = stats['total_nodes']
    total_relationships = stats['total_relationships']
    
    if total_nodes > 0:
        density = (total_relationships * 2) / (total_nodes * (total_nodes - 1)) if total_nodes > 1 else 0
        avg_degree = (total_relationships * 2) / total_nodes if total_nodes > 0 else 0
        
        print(f"📊 Basic Metrics:")
        print(f"   Nodes: {total_nodes}")
        print(f"   Relationships: {total_relationships}")
        print(f"   Network Density: {density:.4f}")
        print(f"   Average Degree: {avg_degree:.2f}")
        
        # Node type distribution
        node_counts = stats.get('node_counts', {})
        print(f"\n📈 Node Distribution:")
        for node_type, count in node_counts.items():
            percentage = (count / total_nodes) * 100
            print(f"   {node_type}: {count} ({percentage:.1f}%)")
        
        # Relationship type distribution
        rel_counts = stats.get('relationship_counts', {})
        print(f"\n🔗 Relationship Distribution:")
        for rel_type, count in rel_counts.items():
            percentage = (count / total_relationships) * 100 if total_relationships > 0 else 0
            print(f"   {rel_type}: {count} ({percentage:.1f}%)")


def analyze_centrality(kg: KnowledgeGraphManager):
    """Analyze node centrality to find important nodes."""
    print("\n🎯 Centrality Analysis")
    print("-" * 30)
    
    # Get degree centrality
    centrality_results = kg.analyze_node_centrality(limit=10)
    
    if centrality_results:
        print("📊 Top 10 Most Connected Nodes (Degree Centrality):")
        for i, result in enumerate(centrality_results, 1):
            node = result['node']
            degree = result['degree']
            name = node.get('name', 'Unknown')
            node_id = node.get('id', 'Unknown')
            print(f"   {i:2d}. {name} (ID: {node_id[:8]}...) - {degree} connections")
        
        # Analyze by node type
        print(f"\n🏷️  Centrality by Node Type:")
        centrality_by_type = {}
        for result in centrality_results:
            # Get node labels (this might require additional query)
            node_id = result['node']['id']
            node_data = kg.get_node_by_id(node_id)
            if node_data:
                labels = node_data.get('labels', ['Unknown'])
                for label in labels:
                    if label not in centrality_by_type:
                        centrality_by_type[label] = []
                    centrality_by_type[label].append(result)
        
        for node_type, nodes in centrality_by_type.items():
            avg_degree = sum(node['degree'] for node in nodes) / len(nodes)
            print(f"   {node_type}: {len(nodes)} nodes, avg degree: {avg_degree:.2f}")


def analyze_communities(kg: KnowledgeGraphManager):
    """Detect and analyze communities in the graph."""
    print("\n🏘️  Community Detection")
    print("-" * 30)
    
    try:
        communities = kg.find_communities()
        
        if communities:
            print(f"Found {len(communities)} communities:")
            
            for i, community in enumerate(communities, 1):
                community_id = community.get('community', i)
                members = community.get('members', [])
                
                print(f"\n   Community {community_id}: {len(members)} members")
                
                # Get details for first few members
                for j, member_id in enumerate(members[:3]):
                    member_data = kg.get_node_by_id(member_id)
                    if member_data:
                        name = member_data['n'].get('name', 'Unknown')
                        labels = ', '.join(member_data.get('labels', ['Unknown']))
                        print(f"     - {name} ({labels})")
                
                if len(members) > 3:
                    print(f"     ... and {len(members) - 3} more")
        else:
            print("No distinct communities detected in the current graph.")
            print("This could mean:")
            print("- The graph is too small")
            print("- The graph is very well connected")
            print("- Community detection algorithm needs different parameters")
            
    except Exception as e:
        print(f"Community detection failed: {e}")
        print("This feature may require additional Neo4j plugins (GDS library)")


def analyze_influence_patterns(kg: KnowledgeGraphManager):
    """Analyze influence patterns in the graph."""
    print("\n💫 Influence Pattern Analysis")
    print("-" * 30)
    
    # Get all people and analyze their connections
    people = kg.get_nodes_by_type("Person")
    organizations = kg.get_nodes_by_type("Organization")
    
    if people and organizations:
        print("🔄 Connection Patterns:")
        
        # Analyze person-organization connections
        org_connections = {}
        for person in people[:10]:  # Analyze first 10 people
            person_id = person['n']['id']
            neighbors = kg.get_neighbors(person_id)
            
            org_count = 0
            for neighbor in neighbors:
                if 'Organization' in neighbor['labels']:
                    org_count += 1
                    org_name = neighbor['neighbor'].get('name', 'Unknown')
                    if org_name not in org_connections:
                        org_connections[org_name] = 0
                    org_connections[org_name] += 1
        
        # Show most attractive organizations
        if org_connections:
            sorted_orgs = sorted(org_connections.items(), key=lambda x: x[1], reverse=True)
            print(f"\n🏢 Most Connected Organizations:")
            for org_name, connection_count in sorted_orgs[:5]:
                print(f"   {org_name}: {connection_count} people connected")


def analyze_skill_patterns(kg: KnowledgeGraphManager):
    """Analyze skill distribution and patterns."""
    print("\n🎯 Skill Pattern Analysis")
    print("-" * 30)
    
    skills = kg.get_nodes_by_type("Skill")
    people = kg.get_nodes_by_type("Person")
    
    if skills and people:
        print(f"📊 Skill Overview:")
        print(f"   Total skills: {len(skills)}")
        print(f"   Total people: {len(people)}")
        
        # Analyze skill popularity
        skill_connections = {}
        for skill in skills:
            skill_id = skill['n']['id']
            skill_name = skill['n'].get('name', 'Unknown')
            
            # Count connections to people
            neighbors = kg.get_neighbors(skill_id)
            person_count = sum(1 for n in neighbors if 'Person' in n['labels'])
            skill_connections[skill_name] = person_count
        
        # Show most popular skills
        if skill_connections:
            sorted_skills = sorted(skill_connections.items(), key=lambda x: x[1], reverse=True)
            print(f"\n🔥 Most Popular Skills:")
            for skill_name, person_count in sorted_skills[:5]:
                print(f"   {skill_name}: {person_count} people have this skill")
        
        # Analyze skill categories
        skill_categories = {}
        for skill in skills:
            category = skill['n'].get('category', 'Unknown')
            if category not in skill_categories:
                skill_categories[category] = 0
            skill_categories[category] += 1
        
        print(f"\n📂 Skill Categories:")
        for category, count in sorted(skill_categories.items(), key=lambda x: x[1], reverse=True):
            print(f"   {category}: {count} skills")


def find_interesting_paths(kg: KnowledgeGraphManager):
    """Find interesting paths in the graph."""
    print("\n🛤️  Interesting Path Analysis")
    print("-" * 30)
    
    people = kg.get_nodes_by_type("Person")
    
    if len(people) >= 2:
        # Find paths between random people
        import random
        sample_people = random.sample(people, min(3, len(people)))
        
        print("🔍 Sample Path Analysis:")
        for i in range(len(sample_people) - 1):
            person1 = sample_people[i]['n']
            person2 = sample_people[i + 1]['n']
            
            person1_id = person1['id']
            person2_id = person2['id']
            person1_name = person1.get('name', 'Person 1')
            person2_name = person2.get('name', 'Person 2')
            
            path = kg.find_shortest_path(person1_id, person2_id)
            
            if path:
                print(f"   {person1_name} → {person2_name}: {path['length']} steps")
            else:
                print(f"   {person1_name} → {person2_name}: No direct path")


def analyze_graph_quality(kg: KnowledgeGraphManager):
    """Analyze the quality and completeness of graph data."""
    print("\n✅ Graph Quality Analysis")
    print("-" * 30)
    
    stats = kg.get_graph_statistics()
    
    # Check for isolated nodes
    query = """
    MATCH (n)
    WHERE NOT (n)--()
    RETURN count(n) as isolated_count
    """
    
    try:
        result = kg.db.execute_query(query)
        isolated_count = result[0]['isolated_count'] if result else 0
        
        total_nodes = stats['total_nodes']
        if total_nodes > 0:
            isolation_rate = (isolated_count / total_nodes) * 100
            print(f"🏝️  Isolated Nodes: {isolated_count} ({isolation_rate:.1f}%)")
        
        # Check for missing properties
        people = kg.get_nodes_by_type("Person")
        if people:
            missing_email = sum(1 for p in people[:20] if not p['n'].get('email'))
            missing_age = sum(1 for p in people[:20] if not p['n'].get('age'))
            sample_size = min(20, len(people))
            
            print(f"📧 Data Completeness (sample of {sample_size} people):")
            print(f"   Missing email: {missing_email}/{sample_size}")
            print(f"   Missing age: {missing_age}/{sample_size}")
        
        # Relationship balance
        total_relationships = stats['total_relationships']
        if total_nodes > 0 and total_relationships > 0:
            connectivity_ratio = total_relationships / total_nodes
            print(f"🔗 Connectivity Ratio: {connectivity_ratio:.2f} relationships per node")
            
            if connectivity_ratio < 1:
                print("   ⚠️  Low connectivity - consider adding more relationships")
            elif connectivity_ratio > 10:
                print("   ℹ️  High connectivity - rich relationship network")
            else:
                print("   ✅ Good connectivity balance")
        
    except Exception as e:
        print(f"Quality analysis error: {e}")


def main():
    """Run comprehensive graph analysis."""
    print("📊 Knowledge Graph - Advanced Analysis Example")
    print("=" * 55)
    
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
    
    # Check if we have data
    stats = kg.get_graph_statistics()
    if stats['total_nodes'] == 0:
        print("\n⚠️  No data found in the database!")
        print("Please run: python main.py generate")
        return
    
    print(f"\n📈 Analyzing graph with {stats['total_nodes']} nodes and {stats['total_relationships']} relationships")
    
    # Run all analyses
    analyze_network_structure(kg)
    analyze_centrality(kg)
    analyze_communities(kg)
    analyze_influence_patterns(kg)
    analyze_skill_patterns(kg)
    find_interesting_paths(kg)
    analyze_graph_quality(kg)
    
    print("\n✨ Graph analysis completed!")
    print("\nKey Insights Summary:")
    print("- Check the centrality analysis to identify key influencers")
    print("- Review community structure for natural groupings")
    print("- Examine skill patterns for learning opportunities")
    print("- Monitor graph quality metrics for data improvements")
    
    print("\nNext steps:")
    print("- Try the recommendation system: python examples/recommendation_system.py")
    print("- Explore visualizations: python examples/visualization_examples.py")
    print("- Use Jupyter notebooks for interactive analysis")
    
    # Close database connection
    db.close()


if __name__ == "__main__":
    main()
