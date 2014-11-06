/* 
 * rosserial Ultrasound Example
 * 
 * This example is for the Maxbotix Ultrasound rangers.
 */

#include <ros.h>
#include <ros/time.h>
#include <sensor_msgs/Range.h>
#include <tf/transform_broadcaster.h>

ros::NodeHandle  nh;

sensor_msgs::Range range_msg;
ros::Publisher pub_range( "/ultrasound", &range_msg);


char base_link[] = "/base_link";
char odom[] = "/odom";

const int pinTrigger = 3;
const int pinEcho = 2;

char frameid[] = "/ultrasound";



float getRange_Ultrasound(){
  long duration;
  float cm;
  pinMode(pinEcho, INPUT);
  pinMode(pinTrigger, OUTPUT);
  digitalWrite(pinTrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrigger, LOW);
  duration = pulseIn(pinEcho, HIGH);
  cm = (duration*0.034029)/2;
  delay(10);
  return cm;
}

void setup()
{
  
  nh.initNode();
  nh.advertise(pub_range);
  range_msg.radiation_type = sensor_msgs::Range::ULTRASOUND;
  range_msg.header.frame_id =  frameid;
  range_msg.field_of_view = 0.1;  // fake
  range_msg.min_range = 0.0;
  range_msg.max_range = 10.00;
 
}


long range_time;

void loop()
{
  //publish the adc value every 50 milliseconds
  //since it takes that long for the sensor to stablize
  if ( millis() >= range_time ){
    int r =0;

    range_msg.range = getRange_Ultrasound();
    range_msg.header.stamp = nh.now();
    pub_range.publish(&range_msg);
    range_time =  millis() + 50;
  }
  nh.spinOnce();


  
}
