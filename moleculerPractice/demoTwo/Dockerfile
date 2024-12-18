FROM node:20-alpine

# Install dependencies for bun installation
RUN apk add --no-cache curl bash

# Install bun
RUN curl -fsSL https://bun.sh/install | bash

# Set the working directory
WORKDIR /app

# Copy package.json and package-lock.json (or bun.lockb if applicable)
COPY package*.json ./

# Copy the rest of the application files
COPY . .

# Expose port
EXPOSE 3000

# Start the application using bun
CMD ["bun", "run", "index.js"]
