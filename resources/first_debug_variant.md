## 1-й вариант настройки отладки через gdbserver согласно [инструкции](https://gist.github.com/JADC362/a4425c2d05cdaadaaa71b697b674425f)
### 1. устанавливаем [gdbserver](https://habr.com/ru/companies/rainbow/articles/251053/):
```bash
sudo apt install gdbserver
```
### Все последующие команды можно выполнять в терминале VScode:
![alt text](../images/image6.png)
![alt text](../images/image7.png)
### в случае необходимости отладки в терминале linux перейдите в рабочую папку проекта:
```bash
cd /home/ros-user/ros2_jazzy/src/ros2/cpp_pubsub
```
### удаляем папки build, install и log
### 2. *После того, как вы правильно реализовали свой код C++ (по крайней мере, скомпилировали), первое, что нужно сделать, это скомпилировать пакет, экспортирующий символы (разрешив точки останова, где вы хотите остановить код):*
```bash
source /opt/ros/jazzy/setup.bash
. install/setup.bash
colcon build --symlink-install --cmake-args -DCMAKE_BUILD_TYPE=RelWithDebInfo
```
### запустить GDB Server для отладки кода CPP. Здесь мы будем использовать localhost:port для создания сервера. Выберите любой свободный порт, который вам нужен:
```bash
ros2 run --prefix 'gdbserver localhost:3000' cpp_pubsub talker
```
### создать launch.json на VSCode. Другими словами, мы создадим пользовательскую конфигурацию отладки. В нашем случае создадим клиент GDB и подключимся к серверу:
1) Откройте VSCode на рабочем столе.
2) Перейдите на боковую панель, в раздел «Запуск и отладка».
3) Добавьте новую конфигурацию (выберите среду C++ или любую другую)
4) В файле launch.json поместите следующую информацию;
```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "C++ Debugger",
            "request": "launch",
            "type": "cppdbg",
            "miDebuggerServerAddress": "localhost:3000",
            "cwd": "/",
            "program": "/home/ros-user/ros2_jazzy/src/ros2/cpp_pubsub/build/cpp_pubsub/talker"
        }
    ]
}
```
- name - Пользовательское имя конфигурации вашего отладчика
- request - В этом случае мы хотим запустить клиент
- type - cppdbg для отладки c++
- miDebuggerServerAddress - path_server:port
- cwd - Где найти все необходимые файлы. Мы используем root, потому что ROS, пакет и другие необходимые файлы распределены по всему ПК.
- program - Измените [build-path-executable] на ваш исполняемый файл сборки. Вы можете найти этот путь в консоли при запуске сервера.

### используйте кнопки и панели VSCode для корректной отладки кода.
#### Такой проект должен получиться: [cpp_pubsub](/cpp_pubsub) Запуск через конфигурацю "C++ Debugger"
![alt text](../images/image8.png)
![alt text](../images/image9.png)