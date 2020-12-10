# ezPoll
An epoll wrapper that is elegant and easy-to-use. Note that this only works on Linux because epoll is a Linux kernel data structure.

## Setup/Testing

Install googletest onto your system if you want to run the library tests. This involves downloading the source files and manually installing them:

To download the source:
```
sudo apt-get install libgtest-dev
```

To install the library:
```
cd /usr/src/gtest
sudo mkdir build
cd build
sudo cmake ..
sudo make
sudo make install
```

Now, running `test.sh` should run all library tests!
