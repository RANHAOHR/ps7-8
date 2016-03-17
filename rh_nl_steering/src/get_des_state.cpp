#include "rh_nl_steering.h"
#include <iostream>
using namespace std;

nav_msgs::Odometry get_state() {
  double x;
  double y;
  double psi;
  double speed;
  nav_msgs::Odometry des_state;
 
    cout << "Enter x: ";
    cin >> x;
    cout << "Enter y: ";
    cin >> y;
    cout << "Enter psi: ";
    cin >> psi;
    cout << "Enter speed: ";
    cin >> speed;
    //geometry_msgs::PoseStamped des_pose = steering_get_state.xyPsi2PoseStamped(x,y,psi);
    geometry_msgs::Quaternion quaternion;
	quaternion.x = 0.0;
	quaternion.y = 0.0;
	quaternion.z = sin(psi / 2.0);
	quaternion.w = cos(psi / 2.0);

    des_state.pose.pose.orientation = quaternion;
	des_state.pose.pose.position.x = x; // keep the robot on the ground!
	des_state.pose.pose.position.y = y;
	des_state.pose.pose.position.z = 0.0;

	des_state.twist.twist.linear.x = speed;
    return des_state;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "get_states");

  ros::NodeHandle n_;

  ros::Publisher des_state_publisher_ = n_.advertise<nav_msgs::Odometry>("/desState", 1,true);

  ros::Rate sleep_timer(100);
  // main loop; publish a desired state every iteration
  nav_msgs::Odometry des_states;

  int button = 0;
  while (ros::ok()) {
    cout << "If you want to add state, Press 1 " << endl;
    cout << "If you want robot to stop, Press 0 " << endl;
    cin >> button;
	if(button == 1){
		ROS_INFO("published a state");
		des_states = get_state();
		des_state_publisher_.publish(des_states);
	}

	if(button == 0){
		ROS_INFO("ask to stop!");
		des_states.twist.twist.linear.x = 0.0;
		des_states.twist.twist.angular.z = 0.0;
		des_state_publisher_.publish(des_states);
		}
    sleep_timer.sleep();
  }
  return 0;
}
