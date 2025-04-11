#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <memory>
#include <chrono>

using namespace std::chrono_literals;

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("turtle_controller");

    auto publisher = node->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
    geometry_msgs::msg::Twist twist;

    // 적당한 선속도와 각속도 설정
    twist.linear.x = 2.0;   // 앞으로 가는 속도
    twist.angular.z = 1.0;  // 회전 속도

    rclcpp::WallRate loop_rate(10);  // 10Hz로 주기적 발행

    while (rclcpp::ok())
    {
        publisher->publish(twist);
        RCLCPP_INFO(node->get_logger(), "Publishing linear.x=%.2f angular.z=%.2f",
                    twist.linear.x, twist.angular.z);
        loop_rate.sleep();
    }

    rclcpp::shutdown();
    return 0;
}
