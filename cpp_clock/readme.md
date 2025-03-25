Предварительно в любом в целевом терминале
```bash
source /opt/ros/jazzy/setup.bash
. install/setup.bash
```
Сборка для запуска
```bash
colcon build --packages-select cpp_clock
```
Сборка для отладки
```bash
colcon build --symlink-install --cmake-args -DCMAKE_BUILD_TYPE=RelWithDebInfo
```