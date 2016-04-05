# rh_map_client



## Example usage
roslaunch gazebo_ros empty_world.launch

roslaunch mobot_urdf mobot_startup_open_loop.launch

rosrun map_server map_server rhMap1.yaml

rosrun amcl amcl

rosrun odom_tf odom_tf

rosrun rh_map_client lin_steering
rosrun rh_map_client amcl_path_client

## Running tests/demos
    
