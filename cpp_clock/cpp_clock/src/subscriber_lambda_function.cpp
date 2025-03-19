// Copyright 2016 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <ctime>

class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber()
  : Node("minimal_subscriber")
  {
    auto topic_callback =
      [this](std_msgs::msg::String::UniquePtr msg) -> void {
        counter_++;
        if (counter_ == 20) {
          /*printf("%.2d:%.2d:%.2d\n", t.tm_hour, t.tm_min, t.tm_sec);
          tm current_time = *localtime(&t_);
          real_second_count_ = current_time.tm_sec - */
          counter_ = 0;
          second_count_++;
          //RCLCPP_INFO(this->get_logger(), "I count, s: '%lu'", second_count_);
          RCLCPP_INFO(this->get_logger(), "current time, s: '%lu'", second_count_);
        }
      };
    subscription_ =
      this->create_subscription<std_msgs::msg::String>("topic", 10, topic_callback);
  }

private:
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
  size_t counter_ = 0;
  size_t second_count_ = 0;
  /*size_t real_second_count_ = 0;
  time_t t_ = time(NULL);*/

};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}
