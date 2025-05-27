"""
Sample Data Generator for Knowledge Graph

This module generates realistic sample data to populate the knowledge graph
for learning and experimentation purposes.
"""

from typing import List, Dict, Any, Tuple
import random
from datetime import datetime, timedelta
from faker import Faker
from src.graph.models import (
    Person, Organization, Concept, Document, Location, Event, Skill, Project,
    GraphRelationship, RelationshipType
)
from src.graph.operations import KnowledgeGraphManager

# Initialize Faker for generating realistic data
fake = Faker()
Faker.seed(42)  # For reproducible results


class SampleDataGenerator:
    """
    Generates sample data for the knowledge graph to facilitate learning
    and experimentation with graph database concepts.
    """
    
    def __init__(self, kg_manager: KnowledgeGraphManager):
        """
        Initialize the data generator.
        
        Args:
            kg_manager: KnowledgeGraphManager instance
        """
        self.kg_manager = kg_manager
        self.generated_nodes = {}  # Store generated node IDs by type
        
    def generate_people(self, count: int = 20) -> List[str]:
        """Generate sample person nodes."""
        people_ids = []
        occupations = [
            "Data Scientist", "Software Engineer", "Product Manager", "Designer",
            "Marketing Manager", "Sales Representative", "Research Scientist",
            "Business Analyst", "DevOps Engineer", "Technical Writer"
        ]
        
        for _ in range(count):
            person = Person(
                first_name=fake.first_name(),
                last_name=fake.last_name(),
                email=fake.email(),
                phone=fake.phone_number(),
                age=random.randint(22, 65),
                occupation=random.choice(occupations),
                location=fake.city()
            )
            
            person_id = self.kg_manager.create_node(person)
            people_ids.append(person_id)
        
        self.generated_nodes['people'] = people_ids
        return people_ids
    
    def generate_organizations(self, count: int = 10) -> List[str]:
        """Generate sample organization nodes."""
        org_ids = []
        org_types = ["company", "university", "non-profit", "government", "startup"]
        industries = [
            "Technology", "Healthcare", "Finance", "Education", "Manufacturing",
            "Retail", "Consulting", "Media", "Transportation", "Energy"
        ]
        sizes = ["startup", "small", "medium", "large", "enterprise"]
        
        for _ in range(count):
            org = Organization(
                name=fake.company(),
                organization_type=random.choice(org_types),
                industry=random.choice(industries),
                founded_year=random.randint(1950, 2023),
                website=fake.url(),
                size=random.choice(sizes),
                headquarters=fake.city()
            )
            
            org_id = self.kg_manager.create_node(org)
            org_ids.append(org_id)
        
        self.generated_nodes['organizations'] = org_ids
        return org_ids
    
    def generate_concepts(self, count: int = 15) -> List[str]:
        """Generate sample concept nodes."""
        concept_ids = []
        
        # Predefined concepts for better learning examples
        predefined_concepts = [
            {
                "name": "Machine Learning",
                "description": "A method of data analysis that automates analytical model building",
                "category": "Computer Science",
                "complexity_level": "intermediate",
                "keywords": ["AI", "algorithms", "data", "prediction", "models"]
            },
            {
                "name": "Data Visualization",
                "description": "The graphical representation of information and data",
                "category": "Data Science",
                "complexity_level": "beginner",
                "keywords": ["charts", "graphs", "visual", "analysis", "presentation"]
            },
            {
                "name": "Blockchain",
                "description": "A distributed ledger technology for secure transactions",
                "category": "Technology",
                "complexity_level": "advanced",
                "keywords": ["cryptocurrency", "distributed", "ledger", "security", "decentralized"]
            },
            {
                "name": "Agile Development",
                "description": "An iterative approach to software development",
                "category": "Software Engineering",
                "complexity_level": "intermediate",
                "keywords": ["scrum", "iterative", "collaboration", "flexibility", "methodology"]
            },
            {
                "name": "Cloud Computing",
                "description": "On-demand availability of computer system resources",
                "category": "Technology",
                "complexity_level": "intermediate",
                "keywords": ["AWS", "Azure", "scalability", "infrastructure", "services"]
            }
        ]
        
        # Add predefined concepts
        for concept_data in predefined_concepts:
            concept = Concept(**concept_data)
            concept_id = self.kg_manager.create_node(concept)
            concept_ids.append(concept_id)
        
        # Generate additional random concepts
        categories = ["Technology", "Business", "Science", "Arts", "Engineering"]
        complexity_levels = ["beginner", "intermediate", "advanced"]
        
        for _ in range(count - len(predefined_concepts)):
            concept = Concept(
                name=fake.catch_phrase(),
                description=fake.text(max_nb_chars=200),
                category=random.choice(categories),
                complexity_level=random.choice(complexity_levels),
                keywords=[fake.word() for _ in range(random.randint(2, 6))]
            )
            
            concept_id = self.kg_manager.create_node(concept)
            concept_ids.append(concept_id)
        
        self.generated_nodes['concepts'] = concept_ids
        return concept_ids
    
    def generate_skills(self, count: int = 12) -> List[str]:
        """Generate sample skill nodes."""
        skill_ids = []
        
        predefined_skills = [
            {"name": "Python", "skill_category": "technical", "related_tools": ["Django", "Flask", "NumPy", "Pandas"]},
            {"name": "JavaScript", "skill_category": "technical", "related_tools": ["React", "Node.js", "Vue.js", "Angular"]},
            {"name": "Project Management", "skill_category": "soft", "related_tools": ["Jira", "Trello", "Asana", "Monday.com"]},
            {"name": "Data Analysis", "skill_category": "technical", "related_tools": ["SQL", "Excel", "Tableau", "Power BI"]},
            {"name": "Communication", "skill_category": "soft", "related_tools": ["Slack", "Zoom", "Teams", "Email"]},
            {"name": "Leadership", "skill_category": "soft", "related_tools": ["1-on-1s", "Team meetings", "Goal setting"]},
        ]
        
        for skill_data in predefined_skills:
            skill = Skill(**skill_data)
            skill_id = self.kg_manager.create_node(skill)
            skill_ids.append(skill_id)
        
        # Generate additional skills
        skill_categories = ["technical", "soft", "domain-specific"]
        for _ in range(count - len(predefined_skills)):
            skill = Skill(
                name=fake.job().replace(" ", "_").lower(),
                skill_category=random.choice(skill_categories),
                related_tools=[fake.word() for _ in range(random.randint(1, 4))]
            )
            
            skill_id = self.kg_manager.create_node(skill)
            skill_ids.append(skill_id)
        
        self.generated_nodes['skills'] = skill_ids
        return skill_ids
    
    def generate_projects(self, count: int = 8) -> List[str]:
        """Generate sample project nodes."""
        project_ids = []
        project_types = ["software", "research", "business", "infrastructure", "data"]
        statuses = ["planning", "active", "completed", "cancelled"]
        technologies = [
            "Python", "JavaScript", "React", "Django", "PostgreSQL", "MongoDB",
            "AWS", "Docker", "Kubernetes", "TensorFlow", "PyTorch", "Spark"
        ]
        
        for _ in range(count):
            start_date = fake.date_between(start_date='-2y', end_date='today')
            
            project = Project(
                name=fake.catch_phrase(),
                description=fake.text(max_nb_chars=300),
                project_type=random.choice(project_types),
                status=random.choice(statuses),
                start_date=start_date,
                end_date=start_date + timedelta(days=random.randint(30, 365)) if random.choice([True, False]) else None,
                budget=random.uniform(10000, 1000000) if random.choice([True, False]) else None,
                technologies=random.sample(technologies, random.randint(2, 5))
            )
            
            project_id = self.kg_manager.create_node(project)
            project_ids.append(project_id)
        
        self.generated_nodes['projects'] = project_ids
        return project_ids
    
    def generate_relationships(self) -> List[Tuple[str, str, str]]:
        """Generate relationships between existing nodes."""
        relationships = []
        
        people_ids = self.generated_nodes.get('people', [])
        org_ids = self.generated_nodes.get('organizations', [])
        concept_ids = self.generated_nodes.get('concepts', [])
        skill_ids = self.generated_nodes.get('skills', [])
        project_ids = self.generated_nodes.get('projects', [])
        
        # People work for organizations
        for person_id in people_ids:
            if random.random() < 0.8:  # 80% of people work for organizations
                org_id = random.choice(org_ids)
                relationship = GraphRelationship(
                    from_node_id=person_id,
                    to_node_id=org_id,
                    relationship_type=RelationshipType.WORKS_FOR,
                    properties={
                        "position": fake.job(),
                        "start_date": fake.date_between(start_date='-5y', end_date='today').isoformat()
                    }
                )
                self.kg_manager.create_relationship(relationship)
                relationships.append((person_id, org_id, "WORKS_FOR"))
        
        # People know each other
        for i, person1_id in enumerate(people_ids):
            # Each person knows 2-5 other people
            num_connections = random.randint(2, min(5, len(people_ids) - 1))
            potential_connections = people_ids[:i] + people_ids[i+1:]
            connections = random.sample(potential_connections, num_connections)
            
            for person2_id in connections:
                relationship = GraphRelationship(
                    from_node_id=person1_id,
                    to_node_id=person2_id,
                    relationship_type=RelationshipType.KNOWS,
                    properties={
                        "relationship_strength": random.uniform(0.3, 1.0),
                        "connection_type": random.choice(["colleague", "friend", "professional"])
                    }
                )
                self.kg_manager.create_relationship(relationship)
                relationships.append((person1_id, person2_id, "KNOWS"))
        
        # People have skills
        for person_id in people_ids:
            num_skills = random.randint(3, 7)
            person_skills = random.sample(skill_ids, min(num_skills, len(skill_ids)))
            
            for skill_id in person_skills:
                relationship = GraphRelationship(
                    from_node_id=person_id,
                    to_node_id=skill_id,
                    relationship_type=RelationshipType.HAS_SKILL,
                    properties={
                        "proficiency_level": random.choice(["beginner", "intermediate", "advanced", "expert"]),
                        "years_experience": random.randint(1, 10)
                    }
                )
                self.kg_manager.create_relationship(relationship)
                relationships.append((person_id, skill_id, "HAS_SKILL"))
        
        # People work on projects
        for project_id in project_ids:
            num_participants = random.randint(2, 6)
            participants = random.sample(people_ids, min(num_participants, len(people_ids)))
            
            for person_id in participants:
                relationship = GraphRelationship(
                    from_node_id=person_id,
                    to_node_id=project_id,
                    relationship_type=RelationshipType.PARTICIPATED_IN,
                    properties={
                        "role": random.choice(["developer", "manager", "analyst", "designer", "tester"]),
                        "contribution_level": random.choice(["minor", "moderate", "major", "lead"])
                    }
                )
                self.kg_manager.create_relationship(relationship)
                relationships.append((person_id, project_id, "PARTICIPATED_IN"))
        
        # Projects relate to concepts
        for project_id in project_ids:
            num_concepts = random.randint(1, 3)
            project_concepts = random.sample(concept_ids, min(num_concepts, len(concept_ids)))
            
            for concept_id in project_concepts:
                relationship = GraphRelationship(
                    from_node_id=project_id,
                    to_node_id=concept_id,
                    relationship_type=RelationshipType.RELATED_TO,
                    properties={
                        "relevance_score": random.uniform(0.5, 1.0)
                    }
                )
                self.kg_manager.create_relationship(relationship)
                relationships.append((project_id, concept_id, "RELATED_TO"))
        
        # Organizations collaborate
        for i, org1_id in enumerate(org_ids):
            if random.random() < 0.3:  # 30% chance of collaboration
                other_orgs = org_ids[:i] + org_ids[i+1:]
                if other_orgs:
                    org2_id = random.choice(other_orgs)
                    relationship = GraphRelationship(
                        from_node_id=org1_id,
                        to_node_id=org2_id,
                        relationship_type=RelationshipType.COLLABORATES_WITH,
                        properties={
                            "collaboration_type": random.choice(["partnership", "vendor", "client", "joint_venture"]),
                            "start_date": fake.date_between(start_date='-3y', end_date='today').isoformat()
                        }
                    )
                    self.kg_manager.create_relationship(relationship)
                    relationships.append((org1_id, org2_id, "COLLABORATES_WITH"))
        
        return relationships
    
    def generate_complete_dataset(self, 
                                people_count: int = 20,
                                org_count: int = 10,
                                concept_count: int = 15,
                                skill_count: int = 12,
                                project_count: int = 8) -> Dict[str, Any]:
        """
        Generate a complete sample dataset with all node types and relationships.
        
        Returns:
            Dictionary with generation statistics
        """
        print("Generating sample knowledge graph dataset...")
        
        # Generate nodes
        print(f"Creating {people_count} people...")
        people_ids = self.generate_people(people_count)
        
        print(f"Creating {org_count} organizations...")
        org_ids = self.generate_organizations(org_count)
        
        print(f"Creating {concept_count} concepts...")
        concept_ids = self.generate_concepts(concept_count)
        
        print(f"Creating {skill_count} skills...")
        skill_ids = self.generate_skills(skill_count)
        
        print(f"Creating {project_count} projects...")
        project_ids = self.generate_projects(project_count)
        
        # Generate relationships
        print("Creating relationships...")
        relationships = self.generate_relationships()
        
        stats = {
            "nodes_created": {
                "people": len(people_ids),
                "organizations": len(org_ids),
                "concepts": len(concept_ids),
                "skills": len(skill_ids),
                "projects": len(project_ids),
                "total": len(people_ids) + len(org_ids) + len(concept_ids) + len(skill_ids) + len(project_ids)
            },
            "relationships_created": len(relationships),
            "generation_time": datetime.now().isoformat()
        }
        
        print("Sample dataset generation complete!")
        return stats


# Example usage
if __name__ == "__main__":
    from src.graph.database import GraphDatabase, GraphConfig
    
    print("Sample Data Generator Demo")
    print("=" * 30)
    
    config = GraphConfig()
    
    try:
        with GraphDatabase(config) as db:
            kg_manager = KnowledgeGraphManager(db)
            generator = SampleDataGenerator(kg_manager)
            
            # Clear database first (optional)
            response = input("Clear existing data? (y/N): ")
            if response.lower() == 'y':
                db.clear_database()
                print("Database cleared.")
            
            # Generate sample dataset
            stats = generator.generate_complete_dataset(
                people_count=15,
                org_count=8,
                concept_count=12,
                skill_count=10,
                project_count=6
            )
            
            print("\nGeneration Statistics:")
            print(f"Total nodes: {stats['nodes_created']['total']}")
            print(f"Total relationships: {stats['relationships_created']}")
            
            # Show final database stats
            db_stats = kg_manager.get_graph_statistics()
            print(f"\nFinal database stats:")
            print(f"Nodes: {db_stats['node_count']}")
            print(f"Relationships: {db_stats['relationship_count']}")
            
    except Exception as e:
        print(f"Demo failed: {e}")
        print("Make sure Neo4j is running and accessible.")
