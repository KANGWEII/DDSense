#include "DDSense/publisher/temperature_pub.hpp"

namespace ddsense {
namespace publisher {
TemperaturePub::TemperaturePub()
    : participant_(nullptr),
      publisher_(nullptr),
      topic_(nullptr),
      writer_(nullptr),
      type_(new TemperaturePubSubType()) {}

TemperaturePub::~TemperaturePub() {
  if (writer_ != nullptr) {
    publisher_->delete_datawriter(writer_);
  }
  if (publisher_ != nullptr) {
    participant_->delete_publisher(publisher_);
  }
  if (topic_ != nullptr) {
    participant_->delete_topic(topic_);
  }
  DomainParticipantFactory::get_instance()->delete_participant(participant_);
}

bool TemperaturePub::Init() {
  temp_.timestamp(0);
  temp_.temperature(0.0);

  DomainParticipantQos participant_qos;
  participant_qos.name("Participant_publisher");
  participant_ = DomainParticipantFactory::get_instance()->create_participant(
      0, participant_qos);

  if (participant_ == nullptr) {
    return false;
  }

  type_.register_type(participant_);
  topic_ = participant_->create_topic("sensor/temperature", "Temperature",
                                      TOPIC_QOS_DEFAULT);

  if (topic_ == nullptr) {
    return false;
  }

  publisher_ = participant_->create_publisher(PUBLISHER_QOS_DEFAULT, nullptr);

  if (publisher_ == nullptr) {
    return false;
  }

  writer_ =
      publisher_->create_datawriter(topic_, DATAWRITER_QOS_DEFAULT, &listener_);

  if (writer_ == nullptr) {
    return false;
  }

  return true;
}

bool TemperaturePub::Publish() {
  temp_.timestamp(temp_.timestamp() + 1);
  temp_.temperature(temp_.temperature() + 0.1);
  writer_->write(&temp_);

  return true;
}

void TemperaturePub::Run(uint32_t samples) {
  uint32_t sample_count = 0;
  while (sample_count < samples) {
    if (Publish()) {
      std::cout << "Timestamp: " << temp_.timestamp()
                << " Temperature: " << temp_.temperature() << std::endl;
      sample_count++;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

}  // namespace publisher
}  // namespace ddsense

int main(int argc, char** argv) {
  std::cout << "Starting publisher." << std::endl;
  uint32_t samples = 10;

  ddsense::publisher::TemperaturePub* temp =
      new ddsense::publisher::TemperaturePub();
  if (temp->Init()) {
    temp->Run(samples);
  }

  delete temp;

  return 0;
}