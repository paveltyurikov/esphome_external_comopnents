#pragma once

#include <map>
#include <string>
#include "esphome/core/log.h"
#include "esphome/core/component.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace paj7620u2 {

class PAJ7620U2Component : public text_sensor::TextSensor, public PollingComponent, public i2c::I2CDevice {
  public:
    // void set_gesture_sensor(std::string *gesture) { gesture_sensor_ = gesture; }
    /// Setup the sensor and test for a connection.
    void setup() override;
    void dump_config() override;
    float get_setup_priority() const override { return setup_priority::DATA; };
    /// Schedule gesture readings.
    void update() override;
    

  private:
    std::string gesture_sensor_;
    void initialize_device();
    std::string gesture_to_string(uint8_t gesture_byte);

    void select_bank_0();
    void select_bank_1();

    bool get_gestures_reg_0(uint8_t *data);
    bool get_gestures_reg_1(uint8_t *data);
};

}  // namespace paj7620u2
}  // namespace esphome