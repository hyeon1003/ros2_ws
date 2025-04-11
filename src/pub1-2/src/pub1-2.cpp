#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/vector3.hpp"
#include <iostream>

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("node_pub1_2");
    auto qos = rclcpp::QoS(rclcpp::KeepLast(10));
    auto publisher = node->create_publisher<geometry_msgs::msg::Vector3>("topic_pub1", qos);

    geometry_msgs::msg::Vector3 msg;
    rclcpp::WallRate loop_rate(1.0); //반복주파수를 저장하는 객체(단위 Hz)
    while (rclcpp::ok()) {
        std::cout << "실수값 3개를 입력하세요 (x y z): ";
        std::cin >> msg.x >> msg.y >> msg.z;

        RCLCPP_INFO(node->get_logger(), "Publishing: x=%.2f, y=%.2f, z=%.2f", msg.x, msg.y, msg.z);
        publisher->publish(msg);
        loop_rate.sleep();
    }

    rclcpp::shutdown();
    return 0;
}