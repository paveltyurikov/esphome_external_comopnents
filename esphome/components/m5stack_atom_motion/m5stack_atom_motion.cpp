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

};
};