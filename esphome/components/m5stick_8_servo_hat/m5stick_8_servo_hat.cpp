#include "esphome/core/log.h"
#include "esphome/core/helpers.h"
#include "./m5stick_8_servo_hat.h"


namespace esphome {
namespace m5stick_8_servo_hat {
    
    static const char *TAG = "m5stick_8_servo_hat";
      
    void M5Stick8ServoHat::setup() {
        ESP_LOGCONFIG(TAG, "Setting up m5stick I2C_8_Servo platform...");
        LOG_I2C_DEVICE(this);
          if (this->is_failed()) {
            ESP_LOGE(TAG, "Communication with I2C_8_Servo failed!");
          }
        this->write_byte(0x30, 1);
    }

    void M5Stick8ServoHat::dump_config() {
      ESP_LOGCONFIG(TAG, "I2C_8_Servo:");
      LOG_I2C_DEVICE(this);
      if (this->is_failed()) {
        ESP_LOGE(TAG, "Communication with I2C_8_Servo failed!");
      }
    }

}; // namespace m5stick_8_servo_hat
}; // namespace esphome