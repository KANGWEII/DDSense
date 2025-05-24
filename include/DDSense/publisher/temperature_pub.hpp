#ifndef PUBLISHER_TEMPERATURE_PUB_HPP
#define PUBLISHER_TEMPERATURE_PUB_HPP

#include "idl/temperature/TemperaturePubSubTypes.hpp"

#include <chrono>
#include <thread>
#include <iostream>

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>

using namespace eprosima::fastdds::dds;

namespace ddsense {
namespace publisher {
class TemperaturePub {
 public:
  TemperaturePub();
  virtual ~TemperaturePub();
  bool Init();
  bool Publish();
  void Run(uint32_t samples);

 private:
  Temperature temp_;
  DomainParticipant* participant_;
  Publisher* publisher_;
  Topic* topic_;
  DataWriter* writer_;
  TypeSupport type_;

  class PubListener : public DataWriterListener {
   public:
    PubListener() : matched_(0) {}
    ~PubListener() override {}

    void on_publication_matched(DataWriter*,
                                const PublicationMatchedStatus& info) override {
      if (info.current_count_change == 1) {
        matched_ = info.total_count;
        std::cout << "Publisher matched." << std::endl;
      } else if (info.current_count_change == -1) {
        matched_ = info.total_count;
        std::cout << "Publisher unmatched." << std::endl;
      } else {
        std::cout << info.current_count_change
                  << " is not a valid value for PublicationMatchedStatus "
                     "current count change."
                  << std::endl;
      }
    }

    std::atomic_int matched_;
  } listener_;
};
}  // namespace publisher
}  // namespace ddsense

#endif /* PUBLISHER_TEMPERATURE_PUB_HPP */
