cmake_minimum_required(VERSION 2.8.3)
project(rh_nl_steering)

find_package(catkin_simple REQUIRED)

#uncomment next line to use OpenCV library
#find_package(OpenCV REQUIRED)

#uncomment the next line to use the point-cloud library
#find_package(PCL 1.7 REQUIRED)

#uncomment the following 4 lines to use the Eigen library
#find_package(cmake_modules REQUIRED)
#find_package(Eigen3 REQUIRED)
#include_directories(${EIGEN3_INCLUDE_DIR})
#add_definitions(${EIGEN_DEFINITIONS})

catkin_simple()

cs_add_executable(rh_nl_steering src/rh_nl_steering.cpp)
cs_add_executable(get_des_state src/get_des_state.cpp)


cs_install()
cs_export()
    