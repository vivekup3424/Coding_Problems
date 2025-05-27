"""
Knowledge Graph Visualization

This module provides visualization capabilities for the knowledge graph
using various libraries including NetworkX, Matplotlib, and Plotly.
"""

import matplotlib.pyplot as plt
import networkx as nx
import plotly.graph_objects as go
import plotly.express as px
from plotly.subplots import make_subplots
import pandas as pd
from typing import Dict, List, Any, Optional, Tuple
import random
import colorsys
from src.graph.operations import KnowledgeGraphManager


class GraphVisualizer:
    """
    Provides various visualization methods for knowledge graphs.
    
    This class offers multiple ways to visualize graph data, from simple
    network diagrams to interactive web-based visualizations.
    """
    
    def __init__(self, kg_manager: KnowledgeGraphManager):
        """
        Initialize the graph visualizer.
        
        Args:
            kg_manager: KnowledgeGraphManager instance
        """
        self.kg_manager = kg_manager
        self.color_map = {}
        
    def _generate_colors(self, labels: List[str]) -> Dict[str, str]:
        """Generate distinct colors for different node labels."""
        if not self.color_map:
            colors = []
            for i, label in enumerate(labels):
                hue = i / len(labels)
                saturation = 0.7
                value = 0.9
                rgb = colorsys.hsv_to_rgb(hue, saturation, value)
                hex_color = '#{:02x}{:02x}{:02x}'.format(
                    int(rgb[0] * 255), int(rgb[1] * 255), int(rgb[2] * 255)
                )
                colors.append(hex_color)
            
            self.color_map = dict(zip(labels, colors))
        
        return self.color_map
    
    def _create_networkx_graph(self, limit_nodes: int = 100) -> Tuple[nx.Graph, Dict[str, Any]]:
        """
        Create a NetworkX graph from the knowledge graph data.
        
        Args:
            limit_nodes: Maximum number of nodes to include
            
        Returns:
            Tuple of (NetworkX graph, node metadata)
        """
        # Get all nodes and relationships
        stats = self.kg_manager.get_graph_statistics()
        
        G = nx.Graph()
        node_metadata = {}
        
        # Get nodes by label type
        node_labels = stats.get('node_labels', [])
        added_nodes = 0
        
        for label in node_labels:
            if added_nodes >= limit_nodes:
                break
                
            nodes = self.kg_manager.find_nodes_by_label(
                label, 
                limit=min(limit_nodes - added_nodes, 20)
            )
            
            for node in nodes:
                node_id = node.get('id')
                if node_id:
                    G.add_node(node_id)
                    node_metadata[node_id] = {
                        'name': node.get('name', 'Unknown'),
                        'label': label,
                        'data': node
                    }
                    added_nodes += 1
        
        # Add relationships
        for node_id in list(G.nodes()):
            relationships = self.kg_manager.get_node_relationships(node_id)
            
            for rel in relationships:
                related_node_id = rel['related_node'].get('id')
                if related_node_id and related_node_id in G.nodes():
                    G.add_edge(node_id, related_node_id, 
                              relationship=rel['type'])
        
        return G, node_metadata
    
    def create_network_diagram(self, 
                             limit_nodes: int = 50,
                             layout: str = 'spring',
                             figsize: Tuple[int, int] = (12, 8),
                             save_path: Optional[str] = None) -> None:
        """
        Create a network diagram using Matplotlib and NetworkX.
        
        Args:
            limit_nodes: Maximum number of nodes to visualize
            layout: Layout algorithm ('spring', 'circular', 'random', 'shell')
            figsize: Figure size as (width, height)
            save_path: Path to save the visualization (optional)
        """
        G, node_metadata = self._create_networkx_graph(limit_nodes)
        
        if len(G.nodes()) == 0:
            print("No nodes found to visualize")
            return
        
        # Choose layout
        layout_functions = {
            'spring': nx.spring_layout,
            'circular': nx.circular_layout,
            'random': nx.random_layout,
            'shell': nx.shell_layout
        }
        
        layout_func = layout_functions.get(layout, nx.spring_layout)
        pos = layout_func(G, k=1, iterations=50)
        
        # Create figure
        plt.figure(figsize=figsize)
        
        # Get unique labels and colors
        labels = list(set(meta['label'] for meta in node_metadata.values()))
        colors = self._generate_colors(labels)
        
        # Draw nodes by label type
        for label in labels:
            nodes_of_label = [node_id for node_id, meta in node_metadata.items() 
                            if meta['label'] == label]
            
            if nodes_of_label:
                nx.draw_networkx_nodes(
                    G, pos,
                    nodelist=nodes_of_label,
                    node_color=colors[label],
                    node_size=300,
                    alpha=0.8,
                    label=label
                )
        
        # Draw edges
        nx.draw_networkx_edges(G, pos, alpha=0.6, width=1, edge_color='gray')
        
        # Add labels for nodes
        node_labels = {node_id: meta['name'][:10] + ('...' if len(meta['name']) > 10 else '')
                      for node_id, meta in node_metadata.items()}
        nx.draw_networkx_labels(G, pos, node_labels, font_size=8)
        
        plt.title(f"Knowledge Graph Network\n{len(G.nodes())} nodes, {len(G.edges())} relationships")
        plt.legend(scatterpoints=1)
        plt.axis('off')
        
        if save_path:
            plt.savefig(save_path, dpi=300, bbox_inches='tight')
            print(f"Network diagram saved to: {save_path}")
        
        plt.tight_layout()
        plt.show()
    
    def create_interactive_network(self, 
                                 limit_nodes: int = 100,
                                 save_path: Optional[str] = None) -> go.Figure:
        """
        Create an interactive network visualization using Plotly.
        
        Args:
            limit_nodes: Maximum number of nodes to visualize
            save_path: Path to save the HTML file (optional)
            
        Returns:
            Plotly figure object
        """
        G, node_metadata = self._create_networkx_graph(limit_nodes)
        
        if len(G.nodes()) == 0:
            print("No nodes found to visualize")
            return None
        
        # Calculate layout
        pos = nx.spring_layout(G, k=1, iterations=50)
        
        # Prepare edge traces
        edge_x = []
        edge_y = []
        edge_info = []
        
        for edge in G.edges():
            x0, y0 = pos[edge[0]]
            x1, y1 = pos[edge[1]]
            edge_x.extend([x0, x1, None])
            edge_y.extend([y0, y1, None])
            
            # Get relationship type
            rel_type = G.edges[edge].get('relationship', 'CONNECTED')
            edge_info.append(f"{node_metadata[edge[0]]['name']} {rel_type} {node_metadata[edge[1]]['name']}")
        
        edge_trace = go.Scatter(
            x=edge_x, y=edge_y,
            line=dict(width=1, color='lightgray'),
            hoverinfo='none',
            mode='lines'
        )
        
        # Prepare node traces by label
        labels = list(set(meta['label'] for meta in node_metadata.values()))
        colors = self._generate_colors(labels)
        
        node_traces = []
        
        for label in labels:
            nodes_of_label = [(node_id, meta) for node_id, meta in node_metadata.items() 
                            if meta['label'] == label]
            
            if not nodes_of_label:
                continue
            
            node_x = [pos[node_id][0] for node_id, _ in nodes_of_label]
            node_y = [pos[node_id][1] for node_id, _ in nodes_of_label]
            
            # Create hover text
            hover_text = []
            for node_id, meta in nodes_of_label:
                connections = len(list(G.neighbors(node_id)))
                hover_info = f"<b>{meta['name']}</b><br>"
                hover_info += f"Type: {label}<br>"
                hover_info += f"Connections: {connections}<br>"
                hover_info += f"ID: {node_id}"
                hover_text.append(hover_info)
            
            node_trace = go.Scatter(
                x=node_x, y=node_y,
                mode='markers+text',
                hoverinfo='text',
                hovertext=hover_text,
                text=[meta['name'][:15] for _, meta in nodes_of_label],
                textposition="middle center",
                textfont=dict(size=10),
                marker=dict(
                    size=15,
                    color=colors[label],
                    line=dict(width=2, color='white')
                ),
                name=label
            )
            node_traces.append(node_trace)
        
        # Create figure
        fig = go.Figure(data=[edge_trace] + node_traces,
                       layout=go.Layout(
                           title=f'Interactive Knowledge Graph<br>{len(G.nodes())} nodes, {len(G.edges())} relationships',
                           titlefont_size=16,
                           showlegend=True,
                           hovermode='closest',
                           margin=dict(b=20,l=5,r=5,t=40),
                           annotations=[ dict(
                               text="Click and drag to explore the network",
                               showarrow=False,
                               xref="paper", yref="paper",
                               x=0.005, y=-0.002,
                               xanchor="left", yanchor="bottom",
                               font=dict(color="gray", size=12)
                           )],
                           xaxis=dict(showgrid=False, zeroline=False, showticklabels=False),
                           yaxis=dict(showgrid=False, zeroline=False, showticklabels=False)
                       ))
        
        if save_path:
            fig.write_html(save_path)
            print(f"Interactive network saved to: {save_path}")
        
        return fig
    
    def create_statistics_dashboard(self, save_path: Optional[str] = None) -> go.Figure:
        """
        Create a dashboard showing graph statistics.
        
        Args:
            save_path: Path to save the HTML file (optional)
            
        Returns:
            Plotly figure object
        """
        stats = self.kg_manager.get_graph_statistics()
        
        # Create subplots
        fig = make_subplots(
            rows=2, cols=2,
            subplot_titles=[
                'Node Distribution by Type',
                'Relationship Distribution',
                'Most Connected Nodes',
                'Node Label Statistics'
            ],
            specs=[[{'type': 'pie'}, {'type': 'bar'}],
                   [{'type': 'bar'}, {'type': 'bar'}]]
        )
        
        # Node distribution pie chart
        if 'node_label_distribution' in stats and stats['node_label_distribution']:
            labels = [item['label'] for item in stats['node_label_distribution']]
            values = [item['count'] for item in stats['node_label_distribution']]
            
            fig.add_trace(
                go.Pie(labels=labels, values=values, name="Node Types"),
                row=1, col=1
            )
        
        # Relationship distribution bar chart
        if 'relationship_distribution' in stats and stats['relationship_distribution']:
            rel_types = [item['relationship_type'] for item in stats['relationship_distribution']]
            rel_counts = [item['count'] for item in stats['relationship_distribution']]
            
            fig.add_trace(
                go.Bar(x=rel_types, y=rel_counts, name="Relationships"),
                row=1, col=2
            )
        
        # Most connected nodes
        if 'most_connected_nodes' in stats and stats['most_connected_nodes']:
            node_names = [item['name'][:20] for item in stats['most_connected_nodes'][:10]]
            connections = [item['connections'] for item in stats['most_connected_nodes'][:10]]
            
            fig.add_trace(
                go.Bar(x=node_names, y=connections, name="Connections"),
                row=2, col=1
            )
        
        # Overall statistics
        overall_stats = [
            'Total Nodes', 'Total Relationships', 'Node Types', 'Relationship Types'
        ]
        overall_values = [
            stats.get('node_count', 0),
            stats.get('relationship_count', 0),
            len(stats.get('node_labels', [])),
            len(stats.get('relationship_types', []))
        ]
        
        fig.add_trace(
            go.Bar(x=overall_stats, y=overall_values, name="Overall Stats"),
            row=2, col=2
        )
        
        # Update layout
        fig.update_layout(
            title_text="Knowledge Graph Statistics Dashboard",
            showlegend=False,
            height=600
        )
        
        if save_path:
            fig.write_html(save_path)
            print(f"Statistics dashboard saved to: {save_path}")
        
        return fig
    
    def visualize_node_neighborhood(self, 
                                  node_id: str, 
                                  hops: int = 2,
                                  save_path: Optional[str] = None) -> go.Figure:
        """
        Visualize the neighborhood around a specific node.
        
        Args:
            node_id: Central node ID
            hops: Number of hops to include
            save_path: Path to save the visualization
            
        Returns:
            Plotly figure object
        """
        # Get the central node
        central_node = self.kg_manager.get_node_by_id(node_id)
        if not central_node:
            print(f"Node {node_id} not found")
            return None
        
        # Get neighbors
        neighbors = self.kg_manager.get_node_neighbors(node_id, hops)
        
        # Create a small graph
        G = nx.Graph()
        node_metadata = {}
        
        # Add central node
        G.add_node(node_id)
        node_metadata[node_id] = {
            'name': central_node.get('name', 'Unknown'),
            'label': central_node.get('labels', ['Unknown'])[0],
            'distance': 0,
            'is_central': True
        }
        
        # Add neighbors
        for neighbor_data in neighbors:
            neighbor = neighbor_data['node']
            neighbor_id = neighbor.get('id')
            distance = neighbor_data['distance']
            
            if neighbor_id:
                G.add_node(neighbor_id)
                node_metadata[neighbor_id] = {
                    'name': neighbor.get('name', 'Unknown'),
                    'label': 'Neighbor',  # Simplified for visualization
                    'distance': distance,
                    'is_central': False
                }
        
        # Add edges (get relationships for central node)
        relationships = self.kg_manager.get_node_relationships(node_id)
        for rel in relationships:
            related_id = rel['related_node'].get('id')
            if related_id and related_id in G.nodes():
                G.add_edge(node_id, related_id, relationship=rel['type'])
        
        if len(G.nodes()) <= 1:
            print(f"No neighbors found for node {node_id}")
            return None
        
        # Create layout
        pos = nx.spring_layout(G, k=2, iterations=50)
        
        # Prepare traces
        edge_x, edge_y = [], []
        for edge in G.edges():
            x0, y0 = pos[edge[0]]
            x1, y1 = pos[edge[1]]
            edge_x.extend([x0, x1, None])
            edge_y.extend([y0, y1, None])
        
        edge_trace = go.Scatter(
            x=edge_x, y=edge_y,
            line=dict(width=2, color='lightblue'),
            hoverinfo='none',
            mode='lines'
        )
        
        # Central node
        central_x, central_y = pos[node_id]
        central_trace = go.Scatter(
            x=[central_x], y=[central_y],
            mode='markers+text',
            text=[node_metadata[node_id]['name']],
            textposition="middle center",
            hovertext=f"<b>{node_metadata[node_id]['name']}</b><br>Central Node",
            marker=dict(size=25, color='red', line=dict(width=3, color='darkred')),
            name='Central Node'
        )
        
        # Neighbor nodes by distance
        distance_traces = []
        colors = ['orange', 'yellow', 'lightgreen', 'lightblue', 'purple']
        
        for distance in range(1, hops + 1):
            distance_nodes = [nid for nid, meta in node_metadata.items() 
                            if meta['distance'] == distance]
            
            if distance_nodes:
                node_x = [pos[nid][0] for nid in distance_nodes]
                node_y = [pos[nid][1] for nid in distance_nodes]
                node_text = [node_metadata[nid]['name'] for nid in distance_nodes]
                
                hover_text = [f"<b>{node_metadata[nid]['name']}</b><br>Distance: {distance}"
                            for nid in distance_nodes]
                
                trace = go.Scatter(
                    x=node_x, y=node_y,
                    mode='markers+text',
                    text=node_text,
                    textposition="middle center",
                    hovertext=hover_text,
                    marker=dict(
                        size=15,
                        color=colors[(distance - 1) % len(colors)],
                        line=dict(width=2, color='white')
                    ),
                    name=f'Distance {distance}'
                )
                distance_traces.append(trace)
        
        # Create figure
        fig = go.Figure(
            data=[edge_trace, central_trace] + distance_traces,
            layout=go.Layout(
                title=f'Neighborhood of "{node_metadata[node_id]["name"]}"<br>{len(G.nodes())} nodes, {len(G.edges())} connections',
                titlefont_size=16,
                showlegend=True,
                hovermode='closest',
                margin=dict(b=20,l=5,r=5,t=60),
                xaxis=dict(showgrid=False, zeroline=False, showticklabels=False),
                yaxis=dict(showgrid=False, zeroline=False, showticklabels=False)
            )
        )
        
        if save_path:
            fig.write_html(save_path)
            print(f"Neighborhood visualization saved to: {save_path}")
        
        return fig


# Example usage
if __name__ == "__main__":
    from src.graph.database import GraphDatabase, GraphConfig
    from src.graph.operations import KnowledgeGraphManager
    
    print("Graph Visualization Demo")
    print("=" * 25)
    
    config = GraphConfig()
    
    try:
        with GraphDatabase(config) as db:
            kg_manager = KnowledgeGraphManager(db)
            visualizer = GraphVisualizer(kg_manager)
            
            # Check if we have data
            stats = kg_manager.get_graph_statistics()
            if stats['node_count'] == 0:
                print("No data found in the graph. Please run the data generator first.")
            else:
                print(f"Found {stats['node_count']} nodes and {stats['relationship_count']} relationships")
                
                # Create visualizations
                print("\n1. Creating network diagram...")
                visualizer.create_network_diagram(limit_nodes=30)
                
                print("\n2. Creating interactive network...")
                fig = visualizer.create_interactive_network(limit_nodes=50)
                if fig:
                    fig.show()
                
                print("\n3. Creating statistics dashboard...")
                dashboard = visualizer.create_statistics_dashboard()
                dashboard.show()
                
    except Exception as e:
        print(f"Visualization demo failed: {e}")
        print("Make sure Neo4j is running and contains data.")
