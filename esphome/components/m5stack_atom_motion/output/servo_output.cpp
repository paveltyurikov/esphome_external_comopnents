#include "servo_output.h"
#include "esphome/core/log.h"

namespace esphome {
namespace m5stack_atom_motion {

    static const char *const TAG = "m5stack_atom_motion.output";

    static const uint8_t OUTPUT_REGISTER = 0x02;
    static const uint8_t IDLE_SERVO_VALUE = 90;

    void M5StackMotionOutput::setup() {
        this->parent_->write_byte(this->channel_, IDLE_SERVO_VALUE);
    }

    void M5StackMotionOutput::dump_config() {
      ESP_LOGCONFIG(TAG, "m5stack_atom_motion Output: channel-%u", this->channel_);
    }

    void M5StackMotionOutput::set_channel(uint8_t channel) {
        this->channel_ = channel;
    }

    void M5StackMotionOutput::write_state(float state) {
      uint8_t value = (uint8_t)(state * 1000);
      if (this->parent_->write_byte(this->channel_, value)) {
        ESP_LOGD(TAG, "Got next state: %.3f, value: %d, channel: %u",  state, value, this->channel_);
      } else {
        ESP_LOGE(TAG, "Error writing to channel: %u, state %.3f", this->channel_, &state);
      }
    }

 }  // namespace m5stack_atom_motion
}  // namespace esphome
