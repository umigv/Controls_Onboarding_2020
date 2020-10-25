#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Pose.h>
#include <turtlesim/Pose.h>
#include <geometry_msgs/Quaternion.h>
#include <nav_msgs/Odometry.h>
#include <tf/tf.h>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <fstream>


//ros::Rate loop_rate(10);

double cur_x = 5.544;
double cur_y = 5.544;
double cur_theta = 0;

// update pose then genearte next /cmd_vel
void poseCallback(const turtlesim::Pose& msg) {

    cur_x = msg.x;
    cur_y = msg.y;
    cur_theta = msg.theta;

    ROS_INFO_STREAM("updating pose");
    ROS_INFO_STREAM(cur_x);
    ROS_INFO_STREAM(cur_y);
    ROS_INFO_STREAM(cur_theta);

} // poseCallback()




int main(int argc, char** argv){

    ros::init(argc, argv, "sim_controller");
    ros::NodeHandle nh_pub;
    
    geometry_msgs::Point p;
    p.x = 7.544;
    p.y = 5.544;
    
    std::vector<geometry_msgs::Point> fake_path = {p};

    ros::Publisher pub = nh_pub.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);

    ros::Subscriber sub = nh_pub.subscribe("turtle1/pose", 1000, poseCallback);
    
    int index = 0;
    while (ros::ok()) {
    	
    	geometry_msgs::Twist t;
		t.linear.x = 2;
		pub.publish(t);
		
		if(abs(cur_x - fake_path[0].x) < 0.1 && abs(cur_y - fake_path[0].y) < 0.1) {
			geometry_msgs::Twist t; // default all 0
			pub.publish(t);
			ROS_INFO_STREAM("reached final goal!");
			break;
		}
    	
    	
    	// the code is incorrect, it's only for demo ROS functions purose
    	/*if(index < fake_path.size()) {
    	
    		geometry_msgs::Twist t;
    		
    		// check something else first
    		
    		t.linear.x = 2;
    		pub.publish(t);
    		
    		// also check if you hit the target yet, otherwise, you would go past it unnoticed
    		
    		//++index;
    	}
    	else {
    		break;
    	}*/

    	ros::spinOnce();
    	//loop_rate.sleep();
  	}
    
	
	return 0;
	
}



