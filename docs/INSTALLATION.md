# Installation Guide
This code should compile on any recent Linux distribution with a C++11/14/17-compatible compiler. Development and testing were performed on Ubuntu 24.04.2 LTS.

## Install Dependencies

```bash
# System Dependencies
$ sudo apt-get install cmake g++ python3-pip wget git

# Asio and TinyXML2 libraries
$ sudo apt-get install libasio-dev libtinyxml2-dev

# OpenSSL
$ sudo apt-get install libssl-dev

# Libp11 and SoftHSM libraries
$ sudo apt-get install libp11-dev softhsm2 libengine-pkcs11-openssl
```

## Getting this repository
```bash
$ git clone --recursive https://github.com/KANGWEII/DDSense.git
```

## Build the Workspace
After installing the required system dependencies, compile and install eProsima Fast DDS and its dependencies system-wide using the steps below. For local installation, refer to the official [guide](https://fast-dds.docs.eprosima.com/en/latest/installation/sources/sources_linux.html#local-installation).

Flags for the CMake compilation:
| Option                     | Default | Description                                 |
|----------------------------|---------|---------------------------------------------|
| `DBUILD_FAST_DEPENDENCIES` | OFF     | Option to build Fast DDS dependencies       |
| `DBUILD_FAST_DDS`          | OFF     | Option to build Fast DDS                    |
| `FAST_DDS_SAMPLE`          | OFF     | Option to build Fast DDS HelloWorld sample  |

```bash
$ cd DDSense
$ mkdir build && cd build

# Build Fast DDS dependencies
$ cmake -DBUILD_FAST_DEPENDENCIES=ON ..
$ sudo make install

# Build Fast DDS
$ cmake -DBUILD_FAST_DDS=ON ..
$ sudo make install
```