#include <WiFi.h>
#include <PubSubClient.h>

int BUT1 = 12;
int BUT2 = 14;
int LED1 = 33;
int LED2 = 32;
int trthaiButton1 = LOW;
int trthaiButton2 = LOW;
int trthaiLed1 = LOW;
int trthaiLed2 = LOW;

const char* ssid = "Xuong";
const char* password = "68686868";

#define MQTT_SERVER "broker.hivemq.com"
#define MQTT_PORT 1883
#define MQTT_USER "do-gia-h4y"
#define MQTT_PASSWORD "SkX28ttjSs3eF@5"

#define MQTT_LED1_TOPIC "MQTT_ESP32/LED1"
#define MQTT_LED2_TOPIC "MQTT_ESP32/LED2"

WiFiClient wifiClient;
PubSubClient client(wifiClient);

void setup_wifi() {
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void connect_to_broker() {
  static unsigned long lastReconnectAttempt = 0;
  if (!client.connected()) {
    unsigned long now = millis();
    if (now - lastReconnectAttempt > 5000) {
      lastReconnectAttempt = now;
      if (client.connect("ESP32", MQTT_USER, MQTT_PASSWORD)) {
        Serial.println("Connected to MQTT broker");
        client.subscribe(MQTT_LED1_TOPIC);
        client.subscribe(MQTT_LED2_TOPIC);
      } else {
        Serial.print("MQTT connection failed, rc=");
        Serial.println(client.state());
      }
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println("-------new message from broker-----");
  Serial.print("topic: ");
  Serial.println(topic);
  Serial.print("message: ");
  
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.println(message);

  if (String(topic) == MQTT_LED1_TOPIC) {
    if (message == "OFF") {
      trthaiLed1 = LOW;
      digitalWrite(LED1, LOW);
      Serial.println("LED1 OFF");
    } else if (message == "ON") {
      trthaiLed1 = HIGH;
      digitalWrite(LED1, HIGH);
      Serial.println("LED1 ON");
    }
  } else if (String(topic) == MQTT_LED2_TOPIC) {
    if (message == "OFF") {
      trthaiLed2 = LOW;
      digitalWrite(LED2, LOW);
      Serial.println("LED2 OFF");
    } else if (message == "ON") {
      trthaiLed2 = HIGH;
      digitalWrite(LED2, HIGH);
      Serial.println("LED2 ON");
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);
  connect_to_broker();

  pinMode(BUT1, INPUT);
  pinMode(BUT2, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  // Send initial LED states
  client.publish(MQTT_LED1_TOPIC, trthaiLed1 == HIGH ? "ON" : "OFF");
  client.publish(MQTT_LED2_TOPIC, trthaiLed2 == HIGH ? "ON" : "OFF");
}

void loop() {
  client.loop();
  if (!client.connected()) {
    connect_to_broker();
  }

  trthaiButton1 = digitalRead(BUT1);
  trthaiButton2 = digitalRead(BUT2);

  if (trthaiButton1 == HIGH) {
    trthaiLed1 = !trthaiLed1;
    digitalWrite(LED1, trthaiLed1);
    client.publish(MQTT_LED1_TOPIC, trthaiLed1 == HIGH ? "ON" : "OFF");
    while (digitalRead(BUT1) == HIGH) {
      delay(5);
    }
  }

  if (trthaiButton2 == HIGH) {
    trthaiLed2 = !trthaiLed2;
    digitalWrite(LED2, trthaiLed2);
    client.publish(MQTT_LED2_TOPIC, trthaiLed2 == HIGH ? "ON" : "OFF");
    while (digitalRead(BUT2) == HIGH) {
      delay(5);
    }
  }
}
