# D23_DoGiaHuy

## A. NỘI DUNG ĐÃ TÌM HIỂU

### Demo về MQTT:

- Em đang tìm hiểu và chạy thử code examples:
	
	+ Dùng public broker HiveMQ thành công chuyển đổi trạng thái led bằng button hoặc từ broker gửi bản tin(ON/OFF) về

#### Code và giải thích
	
- Hàm setup_wifi() để kết nối esp32 với wifi

```cpp
void setup_wifi() {
  Serial.print("Connecting to ");
  Serial.println(ssid);					// kết nối wifi với ssid và pass
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {		// Sau đấy thì em cho esp liên tục kết nối với wifi bằng WiFi.status()
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");			// Sau khi kết nối wifi thành công thì in ra serial cùng với địa chỉ IP 
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

```

- Hàm connect_to_broker() để kết nối esp với broker

```cpp
void connect_to_broker() {
  static unsigned long lastReconnectAttempt = 0;
  if (!client.connected()) {
    unsigned long now = millis();
    if (now - lastReconnectAttempt > 5000) {			// Chờ 5 giây để gọi lại
      lastReconnectAttempt = now;
      if (client.connect("ESP32", MQTT_USER, MQTT_PASSWORD)) {	// Kết nối với client.connect() và xác thực bằng tên người dùng, mật khẩu
        Serial.println("Connected to MQTT broker");
        client.subscribe(MQTT_LED1_TOPIC);
        client.subscribe(MQTT_LED2_TOPIC);			// Nếu kết nối được in ra serial và đăng ký 2 chủ đề LED1 và LED2
      } else {
        Serial.print("MQTT connection failed, rc=");
        Serial.println(client.state());				// Nếu không kết nối được, in ra serial và kết nối lại 
      }
    }
  }
}
```

- Hàm callback() để xử lý các tin nhắn nhận từ máy chủ MQTT.

```cpp
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println("-------new message from broker-----");
  Serial.print("topic: ");
  Serial.println(topic);
  Serial.print("message: ");			// In thông tin tin nhắn nhận được (topic và nội dung).
  
  String message = "";
  for (int i = 0; i < length; i++) {		// Chuyển tin nhắn vào mảng string và in ra serial
    message += (char)payload[i];
  }
  Serial.println(message);

  if (String(topic) == MQTT_LED1_TOPIC) {	// Kiểm tra nội dung tin nhắn có phải là tin nhắn điểu khiển không(ON/OFF)
    if (message == "OFF") {			// Nếu tin nhắn là OFF thì cập nhật trạng thái led, tắt đèn và in ra màn hình
      trthaiLed1 = LOW;
      digitalWrite(LED1, LOW);
      Serial.println("LED1 OFF");
    } else if (message == "ON") {		// Nếu tin nhắn là ON thì cập nhật trạng thái led, bật đèn và in ra màn hình
      trthaiLed1 = HIGH;
      digitalWrite(LED1, HIGH);
      Serial.println("LED1 ON");
    }
  } else if (String(topic) == MQTT_LED2_TOPIC) {	// Kiểm tra nội dung tin nhắn có phải là tin nhắn điểu khiển không(ON/OFF)
    if (message == "OFF") {				// Nếu tin nhắn là OFF thì cập nhật trạng thái led, tắt đèn và in ra màn hình
      trthaiLed2 = LOW;
      digitalWrite(LED2, LOW);
      Serial.println("LED2 OFF");
    } else if (message == "ON") {			// Nếu tin nhắn là ON thì cập nhật trạng thái led, bật đèn và in ra màn hình
      trthaiLed2 = HIGH;
      digitalWrite(LED2, HIGH);
      Serial.println("LED2 ON");
    }
  }
}
```

- Hàm setup() để khởi tạo chương trình và hàm loop() vòng lặp chính để chạy chương trình

```cpp
void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(MQTT_SERVER, MQTT_PORT);	// Gán địa chỉ máy chủ và cổng MQTT cho đối tượng client.
  client.setCallback(callback);			// Gán hàm callback xử lý tin nhắn từ MQTT.
  connect_to_broker();

  pinMode(BUT1, INPUT);
  pinMode(BUT2, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  // Send initial LED states
  client.publish(MQTT_LED1_TOPIC, trthaiLed1 == HIGH ? "ON" : "OFF");	// Gửi trạng thái ban đầu của LED đến máy chủ MQTT.
  client.publish(MQTT_LED2_TOPIC, trthaiLed2 == HIGH ? "ON" : "OFF");
}

void loop() {
  client.loop();
  if (!client.connected()) {			// Gọi client.loop() để xử lý kết nối và tin nhắn MQTT nếu không kết nối MQTT, thử kết nối lại (connect_to_broker())
    connect_to_broker();
  }

  trthaiButton1 = digitalRead(BUT1);		// Đọc trạng thái 2 button
  trthaiButton2 = digitalRead(BUT2);

  if (trthaiButton1 == HIGH) {			// Nếu button được nhấn, đảo trạng thái led và gửi trạng thái mới về broker
    trthaiLed1 = !trthaiLed1;
    digitalWrite(LED1, trthaiLed1);
    client.publish(MQTT_LED1_TOPIC, trthaiLed1 == HIGH ? "ON" : "OFF");
    while (digitalRead(BUT1) == HIGH) {		// Chờ cho nút nhấn được thả ra
      delay(5);
    }
  }

  if (trthaiButton2 == HIGH) {			// Nếu button được nhấn, đảo trạng thái led và gửi trạng thái mới về broker
    trthaiLed2 = !trthaiLed2;
    digitalWrite(LED2, trthaiLed2);
    client.publish(MQTT_LED2_TOPIC, trthaiLed2 == HIGH ? "ON" : "OFF");
    while (digitalRead(BUT2) == HIGH) {		// Chờ cho nút nhấn được thả ra
      delay(5);
    }
  }
}

```

- Kết quả:



## B. CÔNG VIỆC TIẾP THEO

- Tiếp tục tìm hiểu về ESP32 và giao thức MQTT

## C. MƯỢN ĐỒ CỦA LAB

- Không
