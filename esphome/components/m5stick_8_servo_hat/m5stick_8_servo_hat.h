#pragma once

#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
  namespace m5stick_8_servo_hat {

    class M5Stick8ServoHat : public Component, public i2c::I2CDevice {
       public:
        void setup() override;
        void dump_config() override;
    };

  }
}
