# clipboard-task

ubuntu 20.04 build deps
```bash
apt update && apt install -y git g++-10 qt5-default wget libx11-dev
update-alternatives --install /usr/bin/c++ c++ /usr/bin/g++-10 100
wget -O - https://raw.githubusercontent.com/alec-chicherini/development-scripts/refs/heads/main/cmake/install_cmake.sh 2>/dev/null | bash
```

redos 7.3 build deps
```
dnf check-update
dnf install git qt5-qtbase-devel cmake rpmdevtools python-srpm-macros libX11-devel -y
```

Собрать
```bash
git clone https://github.com/alec-chicherini/clipboard-task.git
cd clipboard-task
mkdir build && cd build
cmake ..
cmake --build .
```

Собрать пакет и установить ubuntu 20.04
```
cd clipboard-task/build
cpack -G DEB .
dpkg -i clipboard-task_01.00_amd64.deb
apt-get install -f
```

Собрать пакет и установить redos 7.3
```
cd clipboard-task/build
cpack -G RPM .
dnf install ./clipboard-task_01.00_amd64.rpm
```

Подготовить чистую машину для теста
ubuntu 20.04 - GNOME X - xrdp
```bash
apt update
apt install ubuntu-desktop
apt install xrdp
#passwd

```
redos 7.3 - GNOME X - xrdp
```bash
 dnf groupinstall mate-desktop
 dnf install xrdp xorgxrdp pulseaudio-module-xrdp
 sed -i '/PREFERRED=/d' /etc/sysconfig/desktop 2>/dev/null; echo 'PREFERRED="$(type -p mate-session)"' >> /etc/sysconfig/desktop
 systemctl enable xrdp --now
```

Запустить
```
#help
clipboard-task --help
#строка
clipboard-task --qt --string="12345string"
clipboard-task --x11 --string="12345string"
#файл
clipboard-task --qt --file=/etc/os-release
clipboard-task --x11 --file=/etc/os-release
```

Удалить
```
apt remove clipboard-task
```

```
dnf remove clipboard-task
```
