/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <WiFi.h>
#include <BME280I2C.h>
#include <Wire.h>

const char* ssid     = "IT";
const char* password = "it_support2011";

const char* TOKEN = "A1E-ACOZLAZ17KiBj10yR4HdVl3FcF9FPE"; // Put here your TOKEN
const char* DEVICE_LABEL = "Heltec_Mitja"; // Your device label
const char* VARIABLE_LABEL = "temperature"; // Your variable label
const char* USER_AGENT = "ESP32";
const char* VERSION = "1.0";
const char* HTTPSERVER = "things.ubidots.com";
int HTTPPORT = 80;

WiFiClient clientUbi;
BME280I2C bme;

/********************************
 * Auxiliar Functions
 *******************************/
/**
 * Gets the length of the body
 * @arg variable the body of type char
 * @return dataLen the length of the variable
 */
int dataLen(char* variable) {
  uint8_t dataLen = 0;
  for (int i = 0; i <= 250; i++) {
    if (variable[i] != '\0') {
      dataLen++;
    } else {
      break;
    }
  }
  return dataLen;
}

void setup()
{
    Serial.begin(115200);
    delay(10);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    WiFi.setAutoReconnect(true);
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    Wire.begin();

  while(!bme.begin())
  {
    Serial.println("Could not find BME280 sensor!");
    delay(1000);
  }

  // bme.chipID(); // Deprecated. See chipModel().
  switch(bme.chipModel())
  {
     case BME280::ChipModel_BME280:
       Serial.println("Found BME280 sensor! Success.");
       break;
     case BME280::ChipModel_BMP280:
       Serial.println("Found BMP280 sensor! No Humidity available.");
       break;
     default:
       Serial.println("Found UNKNOWN sensor! Error!");
  }
}

void loop() {

  char* body = (char *) malloc(sizeof(char) * 150);
  char* data = (char *) malloc(sizeof(char) * 300);
  /* Space to store values to send */
  char str_val[10];

  /* Read the sensor from the analog input*/
  float temp(NAN), hum(NAN), pres(NAN), sensor_value(NAN);

   BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
   BME280::PresUnit presUnit(BME280::PresUnit_Pa);

   bme.read(pres, sensor_value, hum, tempUnit, presUnit);

  /*---- Transforms the values of the sensors to char type -----*/
  /* 4 is mininum width, 2 is precision; float value is copied onto str_val*/
  dtostrf(sensor_value, 4, 2, str_val);

  /* Builds the body to be send into the request*/ 
  sprintf(body, "{\"%s\":%s}", VARIABLE_LABEL, str_val);
  
  /* Builds the HTTP request to be POST */
  sprintf(data, "POST /api/v1.6/devices/%s", DEVICE_LABEL);
  sprintf(data, "%s HTTP/1.1\r\n", data);
  sprintf(data, "%sHost: things.ubidots.com\r\n", data);
  sprintf(data, "%sUser-Agent: %s/%s\r\n", data, USER_AGENT, VERSION);
  sprintf(data, "%sX-Auth-Token: %s\r\n", data, TOKEN);
  sprintf(data, "%sConnection: close\r\n", data);
  sprintf(data, "%sContent-Type: application/json\r\n", data);
  sprintf(data, "%sContent-Length: %d\r\n\r\n", data, dataLen(body));
  sprintf(data, "%s%s\r\n\r\n", data, body);

  /* Initial connection */
  clientUbi.connect(HTTPSERVER, HTTPPORT);

  /* Verify the client connection */
  if (clientUbi.connect(HTTPSERVER, HTTPPORT)) {
        Serial.println(F("Posting your variables: "));
        Serial.println(data);
        /* Send the HTTP Request */
        clientUbi.print(data);
  }

  /* While the client is available read the response of the server */
  while (clientUbi.available()) {
        char c = clientUbi.read();
        Serial.write(c);
  }
   /* Free memory */
  free(data);
  free(body);
  /* Stop the client */
  clientUbi.stop();
  /* Five second delay */
  delay(50000);
}
