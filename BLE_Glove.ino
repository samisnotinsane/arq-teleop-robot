
#include <SimbleeCOM.h>
const int vibePins[] = {5,15,12,11,6,9};

void setup() {
  int i;
  // put your setup code here, to run once:
  for(i=0;i<6;i++){
    pinMode(vibePins[i],OUTPUT);
    }
  pinMode(13,OUTPUT);
  Serial.begin(9600);
  SimbleeCOM.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

}

void SimbleeCOM_onReceive(unsigned int esn, const char *payload, int len, int rssi){
    if(payload[0]==0){
      digitalWrite(13,LOW);
      resetVibe();
      }
    else{
      initVibe(payload);
      }
}

void initVibe(const char *payload){
    if(payload[0]==15){
      digitalWrite(13,HIGH);
      }
    digitalWrite(payload[0], HIGH);
    
}

void resetVibe(){
  int i;
    for(i=0;i<6;i++){
      digitalWrite(vibePins[i],LOW);
    }
}
