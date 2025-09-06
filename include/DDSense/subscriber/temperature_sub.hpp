#ifndef SUBSCRIBER_TEMPERATURE_SUB_HPP
#define SUBSCRIBER_TEMPERATURE_SUB_HPP

#include "idl/temperature/TemperaturePubSubTypes.hpp"

#include <chrono>
#include <thread>
#include <iostream>

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastdds/dds/subscriber/qos/DataReaderQos.hpp>
#include <fastdds/dds/subscriber/SampleInfo.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>

using namespace eprosima::fastdds::dds;

namespace ddsense {
namespace subscriber {
class TemperatureSub {
 public:
  TemperatureSub();
  virtual ~TemperatureSub();
  bool Init();
  void Run();

 private:
  DomainParticipant* participant_;
  Subscriber* subscriber_;
  DataReader* reader_;
  Topic* topic_;
  TypeSupport type_;

  class SubListener : public DataReaderListener {
   public:
    ~SubListener() override {}

    void on_subscription_matched(
        DataReader*, const SubscriptionMatchedStatus& info) override {
      if (info.current_count_change == 1) {
        std::cout << "Subscriber matched." << std::endl;
      } else if (info.current_count_change == -1) {
        std::cout << "Subscriber unmatched." << std::endl;
      } else {
        std::cout << info.current_count_change
                  << " is not a valid value for SubscriptionMatchedStatus "
                     "current count change"
                  << std::endl;
      }
    }

    void on_data_available(DataReader* reader) override {
      SampleInfo info;
      if (reader->take_next_sample(&temp_, &info) ==
          eprosima::fastdds::dds::RETCODE_OK) {
        if (info.valid_data) {
          std::cout << "Timestamp: " << temp_.timestamp()
                    << ", Temperature: " << temp_.temperature() << std::endl;
        }
      }
    }

    Temperature temp_;
  } listener_;
};
}  // namespace subscriber
}  // namespace ddsense

#endif /* SUBSCRIBER_TEMPERATURE_SUB_HPP */
