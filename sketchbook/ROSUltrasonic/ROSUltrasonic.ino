
#include <ros.h>
#include <ros/time.h>
#include <tf/transform_broadcaster.h>
#include <sensor_msgs/Range.h>


//Set up the ros node and publisher
sensor_msgs::Range range;
ros::Publisher pub_sonar("ultrasound", &range);
ros::NodeHandle nh;
// for TF
geometry_msgs::TransformStamped t;
tf::TransformBroadcaster broadcaster;

char base_link[] = "/base_link";
char odom[] = "/odom";

int pinTrigger = 3;
int pinEcho = 2;


void setup()
{
  Serial.begin(9600);
  delay(100);
  nh.initNode();
  nh.advertise(pub_sonar);
  broadcaster.init(nh); // initialize TF
  ultrasoundSetup();
  Serial.println("Ready");
}
void ultrasoundSetup(){
 char ultrasound[] = "/ultrasound";
 range.radiation_type = sensor_msgs::Range::ULTRASOUND;
 range.header.frame_id = ultrasound;
 range.field_of_view = 0;
 range.min_range = 0.02;
 range.max_range = 3.0;
}

void loop()
{
  rangeCalc();
  TF();
  nh.spinOnce();
}
void rangeCalc(){
 range.range = ultrasonic();
 range.header.stamp = nh.now();
 pub_sonar.publish(&range);
 delay(100);
}
void TF(){
  t.header.frame_id = odom;
  t.child_frame_id = base_link;
  t.transform.translation.x = 1.0; 
  t.transform.rotation.x = 0.0;
  t.transform.rotation.y = 0.0; 
  t.transform.rotation.z = 0.0; 
  t.transform.rotation.w = 1.0;  
  t.header.stamp = nh.now();
  delay(50);
  broadcaster.sendTransform(t);
}
float ultrasonic(){
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
  cm = microsecondsToCentimeters(duration);
  delay(10);
  return cm;
}
float microsecondsToCentimeters(long microseconds){
  return (microseconds*0.034029)/2;
}
