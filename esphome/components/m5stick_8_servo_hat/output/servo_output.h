#pragma once

#include "esphome/components/output/float_output.h"
#include "esphome/core/component.h"
#include "esphome/core/log.h"
#include "../m5stick_8_servo_hat.h"

namespace esphome {
namespace m5stick_8_servo_hat {

class M5Stick8ServoHatOutput : public Component, public output::FloatOutput, public Parented<M5Stick8ServoHat> {
 public:
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::DATA - 1; }

  void set_channel(uint8_t channel);

  void write_state(float state) override;

 protected:
  uint8_t channel_;
};

}  // namespace m5stick_8_servo_hat_id
}  // namespace esphome
