# Docker configuration for Neo4j Knowledge Graph Project

This directory contains Docker configurations for running the knowledge graph project with Neo4j.

## Quick Start

1. **Start Neo4j with Docker Compose:**
   ```bash
   docker-compose up -d
   ```

2. **Access Neo4j Browser:**
   - URL: http://localhost:7474
   - Username: neo4j
   - Password: knowledge_graph_password

3. **Connect from Python:**
   ```python
   from src.graph.database import GraphDatabase
   
   db = GraphDatabase(
       uri="bolt://localhost:7687",
       username="neo4j", 
       password="knowledge_graph_password"
   )
   ```

## Files

- `docker-compose.yml` - Main orchestration file
- `neo4j.conf` - Neo4j configuration
- `Dockerfile.app` - Application container (optional)

## Environment Variables

The following environment variables can be set:

- `NEO4J_AUTH` - Authentication (default: neo4j/knowledge_graph_password)
- `NEO4J_PLUGINS` - Plugins to install (default: ["apoc", "graph-data-science"])
- `NEO4J_dbms_memory_heap_initial__size` - Initial heap size
- `NEO4J_dbms_memory_heap_max__size` - Maximum heap size

## Persistent Data

Neo4j data is persisted in the `neo4j_data` Docker volume. To reset the database:

```bash
docker-compose down -v
docker-compose up -d
```

## Production Considerations

For production deployments:

1. Change default passwords
2. Configure proper memory settings
3. Set up backup strategies
4. Configure SSL/TLS
5. Set up monitoring
