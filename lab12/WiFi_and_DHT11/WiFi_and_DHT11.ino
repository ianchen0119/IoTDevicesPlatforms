#include <SoftwareSerial.h>
#define WiFi_TX 2
#define WiFi_RX 3
SoftwareSerial WiFi_Serial(WiFi_TX,WiFi_RX);
int flag = 0;

//請輸入自己WiFi熱點的名稱
#define SSID "Neil_2"

//請輸入自己WiFi熱點的密碼
#define PASS "09121021"

#define IP "api.thingspeak.com"
// GET /update?key=[THINGSPEAK_KEY]&field1=[data 1]&filed2=[data 2]...;
String GET = "GET /update?key=U5RQ8FIUOS89J7RK"; //請將key=之後的16碼改為自己的API key

void setup() {
  Serial.begin(9600);
  WiFi_Serial.begin(115200);
  while(flag == 0){
    WiFi_Send("AT"); //測試指令-AT
    delay(1000);
    if(WiFi_Serial.find("OK")){
      Serial.println("RECEIVED: OK");
      WiFi_Send("AT+CIPMUX=0"); //設定為單連線型態
      delay(1000);
      if(WiFi_Serial.find("OK")){
        Serial.println("RECEIVED: OK");
      }
    while(!connectWiFi()); //將Wi-Fi模組連上可連至外網的Wi-Fi AP
    flag = 1; 
  }
    else{
      Serial.println("NO RESPONSE!");
    } 
  }
}

void loop() {
  double Hum = 66; //濕度
  double Temp = 20.5; //溫度
  if (isnan(Hum)||isnan(Temp)){ //確定溫濕度值存在
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  else{
    String HH,TT;
    HH=String(Hum); //將濕度值轉換成字串型態的資料
    TT=String(Temp); //將溫度值轉換成字串型態的資料
    
    updateDHT11(TT,HH); //將溫濕度資料傳至雲端平台

    Serial.print("Humidity: "); 
    Serial.print( HH );
    Serial.print(" %\t");
    Serial.print("Temperature: "); 
    Serial.print( TT );
    Serial.println(" *C\t");
  }
  delay(5000);
}

void updateDHT11(String T, String H){
  String cmd = "AT+CIPSTART=\"TCP\",\""; //建立TCP連線
  cmd += IP;
  cmd += "\",80";
  WiFi_Send(cmd);
  delay(1000);
  if(WiFi_Serial.find("ERROR")){
    Serial.println("RECEIVED: TCP Connect Error");
    return;
  }
  cmd = GET + "&field1=" + T + "&field2=" + H +"\r\n";
  WiFi_Serial.print("AT+CIPSEND="); //傳送資料的指令
  WiFi_Serial.println(cmd.length()); //資料的長度
  if(WiFi_Serial.find(">")){ //確定WiFi模組有接收到指令
    Serial.print(">");
    Serial.print(cmd);
    WiFi_Serial.print(cmd); //傳送資料
    delay(1000);
    if(WiFi_Serial.find("OK")){
      Serial.println("RECEIVED: SEND OK");
    }
    else{
      Serial.println( "RECEIVED: SEND Error_2" );
    }
  }
  else{
    Serial.println( "RECEIVED: SEND Error" );
  }
}

void WiFi_Send(String cmd){
  Serial.print("SEND: ");
  WiFi_Serial.println(cmd);
  Serial.println(cmd);
}

boolean connectWiFi(){
  WiFi_Serial.println("AT+CWMODE=1"); //WiFi 應用型態為Station型態
  delay(1000);
  String cmd="AT+CWJAP=\""; //加入接入點(與WiFi AP連線)
  cmd+=SSID;
  cmd+="\",\"";
  cmd+=PASS;
  cmd+="\"";
  WiFi_Send(cmd);
  delay(1000);
  if(WiFi_Serial.find("OK")){
    Serial.println("RECEIVED: OK");
    return true;
  }
  else{
    Serial.println("RECEIVED: Error");
    return false;
  }
}
