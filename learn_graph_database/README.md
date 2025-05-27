# Knowledge Graph Learning Project

A comprehensive Python-based project for learning graph database concepts using Neo4j. This project provides hands-on experience with graph data modeling, querying with Cypher, visualization, and practical applications.

![Knowledge Graph](https://img.shields.io/badge/Graph%20Database-Neo4j-blue)
![Python](https://img.shields.io/badge/Python-3.11+-green)
![License](https://img.shields.io/badge/License-MIT-yellow)

## 🎯 Learning Objectives

By completing this project, you will learn:

- **Graph Database Fundamentals**: Nodes, relationships, properties, and graph data modeling
- **Cypher Query Language**: From basic queries to advanced pattern matching
- **Graph Algorithms**: Shortest paths, centrality analysis, community detection
- **Data Visualization**: Static and interactive graph visualizations
- **Practical Applications**: Recommendation systems, network analysis, knowledge management
- **Best Practices**: Performance optimization, data quality, and graph design patterns

## 🏗️ Project Structure

```
learn_graph_database/
├── 📚 src/                          # Source code
│   ├── graph/                       # Core graph database modules
│   │   ├── database.py             # Database connection and management
│   │   ├── models.py               # Node and relationship data models
│   │   └── operations.py           # High-level graph operations
│   ├── data/                       # Data generation and import
│   │   └── generator.py            # Sample data generator
│   └── visualization/              # Graph visualization tools
│       └── graph_viz.py            # Visualization capabilities
├── 🔧 api/                         # REST API
│   └── app.py                      # Flask API server
├── 📖 notebooks/                   # Jupyter learning notebooks
│   ├── 01_fundamentals.ipynb      # Basic concepts and operations
│   └── 02_advanced_queries.ipynb  # Advanced analytics and algorithms
├── 💡 examples/                    # Example scripts
│   ├── basic_operations.py        # CRUD operations demo
│   ├── graph_analysis.py          # Advanced analysis techniques
│   └── recommendation_system.py   # Recommendation engine example
├── 🐳 docker/                      # Docker configuration
│   ├── docker-compose.yml         # Neo4j setup with Docker
│   └── neo4j.conf                 # Neo4j configuration
├── 🧪 tests/                       # Comprehensive test suite
├── main.py                         # Main CLI application
└── requirements.txt                # Python dependencies
```

## 🚀 Quick Start

### Prerequisites

- Python 3.11 or higher
- Docker and Docker Compose (recommended)
- Or Neo4j installed locally

### 1. Setup the Environment

```bash
# Clone or download the project
cd learn_graph_database

# Create and activate virtual environment
python -m venv venv
source venv/bin/activate  # On Windows: venv\Scripts\activate

# Install dependencies
pip install -r requirements.txt
```

### 2. Start Neo4j Database

**Option A: Using Docker (Recommended)**

```bash
# Start Neo4j with Docker Compose
docker-compose -f docker/docker-compose.yml up -d

# Check if it's running
docker-compose -f docker/docker-compose.yml ps
```

**Option B: Local Neo4j Installation**

If you have Neo4j installed locally, make sure it's running on the default ports (7474 for HTTP, 7687 for Bolt).

### 3. Initialize the Database

```bash
# Setup database constraints and configuration
python main.py setup

# Generate sample data for learning
python main.py generate

# Verify the setup
python main.py stats
```

### 4. Start Learning!

**Interactive CLI Mode:**
```bash
python main.py interactive
```

**Jupyter Notebooks:**
```bash
# Start Jupyter
jupyter lab notebooks/

# Open and run:
# - 01_fundamentals.ipynb (start here)
# - 02_advanced_queries.ipynb (advanced topics)
```

**Example Scripts:**
```bash
python examples/basic_operations.py
python examples/graph_analysis.py
python examples/recommendation_system.py
```

**REST API:**
```bash
# Start the API server
python api/app.py

# Open browser to: http://localhost:5000
```

## 📚 Learning Path

### Phase 1: Fundamentals (Week 1-2)
1. **Start with the CLI**: `python main.py interactive`
2. **Basic Operations**: Run `examples/basic_operations.py`
3. **Jupyter Fundamentals**: Complete `01_fundamentals.ipynb`
4. **Data Exploration**: Use `python main.py explore <person_name>`

### Phase 2: Advanced Concepts (Week 3-4)
1. **Graph Analysis**: Run `examples/graph_analysis.py`
2. **Advanced Jupyter**: Complete `02_advanced_queries.ipynb`
3. **Custom Queries**: Practice with the CLI search and visualization commands
4. **API Exploration**: Use the REST API for programmatic access

### Phase 3: Applications (Week 5-6)
1. **Recommendation Systems**: Run `examples/recommendation_system.py`
2. **Custom Projects**: Build your own recommendation logic
3. **Visualization**: Create custom visualizations using the visualization module
4. **Testing**: Run the test suite to understand best practices

## 🛠️ Available Commands

### CLI Commands

```bash
# Database setup and management
python main.py setup                    # Initialize database
python main.py generate                 # Create sample data
python main.py stats                    # Show database statistics

# Data exploration
python main.py search "machine learning" # Search nodes
python main.py explore "John Doe"       # Explore person's network
python main.py visualize person "John"  # Visualize subgraph

# Interactive mode
python main.py interactive              # Start interactive session
```

### API Endpoints

- `GET /` - API documentation
- `GET /health` - Health check
- `GET /stats` - Database statistics
- `GET /nodes/<type>` - Get nodes by type
- `GET /search?q=<query>` - Search nodes
- `GET /visualize/<node_id>` - Get visualization data
- `POST /generate` - Generate sample data

Visit `http://localhost:5000` for full API documentation.

## 🧪 Testing

Run the comprehensive test suite:

```bash
# Run all tests
pytest

# Run only unit tests (fast)
pytest -m unit

# Run only integration tests (requires Neo4j)
pytest -m integration

# Run with coverage
pytest --cov=src --cov-report=html
```

## 📊 Sample Data

The generated sample data includes:

- **👥 People** (20): Software engineers, data scientists, managers
- **🏢 Organizations** (10): Tech companies of various sizes
- **💡 Concepts** (15): Technical concepts and methodologies
- **🎯 Skills** (12): Programming languages, tools, methodologies
- **📚 Projects** (8): Software development projects
- **📍 Locations** (6): Major tech cities
- **📄 Documents** (5): Technical resources
- **📅 Events** (4): Conferences and workshops

**Relationships include:**
- People working for organizations
- People having skills and interests
- People knowing each other
- People working on projects
- Skills being related to concepts
- Organizations being located in cities

## 🎨 Visualization Examples

The project includes multiple visualization approaches:

### Static Visualizations (NetworkX + Matplotlib)
- Network diagrams with customizable layouts
- Node sizing based on centrality
- Color coding by node types
- Relationship highlighting

### Interactive Visualizations (Plotly)
- Zoomable and pannable network graphs
- Hover information for nodes and edges
- Filter by node types and relationships
- Export capabilities

### Jupyter Integration
- Embedded visualizations in notebooks
- Step-by-step analysis with visual feedback
- Comparison of different algorithms

## 🔧 Configuration

### Database Configuration

Default settings (can be modified in your scripts):

```python
db_config = {
    "uri": "bolt://localhost:7687",
    "username": "neo4j",
    "password": "knowledge_graph_password",
    "database": "neo4j"
}
```

### Environment Variables

You can use environment variables to override defaults:

```bash
export NEO4J_URI="bolt://localhost:7687"
export NEO4J_USERNAME="neo4j"
export NEO4J_PASSWORD="your_password"
export NEO4J_DATABASE="neo4j"
```

## 🐳 Docker Usage

### Development with Docker

```bash
# Start only Neo4j
docker-compose -f docker/docker-compose.yml up neo4j -d

# Start full stack (Neo4j + Application)
docker-compose -f docker/docker-compose.yml --profile full up -d

# View logs
docker-compose -f docker/docker-compose.yml logs -f

# Stop services
docker-compose -f docker/docker-compose.yml down
```

### Data Persistence

Neo4j data is persisted in Docker volumes. To reset the database:

```bash
docker-compose -f docker/docker-compose.yml down -v
docker-compose -f docker/docker-compose.yml up -d
```

## 📈 Performance Tips

### Query Optimization
- Use parameters in Cypher queries to enable query plan caching
- Create appropriate indexes for frequently queried properties
- Limit result sets with `LIMIT` clauses
- Use `EXPLAIN` and `PROFILE` to analyze query performance

### Memory Management
- Configure Neo4j heap size based on your data size
- Use pagination for large result sets
- Close database connections when done
- Monitor memory usage during large data imports

### Best Practices
- Model your domain carefully - good modeling prevents performance issues
- Use meaningful relationship types and node labels
- Keep property names consistent across similar nodes
- Regular constraint and index maintenance

## 🤝 Contributing

This is a learning project, but contributions are welcome!

### Areas for Improvement
- Additional graph algorithms implementations
- More visualization options
- Extended sample datasets
- Performance benchmarking tools
- Additional example applications

### Development Setup

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Add tests for new functionality
5. Ensure all tests pass
6. Submit a pull request

## 📚 Additional Resources

### Neo4j Learning
- [Neo4j Documentation](https://neo4j.com/docs/)
- [Cypher Query Language Guide](https://neo4j.com/developer/cypher/)
- [Graph Data Modeling Guidelines](https://neo4j.com/developer/data-modeling/)

### Graph Theory
- [Introduction to Graph Theory](https://www.geeksforgeeks.org/graph-theory-tutorial/)
- [Network Analysis with Python](https://networkx.org/documentation/stable/tutorial.html)
- [Graph Algorithms Explained](https://neo4j.com/developer/graph-algorithms/)

### Python Libraries
- [NetworkX Documentation](https://networkx.org/)
- [Plotly Graph Documentation](https://plotly.com/python/network-graphs/)
- [Neo4j Python Driver](https://neo4j.com/docs/python-manual/current/)

## 📝 License

This project is licensed under the MIT License. See the LICENSE file for details.

## ❓ Troubleshooting

### Common Issues

**Q: "Cannot connect to Neo4j database"**
A: Ensure Neo4j is running and accessible on the configured port. Check Docker status or local Neo4j service.

**Q: "No module named 'src'"**
A: Make sure you're running commands from the project root directory and have activated the virtual environment.

**Q: "Empty database - no data found"**
A: Run `python main.py generate` to create sample data.

**Q: "Port 7474 already in use"**
A: Another Neo4j instance might be running. Stop it or change the port in docker-compose.yml.

**Q: "Tests failing with connection errors"**
A: Integration tests require a running Neo4j instance. Run unit tests only with `pytest -m unit`.

### Getting Help

1. Check the examples in the `examples/` directory
2. Review the Jupyter notebooks for step-by-step guidance
3. Use the interactive CLI mode for exploration
4. Check the test files for usage examples

## 🎉 What's Next?

After completing this project, consider exploring:

- **Advanced Neo4j Features**: APOC procedures, Graph Data Science library
- **Production Deployment**: Clustering, backup strategies, monitoring
- **Integration Projects**: Connect with other databases, APIs, or data sources
- **Specialized Applications**: Fraud detection, recommendation engines, knowledge graphs
- **Graph Machine Learning**: Node embeddings, graph neural networks

Happy learning! 🚀
