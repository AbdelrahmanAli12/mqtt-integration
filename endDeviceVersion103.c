#include <lmic.h>
#include <hal/hal.h>
#include <SPI.h>
#include <NewPing.h>

#define TRIGGER_PIN 3
#define ECHO_PIN 4
#define MAX_DISTANCE 500 // Maximum distance (in centimeters) to measure

bool joined = false;

// AppEUI JoinEUI must be in little-endian format
static const u1_t PROGMEM APPEUI[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

// EndDeviceEUI must be in little-endian format
static const u1_t PROGMEM DEVEUI[8] = {0x3C, 0x87, 0x05, 0xD0, 0x7E, 0xD5, 0xB3, 0x70};

// My APPKey must be in big endian format since it is a block of memory, endianness does not really apply
static const u1_t PROGMEM APPKEY[16] = {0xA0, 0x89, 0xCA, 0x22, 0x9C, 0xD6, 0xC6, 0xED, 0x45, 0xB7, 0xBA, 0xA5, 0xC4, 0x1C, 0x91, 0xB0};

// Call back functions to retrieve the session keys
void os_getArtEui(u1_t *buf) { memcpy_P(buf, APPEUI, 8); }
void os_getDevEui(u1_t *buf) { memcpy_P(buf, DEVEUI, 8); }
void os_getDevKey(u1_t *buf) { memcpy_P(buf, APPKEY, 16); }

// The object which is going to be sent to the server
static osjob_t sendjob;

// Create a NewPing object for the ultrasonic sensor
static NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

// Schedule TX every this many seconds (might become longer due to duty cycle limitations).
const unsigned TX_INTERVAL = 30;

// Pin mapping for Arduino Uno
const lmic_pinmap lmic_pins = {
    .nss = 10,
    .rxtx = LMIC_UNUSED_PIN,
    .rst = 9,
    .dio = {2, 6, 7},
};

void onEvent(ev_t ev)
{
  switch (ev)
  {
  case EV_TXCOMPLETE:
    Serial.println(F("EV_TXCOMPLETE (includes waiting for RX windows)"));
    if (LMIC.txrxFlags & TXRX_ACK)
    {
      Serial.println(F("Received ack"));
    }
    if (LMIC.dataLen != 0)
    {
      Serial.print(F("Received "));
      Serial.print(LMIC.dataLen);
      Serial.println(F(" bytes of payload"));
    }
    // Schedule next transmission
    os_setTimedCallback(&sendjob, os_getTime() + sec2osticks(TX_INTERVAL), do_send);
    break;
  }
}

void do_send(osjob_t *j)
{
  // Measure distance with the ultrasonic sensor
  int distance = sonar.ping_cm();
  // Print the reading in the serial monitor
  Serial.print(F("Distance: "));
  Serial.print(distance);
  Serial.println(F(" cm"));
  // Prepare the payload to send
  byte payload[2];
  payload[0] = highByte(distance);
  payload[1] = lowByte(distance);
  // Prepare the frame buffer
  static uint8_t message[64];
  memcpy(message, payload, sizeof(payload));
  // Send the payload using LMIC
  LMIC_setTxData2(1, message, sizeof(payload), 0);
  Serial.println(F("Packet queued for transmission"));
  // Schedule next transmission after a delay of TX_INTERVAL seconds
  os_setTimedCallback(j, os_getTime() + sec2osticks(TX_INTERVAL), do_send);
}

void setup()
{
  Serial.begin(9600);
  Serial.println(F("Starting"));
  // LMIC init
  os_init();
  // Reset the MAC state. Session and pending data transfers will be discarded.
  LMIC_reset();
  // Start job (sending automatically starts OTAA too)
  do_send(&sendjob);
}

void loop()
{
  os_runloop_once();
  // Check if the device has joined the network
  if (!joined && LMIC.devaddr != 0)
  {
    joined = true;
    Serial.println(F("Joined the network"));
    // Schedule the initial transmission after a delay of 1 second
    os_setTimedCallback(&sendjob, os_getTime() + sec2osticks(1), do_send);
  }
}
