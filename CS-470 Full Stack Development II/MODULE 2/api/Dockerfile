# Using Node v10
FROM node:20.1

# Maintainer
LABEL maintainer="Eric Wallace"

# Create application directory
WORKDIR /usr/src/api

# Install application dependencies

COPY package*.json ./

# Install Node modules
RUN npm install

# Bundle application source
COPY . .

# Expose port 4200 for access from outside container
EXPOSE 3000

# Command to start application
CMD ["node", "server/server.js"]
