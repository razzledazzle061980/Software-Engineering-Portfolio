# Using Node v10
FROM node:10.24.1

# Maintainer
LABEL maintainer="Eric Wallace"

# Create application directory
WORKDIR /usr/src/web

# Install application dependencies
COPY package*.json ./

# Install Angular
RUN npm install -g @angular/cli@v6

# Install Node modules
RUN npm install

RUN npm audit fix

# Bundle application source
COPY . .

# Expose port 4200 for access from outside container
EXPOSE 4200

# Command to start application
CMD ng serve --host 0.0.0.0 --port 4200
