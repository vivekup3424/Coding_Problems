FROM python:3.9-slim-bookworm

RUN apt-get update && apt-get install -y \
    curl \
    bash \
    gpg \
    lsb-release \
    ca-certificates \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

RUN curl https://raw.githubusercontent.com/fluent/fluent-bit/master/install.sh | sh
ENV PATH="/opt/fluent-bit/bin:${PATH}"

RUN mkdir -p /fluent-bit/etc

WORKDIR /app

# Copy Fluent Bit configuration files from the parent directory
# Note: Build context should be set to parent directory for this to work
COPY fluentbit-conf/fluent-bit.conf /fluent-bit/etc/
COPY fluentbit-conf/parsers.conf /fluent-bit/etc/
COPY fluentbit-conf/plugins.conf /fluent-bit/etc/

# Copy Python requirements and install
COPY fluentbit-custom/requirements.txt .
RUN pip3 install -r requirements.txt

# Copy application files
COPY fluentbit-custom/python-server.py .
COPY fluentbit-custom/start.sh .

# Make start script executable
RUN chmod +x start.sh

# Create log directory for application logs that Fluent Bit will read
RUN mkdir -p /app/logs

ENTRYPOINT ["./start.sh"]


