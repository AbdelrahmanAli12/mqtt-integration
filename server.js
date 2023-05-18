var express = require("express");
var app = express();
app.use(express.static("public")); //Procedure to set public folder contain process files (css,image,.js,..)
app.set("view engine", "ejs"); // Use ejs instead of html
app.set("views", "./views"); // view folder contain .ejs files

// Parse URL-encoded bodies (as sent by HTML forms)
const bodyParser = require("body-parser");
app.use(bodyParser.urlencoded({ extended: true }));

// Create server
var server = require("http").Server(app);
var io = require("socket.io")(server);
server.listen(process.env.PORT || 3000, () => {
  console.log(`listening on:${3000}`);
});

// MQTT setup
var mqtt = require("mqtt");

var client;

// Global variable to save data
var globalMQTT;

// SOCKET
io.on("connection", function (socket) {
  console.log("Client connected: " + socket.id);

  socket.on("disconnect", function () {
    console.log(socket.id + " disconnected");
  });

  socket.on("REQUEST_GET_DATA", function () {
    socket.emit("SEND_DATA", globalMQTT);
  });

  function intervalFunc() {
    socket.emit("SEND_DATA", globalMQTT);
  }
  setInterval(intervalFunc, 2000);
});

// Setup load ejs file to display on Browsers
app.get("/", function (req, res) {
  res.render("login");
});

app.post("/getData", function (req, res) {
  const { cluster, mqttPort, mqttClientId, mqttUsername, mqttPassword } =
    req.body;

  // Update MQTT options with the submitted values
  var options = {
    port: mqttPort,
    clientId: mqttClientId + Math.random().toString(16).substring(2, 8),
    username: mqttUsername,
    password: mqttPassword,
    keepalive: 60,
    reconnectPeriod: 1000,
    protocolId: "MQIsdp",
    protocolVersion: 3,
    clean: true,
    encoding: "utf8",
  };
  var urlbroker = `https://${cluster}.cloud.thethings.network`;
  connectToMQTT(urlbroker, options);

  res.render("dashboard", { mqttData: globalMQTT, username: mqttUsername });
});

function connectToMQTT(urlbroker, options) {
  client = mqtt.connect(urlbroker, options);

  // MQTT setup
  client.on("connect", function () {
    console.log("Client connected to TTN");
    client.subscribe("#");
  });

  client.on("error", function (err) {
    console.log(err);
  });

  client.on("message", function (topic, message) {
    const payload = JSON.parse(message.toString());
    console.log("Data from TTN: ", payload);
    if (payload?.uplink_message?.decoded_payload) {
      const distance = payload.uplink_message.decoded_payload.distance;
      globalMQTT = distance;
    }
    console.log(`Distance: ${globalMQTT}`);
  });
}
