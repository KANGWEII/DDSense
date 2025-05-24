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

# Java JDK
$ sudo apt-get install openjdk-11-jdk
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

## Compiling Fast DDS-Gen
Fast DDS-Gen is a code generation tool for generating C++ source code for the data types defined in an IDL file.

```bash
$ export JAVA_HOME=/usr/lib/jvm/java-11-openjdk-amd64
$ cd DDSense/third_party/fast-dds/Fast-DDS-Gen/
$ ./gradlew assemble
```

Generate the DDS data type for temperature using the provided `Temperature.idl` file

```bash
$ cd DDSense
$ third_party/fast-dds/Fast-DDS-Gen/scripts/fastddsgen -d generated/ idl/temperature/Temperature.idl
```

## Build examples
Flags for the CMake compilation:
| Option                     | Default | Description                                 |
|----------------------------|---------|---------------------------------------------|
| `FAST_DDS_SAMPLE`          | OFF     | Option to build Fast DDS HelloWorld sample  |
| `BUILD_DDSENSE`            | OFF     | Option to build DDSense publisher and subscriber sample  |

```bash
# Build Fast DDS and DDSense Sample
$ cmake -DFAST_DDS_SAMPLE=ON -DBUILD_DDSENSE=ON ..
$ make -j
```