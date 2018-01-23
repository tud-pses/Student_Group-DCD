#ifndef PSES_TRAJECTORY_HPP
#define PSES_TRAJECTORY_HPP

#include <std_msgs/String.h>
#include <ros/ros.h>
#include <sensor_msgs/Range.h>
#include <ackermann_msgs/AckermannDriveStamped.h>
#include <std_msgs/Int16.h>
#include <stdlib.h>
#include <signal.h>
#include <dynamic_reconfigure/server.h>
#include <pses_control/controllerConfig.h>
#include <math.h>
#include <geometry_msgs/PoseStamped.h>

class PsesTrajectory {

public:
    PsesTrajectory();

    // Variables
    ros::NodeHandle nh;	// use this for global access

    // Subscriber

    // Publisher

    // Functions
    void driveTrajectory();
    void driveSteeringTest();
    void reset();

private:
    // Variables
    dynamic_reconfigure::Server<pses_control::controllerConfig> m_server;
    double m_ack_vel, m_ack_steering;
    std_msgs::Int16 m_velocity, m_velocity_config, m_steering, m_steering_config, m_steering_min, m_steering_max;
    geometry_msgs::PoseStamped m_follow_goal;

    // Subscriber
    ros::Subscriber m_sub_ackermann_cmd;
    ros::Subscriber m_sub_follow_goal;

    // Publisher
    ros::Publisher m_pub_velocity;
    ros::Publisher m_pub_steering;
    ros::Publisher m_pub_goal;

    // Functions
    void paramCallback(pses_control::controllerConfig &config, uint32_t level);
    static void ackermannCmdCallback(const ackermann_msgs::AckermannDriveStamped::ConstPtr& ackermannCmdMsg, double *m_ack_steering, double *m_ack_vel);
    static void followGoalCallback(const geometry_msgs::PoseStamped::ConstPtr& followGoalMsg, geometry_msgs::PoseStamped *m_follow_goal);
    void publishGoal();
};

void signalHandler(int sig);
bool stop_request = false;

#endif // PSES_TRAJECTORY_HPP