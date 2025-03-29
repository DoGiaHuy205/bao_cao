#include <Wire.h>
#include <Adafruit_INA219.h>
#include <WiFi.h>
#include <ESP_Google_Sheet_Client.h>

// WiFi and Google Sheets Credentials
#define WIFI_SSID "Xuong"
#define WIFI_PASSWORD "68686868"
#define PROJECT_ID "esp32-sleepmode"
#define CLIENT_EMAIL "esp32-sleepmode@esp32-sleepmode.iam.gserviceaccount.com"
const char PRIVATE_KEY[] PROGMEM=  "-----BEGIN PRIVATE KEY-----\n MIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQC9G+VXqLBNoug8\nWmQ+j7ugCvYRAbucYau3iPOSpVwTsxLGh2nye+wQ/3Ibg6EGXudLAfJNA5LszO5J\n0Xaqws7M6QIorZw/cZnN4kyqo5Cp/MbQLu/NSvvoTu+bbPlbCbyD4i2xCu2XkxOW\nm4DlKUg4HIEZjcg8g+rC4NqSTFPE0x4ViwukK1rTGXcrSppymLLsYx0eTlvW+OK+\niWHnFZ3P+ONRoZPzCd+f2jrqGRkssNJH6rPmOR4eGWJmisHdlbatiAdC+RFvEDl7\n4lHuW4FNzqECgrmKqW0/QRGO+033IvAy7ool2GOEdf2z+WB0oVuKg07dOBUoN4e3\n/0bhDF4xAgMBAAECggEACKsabmlNruVbMAcJsMzIXNvxGb2irVapzHeDM2iP3wRL\n8Ec9Q0T3Fh62IDjpUkAv6czcn+Hxzm0ktW6xTz8E7o4gup9zTyeEgBQ8j5bV9wDJ\nVo925QoSoCcGzdunK3XiYF48r3CbjEw3hJAQuWW/c85UrvNEPN05eeDc4VdigJ4D\na3uVsQfL3RogX4H/41WQZLKD4ESdZ4noZ/aAnE5UGrtRG5MBw7eZ5qSPqWqF3OQM\nDeWGIewfXarH7dH4JErCIr+P6OBXWpSesHvFfmcBvHadYDtvrj7YZSdSPdeACLTZ\nZD63YDJYomM5UMYfWtnbB78aehxqdN+Islopf/CFlQKBgQD8krIYDWep67lKLNy+\nsC7Sqn3+6453SlEsNsNt36dzCRCnmebRCTnRAPYz86K4iZL/xGqU9Kf/k3r+FESg\nkXpSH8p4xEW/foZK0LEvDbq+tW7neAUoZtEAeiVte6ye4Pm8TqJRByz5n90kRrmb\nmVKJ32cjRCWhQsn3UX5zvQXYnQKBgQC/rMKCo0HD0Qc9R725GrW+HqpY5V2sFHGT\niABOgOmwrw2SeJv2Qk0TORD7VvDstqORik3Y5khBVc6UyYezca6iGfEOmmczjVV3\nElKM7Des433TyWk+MaCJ6hS513bU9lecAVG7DFQ1RcrcmBySAWdFtiYD4fEpmPmB\nnFZMuuh1pQKBgFMOLlBogBFJecnhjMmMCCmwdPRSI6wonR7L92H3LQpQDdD/c/6D\naSbIiS22TWkfnF5NCbtn5KLPrZ9FrPecPzwoRh2GdWUuRxztGYbene0+nnSxbAjI\nHqxofkxNYgtw8c6xkQDSOkDwB/l45Go9df3un+zh6Pnpi56vhsSqgPSlAoGBAI8U\nzZZrfDpKnVbXaP72u1iS16LIhWZhVG9HBMOVY90qr7z5H6Ny1spUvSKCQhLSO8P3\nNCmHrcRn43AaCJyhbjU/nDzEcel/xZ6/JLRh2SXMJC+mmFN/BFIvVQ1tlB1hTwD7\n0yEIEQw7bzXArwMm3Qqi8DnRvg7JTOe95oYcuE6pAoGALNeOXe7SAVt7qrGayrHW\nXGtwJAQpXLSIRtBleNYv8IKJjs4b8gBfqqSXu5luxoWV8NLJW55z78VyxSaAbSmR\ns2Xjv3e9qq8Z1vyQS1xx4W01XpIGI7V4hAXKCQI2da8ev3Xr4ZcvAPusu+k+2GEN\nsZWC8Ilq7LmKQMAzfjSClW4=\n-----END PRIVATE KEY-----\n";
const char spreadsheetId[] = "1tiQCNSUaGzOO7FX5uB4lXYTN_XmHwjWfsWzIRFPlQzs";

Adafruit_INA219 ina219(0x40); // I2C address of INA219
unsigned long lastTime = 0;
unsigned long timerDelay = 30000; // 30 seconds

void setup() {
    Serial.begin(115200);
    while (!Serial) { delay(1); }
    Serial.println("Starting...");

    // Initialize INA219
    if (!ina219.begin()) {
        Serial.println("Failed to find INA219 chip");
        while (1) { delay(10); }
    }
    Serial.println("INA219 Initialized");
    
    // Connect to Wi-Fi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(1000);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    
    // Initialize Google Sheets Client
    GSheet.setTokenCallback(tokenStatusCallback);
    GSheet.setPrerefreshSeconds(10 * 60);
    GSheet.begin(CLIENT_EMAIL, PROJECT_ID, PRIVATE_KEY);
}

void loop() {
    bool ready = GSheet.ready();
    if (ready && millis() - lastTime > timerDelay) {
        lastTime = millis();
        FirebaseJson response;
        FirebaseJson valueRange;
        
        // Read sensor data
        float shuntvoltage = ina219.getShuntVoltage_mV();
        float busvoltage = ina219.getBusVoltage_V();
        float current_mA = ina219.getCurrent_mA();
        float power_mW = ina219.getPower_mW();
        float loadvoltage = busvoltage + (shuntvoltage / 1000);
        
        Serial.println("Appending data to Google Sheets...");
        
        valueRange.add("majorDimension", "COLUMNS");
        valueRange.set("values/[0]/[0]", millis()); // Timestamp
        valueRange.set("values/[1]/[0]", busvoltage);
        valueRange.set("values/[2]/[0]", shuntvoltage);
        valueRange.set("values/[3]/[0]", loadvoltage);
        valueRange.set("values/[4]/[0]", current_mA);
        valueRange.set("values/[5]/[0]", power_mW);
        
        bool success = GSheet.values.append(&response, spreadsheetId, "Sheet1!A1", &valueRange);
        if (success) {
            response.toString(Serial, true);
            valueRange.clear();
        } else {
            Serial.println(GSheet.errorReason());
        }
        Serial.println();
    }
}

void tokenStatusCallback(TokenInfo info) {
    if (info.status == token_status_error) {
        GSheet.printf("Token Error: %s\n", GSheet.getTokenError(info).c_str());
    } else {
        GSheet.printf("Token Status: %s\n", GSheet.getTokenStatus(info).c_str());
    }
}
