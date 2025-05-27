"""
Knowledge Graph Package

This package provides comprehensive functionality for working with knowledge graphs
using Neo4j as the backend database.
"""

from .database import GraphDatabase, GraphConfig
from .models import (
    GraphNode, GraphRelationship, NodeType, RelationshipType,
    Person, Organization, Concept, Document, Location, Event, Skill, Project,
    create_node
)
from .operations import KnowledgeGraphManager

__version__ = "1.0.0"
__author__ = "Knowledge Graph Learning Project"

__all__ = [
    # Database
    'GraphDatabase',
    'GraphConfig',
    
    # Models
    'GraphNode',
    'GraphRelationship',
    'NodeType',
    'RelationshipType',
    'Person',
    'Organization',
    'Concept',
    'Document',
    'Location',
    'Event',
    'Skill',
    'Project',
    'create_node',
    
    # Operations
    'KnowledgeGraphManager'
]
