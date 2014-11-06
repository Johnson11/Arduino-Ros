#include "ros/ros.h"
#include "sensor_msgs/Range.h"

void chatterCallback(const sensor_msgs::Range::ConstPtr& range)
{
std::ostringstream ss;
ss << range->range;
std::string str(ss.str());
 std::cout << str << std::endl;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "arduinoTFMaker");

  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("/ultrasound", 1000, 	chatterCallback);
  
ros::spin();

  return 0;
}

