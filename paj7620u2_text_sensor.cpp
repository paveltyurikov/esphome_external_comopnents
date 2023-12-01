#include "paj7620u2_text_sensor.h"
#include "esphome/core/helpers.h"
#include "esphome/core/log.h"
#include "esphome/components/i2c/i2c_bus.h"

namespace esphome {
namespace paj7620u2 {

static const char *const TAG = "paj7620u2.text_sensor";

static const  uint8_t BYTE_GESTURE_NONE                 = 0x00;  // No gesture
static const  uint8_t BYTE_GESTURE_UP                   = 0x01;  // Upwards gesture
static const  uint8_t BYTE_GESTURE_DOWN                 = 0x02;  // Downward gesture
static const  uint8_t BYTE_GESTURE_LEFT                 = 0x04;  // Leftward gesture
static const  uint8_t BYTE_GESTURE_RIGHT                = 0x08;  // Rightward gesture
static const  uint8_t BYTE_GESTURE_FORWARD              = 0x10;  // Forward gesture
static const  uint8_t BYTE_GESTURE_BACKWARD             = 0x20;  // Backward gesture
static const  uint8_t BYTE_GESTURE_CLOCKWISE            = 0x40;  // Clockwise circular gesture
static const  uint8_t BYTE_GESTURE_ANTICLOCKWISE        = 0x80;  // Anticlockwise circular gesture
static const  uint8_t BYTE_GESTURE_GESTURE_WAVE         = 0xff;   // Wave gesture

static const uint8_t PART_ID_LSB                        = 0x20;
static const uint8_t PART_ID_MSB                        = 0x76;

static const uint8_t SELECT_BANK_CMD                    = 0xEF;  // W

static const  uint8_t FREQUENCY_MODE_NORMAL             = 0xAC; // 120HZ, 60°/s - 600°/s
static const  uint8_t FREQUENCY_MODE_GAME               = 0x30; // 240HZ, 60°/s - 1200°/s;





std::map<uint8_t, std::string> gestures_map = {
{ BYTE_GESTURE_NONE, "none"},
{ BYTE_GESTURE_UP, "up"},
{ BYTE_GESTURE_DOWN, "down"},
{ BYTE_GESTURE_LEFT, "left"},
{ BYTE_GESTURE_RIGHT, "right"},
{ BYTE_GESTURE_FORWARD, "forward"},
{ BYTE_GESTURE_BACKWARD, "backward"},
{ BYTE_GESTURE_CLOCKWISE, "clockwise"},
{ BYTE_GESTURE_ANTICLOCKWISE, "anticlockwise"},
{ BYTE_GESTURE_GESTURE_WAVE, "gesture_wave"},
};

static const uint8_t INITIAL_REGISTER_VALUES[219][2] = {
    {0xEF,0x00},
    {0x32,0x29},
    {0x33,0x01},
    {0x34,0x00},
    {0x35,0x01},
    {0x36,0x00},
    {0x37,0x07},
    {0x38,0x17},
    {0x39,0x06},
    {0x3A,0x12},
    {0x3F,0x00},
    {0x40,0x02},
    {0x41,0xFF},
    {0x42,0x01},
    {0x46,0x2D},
    {0x47,0x0F},
    {0x48,0x3C},
    {0x49,0x00},
    {0x4A,0x1E},
    {0x4B,0x00},
    {0x4C,0x20},
    {0x4D,0x00},
    {0x4E,0x1A},
    {0x4F,0x14},
    {0x50,0x00},
    {0x51,0x10},
    {0x52,0x00},
    {0x5C,0x02},
    {0x5D,0x00},
    {0x5E,0x10},
    {0x5F,0x3F},
    {0x60,0x27},
    {0x61,0x28},
    {0x62,0x00},
    {0x63,0x03},
    {0x64,0xF7},
    {0x65,0x03},
    {0x66,0xD9},
    {0x67,0x03},
    {0x68,0x01},
    {0x69,0xC8},
    {0x6A,0x40},
    {0x6D,0x04},
    {0x6E,0x00},
    {0x6F,0x00},
    {0x70,0x80},
    {0x71,0x00},
    {0x72,0x00},
    {0x73,0x00},
    {0x74,0xF0},
    {0x75,0x00},
    {0x80,0x42},
    {0x81,0x44},
    {0x82,0x04},
    {0x83,0x20},
    {0x84,0x20},
    {0x85,0x00},
    {0x86,0x10},
    {0x87,0x00},
    {0x88,0x05},
    {0x89,0x18},
    {0x8A,0x10},
    {0x8B,0x01},
    {0x8C,0x37},
    {0x8D,0x00},
    {0x8E,0xF0},
    {0x8F,0x81},
    {0x90,0x06},
    {0x91,0x06},
    {0x92,0x1E},
    {0x93,0x0D},
    {0x94,0x0A},
    {0x95,0x0A},
    {0x96,0x0C},
    {0x97,0x05},
    {0x98,0x0A},
    {0x99,0x41},
    {0x9A,0x14},
    {0x9B,0x0A},
    {0x9C,0x3F},
    {0x9D,0x33},
    {0x9E,0xAE},
    {0x9F,0xF9},
    {0xA0,0x48},
    {0xA1,0x13},
    {0xA2,0x10},
    {0xA3,0x08},
    {0xA4,0x30},
    {0xA5,0x19},
    {0xA6,0x10},
    {0xA7,0x08},
    {0xA8,0x24},
    {0xA9,0x04},
    {0xAA,0x1E},
    {0xAB,0x1E},
    {0xCC,0x19},
    {0xCD,0x0B},
    {0xCE,0x13},
    {0xCF,0x64},
    {0xD0,0x21},
    {0xD1,0x0F},
    {0xD2,0x88},
    {0xE0,0x01},
    {0xE1,0x04},
    {0xE2,0x41},
    {0xE3,0xD6},
    {0xE4,0x00},
    {0xE5,0x0C},
    {0xE6,0x0A},
    {0xE7,0x00},
    {0xE8,0x00},
    {0xE9,0x00},
    {0xEE,0x07},
    {0xEF,0x01},
    {0x00,0x1E},
    {0x01,0x1E},
    {0x02,0x0F},
    {0x03,0x10},
    {0x04,0x02},
    {0x05,0x00},
    {0x06,0xB0},
    {0x07,0x04},
    {0x08,0x0D},
    {0x09,0x0E},
    {0x0A,0x9C},
    {0x0B,0x04},
    {0x0C,0x05},
    {0x0D,0x0F},
    {0x0E,0x02},
    {0x0F,0x12},
    {0x10,0x02},
    {0x11,0x02},
    {0x12,0x00},
    {0x13,0x01},
    {0x14,0x05},
    {0x15,0x07},
    {0x16,0x05},
    {0x17,0x07},
    {0x18,0x01},
    {0x19,0x04},
    {0x1A,0x05},
    {0x1B,0x0C},
    {0x1C,0x2A},
    {0x1D,0x01},
    {0x1E,0x00},
    {0x21,0x00},
    {0x22,0x00},
    {0x23,0x00},
    {0x25,0x01},
    {0x26,0x00},
    {0x27,0x39},
    {0x28,0x7F},
    {0x29,0x08},
    {0x30,0x03},
    {0x31,0x00},
    {0x32,0x1A},
    {0x33,0x1A},
    {0x34,0x07},
    {0x35,0x07},
    {0x36,0x01},
    {0x37,0xFF},
    {0x38,0x36},
    {0x39,0x07},
    {0x3A,0x00},
    {0x3E,0xFF},
    {0x3F,0x00},
    {0x40,0x77},
    {0x41,0x40},
    {0x42,0x00},
    {0x43,0x30},
    {0x44,0xA0},
    {0x45,0x5C},
    {0x46,0x00},
    {0x47,0x00},
    {0x48,0x58},
    {0x4A,0x1E},
    {0x4B,0x1E},
    {0x4C,0x00},
    {0x4D,0x00},
    {0x4E,0xA0},
    {0x4F,0x80},
    {0x50,0x00},
    {0x51,0x00},
    {0x52,0x00},
    {0x53,0x00},
    {0x54,0x00},
    {0x57,0x80},
    {0x59,0x10},
    {0x5A,0x08},
    {0x5B,0x94},
    {0x5C,0xE8},
    {0x5D,0x08},
    {0x5E,0x3D},
    {0x5F,0x99},
    {0x60,0x45},
    {0x61,0x40},
    {0x63,0x2D},
    {0x64,0x02},
    {0x65,0x96},
    {0x66,0x00},
    {0x67,0x97},
    {0x68,0x01},
    {0x69,0xCD},
    {0x6A,0x01},
    {0x6B,0xB0},
    {0x6C,0x04},
    {0x6D,0x2C},
    {0x6E,0x01},
    {0x6F,0x32},
    {0x71,0x00},
    {0x72,0x01},
    {0x73,0x35},
    {0x74,0x00},
    {0x75,0x33},
    {0x76,0x31},
    {0x77,0x01},
    {0x7C,0x84},
    {0x7D,0x03},
    {0x7E,0x01}
};

void PAJ7620U2Component::setup(){
   ESP_LOGD(TAG, "Setup PAJ7620U2Component...");
  this->select_bank_0();               // Default operations on BANK0
  this->initialize_device();           // Set registers up (it ends up with BANK0 selected)
  this->select_bank_0();
}

void PAJ7620U2Component::dump_config() {
  ESP_LOGCONFIG(TAG, "Setting up PAJ7620U2 sensor platform...");
  LOG_I2C_DEVICE(this);
  if (this->is_failed()) {
    ESP_LOGE(TAG, "Connection with PAJ7620U2 failed!");
  }
  LOG_UPDATE_INTERVAL(this);
  LOG_TEXT_SENSOR("", "Gesture sensor", this)
}


void PAJ7620U2Component::update() {
  uint8_t gesture_byte = BYTE_GESTURE_NONE;
  this->get_gestures_reg_0(&gesture_byte);
  std::string gesture = this->gesture_to_string(gesture_byte);

//  if(this->gesture_sensor_!=gesture){
//     this->gesture_sensor_ = gesture;
//     this->publish_state(gesture);
//  }
}

void PAJ7620U2Component::initialize_device(){
  for (uint16_t i = 0; i < sizeof(INITIAL_REGISTER_VALUES)/sizeof(INITIAL_REGISTER_VALUES[0]); i++) {
    this-write_byte(INITIAL_REGISTER_VALUES[i][0], INITIAL_REGISTER_VALUES[i][1]);
  }
}


// Read the gestures interrupt vector #0 - all gestures except wave
bool PAJ7620U2Component::get_gestures_reg_0(uint8_t *data){
    return this->read_register(0x43, data, 1) == 0;
}


// Read the gestures interrupt vector #1 - only holds wave
bool PAJ7620U2Component::get_gestures_reg_1(uint8_t data){
    return this->read_byte(0x44, &data);
}

static const uint8_t BANK0[1] = {0x00};
static const uint8_t BANK1[1] = {0x01};

void PAJ7620U2Component::select_bank_0(){
  this->write_register(SELECT_BANK_CMD, BANK0, 1);
}

void PAJ7620U2Component::select_bank_1(){
  this->write_register(SELECT_BANK_CMD, BANK1, 1);
}


std::string PAJ7620U2Component::gesture_to_string(uint8_t gesture_byte){
    switch (gesture_byte){
        case BYTE_GESTURE_NONE:
           ESP_LOGD(TAG, "Got gesture = none [%#x / %#x ]", BYTE_GESTURE_NONE, gesture_byte);
           return "none";
        case BYTE_GESTURE_UP:
           ESP_LOGD(TAG, "Got gesture = up [%#x / %#x ]", BYTE_GESTURE_UP, gesture_byte);
           return "up";
        case BYTE_GESTURE_DOWN:
           ESP_LOGD(TAG, "Got gesture = down [%#x / %#x ]", BYTE_GESTURE_DOWN, gesture_byte);
           return "down";
        case BYTE_GESTURE_LEFT:
           ESP_LOGD(TAG, "Got gesture = left [%#x / %#x ]", BYTE_GESTURE_LEFT, gesture_byte);
           return "left";
        case BYTE_GESTURE_RIGHT:
           ESP_LOGD(TAG, "Got gesture = right [%#x / %#x ]", BYTE_GESTURE_RIGHT, gesture_byte);
           return "right";
        case BYTE_GESTURE_FORWARD:
           ESP_LOGD(TAG, "Got gesture = forward [%#x / %#x ]", BYTE_GESTURE_FORWARD, gesture_byte);
           return "forward";
        case BYTE_GESTURE_BACKWARD:
           ESP_LOGD(TAG, "Got gesture = backward [%#x / %#x ]", BYTE_GESTURE_BACKWARD, gesture_byte);
           return "backward";
        case BYTE_GESTURE_CLOCKWISE:
           ESP_LOGD(TAG, "Got gesture = clockwise [%#x / %#x ]", BYTE_GESTURE_CLOCKWISE, gesture_byte);
           return "clockwise";
        case BYTE_GESTURE_ANTICLOCKWISE:
           ESP_LOGD(TAG, "Got gesture = anticlockwise [%#x / %#x ]", BYTE_GESTURE_ANTICLOCKWISE, gesture_byte);
           return "anticlockwise";
        default:
           ESP_LOGD(TAG, "Got gesture = default [ default / %#x ]",  gesture_byte);
           return "none";
    }

    return gestures_map[gesture_byte];
}



}  // namespace paj7620u2
}  // namespace esphome