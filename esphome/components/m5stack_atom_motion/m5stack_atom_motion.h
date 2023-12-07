#pragma once
#include "esphome/core/log.h"
#include "esphome/core/component.h"
#include "esphome/core/automation.h"
#include "esphome/components/i2c/i2c.h"

#define STM32_ADDRESS 0X38

namespace esphome {
  namespace m5stack_atom_motion {

    class M5StackAtomMotion : public Component, public i2c::I2CDevice {
       public:
        void setup() override;
        void dump_config() override;

        bool set_servo_angle(uint8_t channel_id, uint8_t angle);
        // uint8_t read_servo_angle(uint8_t channel_id);

        bool set_servo_pulse(uint8_t channel_id, uint16_t pulse);
//        // uint16_t read_servo_pulse(uint8_t channel_id);
//
//        uint8_t set_motor_speed(uint8_t channel_id, int8_t speed);
//        // int8_t read_motor_speed(uint8_t channel_id);


//       private:
//        void Write2Byte(uint8_t address, uint8_t a_register,
//                                uint16_t data);
//        uint8_t ReadBytes(uint8_t address, uint8_t subAddress, uint8_t count, uint8_t* dest);
    };

    template<typename... Ts> class ServoAngleAction : public Action<Ts...> {
     public:
      explicit ServoAngleAction(M5StackAtomMotion *m5stack_atom_motion) : m5stack_atom_motion_(m5stack_atom_motion) {}

      TEMPLATABLE_VALUE(uint8_t, channel_id)
      TEMPLATABLE_VALUE(uint8_t, angle)

      void play(Ts... x) override {
        auto channel_id = this->channel_id_.optional_value(x...);
        auto angle = this->angle_.optional_value(x...);
        if (channel_id.has_value() && angle.has_value()){
          this->m5stack_atom_motion_->set_servo_angle(channel_id.value(), angle.value());
        }

      }

     protected:
      M5StackAtomMotion *m5stack_atom_motion_;
    };

    template<typename... Ts> class ServoPulseAction : public Action<Ts...> {
     public:
      explicit ServoPulseAction(M5StackAtomMotion *m5stack_atom_motion) : m5stack_atom_motion_(m5stack_atom_motion) {}

      TEMPLATABLE_VALUE(uint8_t, channel_id)
      TEMPLATABLE_VALUE(uint8_t, pulse)

      void play(Ts... x) override {
        auto channel_id = this->channel_id_.optional_value(x...);
        auto pulse = this->pulse_.optional_value(x...);
        if (channel_id.has_value() && pulse.has_value()){
          this->m5stack_atom_motion_->set_servo_pulse(channel_id.value(), pulse.value());
        }

      }

     protected:
      M5StackAtomMotion *m5stack_atom_motion_;
    };

  }
}
