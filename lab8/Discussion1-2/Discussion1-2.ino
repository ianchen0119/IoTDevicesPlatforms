unsigned long duration;
unsigned long starttime;
unsigned long sampletime_ms = 3000; //sampe 30s
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;

void setup() {
  Serial.begin(9600);
  pinMode(8,INPUT);
  starttime = millis();
}

void loop() {
  duration = pulseIn(8, LOW);
  lowpulseoccupancy = lowpulseoccupancy+duration;
  if ((millis()-starttime) >= sampletime_ms){
    ratio = lowpulseoccupancy/(sampletime_ms*10.0); // Integer percentage 0~100
    concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // using spec sheet curve

    if(concentration < 500){
      digitalWrite(7, HIGH);
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
    }
    else if(concentration >= 500 && concentration < 1000){
      digitalWrite(7, LOW);
      digitalWrite(9, HIGH);
      digitalWrite(10, LOW);
    }
    else if(concentration >= 1000){
      digitalWrite(7, LOW);
      digitalWrite(9, LOW);
      digitalWrite(10, HIGH);
    }
    
    Serial.print("concentration = ");
    Serial.print(concentration);
    Serial.println(" pcs/0.01cf");
    Serial.print(concentration / 0.2832);
    Serial.println(" pcs/liter");
    Serial.println("\n");
    lowpulseoccupancy = 0;
    starttime = millis();
  }
}
