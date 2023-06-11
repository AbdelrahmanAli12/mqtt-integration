
# Description
This project is a Node.js application that uses Express.js and Socket.io to create a real-time dashboard for displaying MQTT data received from The Things Network (TTN). The application allows users to enter MQTT connection details, connect to the TTN MQTT broker, and display the received data on a web dashboard.

# Installation
To run the application, follow these steps:

Clone the repository or download the source code.

Install the required dependencies by running the following command:

npm install
Set up the required environment variables:

PORT: The port on which the server will listen. If not specified, the default is 3000.
Start the server by running the following command:

node server.js
Open a web browser and navigate to http://localhost:3000 (replace 3000 with the configured port if different).

# Usage
Upon accessing the application in a web browser, you will be redirected to the login page.
Enter the required MQTT connection details in the provided form.
Submit the form to establish a connection to the TTN MQTT broker and retrieve data.
You will be redirected to the dashboard page, where the received MQTT data will be displayed.
The dashboard will automatically update every 2 seconds with the latest data received from the broker.
Code Overview
The main components of the code are as follows:

Express: The application is built using the Express.js framework.
Socket.io: Real-time communication between the server and clients is implemented using Socket.io.
MQTT: The MQTT connection to the TTN broker is established using the mqtt package.
Views: The application uses the EJS templating engine to render dynamic views.
The code contains the following files:

server.js: This file sets up the Express application, configures middleware, starts the server, and handles the MQTT connection.
views/: This directory contains the EJS templates used to render the login and dashboard pages.

# End device C code

The code for the end device is available in the endDeviceVersion103.c file.

This code is implemented to make the end device join the server using OTAA, measure distance using an ultrasonic sensor, and send it to the server.

# TTN uplink formatter

In TTNformatter.js, this is the formatter used to make the server side decode the raw payload and provide us the distance value.

# Description
This project is a Node.js application that uses Express.js and Socket.io to create a real-time dashboard for displaying MQTT data received from The Things Network (TTN). The application allows users to enter MQTT connection details, connect to the TTN MQTT broker, and display the received data on a web dashboard.

# Installation
To run the application, follow these steps:

Clone the repository or download the source code.

Install the required dependencies by running the following command:

npm install
Set up the required environment variables:

PORT: The port on which the server will listen. If not specified, the default is 3000.
Start the server by running the following command:

node server.js
Open a web browser and navigate to http://localhost:3000 (replace 3000 with the configured port if different).

# Usage
Upon accessing the application in a web browser, you will be redirected to the login page.
Enter the required MQTT connection details in the provided form.
Submit the form to establish a connection to the TTN MQTT broker and retrieve data.
You will be redirected to the dashboard page, where the received MQTT data will be displayed.
The dashboard will automatically update every 2 seconds with the latest data received from the broker.
Code Overview
The main components of the code are as follows:

Express: The application is built using the Express.js framework.
Socket.io: Real-time communication between the server and clients is implemented using Socket.io.
MQTT: The MQTT connection to the TTN broker is established using the mqtt package.
Views: The application uses the EJS templating engine to render dynamic views.
The code contains the following files:

server.js: This file sets up the Express application, configures middleware, starts the server, and handles the MQTT connection.
views/: This directory contains the EJS templates used to render the login and dashboard pages.
Dependencies
The project relies on the following dependencies:

express: A fast, unopinionated, minimalist web framework for Node.js
socket.io: A real-time bidirectional event-based communication library
mqtt: MQTT client library for Node.js
body-parser: Middleware for parsing URL-encoded request bodies
These dependencies are listed in the package. json file and will be installed automatically when running npm install.

# End device C code

The code for the end device is available in the endDeviceVersion103.c file.

This code is implemented to make the end device join the server using OTAA, measure distance using an ultrasonic sensor, and send it to the server.

# TTN uplink formatter

In TTNformatter.js, this is the formatter used to make the server side decode the raw payload and provide us the distance value.


