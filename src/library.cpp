#include <ros/ros.h>
#include <std_msgs/String.h>

#include <iostream>

class ClassThatUsesRoscpp
{
public:
  ClassThatUsesRoscpp();
  ~ClassThatUsesRoscpp();

  void callback(const std_msgs::StringConstPtr& message);

private:
  ros::NodeHandle node_handle_;
  ros::Subscriber subscriber_;
  ros::AsyncSpinner spinner_;
};
typedef boost::shared_ptr<ClassThatUsesRoscpp> ClassThatUsesRoscppPtr;

ClassThatUsesRoscpp::ClassThatUsesRoscpp()
  : spinner_(1)
{
  std::cout << "in: " << __PRETTY_FUNCTION__ << std::endl;
  subscriber_ = node_handle_.subscribe("chatter", 10, &ClassThatUsesRoscpp::callback, this);
  spinner_.start();
}

ClassThatUsesRoscpp::~ClassThatUsesRoscpp()
{
  std::cout << "in: " << __PRETTY_FUNCTION__ << std::endl;
}

void ClassThatUsesRoscpp::callback(const std_msgs::StringConstPtr &message)
{
  std::cout << "in: " << __PRETTY_FUNCTION__ << std::endl;
  std::cout << "Got message: " << message->data << std::endl;
}

// The factory
extern int g_argc;
extern char **g_argv;
extern "C" {
  ClassThatUsesRoscppPtr createClassThatUsesRoscppInstance()
  {
    if (!ros::isInitialized()) {
      ros::init(g_argc, g_argv, ROS_PACKAGE_NAME);
    }
    return ClassThatUsesRoscppPtr(new ClassThatUsesRoscpp());
  }
}
