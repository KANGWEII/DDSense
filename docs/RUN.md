# Running Guide
This guide walks you through running the sample publisher and subscriber that simulate temperature data.

## [Publisher](../src/publisher/temperature_pub.cpp)
 The publisher is responsible to simulate sensor readings and publishes them to the topic `sensor/temperature`. It initializes a participant, publisher, topic, and data writer, then continuously generates random temperature values with timestamps and sends them every 1 second.
```bash
$ cd DDSense/build/bin
$ sudo ./temperature_publisher
```

## [Subscriber](../src/subscriber/temperature_sub.cpp)
The subscriber is designed to listen to the `sensor/temperature` topic. It sets up a participant, subscriber, topic, and data reader to receive temperature messages published by the corresponding publisher. The subscriber runs continuously, waiting for incoming data.
```bash
$ cd DDSense/build/bin
$ sudo ./temperature_subscriber
```