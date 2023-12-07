#include "esphome/core/log.h"
#include "esphome/core/helpers.h"
#include "m5stack_atom_motion.h"


namespace esphome {
namespace m5stack_atom_motion {
    
    static const char *TAG = "m5stack_atom_motion";
      
    void M5StackAtomMotion::setup() {
        ESP_LOGCONFIG(TAG, "Setting up m5stack Atom Motion platform...");
        LOG_I2C_DEVICE(this);
          if (this->is_failed()) {
            ESP_LOGE(TAG, "Communication with m5stack Atom Motion failed!");
          }
    }

    void M5StackAtomMotion::dump_config() {
      ESP_LOGCONFIG(TAG, "m5stack Atom Motion:");
      LOG_I2C_DEVICE(this);
      if (this->is_failed()) {
        ESP_LOGE(TAG, "Communication with m5stack Atom Motion failed!");
      }
    }

    /*
    void M5StackAtomMotion::Write2Byte(uint8_t address, uint8_t a_register,
                                uint16_t data) {
        Wire.beginTransmission(address);
        Wire.write(a_register);
        Wire.write(data >> 8);    // MSB
        Wire.write(data & 0xFF);  // LSB

        Wire.endTransmission();
    }

    uint8_t M5StackAtomMotion::ReadBytes(uint8_t address, uint8_t a_read_register,
                                  uint8_t count, uint8_t *dest) {
        Wire.beginTransmission(address);  // Initialize the Tx buffer
        Wire.write(a_read_register);           // Put slave register address in Tx buffer
        uint8_t i = 0;
        if (Wire.endTransmission(false) == 0 &&
            Wire.requestFrom(address, (uint8_t)count)) {
            while (Wire.available()) {
                dest[i++] = Wire.read();
            }
            return true;
        }
        return false;
    }*/

    /*******************************************************************************/

    bool M5StackAtomMotion::set_servo_angle(uint8_t channel_id, uint8_t angle) {
        ESP_LOGD(TAG, "set_servo_angle action... channel_id: %#x, angle: %d", channel_id, angle);
        uint8_t a_register = channel_id - 1;
        if (angle > 0 || angle < 180) return false;
        if (a_register > 3) return false;
        this->write_byte(a_register, angle);
    }

    bool M5StackAtomMotion::set_servo_pulse(uint8_t channel_id, uint16_t pulse) {
        ESP_LOGD(TAG, "set_servo_pulse action... channel_id: %#x, pulse: %i", channel_id, pulse);
//        if(pulse<500||pulse>2500){
//         ESP_LOGD(TAG, "Pulse should be 500-2500", pulse);
//         return false;
//        }
        this->write_byte_16(channel_id, 600);
    }
//
//    uint8_t M5StackAtomMotion::set_motor_speed(uint8_t Motor_CH, int8_t speed)  // 0x10 ->16
//    {
//        uint8_t channel_id = Motor_CH - 1;
//        if (channel_id > 1) return 1;
//        if(speed > 127) return 1;
//        if(speed < -127) return 1;
//        uint8_t a_register = channel_id + 32;
//
//        this->write_byte(a_register, (uint8_t)speed);
//
//        return 0;
//    }

//    uint8_t M5StackAtomMotion::read_servo_angle(uint8_t channel_id) {
//        uint8_t data             = 0;
//        uint8_t a_register = channel_id - 1;
//        ReadBytes(STM32_ADDRESS, a_register, 1, &data);
//        return data;
//    }

//    uint16_t M5StackAtomMotion::read_servo_pulse(uint8_t channel_id) {
//        uint8_t data[2];
//        uint8_t channel_id         = channel_id - 1;
//        uint8_t a_register = 2 * channel_id | 0x10;
//        ReadBytes(STM32_ADDRESS, a_register, 2, data);
//        return (data[0] << 8) + data[1];
//    }

//    int8_t M5StackAtomMotion::read_motor_speed(uint8_t Motor_CH) {
//        int8_t data      = 0;
//        uint8_t channel_id = Motor_CH - 1;
//        if (channel_id > 1) return 1;
//        uint8_t a_register = channel_id | 0x20;
//        ReadBytes(STM32_ADDRESS, a_register, 1, (uint8_t *)&data);
//        return data;
//    }

};
};