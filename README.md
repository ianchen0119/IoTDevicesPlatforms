# 2020 NCTU IoT Device Platform
## 課程介紹
用 Arduino UNO 配合各種元件開發各種應用

## [Lab1](Lab1)
### Demo1
控制 LED 讓它閃出 SOS 訊號

### Demo2
承 Demo1，按下按鈕後讓 LED 閃出 SOS 訊號

### Demo3
LED 閃著 SOS 訊號的同時，利用光敏電阻控制 LED 的亮度


## [Lab2](Lab2)
### Demo1
使用蜂鳴器，使它發出一段旋律

### Demo2
配合可變電阻，當每按下按鈕後，記錄可變電阻當時的電阻，並把它當作蜂鳴器的頻率，當長按按鈕時播放出來


## [Lab3](Lab3)
### Demo1
讀取 analog 訊號並印出來

### Demo2
將 analog 訊號 map 到一段區間(calibration)，並且要做很多次取平均(smoothing)

### Demo3
利用光敏電阻控制 LED 亮度，並且要將光敏電阻的 analog 訊號做 calibration 和 smoothing

### Demo4
做 cumulative moving average 的 smoothing


## [Lab4](Lab4)
### Demo1
用超音波感測器 + 蜂鳴器做出倒車雷達，根據不同距離發出不同頻率的聲音

### Demo2
使用 DHT11 溫濕度感測器測量溫度與濕度並算出目前的音速

## [Lab5](Lab5)
### Demo1
承 Lab4 Demo1 的倒車雷達，使用 analog 訊號讓 RGB LED 發出不同顏色

### Demo2
用 RGB LED 實作紅綠燈，並且要用蜂鳴器在不同燈號發出不同聲音

### Demo3
配合光敏電阻，當得到的訊號過了某個 threshold 就讓 [processing 軟體](https://processing.org/download/)的畫面出現紅色

### Demo4
按下按鈕讓光敏電阻記下一個值，然後我們用 monitor 去猜，猜對的話就讓 RGB LED 亮不同顏色`


## [Lab6](Lab6)
### Demo1
讓馬達持續來回運轉

### Demo2
把兩個光敏電阻放在馬達上，哪邊光比較少就往哪邊轉，做出像是向光性的現象

### Demo3
用 BMP085 記錄每層樓的高度，並在每層樓分別按一下按鈕算出不同樓層的高度，最後算出高度差，在不同樓層時讓不同數量的 LED 亮起


## [Lab7](Lab7)
### Demo1
用 MPU6050 陀螺儀算出 G_accel = Raw_accel / Sensitivity

### Demo2
計算出三軸的總加速度

### Demo3
計算 roll 和 pitch


## [Lab8](Lab8)
### Demo1
用 KY-038 聲音感測器看音量，並在 Serial Plotter 顯示音波圖，音亮大於某 threshold 就讓 LED 亮起

### Demo2
用 PPD42NS dust sensor 計算 PM 值，根據不同值亮不同顏色的 LED

### Demo3
用水深感測器(Water Level Sensor) 模擬幫浦，在水滿時停止馬達運作


## [Lab9](Lab9)
### Demo1
用 XD-58C pulse sensor 測量心跳，根據不同 BPM 讓蜂鳴器發出不同速度的音樂

### Demo2
使用 PIR Motion Sensor，配合光敏電阻，在暗的情況下，當有人經過時讓 LED 亮起

### Demo3
將 MPU-6050 和 HMC-5883L 的測量結果印出來


## [Lab10](Lab10)
### Demo1
使用 accelerometer, gyroscope, compass 做一個小遊戲，要在時間內完成指定任務 


## [Lab11](Lab11)
### Demo1
使用 HM-10 藍芽模組傳遞訊息

### Demo2
使用 HM-10 傳遞溫濕度資訊

### Demo3
使用 Grove-LoRa Radio 傳遞溫濕度資訊


## [Lab12](Lab12)
### Demo1
使用 ESP8266 wifi 模組 將溫濕度資訊傳送至 [ThingSpeak](https://thingspeak.com/)

## [Lab13](Lab13)
使用 ESP8266 傳送 GET/POST request 到 ThinkSpeak


## [Lab14](Lab14)
訓練一個 AI 模型辨識目前的並配合 MPU-6050 記錄手掌動作
