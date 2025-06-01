#include "DDSense/subscriber/temperature_sub.hpp"

namespace ddsense {
namespace subscriber {
TemperatureSub::TemperatureSub()
    : participant_(nullptr),
      subscriber_(nullptr),
      topic_(nullptr),
      reader_(nullptr),
      type_(new TemperaturePubSubType()) {}

TemperatureSub::~TemperatureSub() {
  if (reader_ != nullptr) {
    subscriber_->delete_datareader(reader_);
  }
  if (topic_ != nullptr) {
    participant_->delete_topic(topic_);
  }
  if (subscriber_ != nullptr) {
    participant_->delete_subscriber(subscriber_);
  }
  DomainParticipantFactory::get_instance()->delete_participant(participant_);
}

bool TemperatureSub::Init() {
  DomainParticipantQos participant_qos;
  participant_qos.name("Participant_subscriber");
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

  subscriber_ =
      participant_->create_subscriber(SUBSCRIBER_QOS_DEFAULT, nullptr);

  if (subscriber_ == nullptr) {
    return false;
  }

  reader_ = subscriber_->create_datareader(topic_, DATAREADER_QOS_DEFAULT,
                                           &listener_);

  if (reader_ == nullptr) {
    return false;
  }

  return true;
}

void TemperatureSub::Run() {
  while (true) {
  }
}

}  // namespace subscriber
}  // namespace ddsense

int main(int argc, char** argv) {
  std::cout
      << "Subscribing temperature sensor data from topic 'sensor/temperature'"
      << std::endl;

  ddsense::subscriber::TemperatureSub* temp =
      new ddsense::subscriber::TemperatureSub();
  if (temp->Init()) {
    temp->Run();
  }

  delete temp;
  return 0;
}
