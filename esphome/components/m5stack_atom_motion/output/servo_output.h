#pragma once

#include "esphome/components/output/float_output.h"
#include "esphome/core/component.h"
#include "esphome/core/log.h"
#include "../m5stack_atom_motion.h"

namespace esphome {
namespace m5stack_atom_motion {

class M5StackMotionOutput : public Component, public output::FloatOutput, public Parented<M5StackAtomMotion> {
 public:
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::DATA - 1; }

  void set_channel(uint8_t channel);

  void write_state(float state) override;

 protected:
  uint8_t channel_;
};

}  // namespace m5stack_atom_motion
}  // namespace esphome
