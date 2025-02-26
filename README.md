# clipboard-task

ubuntu 20.04 build deps
```bash
apt update && apt install -y git g++-10 qt5-default wget libx11-dev
update-alternatives --install /usr/bin/c++ c++ /usr/bin/g++-10 100
wget -O - https://raw.githubusercontent.com/alec-chicherini/development-scripts/refs/heads/main/cmake/install_cmake.sh 2>/dev/null | bash
```

Собрать
```bash
git clone https://github.com/alec-chicherini/clipboard-task.git
cd clipboard-task
mkdir build && cd build
cmake ..
cmake --build .
cpack .
dpkg -i clipboard-task_01.00_amd64.deb
apt-get install -f
```

Подготовить чистую машину для тестов Ubuntu 20.04 - GNOME X - xrdp
```
apt update
apt install ubuntu-desktop #
apt install xrdp
#passwd

```

Запустить
```
#help
clipboard-task --help
#строка
clipboard-task --qt --string="12345string"
clipboard-task --x11 --string="12345string"
#файл
clipboard-task --qt --file=/etc/apt/sources.list
clipboard-task --x11 --file=/etc/apt/sources.list
```

Удалить
```
apt remove clipboard-task
```
