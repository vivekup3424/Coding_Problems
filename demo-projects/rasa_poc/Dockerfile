FROM python:3.9-slim-bookworm

# Set environment variables
ENV PYTHONUNBUFFERED=1
ENV PYTHONDONTWRITEBYTECODE=1
ENV RASA_TELEMETRY_ENABLED=false
ENV RASA_NLU_DOCKER="YES"

# Set working directory
WORKDIR /app

# Install system dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    curl \
    git \
    rustc \
    cargo \
    && rm -rf /var/lib/apt/lists/* \
    && apt-get clean

# Copy requirements first for better caching
COPY requirements.txt .

# Install Python dependencies
RUN pip3 install --no-cache-dir --upgrade pip setuptools wheel
RUN pip3 install --no-cache-dir -r requirements.txt

# Download spaCy model
RUN python3 -m spacy download en_core_web_md

# Copy project files
COPY config.yml domain.yml endpoints.yml ./
COPY data/ ./data/
COPY actions/ ./actions/

# Create directories
RUN mkdir -p models logs

# Default command for training
CMD ["rasa", "train"]
