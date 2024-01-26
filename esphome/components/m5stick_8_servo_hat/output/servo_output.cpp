#include "servo_output.h"
#include "esphome/core/log.h"

namespace esphome {
namespace m5stick_8_servo_hat {

    static const char *const TAG = "m5stick_8_servo_hat.output";

    static const uint8_t IDLE_SERVO_VALUE = 90;

    static const float OUTPUT_MIN_POWER = 0;
    static const float OUTPUT_POWER_OFF = IDLE_SERVO_VALUE;
    static const float OUTPUT_MAX_POWER = 180;


    void M5Stick8ServoHatOutput::setup() {
        this->parent_->write_byte(this->channel_, IDLE_SERVO_VALUE);
        this->parent_->write_byte(this->channel_, IDLE_SERVO_VALUE);
    }

    void M5Stick8ServoHatOutput::dump_config() {
      ESP_LOGCONFIG(TAG, "m5stick_8_servo_hat_id Output: channel-%u", this->channel_);
    }

    void M5Stick8ServoHatOutput::set_channel(uint8_t channel) {
        this->channel_ = channel;
    }

    void M5Stick8ServoHatOutput::write_state(float state) {
      uint8_t value = (uint8_t)(state * 1000);
      if (this->parent_->write_byte(this->channel_, value)) {
        ESP_LOGD(TAG, "Got next state: %.3f, value: %d, channel: %u",  &state, &value, &this->channel_);
      } else {
        ESP_LOGE(TAG, "Error writing to channel: %u, state %.3f", this->channel_, &state);
      }
    }

 }  // namespace m5stick_8_servo_hat
}  // namespace esphome
