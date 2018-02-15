#include <SimbleeCOM.h>
#include <ros.h>
#include <std_msgs/Int32.h>

ros::NodeHandle  nh;
char toggleOff[] = {0};
const int vibePins[] = {5,15,12,11,6,9};

void messageCb( const std_msgs::Int32& toggle_msg){
  if (toggle_msg.data == 5){
  digitalWrite(13,HIGH);   // blink the led
  toggleOff[0] = 5;
  }
  else if(toggle_msg.data == 15){ 
  digitalWrite(13,HIGH);
  toggleOff[0] = 15;
  }
  else if(toggle_msg.data == 12){ 
  digitalWrite(13,HIGH);
  toggleOff[0] = 12;
  }
  else if(toggle_msg.data == 11){ 
  digitalWrite(13,HIGH);
  toggleOff[0] = 11;
  }
  else if(toggle_msg.data == 6){ 
  digitalWrite(13,HIGH);
  toggleOff[0] = 6;
  }
  else if(toggle_msg.data == 9){ 
  digitalWrite(13,HIGH);
  toggleOff[0] = 9;
  }
  else if(toggle_msg.data == 0){ 
  digitalWrite(13,LOW);
  toggleOff[0] = 0;
  }
}

ros::Subscriber<std_msgs::Int32> sub("ble_com", &messageCb );

void setup()
{ 
  pinMode(13,OUTPUT);
  pinMode(5, OUTPUT);
  SimbleeCOM.txPowerLevel = 4;
  SimbleeCOM.proximityMode(0);
  nh.initNode();
  nh.subscribe(sub);
  SimbleeCOM.begin();
}

void loop()
{  
  nh.spinOnce();
  delay(1);
  SimbleeCOM.send(toggleOff,sizeof(toggleOff));
}
