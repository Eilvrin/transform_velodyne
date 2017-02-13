#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <dynamic_reconfigure/server.h>
#include <tf_velodyne/TfVelodyneNodeConfig.h>
#include <math.h>

double rps = 0.0; // Rotation velocity in rounds per second

void callback(tf_velodyne::TfVelodyneNodeConfig &config, uint32_t level) {
  ROS_INFO("Reconfigure request.");
  rps = config.rps;
}

int main(int argc, char** argv){
  ros::init(argc, argv, "velodyne_tf_broadcaster");
  ros::NodeHandle node;

  dynamic_reconfigure::Server<tf_velodyne::TfVelodyneNodeConfig> server;
  dynamic_reconfigure::Server<tf_velodyne::TfVelodyneNodeConfig>::CallbackType f;
  f = boost::bind(&callback, _1, _2);
  server.setCallback(f);

  tf::TransformBroadcaster br;
  tf::Transform transform;

  const ros::Time t_start = ros::Time::now();
  ros::Rate rate(1000.0);
  while (node.ok()){
    transform.setOrigin(tf::Vector3(0.0, 0.0, 0.0));
    tf::Quaternion q;
    double t_dif = (ros::Time::now() - t_start).toSec();
    q.setRPY(0, 0, 2*M_PI*rps*t_dif );
    transform.setRotation(q);
    br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", "velodyne16"));
    rate.sleep();
    ros::spinOnce();
  }
  return 0;
};
