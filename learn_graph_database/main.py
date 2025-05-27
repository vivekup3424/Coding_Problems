#!/usr/bin/env python3
"""
Knowledge Graph Learning Project - Main Application

This is the main entry point for the knowledge graph learning project.
It provides a command-line interface for interacting with the graph database.
"""

import argparse
import sys
from typing import Optional
from pathlib import Path

# Add src to path for imports
sys.path.append(str(Path(__file__).parent / "src"))

from src.graph.database import GraphDatabase, GraphConfig
from src.graph.operations import KnowledgeGraphManager
from src.data.generator import SampleDataGenerator
from src.visualization.graph_viz import GraphVisualizer


def setup_database() -> None:
    """Initialize database with constraints and indexes."""
    print("Setting up database...")
    config = GraphConfig.from_env()
    
    try:
        with GraphDatabase(config) as db:
            if not db.health_check():
                print("❌ Database health check failed")
                return
            
            db.create_constraints()
            print("✅ Database setup complete")
            
    except Exception as e:
        print(f"❌ Database setup failed: {e}")
        print("\nPlease ensure Neo4j is running and accessible.")
        print("Default connection: bolt://localhost:7687")


def generate_sample_data(people: int = 20, orgs: int = 10, concepts: int = 15, 
                        skills: int = 12, projects: int = 8) -> None:
    """Generate sample data for learning purposes."""
    print("Generating sample data...")
    config = GraphConfig.from_env()
    
    try:
        with GraphDatabase(config) as db:
            kg_manager = KnowledgeGraphManager(db)
            generator = SampleDataGenerator(kg_manager)
            
            # Check if data already exists
            stats = kg_manager.get_graph_statistics()
            if stats['node_count'] > 0:
                response = input(f"Database contains {stats['node_count']} nodes. Clear existing data? (y/N): ")
                if response.lower() == 'y':
                    db.clear_database()
                    print("Database cleared")
                else:
                    print("Keeping existing data")
            
            # Generate new sample data
            generation_stats = generator.generate_complete_dataset(
                people_count=people,
                org_count=orgs,
                concept_count=concepts,
                skill_count=skills,
                project_count=projects
            )
            
            print("\n✅ Sample data generation complete!")
            print(f"Created {generation_stats['nodes_created']['total']} nodes")
            print(f"Created {generation_stats['relationships_created']} relationships")
            
    except Exception as e:
        print(f"❌ Sample data generation failed: {e}")


def show_statistics() -> None:
    """Display graph statistics."""
    print("Graph Database Statistics")
    print("=" * 30)
    
    config = GraphConfig.from_env()
    
    try:
        with GraphDatabase(config) as db:
            kg_manager = KnowledgeGraphManager(db)
            stats = kg_manager.get_graph_statistics()
            
            print(f"Total Nodes: {stats['node_count']}")
            print(f"Total Relationships: {stats['relationship_count']}")
            print(f"Node Types: {len(stats.get('node_labels', []))}")
            print(f"Relationship Types: {len(stats.get('relationship_types', []))}")
            
            # Node distribution
            if 'node_label_distribution' in stats and stats['node_label_distribution']:
                print("\nNode Distribution:")
                for item in stats['node_label_distribution']:
                    print(f"  {item['label']}: {item['count']}")
            
            # Relationship distribution
            if 'relationship_distribution' in stats and stats['relationship_distribution']:
                print("\nRelationship Distribution:")
                for item in stats['relationship_distribution'][:5]:  # Top 5
                    print(f"  {item['relationship_type']}: {item['count']}")
            
            # Most connected nodes
            if 'most_connected_nodes' in stats and stats['most_connected_nodes']:
                print("\nMost Connected Nodes:")
                for item in stats['most_connected_nodes'][:5]:  # Top 5
                    print(f"  {item['name']}: {item['connections']} connections")
                    
    except Exception as e:
        print(f"❌ Failed to get statistics: {e}")


def search_nodes(query: str) -> None:
    """Search for nodes by name."""
    print(f"Searching for: '{query}'")
    print("-" * 30)
    
    config = GraphConfig.from_env()
    
    try:
        with GraphDatabase(config) as db:
            kg_manager = KnowledgeGraphManager(db)
            results = kg_manager.search_nodes_by_name(query, limit=10)
            
            if not results:
                print("No results found")
                return
            
            for i, node in enumerate(results, 1):
                labels = node.get('labels', ['Unknown'])
                print(f"{i}. {node.get('name', 'Unknown')} ({labels[0]})")
                if node.get('description'):
                    print(f"   Description: {node['description'][:100]}...")
                print(f"   ID: {node.get('id')}")
                print()
                
    except Exception as e:
        print(f"❌ Search failed: {e}")


def explore_node(node_id: str) -> None:
    """Explore a specific node and its relationships."""
    print(f"Exploring node: {node_id}")
    print("-" * 40)
    
    config = GraphConfig.from_env()
    
    try:
        with GraphDatabase(config) as db:
            kg_manager = KnowledgeGraphManager(db)
            
            # Get node details
            node = kg_manager.get_node_by_id(node_id)
            if not node:
                print("Node not found")
                return
            
            print(f"Name: {node.get('name', 'Unknown')}")
            print(f"Type: {node.get('labels', ['Unknown'])[0]}")
            
            if node.get('description'):
                print(f"Description: {node['description']}")
            
            # Get relationships
            relationships = kg_manager.get_node_relationships(node_id)
            
            if relationships:
                print(f"\nRelationships ({len(relationships)}):")
                for rel in relationships[:10]:  # Show first 10
                    related_name = rel['related_node'].get('name', 'Unknown')
                    rel_type = rel['type']
                    print(f"  {rel_type} → {related_name}")
            else:
                print("\nNo relationships found")
                
    except Exception as e:
        print(f"❌ Node exploration failed: {e}")


def create_visualization(viz_type: str = "network", output_path: Optional[str] = None) -> None:
    """Create visualizations of the graph."""
    print(f"Creating {viz_type} visualization...")
    
    config = GraphConfig.from_env()
    
    try:
        with GraphDatabase(config) as db:
            kg_manager = KnowledgeGraphManager(db)
            visualizer = GraphVisualizer(kg_manager)
            
            # Check if we have data
            stats = kg_manager.get_graph_statistics()
            if stats['node_count'] == 0:
                print("❌ No data found in the graph. Generate sample data first.")
                return
            
            if viz_type == "network":
                visualizer.create_network_diagram(
                    limit_nodes=50,
                    save_path=output_path
                )
                print("✅ Network diagram created")
                
            elif viz_type == "interactive":
                fig = visualizer.create_interactive_network(
                    limit_nodes=100,
                    save_path=output_path
                )
                if fig:
                    fig.show()
                print("✅ Interactive network visualization created")
                
            elif viz_type == "stats":
                fig = visualizer.create_statistics_dashboard(
                    save_path=output_path
                )
                fig.show()
                print("✅ Statistics dashboard created")
                
            else:
                print(f"❌ Unknown visualization type: {viz_type}")
                
    except Exception as e:
        print(f"❌ Visualization failed: {e}")


def run_interactive_mode() -> None:
    """Run interactive exploration mode."""
    print("Knowledge Graph Interactive Explorer")
    print("=" * 40)
    print("Commands:")
    print("  search <query>     - Search for nodes")
    print("  explore <node_id>  - Explore a specific node")
    print("  stats             - Show graph statistics")
    print("  viz <type>        - Create visualization (network/interactive/stats)")
    print("  help              - Show this help")
    print("  quit              - Exit")
    print()
    
    while True:
        try:
            command = input("kg> ").strip()
            
            if not command:
                continue
                
            parts = command.split(maxsplit=1)
            cmd = parts[0].lower()
            args = parts[1] if len(parts) > 1 else ""
            
            if cmd == "quit":
                break
            elif cmd == "help":
                print("Available commands: search, explore, stats, viz, help, quit")
            elif cmd == "search":
                if args:
                    search_nodes(args)
                else:
                    print("Usage: search <query>")
            elif cmd == "explore":
                if args:
                    explore_node(args)
                else:
                    print("Usage: explore <node_id>")
            elif cmd == "stats":
                show_statistics()
            elif cmd == "viz":
                viz_type = args if args in ["network", "interactive", "stats"] else "network"
                create_visualization(viz_type)
            else:
                print(f"Unknown command: {cmd}")
                
        except KeyboardInterrupt:
            print("\nExiting...")
            break
        except Exception as e:
            print(f"Error: {e}")
    
    print("Goodbye!")


def main():
    """Main application entry point."""
    parser = argparse.ArgumentParser(
        description="Knowledge Graph Learning Project",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  python main.py setup                     # Setup database
  python main.py generate                  # Generate sample data
  python main.py stats                     # Show statistics
  python main.py search "Alice"            # Search for nodes
  python main.py explore <node-id>         # Explore specific node
  python main.py visualize network         # Create network diagram
  python main.py interactive              # Interactive mode
        """
    )
    
    subparsers = parser.add_subparsers(dest='command', help='Available commands')
    
    # Setup command
    subparsers.add_parser('setup', help='Setup database with constraints and indexes')
    
    # Generate command
    gen_parser = subparsers.add_parser('generate', help='Generate sample data')
    gen_parser.add_argument('--people', type=int, default=20, help='Number of people (default: 20)')
    gen_parser.add_argument('--orgs', type=int, default=10, help='Number of organizations (default: 10)')
    gen_parser.add_argument('--concepts', type=int, default=15, help='Number of concepts (default: 15)')
    gen_parser.add_argument('--skills', type=int, default=12, help='Number of skills (default: 12)')
    gen_parser.add_argument('--projects', type=int, default=8, help='Number of projects (default: 8)')
    
    # Stats command
    subparsers.add_parser('stats', help='Show graph statistics')
    
    # Search command
    search_parser = subparsers.add_parser('search', help='Search for nodes')
    search_parser.add_argument('query', help='Search query')
    
    # Explore command
    explore_parser = subparsers.add_parser('explore', help='Explore a specific node')
    explore_parser.add_argument('node_id', help='Node ID to explore')
    
    # Visualize command
    viz_parser = subparsers.add_parser('visualize', help='Create visualizations')
    viz_parser.add_argument('type', choices=['network', 'interactive', 'stats'], 
                           help='Type of visualization')
    viz_parser.add_argument('--output', help='Output file path')
    
    # Interactive command
    subparsers.add_parser('interactive', help='Run interactive exploration mode')
    
    args = parser.parse_args()
    
    if not args.command:
        parser.print_help()
        return
    
    # Execute commands
    if args.command == 'setup':
        setup_database()
    elif args.command == 'generate':
        generate_sample_data(args.people, args.orgs, args.concepts, args.skills, args.projects)
    elif args.command == 'stats':
        show_statistics()
    elif args.command == 'search':
        search_nodes(args.query)
    elif args.command == 'explore':
        explore_node(args.node_id)
    elif args.command == 'visualize':
        create_visualization(args.type, args.output)
    elif args.command == 'interactive':
        run_interactive_mode()


if __name__ == "__main__":
    main()
