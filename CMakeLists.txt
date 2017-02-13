cmake_minimum_required(VERSION 2.8.3)
project(tf_velodyne)

find_package(catkin REQUIRED COMPONENTS
  dynamic_reconfigure
  roscpp
  rospy
  tf
)

generate_dynamic_reconfigure_options(
  config/TfVelodyneNode.cfg
)

catkin_package(
  CATKIN_DEPENDS dynamic_reconfigure roscpp rospy  tf
)

add_executable(tf_velodyne_node src/tf_velodyne_node.cpp)
add_dependencies(tf_velodyne_node tf_velodyne_gencfg)
target_link_libraries(tf_velodyne_node ${catkin_LIBRARIES} )

install(TARGETS tf_velodyne_node
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)