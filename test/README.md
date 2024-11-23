# D23_DoGiaHuy

## A. NỘI DUNG ĐÃ TÌM HIỂU VÀ ĐƯỢC HỌC

### Tìm hiểu về MQTT qua các tài liệu anh Thế Anh chia sẻ:

- Tìm hiểu về khái niệm MQTT và các khái niệm cơ bản qua link https://viblo.asia/p/mqtt-la-gi-vai-tro-cua-mqtt-trong-iot-V3m5WL3bKO7

- Tìm hiểu cách triển khai mqtt client trên esp32 với thư viện pubsubclient.h qua tài liệu https://github.com/knolleary/pubsubclient

- Một vài code examples https://khuenguyencreator.com/lap-trinh-esp32-mqtt-bat-tat-den-voi-hivemq-broker/#google_vignette

- Hai public broker phổ biến được anh Thế Anh giới thiệu:

	+ HiveMQ: https://www.mqtt-dashboard.com/
	
	+ EMQX: https://www.emqx.com/en/mqtt/public-mqtt5-broker
	

### Demo về MQTT:

- Em đang tìm hiểu và chạy thử code examples: đăng ký(đọc) chủ đề "DGH_PTIT_MQTT_ESP32/OUT_TOPIC" từ chương trình (hello world-biến đếm)

```cpp
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Xuong";				//khai báo tài khoản mật khẩu wifi
const char* password = "68686868";

const char* mqtt_server = "broker.hivemq.com";
//const char* mqtt_server = "192.168.1.11";

#define MQTT_PORT 1883
#define MQTT_USER "dgh_ptit_1234_test"
#define MQTT_PASSWORD "12345678"
 
#define MQTT_TOPIC_IN "DGH_PTIT_MQTT_ESP32/IN_TOPIC"
#define MQTT_TOPIC_OUT "DGH_PTIT_MQTT_ESP32/OUT_TOPIC"

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (150)				// khai báo kích thước mảng
char msg[MSG_BUFFER_SIZE];
int value = 0;

void setup_wifi(){

  delay(10);
  Serial.println();					// Bắt đầu bằng cách kết nối với mạng WiFi
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  while (!client.connected()) {						// Lặp lại cho đến khi kết nối lại
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";					// Tạo ID client ngẫu nhiên
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {				// Tiếp tục kết nối
      Serial.println("connected");					// Sau khi kết nối, hãy đăng thông báo...
      client.publish(MQTT_TOPIC_OUT, "hello world");	
      client.subscribe(MQTT_TOPIC_IN);					// ... và đăng ký lại
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);							// Chờ 5 giây trước khi thử lại
    }
  }
}

void setup(){
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, MQTT_PORT);
  client.setCallback(callback);
}

void loop(){
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf (msg, MSG_BUFFER_SIZE, "hello world #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish(MQTT_TOPIC_OUT, msg);
  }
}

```

- Kết quả:

- ![ảnh](MQTT-test.PNG)

- ![ảnh](MQTT-test1.PNG)
## B. CÔNG VIỆC TIẾP THEO

- Tiếp tục tìm hiểu về ESP32 và giao thức MQTT

## C. MƯỢN ĐỒ CỦA LAB

- Không