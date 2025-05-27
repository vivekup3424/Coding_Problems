#!/usr/bin/env python3
"""
Recommendation System Example

This script demonstrates building a simple recommendation system using graph data:
- Skill-based recommendations
- People you might know
- Organization recommendations
- Learning path suggestions
- Collaboration opportunities

Run this after setting up the database and generating sample data.
"""

import sys
import os
from pathlib import Path
from collections import defaultdict, Counter

# Add the src directory to the path
sys.path.append(str(Path(__file__).parent.parent / "src"))

from graph.database import GraphDatabase
from graph.operations import KnowledgeGraphManager


class GraphRecommendationEngine:
    """A simple recommendation engine using graph data."""
    
    def __init__(self, kg_manager: KnowledgeGraphManager):
        self.kg = kg_manager
    
    def recommend_people_to_know(self, person_id: str, limit: int = 5):
        """Recommend people based on mutual connections and shared interests."""
        print(f"👥 People You Might Know")
        print("-" * 30)
        
        # Get the person's current connections
        current_connections = set()
        relationships = self.kg.get_relationships(person_id)
        for rel in relationships:
            if 'Person' in rel.get('other_labels', []):
                current_connections.add(rel['other']['id'])
        
        # Find people with mutual connections
        mutual_connection_scores = defaultdict(int)
        
        # Check connections of connections (2-hop)
        for connected_person_id in current_connections:
            second_hop = self.kg.get_relationships(connected_person_id)
            for rel in second_hop:
                if ('Person' in rel.get('other_labels', []) and 
                    rel['other']['id'] not in current_connections and 
                    rel['other']['id'] != person_id):
                    mutual_connection_scores[rel['other']['id']] += 1
        
        # Get people with shared skills
        person_skills = set()
        person_relationships = self.kg.get_relationships(person_id)
        for rel in person_relationships:
            if rel['r']['type'] == 'HAS_SKILL':
                person_skills.add(rel['other']['id'])
        
        skill_similarity_scores = defaultdict(int)
        if person_skills:
            # Find other people with similar skills
            for skill_id in person_skills:
                skill_relationships = self.kg.get_relationships(skill_id)
                for rel in skill_relationships:
                    if (rel['r']['type'] == 'HAS_SKILL' and 
                        'Person' in rel.get('other_labels', []) and
                        rel['other']['id'] not in current_connections and
                        rel['other']['id'] != person_id):
                        skill_similarity_scores[rel['other']['id']] += 1
        
        # Combine scores
        all_candidates = set(mutual_connection_scores.keys()) | set(skill_similarity_scores.keys())
        recommendations = []
        
        for candidate_id in all_candidates:
            mutual_score = mutual_connection_scores[candidate_id]
            skill_score = skill_similarity_scores[candidate_id]
            total_score = mutual_score * 2 + skill_score  # Weight mutual connections more
            
            candidate_data = self.kg.get_node_by_id(candidate_id)
            if candidate_data:
                recommendations.append({
                    'person': candidate_data['n'],
                    'mutual_connections': mutual_score,
                    'shared_skills': skill_score,
                    'total_score': total_score
                })
        
        # Sort by total score
        recommendations.sort(key=lambda x: x['total_score'], reverse=True)
        
        if recommendations:
            for i, rec in enumerate(recommendations[:limit], 1):
                person = rec['person']
                name = person.get('name', 'Unknown')
                location = person.get('location', 'Unknown location')
                mutual = rec['mutual_connections']
                skills = rec['shared_skills']
                
                print(f"   {i}. {name} ({location})")
                print(f"      Mutual connections: {mutual}, Shared skills: {skills}")
        else:
            print("   No recommendations found based on current network")
    
    def recommend_skills_to_learn(self, person_id: str, limit: int = 5):
        """Recommend skills based on connections and career patterns."""
        print(f"\n🎯 Skills You Should Learn")
        print("-" * 30)
        
        # Get person's current skills
        current_skills = set()
        relationships = self.kg.get_relationships(person_id)
        for rel in relationships:
            if rel['r']['type'] == 'HAS_SKILL':
                current_skills.add(rel['other']['id'])
        
        # Get person's organization and similar people
        person_org = None
        similar_people = []
        
        for rel in relationships:
            if rel['r']['type'] == 'WORKS_FOR':
                person_org = rel['other']['id']
                break
        
        # Find people in same organization
        if person_org:
            org_relationships = self.kg.get_relationships(person_org)
            for rel in org_relationships:
                if (rel['r']['type'] == 'EMPLOYS' and 
                    'Person' in rel.get('other_labels', []) and
                    rel['other']['id'] != person_id):
                    similar_people.append(rel['other']['id'])
        
        # Count skills of similar people
        skill_popularity = defaultdict(int)
        skill_names = {}
        
        for similar_person_id in similar_people:
            similar_relationships = self.kg.get_relationships(similar_person_id)
            for rel in similar_relationships:
                if (rel['r']['type'] == 'HAS_SKILL' and 
                    rel['other']['id'] not in current_skills):
                    skill_id = rel['other']['id']
                    skill_popularity[skill_id] += 1
                    if skill_id not in skill_names:
                        skill_data = self.kg.get_node_by_id(skill_id)
                        if skill_data:
                            skill_names[skill_id] = skill_data['n']
        
        # Also look at trending skills globally
        all_skills = self.kg.get_nodes_by_type("Skill")
        global_skill_popularity = defaultdict(int)
        
        for skill in all_skills:
            skill_id = skill['n']['id']
            if skill_id not in current_skills:
                skill_relationships = self.kg.get_relationships(skill_id)
                person_count = sum(1 for rel in skill_relationships 
                                 if rel['r']['type'] == 'HAS_SKILL' and 'Person' in rel.get('other_labels', []))
                global_skill_popularity[skill_id] = person_count
                if skill_id not in skill_names:
                    skill_names[skill_id] = skill['n']
        
        # Combine recommendations
        recommendations = []
        
        # Prioritize skills from similar people
        for skill_id, count in skill_popularity.items():
            if skill_id in skill_names:
                skill = skill_names[skill_id]
                recommendations.append({
                    'skill': skill,
                    'reason': f'Popular among colleagues ({count} people)',
                    'priority': count * 10  # Higher weight for colleague skills
                })
        
        # Add globally popular skills
        sorted_global = sorted(global_skill_popularity.items(), key=lambda x: x[1], reverse=True)
        for skill_id, count in sorted_global[:10]:
            if skill_id in skill_names and skill_id not in [r['skill']['id'] for r in recommendations]:
                skill = skill_names[skill_id]
                recommendations.append({
                    'skill': skill,
                    'reason': f'Trending globally ({count} people)',
                    'priority': count
                })
        
        # Sort by priority
        recommendations.sort(key=lambda x: x['priority'], reverse=True)
        
        if recommendations:
            for i, rec in enumerate(recommendations[:limit], 1):
                skill = rec['skill']
                name = skill.get('name', 'Unknown')
                category = skill.get('category', 'Unknown')
                reason = rec['reason']
                
                print(f"   {i}. {name} ({category})")
                print(f"      {reason}")
        else:
            print("   No skill recommendations available")
    
    def recommend_organizations(self, person_id: str, limit: int = 3):
        """Recommend organizations based on skills and network."""
        print(f"\n🏢 Organizations You Might Like")
        print("-" * 30)
        
        # Get person's skills
        person_skills = set()
        relationships = self.kg.get_relationships(person_id)
        for rel in relationships:
            if rel['r']['type'] == 'HAS_SKILL':
                person_skills.add(rel['other']['id'])
        
        # Find organizations where people with similar skills work
        org_scores = defaultdict(int)
        org_data = {}
        
        if person_skills:
            for skill_id in person_skills:
                # Find people with this skill
                skill_relationships = self.kg.get_relationships(skill_id)
                for rel in skill_relationships:
                    if rel['r']['type'] == 'HAS_SKILL' and 'Person' in rel.get('other_labels', []):
                        person_with_skill_id = rel['other']['id']
                        
                        # Find their organizations
                        person_relationships = self.kg.get_relationships(person_with_skill_id)
                        for person_rel in person_relationships:
                            if (person_rel['r']['type'] == 'WORKS_FOR' and 
                                'Organization' in person_rel.get('other_labels', [])):
                                org_id = person_rel['other']['id']
                                org_scores[org_id] += 1
                                if org_id not in org_data:
                                    org_data[org_id] = person_rel['other']
        
        # Sort organizations by score
        sorted_orgs = sorted(org_scores.items(), key=lambda x: x[1], reverse=True)
        
        if sorted_orgs:
            for i, (org_id, score) in enumerate(sorted_orgs[:limit], 1):
                if org_id in org_data:
                    org = org_data[org_id]
                    name = org.get('name', 'Unknown')
                    industry = org.get('industry', 'Unknown')
                    location = org.get('location', 'Unknown')
                    
                    print(f"   {i}. {name}")
                    print(f"      Industry: {industry}, Location: {location}")
                    print(f"      {score} people with your skills work here")
        else:
            print("   No organization recommendations available")
    
    def recommend_learning_path(self, person_id: str):
        """Suggest a learning path based on current skills and career goals."""
        print(f"\n📚 Suggested Learning Path")
        print("-" * 30)
        
        # Get current skills
        current_skills = []
        relationships = self.kg.get_relationships(person_id)
        for rel in relationships:
            if rel['r']['type'] == 'HAS_SKILL':
                skill_data = self.kg.get_node_by_id(rel['other']['id'])
                if skill_data:
                    current_skills.append(skill_data['n'])
        
        if not current_skills:
            print("   No current skills found. Start with fundamental skills!")
            return
        
        # Analyze skill categories
        skill_categories = Counter()
        for skill in current_skills:
            category = skill.get('category', 'Unknown')
            skill_categories[category] += 1
        
        print(f"📊 Your Current Skill Profile:")
        for category, count in skill_categories.most_common():
            print(f"   {category}: {count} skills")
        
        # Find skill gaps in dominant category
        dominant_category = skill_categories.most_common(1)[0][0] if skill_categories else None
        
        if dominant_category:
            print(f"\n🎯 Recommended Next Steps in {dominant_category}:")
            
            # Find related skills in the same category
            all_skills = self.kg.get_nodes_by_type("Skill")
            related_skills = []
            
            current_skill_names = {skill.get('name', '') for skill in current_skills}
            
            for skill in all_skills:
                if (skill['n'].get('category') == dominant_category and 
                    skill['n'].get('name') not in current_skill_names):
                    
                    # Calculate popularity
                    skill_relationships = self.kg.get_relationships(skill['n']['id'])
                    popularity = sum(1 for rel in skill_relationships 
                                   if rel['r']['type'] == 'HAS_SKILL')
                    
                    related_skills.append({
                        'skill': skill['n'],
                        'popularity': popularity
                    })
            
            # Sort by popularity
            related_skills.sort(key=lambda x: x['popularity'], reverse=True)
            
            for i, skill_info in enumerate(related_skills[:3], 1):
                skill = skill_info['skill']
                name = skill.get('name', 'Unknown')
                description = skill.get('description', 'No description')
                popularity = skill_info['popularity']
                
                print(f"   {i}. {name}")
                print(f"      {description[:100]}...")
                print(f"      {popularity} people have this skill")
    
    def find_collaboration_opportunities(self, person_id: str, limit: int = 3):
        """Find potential collaboration opportunities."""
        print(f"\n🤝 Collaboration Opportunities")
        print("-" * 30)
        
        # Get person's skills
        person_skills = set()
        relationships = self.kg.get_relationships(person_id)
        for rel in relationships:
            if rel['r']['type'] == 'HAS_SKILL':
                person_skills.add(rel['other']['id'])
        
        # Find projects that might need these skills
        projects = self.kg.get_nodes_by_type("Project")
        
        if projects:
            print("🚀 Projects that might need your skills:")
            project_count = 0
            
            for project in projects[:limit * 2]:  # Check more projects to find good matches
                project_id = project['n']['id']
                project_name = project['n'].get('name', 'Unknown Project')
                project_status = project['n'].get('status', 'Unknown')
                
                # Find people working on this project
                project_relationships = self.kg.get_relationships(project_id)
                project_people = []
                for rel in project_relationships:
                    if (rel['r']['type'] == 'WORKS_ON' and 
                        'Person' in rel.get('other_labels', []) and
                        rel['other']['id'] != person_id):
                        project_people.append(rel['other']['id'])
                
                if project_people and project_count < limit:
                    # Check if any project members have complementary skills
                    complementary_skills = set()
                    for person_id_in_project in project_people:
                        person_relationships = self.kg.get_relationships(person_id_in_project)
                        for rel in person_relationships:
                            if (rel['r']['type'] == 'HAS_SKILL' and 
                                rel['other']['id'] not in person_skills):
                                complementary_skills.add(rel['other']['id'])
                    
                    if complementary_skills:
                        project_count += 1
                        print(f"   {project_count}. {project_name} (Status: {project_status})")
                        print(f"      Team size: {len(project_people)} people")
                        print(f"      Complementary skills available: {len(complementary_skills)}")
            
            if project_count == 0:
                print("   No specific project matches found")
        
        # Also suggest based on skill complementarity
        print(f"\n💡 People with Complementary Skills:")
        
        # Find people with different but related skills
        complementary_people = []
        all_people = self.kg.get_nodes_by_type("Person")
        
        for person in all_people[:20]:  # Check first 20 people
            if person['n']['id'] == person_id:
                continue
                
            other_person_skills = set()
            other_relationships = self.kg.get_relationships(person['n']['id'])
            for rel in other_relationships:
                if rel['r']['type'] == 'HAS_SKILL':
                    other_person_skills.add(rel['other']['id'])
            
            # Calculate skill overlap and complementarity
            overlap = len(person_skills & other_person_skills)
            complementary = len(other_person_skills - person_skills)
            
            if overlap > 0 and complementary > 0:  # Some overlap, some new skills
                complementary_people.append({
                    'person': person['n'],
                    'overlap': overlap,
                    'complementary': complementary,
                    'score': overlap + complementary * 2  # Weight new skills more
                })
        
        # Sort by score
        complementary_people.sort(key=lambda x: x['score'], reverse=True)
        
        for i, person_info in enumerate(complementary_people[:3], 1):
            person = person_info['person']
            name = person.get('name', 'Unknown')
            overlap = person_info['overlap']
            complementary = person_info['complementary']
            
            print(f"   {i}. {name}")
            print(f"      Shared skills: {overlap}, New skills they bring: {complementary}")


def main():
    """Run the recommendation system example."""
    print("🎯 Knowledge Graph - Recommendation System Example")
    print("=" * 60)
    
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
    
    # Get a sample person for recommendations
    people = kg.get_nodes_by_type("Person")
    if not people:
        print("❌ No people found in the database!")
        return
    
    # Let user choose a person or pick the first one
    print(f"\n👥 Found {len(people)} people in the database")
    print("Sample people:")
    for i, person in enumerate(people[:5], 1):
        name = person['n'].get('name', 'Unknown')
        location = person['n'].get('location', 'Unknown')
        print(f"   {i}. {name} ({location})")
    
    try:
        choice = input(f"\nEnter person number (1-{min(5, len(people))}) or press Enter for person 1: ").strip()
        if choice:
            person_index = int(choice) - 1
            if person_index < 0 or person_index >= len(people):
                person_index = 0
        else:
            person_index = 0
    except ValueError:
        person_index = 0
    
    selected_person = people[person_index]['n']
    person_id = selected_person['id']
    person_name = selected_person.get('name', 'Unknown')
    
    print(f"\n🎯 Generating recommendations for: {person_name}")
    print("=" * 60)
    
    # Create recommendation engine
    rec_engine = GraphRecommendationEngine(kg)
    
    # Generate all types of recommendations
    rec_engine.recommend_people_to_know(person_id)
    rec_engine.recommend_skills_to_learn(person_id)
    rec_engine.recommend_organizations(person_id)
    rec_engine.recommend_learning_path(person_id)
    rec_engine.find_collaboration_opportunities(person_id)
    
    print("\n✨ Recommendation system example completed!")
    print("\nHow Recommendations Work:")
    print("- People recommendations: Based on mutual connections and shared skills")
    print("- Skill recommendations: Based on colleague skills and global trends")
    print("- Organization recommendations: Based on where people with similar skills work")
    print("- Learning paths: Based on your current skill profile and gaps")
    print("- Collaborations: Based on complementary skills and project opportunities")
    
    print("\nNext steps:")
    print("- Try different people to see how recommendations vary")
    print("- Explore visualization examples: python examples/visualization_examples.py")
    print("- Use the interactive mode: python main.py interactive")
    
    # Close database connection
    db.close()


if __name__ == "__main__":
    main()
