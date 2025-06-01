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

float TemperaturePub::GenerateTemperature() {
  return std::round(
             (kAverageTemp + ((2.0f * rand() / RAND_MAX - 1.0f) * kDeviation)) *
             10.0f) /
         10.0f;
}

bool TemperaturePub::Publish() {
  temp_.timestamp(
      std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
  temp_.temperature(GenerateTemperature());
  writer_->write(&temp_);

  return true;
}

void TemperaturePub::Run() {
  while (Publish()) {
    // std::cout << "Timestamp: " << temp_.timestamp()
    //           << ", Temperature: " << temp_.temperature() << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
}

}  // namespace publisher
}  // namespace ddsense

int main(int argc, char** argv) {
  std::cout
      << "Publishing temperature sensor data to topic 'sensor/temperature'"
      << std::endl;

  ddsense::publisher::TemperaturePub* temp =
      new ddsense::publisher::TemperaturePub();
  if (temp->Init()) {
    temp->Run();
  }

  delete temp;

  return 0;
}