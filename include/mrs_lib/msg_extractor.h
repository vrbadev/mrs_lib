// clang: TomasFormat
#ifndef MRS_LIB_MSG_EXTRACTOR_H
#define MRS_LIB_MSG_EXTRACTOR_H

#include <mrs_msgs/PositionCommand.h>

#include <nav_msgs/Odometry.h>

#include <mrs_lib/attitude_converter.h>

namespace mrs_lib
{

std::tuple<double, double, double, double> getPose(const mrs_msgs::PositionCommand& data) {

  double x = data.position.x;
  double y = data.position.y;
  double z = data.position.z;

  double heading = 0;
  if (data.use_heading) {
    heading = data.heading;
  } else if (data.use_orientation) {
    try {
      heading = mrs_lib::AttitudeConverter(data.orientation).getHeading();
    }
    catch (mrs_lib::AttitudeConverter::GetHeadingException e) {
      ROS_ERROR_THROTTLE(1.0, "[%s]: error while extracting heading from PositionCommand: %s", ros::this_node::getName().c_str(), e.what());
    }
  }

  return std::tuple(x, y, z, heading);
}

std::tuple<double, double, double, double> getPose(const mrs_msgs::PositionCommandConstPtr& data) {

  double x = data->position.x;
  double y = data->position.y;
  double z = data->position.z;

  double heading = 0;
  if (data->use_heading) {
    heading = data->heading;
  } else if (data->use_orientation) {
    try {
      heading = mrs_lib::AttitudeConverter(data->orientation).getHeading();
    }
    catch (mrs_lib::AttitudeConverter::GetHeadingException e) {
      ROS_ERROR_THROTTLE(1.0, "[%s]: error while extracting heading from PositionCommand: %s", ros::this_node::getName().c_str(), e.what());
    }
  }

  return std::tuple(x, y, z, heading);
}

std::tuple<double, double, double> getVelocity(const mrs_msgs::PositionCommand& data) {

  double x = data.velocity.x;
  double y = data.velocity.y;
  double z = data.velocity.z;

  return std::tuple(x, y, z);
}

std::tuple<double, double, double> getVelocity(const mrs_msgs::PositionCommandConstPtr& data) {

  double x = data->velocity.x;
  double y = data->velocity.y;
  double z = data->velocity.z;

  return std::tuple(x, y, z);
}

std::tuple<double, double, double, double> getPose(const nav_msgs::Odometry& data) {

  double x = data.pose.pose.position.x;
  double y = data.pose.pose.position.y;
  double z = data.pose.pose.position.z;

  double heading = 0;

  try {
    heading = mrs_lib::AttitudeConverter(data.pose.pose.orientation).getHeading();
  }
  catch (mrs_lib::AttitudeConverter::GetHeadingException e) {
    ROS_ERROR_THROTTLE(1.0, "[%s]: error while extracting heading from Odometry: %s", ros::this_node::getName().c_str(), e.what());
  }

  return std::tuple(x, y, z, heading);
}

std::tuple<double, double, double, double> getPose(const nav_msgs::OdometryConstPtr& data) {

  double x = data->pose.pose.position.x;
  double y = data->pose.pose.position.y;
  double z = data->pose.pose.position.z;

  double heading = 0;

  try {
    heading = mrs_lib::AttitudeConverter(data->pose.pose.orientation).getHeading();
  }
  catch (mrs_lib::AttitudeConverter::GetHeadingException e) {
    ROS_ERROR_THROTTLE(1.0, "[%s]: error while extracting heading from Odometry: %s", ros::this_node::getName().c_str(), e.what());
  }

  return std::tuple(x, y, z, heading);
}

std::tuple<double, double, double> getVelocity(const nav_msgs::Odometry& data) {

  double x = data.twist.twist.linear.x;
  double y = data.twist.twist.linear.y;
  double z = data.twist.twist.linear.z;

  return std::tuple(x, y, z);
}

std::tuple<double, double, double> getVelocity(const nav_msgs::OdometryConstPtr& data) {

  double x = data->twist.twist.linear.x;
  double y = data->twist.twist.linear.y;
  double z = data->twist.twist.linear.z;

  return std::tuple(x, y, z);
}

}  // namespace mrs_lib

#endif  // MRS_LIB_MSG_EXTRACTOR_H
