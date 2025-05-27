"""
Knowledge Graph Node and Relationship Models

This module defines the core data models for nodes and relationships
in the knowledge graph.
"""

from typing import Dict, List, Optional, Any, Union
from dataclasses import dataclass, field, asdict
from datetime import datetime
import uuid
from enum import Enum


class NodeType(Enum):
    """Enumeration of supported node types."""
    PERSON = "Person"
    ORGANIZATION = "Organization"
    CONCEPT = "Concept"
    DOCUMENT = "Document"
    LOCATION = "Location"
    EVENT = "Event"
    SKILL = "Skill"
    PROJECT = "Project"


class RelationshipType(Enum):
    """Enumeration of supported relationship types."""
    KNOWS = "KNOWS"
    WORKS_FOR = "WORKS_FOR"
    LOCATED_IN = "LOCATED_IN"
    RELATED_TO = "RELATED_TO"
    AUTHORED = "AUTHORED"
    MENTIONS = "MENTIONS"
    PARTICIPATED_IN = "PARTICIPATED_IN"
    HAS_SKILL = "HAS_SKILL"
    COLLABORATES_WITH = "COLLABORATES_WITH"
    MANAGES = "MANAGES"
    BELONGS_TO = "BELONGS_TO"
    OCCURRED_AT = "OCCURRED_AT"


@dataclass
class GraphNode:
    """
    Base class for all graph nodes.
    
    This represents a vertex in the knowledge graph with common properties
    that all nodes share.
    """
    id: str = field(default_factory=lambda: str(uuid.uuid4()))
    name: str = ""
    description: Optional[str] = None
    created_at: datetime = field(default_factory=datetime.now)
    updated_at: datetime = field(default_factory=datetime.now)
    properties: Dict[str, Any] = field(default_factory=dict)
    
    def __post_init__(self):
        """Post-initialization processing."""
        if not self.name:
            raise ValueError("Node name cannot be empty")
    
    @property
    def label(self) -> str:
        """Get the node label/type."""
        return self.__class__.__name__
    
    def to_dict(self) -> Dict[str, Any]:
        """Convert node to dictionary representation."""
        data = asdict(self)
        # Convert datetime objects to ISO format strings
        data['created_at'] = self.created_at.isoformat()
        data['updated_at'] = self.updated_at.isoformat()
        return data
    
    def update_timestamp(self):
        """Update the last modified timestamp."""
        self.updated_at = datetime.now()


@dataclass
class Person(GraphNode):
    """Represents a person in the knowledge graph."""
    first_name: str = ""
    last_name: str = ""
    email: Optional[str] = None
    phone: Optional[str] = None
    age: Optional[int] = None
    occupation: Optional[str] = None
    location: Optional[str] = None
    
    def __post_init__(self):
        """Post-initialization processing for Person."""
        if not self.name and (self.first_name or self.last_name):
            self.name = f"{self.first_name} {self.last_name}".strip()
        super().__post_init__()
    
    @property
    def full_name(self) -> str:
        """Get the full name of the person."""
        return f"{self.first_name} {self.last_name}".strip()


@dataclass
class Organization(GraphNode):
    """Represents an organization in the knowledge graph."""
    organization_type: Optional[str] = None  # company, university, non-profit, etc.
    industry: Optional[str] = None
    founded_year: Optional[int] = None
    website: Optional[str] = None
    size: Optional[str] = None  # startup, small, medium, large, enterprise
    headquarters: Optional[str] = None


@dataclass
class Concept(GraphNode):
    """Represents a concept or topic in the knowledge graph."""
    category: Optional[str] = None
    complexity_level: Optional[str] = None  # beginner, intermediate, advanced
    keywords: List[str] = field(default_factory=list)
    
    def add_keyword(self, keyword: str):
        """Add a keyword to the concept."""
        if keyword not in self.keywords:
            self.keywords.append(keyword)
            self.update_timestamp()


@dataclass
class Document(GraphNode):
    """Represents a document in the knowledge graph."""
    document_type: Optional[str] = None  # article, paper, book, blog_post, etc.
    author: Optional[str] = None
    publication_date: Optional[datetime] = None
    url: Optional[str] = None
    content_summary: Optional[str] = None
    language: str = "en"
    
    def to_dict(self) -> Dict[str, Any]:
        """Convert document to dictionary with proper date handling."""
        data = super().to_dict()
        if self.publication_date:
            data['publication_date'] = self.publication_date.isoformat()
        return data


@dataclass
class Location(GraphNode):
    """Represents a location in the knowledge graph."""
    location_type: Optional[str] = None  # city, country, building, etc.
    latitude: Optional[float] = None
    longitude: Optional[float] = None
    address: Optional[str] = None
    parent_location: Optional[str] = None  # e.g., city -> state -> country


@dataclass
class Event(GraphNode):
    """Represents an event in the knowledge graph."""
    event_type: Optional[str] = None  # conference, meeting, workshop, etc.
    start_date: Optional[datetime] = None
    end_date: Optional[datetime] = None
    location: Optional[str] = None
    organizer: Optional[str] = None
    
    def to_dict(self) -> Dict[str, Any]:
        """Convert event to dictionary with proper date handling."""
        data = super().to_dict()
        if self.start_date:
            data['start_date'] = self.start_date.isoformat()
        if self.end_date:
            data['end_date'] = self.end_date.isoformat()
        return data


@dataclass
class Skill(GraphNode):
    """Represents a skill in the knowledge graph."""
    skill_category: Optional[str] = None  # technical, soft, domain-specific
    proficiency_levels: List[str] = field(default_factory=lambda: ["beginner", "intermediate", "advanced", "expert"])
    related_tools: List[str] = field(default_factory=list)


@dataclass
class Project(GraphNode):
    """Represents a project in the knowledge graph."""
    project_type: Optional[str] = None  # software, research, business, etc.
    status: Optional[str] = None  # planning, active, completed, cancelled
    start_date: Optional[datetime] = None
    end_date: Optional[datetime] = None
    budget: Optional[float] = None
    technologies: List[str] = field(default_factory=list)
    
    def to_dict(self) -> Dict[str, Any]:
        """Convert project to dictionary with proper date handling."""
        data = super().to_dict()
        if self.start_date:
            data['start_date'] = self.start_date.isoformat()
        if self.end_date:
            data['end_date'] = self.end_date.isoformat()
        return data


@dataclass
class GraphRelationship:
    """
    Represents a relationship between two nodes in the knowledge graph.
    """
    from_node_id: str
    to_node_id: str
    relationship_type: Union[RelationshipType, str]
    properties: Dict[str, Any] = field(default_factory=dict)
    created_at: datetime = field(default_factory=datetime.now)
    weight: float = 1.0  # Relationship strength/importance
    
    def __post_init__(self):
        """Post-initialization processing."""
        if isinstance(self.relationship_type, RelationshipType):
            self.relationship_type = self.relationship_type.value
    
    def to_dict(self) -> Dict[str, Any]:
        """Convert relationship to dictionary representation."""
        data = asdict(self)
        data['created_at'] = self.created_at.isoformat()
        return data


# Node factory for creating nodes of different types
def create_node(node_type: NodeType, **kwargs) -> GraphNode:
    """
    Factory function to create nodes of different types.
    
    Args:
        node_type: The type of node to create
        **kwargs: Node properties
        
    Returns:
        Instance of the appropriate node class
    """
    node_classes = {
        NodeType.PERSON: Person,
        NodeType.ORGANIZATION: Organization,
        NodeType.CONCEPT: Concept,
        NodeType.DOCUMENT: Document,
        NodeType.LOCATION: Location,
        NodeType.EVENT: Event,
        NodeType.SKILL: Skill,
        NodeType.PROJECT: Project
    }
    
    node_class = node_classes.get(node_type)
    if not node_class:
        raise ValueError(f"Unknown node type: {node_type}")
    
    return node_class(**kwargs)


# Example usage and demonstrations
if __name__ == "__main__":
    print("Knowledge Graph Models Demo")
    print("=" * 30)
    
    # Create sample nodes
    person = Person(
        first_name="Alice",
        last_name="Smith",
        email="alice@example.com",
        occupation="Data Scientist",
        age=30
    )
    
    organization = Organization(
        name="TechCorp",
        organization_type="company",
        industry="Technology",
        founded_year=2010,
        size="medium"
    )
    
    concept = Concept(
        name="Machine Learning",
        description="A method of data analysis that automates analytical model building",
        category="Computer Science",
        complexity_level="intermediate",
        keywords=["AI", "algorithms", "data", "prediction"]
    )
    
    # Create a relationship
    relationship = GraphRelationship(
        from_node_id=person.id,
        to_node_id=organization.id,
        relationship_type=RelationshipType.WORKS_FOR,
        properties={"position": "Senior Data Scientist", "start_date": "2022-01-15"}
    )
    
    # Display information
    print(f"Person: {person.full_name} ({person.occupation})")
    print(f"Organization: {organization.name} ({organization.industry})")
    print(f"Concept: {concept.name}")
    print(f"Relationship: {person.name} {relationship.relationship_type} {organization.name}")
    
    # Show serialization
    print("\nSerialized Person:")
    print(person.to_dict())
