#pragma once

#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
  namespace m5stack_atom_motion {

    class M5StackAtomMotion : public Component, public i2c::I2CDevice {
       public:
        void setup() override;
        void dump_config() override;
    };

  }
}
