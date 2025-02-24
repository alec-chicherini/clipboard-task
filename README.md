# clipboard-task

```
apt update && \
    apt install -y \
    git \
    g++-10 \ 
    qt5-default \
    wget
update-alternatives --install /usr/bin/c++ c++ /usr/bin/g++-10 100
wget -O - https://raw.githubusercontent.com/alec-chicherini/development-scripts/refs/heads/main/cmake/install_cmake.sh 2>/dev/null | bash
```