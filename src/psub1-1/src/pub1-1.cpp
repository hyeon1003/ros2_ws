#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "rclcpp/time_source.hpp"
#include <memory>
#include <chrono>

using namespace std::chrono_literals;

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("node_pub1");

    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
    auto mypub = node->create_publisher<std_msgs::msg::String>("topic_pub1", qos_profile);

    auto timer_callback = [node, mypub]() {
        std_msgs::msg::String message;
        message.data = "Hello world!";
        RCLCPP_INFO(node->get_logger(), "Publish: %s", message.data.c_str());
        mypub->publish(message);
    };
    auto timer = node->create_wall_timer(100ms, timer_callback);// 100ms마다 실행되는 타이머 생성
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}