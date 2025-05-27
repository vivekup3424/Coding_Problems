"""
Unit tests for graph data models.
"""
import pytest
from datetime import datetime
from uuid import UUID

from src.graph.models import Person, Organization, Concept, Document, Location, Event, Skill, Project


@pytest.mark.unit
class TestPerson:
    """Test cases for Person model."""

    def test_person_creation(self):
        """Test creating a Person instance."""
        person = Person(
            name="John Doe",
            age=30,
            email="john.doe@example.com",
            location="New York"
        )
        
        assert person.name == "John Doe"
        assert person.age == 30
        assert person.email == "john.doe@example.com"
        assert person.location == "New York"
        assert isinstance(person.id, str)
        assert isinstance(person.created_at, datetime)

    def test_person_to_dict(self):
        """Test converting Person to dictionary."""
        person = Person(
            name="Jane Smith",
            age=25,
            email="jane.smith@example.com"
        )
        
        person_dict = person.to_dict()
        
        assert person_dict["name"] == "Jane Smith"
        assert person_dict["age"] == 25
        assert person_dict["email"] == "jane.smith@example.com"
        assert "id" in person_dict
        assert "created_at" in person_dict

    def test_person_from_dict(self):
        """Test creating Person from dictionary."""
        data = {
            "name": "Bob Johnson",
            "age": 35,
            "email": "bob.johnson@example.com",
            "location": "Chicago",
            "bio": "Software developer"
        }
        
        person = Person.from_dict(data)
        
        assert person.name == "Bob Johnson"
        assert person.age == 35
        assert person.email == "bob.johnson@example.com"
        assert person.location == "Chicago"
        assert person.bio == "Software developer"

    def test_person_validation(self):
        """Test Person validation."""
        # Valid person
        person = Person(name="Valid Person", age=25)
        assert person.name == "Valid Person"
        
        # Test empty name raises error
        with pytest.raises(ValueError, match="Name cannot be empty"):
            Person(name="", age=25)
        
        # Test negative age raises error
        with pytest.raises(ValueError, match="Age must be non-negative"):
            Person(name="Test Person", age=-1)


@pytest.mark.unit
class TestOrganization:
    """Test cases for Organization model."""

    def test_organization_creation(self):
        """Test creating an Organization instance."""
        org = Organization(
            name="Tech Corp",
            industry="Technology",
            size="Large",
            location="San Francisco"
        )
        
        assert org.name == "Tech Corp"
        assert org.industry == "Technology"
        assert org.size == "Large"
        assert org.location == "San Francisco"
        assert isinstance(org.id, str)

    def test_organization_to_dict(self):
        """Test converting Organization to dictionary."""
        org = Organization(
            name="Data Inc",
            industry="Analytics",
            size="Medium"
        )
        
        org_dict = org.to_dict()
        
        assert org_dict["name"] == "Data Inc"
        assert org_dict["industry"] == "Analytics"
        assert org_dict["size"] == "Medium"
        assert "id" in org_dict

    def test_organization_from_dict(self):
        """Test creating Organization from dictionary."""
        data = {
            "name": "AI Solutions",
            "industry": "Artificial Intelligence",
            "size": "Startup",
            "location": "Austin",
            "website": "https://aisolutions.com"
        }
        
        org = Organization.from_dict(data)
        
        assert org.name == "AI Solutions"
        assert org.industry == "Artificial Intelligence"
        assert org.size == "Startup"
        assert org.website == "https://aisolutions.com"


@pytest.mark.unit
class TestConcept:
    """Test cases for Concept model."""

    def test_concept_creation(self):
        """Test creating a Concept instance."""
        concept = Concept(
            name="Machine Learning",
            category="Technology",
            description="AI subset focused on learning algorithms"
        )
        
        assert concept.name == "Machine Learning"
        assert concept.category == "Technology"
        assert concept.description == "AI subset focused on learning algorithms"

    def test_concept_to_dict(self):
        """Test converting Concept to dictionary."""
        concept = Concept(
            name="Deep Learning",
            category="AI",
            description="Neural networks with multiple layers"
        )
        
        concept_dict = concept.to_dict()
        
        assert concept_dict["name"] == "Deep Learning"
        assert concept_dict["category"] == "AI"
        assert concept_dict["description"] == "Neural networks with multiple layers"

    def test_concept_from_dict(self):
        """Test creating Concept from dictionary."""
        data = {
            "name": "Natural Language Processing",
            "category": "AI",
            "description": "AI field focused on language understanding"
        }
        
        concept = Concept.from_dict(data)
        
        assert concept.name == "Natural Language Processing"
        assert concept.category == "AI"


@pytest.mark.unit
class TestSkill:
    """Test cases for Skill model."""

    def test_skill_creation(self):
        """Test creating a Skill instance."""
        skill = Skill(
            name="Python Programming",
            category="Programming Language",
            level="Advanced"
        )
        
        assert skill.name == "Python Programming"
        assert skill.category == "Programming Language"
        assert skill.level == "Advanced"

    def test_skill_level_validation(self):
        """Test skill level validation."""
        # Valid levels
        for level in ["Beginner", "Intermediate", "Advanced", "Expert"]:
            skill = Skill(name="Test Skill", category="Test", level=level)
            assert skill.level == level
        
        # Invalid level should raise error
        with pytest.raises(ValueError, match="Level must be one of"):
            Skill(name="Test Skill", category="Test", level="Invalid")

    def test_skill_to_dict(self):
        """Test converting Skill to dictionary."""
        skill = Skill(
            name="JavaScript",
            category="Programming Language",
            level="Intermediate",
            description="Dynamic programming language for web development"
        )
        
        skill_dict = skill.to_dict()
        
        assert skill_dict["name"] == "JavaScript"
        assert skill_dict["level"] == "Intermediate"
        assert skill_dict["description"] == "Dynamic programming language for web development"


@pytest.mark.unit
class TestProject:
    """Test cases for Project model."""

    def test_project_creation(self):
        """Test creating a Project instance."""
        project = Project(
            name="Knowledge Graph System",
            description="A system for managing knowledge graphs",
            status="Active"
        )
        
        assert project.name == "Knowledge Graph System"
        assert project.description == "A system for managing knowledge graphs"
        assert project.status == "Active"

    def test_project_status_validation(self):
        """Test project status validation."""
        # Valid statuses
        for status in ["Planning", "Active", "Completed", "On Hold", "Cancelled"]:
            project = Project(name="Test Project", status=status)
            assert project.status == status
        
        # Invalid status should raise error
        with pytest.raises(ValueError, match="Status must be one of"):
            Project(name="Test Project", status="Invalid")

    def test_project_from_dict(self):
        """Test creating Project from dictionary."""
        data = {
            "name": "Web Application",
            "description": "E-commerce web application",
            "status": "Active",
            "start_date": "2024-01-01",
            "technologies": ["Python", "React", "PostgreSQL"]
        }
        
        project = Project.from_dict(data)
        
        assert project.name == "Web Application"
        assert project.status == "Active"
        assert project.start_date == "2024-01-01"
        assert project.technologies == ["Python", "React", "PostgreSQL"]


@pytest.mark.unit
class TestLocation:
    """Test cases for Location model."""

    def test_location_creation(self):
        """Test creating a Location instance."""
        location = Location(
            name="New York City",
            country="United States",
            region="North America"
        )
        
        assert location.name == "New York City"
        assert location.country == "United States"
        assert location.region == "North America"

    def test_location_with_coordinates(self):
        """Test creating Location with coordinates."""
        location = Location(
            name="San Francisco",
            country="United States",
            latitude=37.7749,
            longitude=-122.4194
        )
        
        assert location.name == "San Francisco"
        assert location.latitude == 37.7749
        assert location.longitude == -122.4194


@pytest.mark.unit
class TestDocument:
    """Test cases for Document model."""

    def test_document_creation(self):
        """Test creating a Document instance."""
        doc = Document(
            title="Machine Learning Guide",
            doc_type="Article",
            content="A comprehensive guide to machine learning"
        )
        
        assert doc.title == "Machine Learning Guide"
        assert doc.doc_type == "Article"
        assert doc.content == "A comprehensive guide to machine learning"

    def test_document_type_validation(self):
        """Test document type validation."""
        # Valid types
        for doc_type in ["Article", "Book", "Paper", "Report", "Tutorial", "Other"]:
            doc = Document(title="Test Document", doc_type=doc_type)
            assert doc.doc_type == doc_type
        
        # Invalid type should raise error
        with pytest.raises(ValueError, match="Document type must be one of"):
            Document(title="Test Document", doc_type="Invalid")


@pytest.mark.unit
class TestEvent:
    """Test cases for Event model."""

    def test_event_creation(self):
        """Test creating an Event instance."""
        event = Event(
            name="AI Conference 2024",
            event_type="Conference",
            date="2024-06-15"
        )
        
        assert event.name == "AI Conference 2024"
        assert event.event_type == "Conference"
        assert event.date == "2024-06-15"

    def test_event_type_validation(self):
        """Test event type validation."""
        # Valid types
        for event_type in ["Conference", "Workshop", "Meeting", "Seminar", "Training", "Other"]:
            event = Event(name="Test Event", event_type=event_type)
            assert event.event_type == event_type
        
        # Invalid type should raise error
        with pytest.raises(ValueError, match="Event type must be one of"):
            Event(name="Test Event", event_type="Invalid")
