# Description
This is a Node.js application that uses Express.js and Socket.io to build a real-time dashboard for displaying MQTT data from The Things Network (TTN). Users can enter MQTT connection information, connect to the TTN MQTT broker, and view the received data on a web dashboard.


# Installation
Follow these steps to run the application:

Download the source code or clone the repository.

Run the following command to install the required dependencies:

`npm install`

Set the necessary environment variables:
PORT: The port on which the server will listen for connections. If no value is specified, the default value is 3000.
Run the following command to start the server:

`node server.js`

Navigate to http://localhost:3000 (replace 3000 with the configured port if different) in a web browser.

# Usage
When you open the application in a web browser, you will be taken to the login page.
Fill out the form with the necessary MQTT connection information.
You will be redirected to the dashboard page, which will display the received MQTT data.
The dashboard will automatically refresh every 2 seconds with the most recent data from the broker.

# Code Overview
The following are the code's main components:

The Express.js framework is used to build the application.
Socket.io: Socket.io is used to implement real-time communication between the server and clients.
MQTT: The mqtt package is used to establish a MQTT connection to the TTN broker.
Views: To render dynamic views, the application employs the EJS templating engine.
The following files are included in the code:

server.js: This file configures the Express application, middleware, starts the server, and handles the MQTT connection.

views/: The EJS templates used to render the login and dashboard pages can be found in this directory.

End device C code:The code for the end device is available in the endDeviceVersion103.c file, This code is implemented to make the end device join the server using OTAA, measure distance using an ultrasonic sensor, and send it to the server.

TTN uplink formatter:In TTNformatter.js, this is the formatter used to make the server side decode the raw payload and provide us the distance value.

# Dependencies
The project relies on the following dependencies:
express: A fast, unopinionated, minimalist web framework for Node.js

socket.io: A real-time bidirectional event-based communication library

mqtt: MQTT client library for Node.js

body-parser: Middleware for parsing URL-encoded request bodies
These dependencies are listed in the package. json file and will be installed automatically when running npm install.

LMIC library: used to establish the LoRaWAN connection in the end device

NewPing library: used to configure the ultrasonic sensor

project-specific definitions

`#define CFG_eu868 1`
`#define CFG_sx1276_radio 1`
`#define DISABLE_PING`
`#define DISABLE_BEACONS`
`#define USE_IDEETRON_AES`


