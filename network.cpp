#include "network.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <ESP32Time.h>

#ifdef __cplusplus
extern "C" {
#endif

	const char* ssid = "Mark";
	const char* password = "sss11223344";

    extern ESP32Time rtc;
    void get_time() {
        if (WiFi.status() == WL_CONNECTED) { //如果 Wi-Fi 连接成功
            HTTPClient http;  //开始登陆 

            http.begin("http://vv.video.qq.com/checktime?otype=json");
            
            int httpCode = http.GET(); //赋值                               
            if (httpCode > 0) { //检查一下是否为0，应该是去检查缓存区是否为空

                char buff[300];
                sscanf(http.getString().c_str(), "QZOutputJson=%s;", buff);

                Serial.println(http.getString().c_str());
                const size_t capacity = 128;
                DynamicJsonBuffer jsonBuffer(capacity);
                JsonObject& root = jsonBuffer.parseObject(buff);

                long serverTime = root["t"]; // 1610249263328
                if (serverTime != 0)
                {
                    serverTime += 8 * 60 * 60;
                    rtc.setTime(serverTime);
                    Serial.println(serverTime);
                }
            }
            http.end();
        }
    }
    void initwifi()
    {
        WiFi.begin(ssid, password);

        Serial.print("Connecting!");
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
        Serial.print("Connected!");
        get_time();
    }

#ifdef __cplusplus
}
#endif