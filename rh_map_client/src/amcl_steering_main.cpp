#include <ros/ros.h>
#include <rh_map_client/path.h>
#include <iostream>
#include <string>
#include <nav_msgs/Path.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseStamped.h>
using namespace std;

geometry_msgs::Quaternion convertPlanarPhi2Quaternion(double phi) {
    geometry_msgs::Quaternion quaternion;
    quaternion.x = 0.0;
    quaternion.y = 0.0;
    quaternion.z = sin(phi / 2.0);
    quaternion.w = cos(phi / 2.0);
    return quaternion;
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "append_path_client");
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<rh_map_client::path>("append_path_queue_service");
    geometry_msgs::Quaternion quat;
    
    while (!client.exists()) {
      ROS_INFO("waiting for service...");
      ros::Duration(1.0).sleep();
    }
    ROS_INFO("connected client to service");
    rh_map_client::path path_srv;
    
    //create some path points...this should be done by some intelligent algorithm, but we'll hard-code it here
    geometry_msgs::PoseStamped pose_stamped;
    pose_stamped.header.frame_id = "world";
    geometry_msgs::Pose pose;
    pose.position.x = 3.0; // say desired x-coord is 3
    pose.position.y = 0.0;
    pose.position.z = 0.0; // let's hope so!
    quat = convertPlanarPhi2Quaternion(0);
    pose.orientation = quat;
    pose_stamped.pose = pose;
    path_srv.request.path.poses.push_back(pose_stamped);
 
    pose.position.y = 3.0;
    pose_stamped.pose = pose;
    path_srv.request.path.poses.push_back(pose_stamped);

    pose.position.x = 0.0;
    pose_stamped.pose = pose;
    path_srv.request.path.poses.push_back(pose_stamped);
    
    pose.position.y = 7.0;
    pose_stamped.pose = pose;
    path_srv.request.path.poses.push_back(pose_stamped);

    pose.position.x = -8;
    pose_stamped.pose = pose;
    path_srv.request.path.poses.push_back(pose_stamped);

    pose.position.y = 1.0;
    pose_stamped.pose = pose;
    path_srv.request.path.poses.push_back(pose_stamped);    

    pose.position.x = -14.0;
    pose_stamped.pose = pose;
    path_srv.request.path.poses.push_back(pose_stamped);  
    
    //repeat (x,y) with new heading:
    pose_stamped.pose.orientation = convertPlanarPhi2Quaternion(0); 
    path_srv.request.path.poses.push_back(pose_stamped);
    
    client.call(path_srv);

    return 0;
}
