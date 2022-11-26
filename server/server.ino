
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

ESP8266WebServer server;
uint8_t pin_led = D0;
char* ssid = "Ishna";
char* password = "even2468";

void setup()
{
  pinMode(pin_led, OUTPUT);
  WiFi.begin(ssid,password);
  Serial.begin(115200);
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/",[](){server.send(200,"text/plain","Hello World!");});
  server.on("/toggle",toggleLED);
  server.on("/jblink",jBlinkLED);
  server.on("/qblink",qBlinkLED);
  server.begin();
}

void loop()
{
  server.handleClient();
}

void toggleLED()
{
  digitalWrite(pin_led,!digitalRead(pin_led));
  server.send(204,"");
}

void jBlinkLED()
{
  String data = server.arg("plain");
  StaticJsonBuffer<200> jBuffer;
  JsonObject& jObject = jBuffer.parseObject(data);
  String del = jObject["pause"];
  String n = jObject["times"];
  for (int i=0; i<n.toInt();i++)
  {
   digitalWrite(pin_led,!digitalRead(pin_led));
   delay(del.toInt()); 
  }
  server.send(200,"text/plain","GOT THE DATA!"); 
}

void qBlinkLED()
{
  String del = server.arg("pause");
  String n = server.arg("times");
  for (int i=0; i<n.toInt();i++)
  {
   digitalWrite(pin_led,!digitalRead(pin_led));
   delay(del.toInt()); 
  }
}
