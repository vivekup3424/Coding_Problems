FROM fluentd:v1.18.0-debian-1.0

# Update package list and install necessary packages
RUN apt-get update && apt-get install -y \
    build-essential \
    ruby-dev \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

RUN fluent-gem install fluent-plugin-elasticsearch

# Copy configuration files
COPY fluentd.conf /fluentd/etc/

# Expose the port for forward input
EXPOSE 24224

# Set the entrypoint
ENTRYPOINT ["fluentd"]
CMD ["-c", "/fluentd/etc/fluent.conf", "-v"] 