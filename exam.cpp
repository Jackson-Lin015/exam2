#include "rclcpp/rclcpp.hpp"
#include "cus_msg/msg/custom_msg.hpp"
#include <functional>
#include <geometry_msgs/msg/twist.hpp>
using namespace std::chrono_literals;

class Exam : public rclcpp::Node {
public:
  Exam()
  : Node("exam")
  {
    subscriber_ = this->create_subscription<cus_msg::msg::CustomMsg>(
      "/exam_topic", 10, std::bind(&Exam::topic_callback, this, std::placeholders::_1));
    publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", 10);
    RCLCPP_INFO(this->get_logger(), "Subscriber start");
  }

private:
  void topic_callback(const cus_msg::msg::CustomMsg::SharedPtr msg)
  {
   

    auto twist_msg = geometry_msgs::msg::Twist();

    twist_msg.linear.x = msg->v;
    twist_msg.angular.z = msg->rad;
     RCLCPP_INFO(this->get_logger(), "Received: v=%d , rad = %f",
                    msg->v, msg->rad);
       publisher_->publish(twist_msg);              
    RCLCPP_INFO(this->get_logger(), "Publishing: linear.x=%f, angular.z=%f", twist_msg.linear.x, twist_msg.angular.z);
   
  }
  rclcpp::Subscription<cus_msg::msg::CustomMsg>::SharedPtr subscriber_;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;

  
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Exam>());
  rclcpp::shutdown();
  return 0;
}
