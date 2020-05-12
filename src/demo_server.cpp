#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <peanut_action/MoveRobotAction.h>

class PeanutAction
{
protected:

  ros::NodeHandle nh_;
  actionlib::SimpleActionServer<peanut_action::MoveRobotAction> as_;
  std::string action_name_;
  peanut_action::MoveRobotGoal goal_;
  peanut_action::MoveRobotFeedback feedback_;
  peanut_action::MoveRobotResult result_;

public:

  PeanutAction(std::string name) :
    as_(nh_, name, boost::bind(&FibonacciAction::executeCB, this, _1), false),
    action_name_(name)
  {
    as_.start();
  }

  ~PeanutAction(void)
  {
  }

  void executeCB(const peanut_action::MoveRobotGoalConstPtr &goal)
  {
    ros::Rate r(0.1);
    bool success = true;
  
    // check that preempt has not been requested by the client
    if (as_.isPreemptRequested() || !ros::ok())
    {
      ROS_INFO("%s: Preempted", action_name_.c_str());
      as_.setPreempted();
      success = false;
      break;
    }
    feedback_.state = "sleep for 10 sec";
    as_.publishFeedback(feedback_);
    r.sleep();
  

    if(success)
    {
      result_.state = feedback_.state;
      ROS_INFO("%s: Succeeded", action_name_.c_str());
      as_.setSucceeded(result_);
    }
  }


};


int main(int argc, char** argv)
{
  ros::init(argc, argv, "peanut");

  FibonacciAction fibonacci("fibonacci");
  ros::spin();

  return 0;
}