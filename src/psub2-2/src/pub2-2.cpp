#include "psub2-2/pub2-2.hpp"

Pub::Pub() : Node("mypub"), count_(0)
{
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
    pub_ = this->create_publisher<geometry_msgs::msg::Vector3>("mytopic", qos_profile);
    timer_ = this->create_wall_timer(1s, std::bind(&Pub::publish_msg, this));
}

void Pub::publish_msg()
{
    auto msg = geometry_msgs::msg::Vector3();
    double value = count_++;
    msg.x = value;
    msg.y = value;
    msg.z = value;
    RCLCPP_INFO(this->get_logger(), "Published message: '%lf %lf %lf'", msg.x, msg.y, msg.z);
    pub_->publish(msg);
}