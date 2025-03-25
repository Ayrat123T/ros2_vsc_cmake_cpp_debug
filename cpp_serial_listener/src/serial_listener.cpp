#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <serial/serial.h>
#include <string>

class SerialListener : public rclcpp::Node
{
public:
    SerialListener() : Node("serial_listener_node")
    {
        // Инициализация publisher'а для отправки данных в топик
        serial_pub_ = this->create_publisher<std_msgs::msg::String>("/serial_data", 10);

        // Настройка serial-порта
        try
        {
            serial_port_.setPort("/dev/ttyUSB0");  // Укажите ваш порт
            serial_port_.setBaudrate(115200);      // Скорость передачи
            serial_port_.open();
        }
        catch (const std::exception &e)
        {
            RCLCPP_ERROR(this->get_logger(), "Ошибка открытия порта: %s", e.what());
            return;
        }

        // Таймер для чтения данных
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(100),  // Чтение каждые 100 мс
            std::bind(&SerialListener::readSerialData, this));
    }

private:
    void readSerialData()
    {
        if (!serial_port_.isOpen())
        {
            RCLCPP_WARN(this->get_logger(), "Порт не открыт!");
            return;
        }

        try
        {
            // Чтение данных из порта
            std::string data = serial_port_.read(serial_port_.available());

            if (!data.empty())
            {
                // Публикация данных в топик
                auto msg = std_msgs::msg::String();
                msg.data = data;
                serial_pub_->publish(msg);

                RCLCPP_INFO(this->get_logger(), "Получено: %s", data.c_str());
            }
        }
        catch (const std::exception &e)
        {
            RCLCPP_ERROR(this->get_logger(), "Ошибка чтения: %s", e.what());
        }
    }

    serial::Serial serial_port_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr serial_pub_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SerialListener>());
    rclcpp::shutdown();
    return 0;
}