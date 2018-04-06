#include <SimbleeCOM.h>
#include <ros.h>
#include <std_msgs/Float64.h>

ros::NodeHandle  nh;
//first part is integral, second part is fractional
int currentpos = 0;
const int vibePins[] = {5,15,12,11,6,9};
const int vibeLevel[] = {0,140,170,200,230};

void messageCb( const std_msgs::Float64& msg){
  float temp = msg.data;
  int newpos = 0;
  if(temp > 50){
      newpos = 0;
    }
  else if(temp<=50 && temp>40){
      newpos = 1;
    }
  else if(temp<=40 && temp>25){
      newpos = 2;
    }
  else if(temp<=25 && temp>10){
      newpos = 3;
    }
  else if(temp<=10){
      newpos = 4;
    }
  if(newpos!=currentpos){
      currentpos = newpos;
      newVibeLevel();
    }
  
}

ros::Subscriber<std_msgs::Float64> sub("vibedata", &messageCb );

void setup()
{ 
  int i;
  pinMode(13,OUTPUT);
  for(i=0;i<6;i++){
    pinMode(vibePins[i],OUTPUT);
    }
  nh.initNode();
  nh.subscribe(sub);
}

void loop()
{  
  nh.spinOnce();
  delay(1);
}

void newVibeLevel(){
    analogWrite(vibePins[0],vibeLevel[currentpos]);
    analogWrite(vibePins[1],vibeLevel[currentpos]);
}
