#include "rh_nl_steering.h"
#include <iostream>
using namespace std;

SteeringController steering_get_state;

nav_msgs::Odometry get_state() {
  double x;
  double y;
  double psi;
  nav_msgs::Odometry des_state;
 
    cout << "Enter x: ";
    cin >> x;
    cout << "Enter y: ";
    cin >> y;
    cout << "Enter psi: ";
    cin >> psi;
    geometry_msgs::PoseStamped des_pose = steering_get_state.xyPsi2PoseStamped(x,y,psi);
	des_state.pose.pose = des_pose.pose;
    return des_state;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "get_states");
  ros::NodeHandle nh;

  steering_get_state.des_state_publisher_ = nh.advertise<nav_msgs::Odometry>("/desState", 1,true);

  ros::Rate sleep_timer(100);
  // main loop; publish a desired state every iteration
  nav_msgs::Odometry des_states;
  int button = 0;
  while (ros::ok()) {
    cout << "If you want to add state, Press 1 " << endl;
    cout << "If you want to stop, Press 0 " << endl;
    cin >> button;
	if(button == 1){
		des_states = get_state();
		des_state_publisher_.publish(des_states);
	}

	if(button == 0){
		des_states.twist.twist.linear.x = 0.0;
		des_states.twist.twist.angular.z = 0.0;
		des_state_publisher_.publish(des_states);
		return 0;}
    sleep_timer.sleep();
  }
  return 0;
}

