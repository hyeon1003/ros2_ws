#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

bool kbhit()
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return true;
    }
    return false;
}

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("node_pub1_3");
    auto publisher = node->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
    geometry_msgs::msg::Twist msg;

    RCLCPP_INFO(node->get_logger(), "입력 키 - f: 전진, b: 후진, l: 좌회전, r: 우회전, s: 정지, q: 종료");

    rclcpp::WallRate rate(10);

    while (rclcpp::ok())
    {
        if (kbhit())
        {
            char key = getchar();

            msg.linear.x = 0.0;
            msg.angular.z = 0.0;

            switch (key)
            {
                case 'f': msg.linear.x = 2.0; break;
                case 'b': msg.linear.x = -2.0; break;
                case 'l': msg.angular.z = 2.0; break;
                case 'r': msg.angular.z = -2.0; break;
                case 's': break;
                case 'q':
                    rclcpp::shutdown();
                    return 0;
                default:
                    continue;
            }

            publisher->publish(msg);
        }

        rate.sleep();
    }

    rclcpp::shutdown();
    return 0;
}
