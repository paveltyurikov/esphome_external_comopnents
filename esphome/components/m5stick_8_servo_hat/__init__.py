import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c
from esphome.const import (
    CONF_ID,
)

DEVICE_ADDRESS_I2C = 0x36

CHANNEL_ID = 'channel_id'
CONF_8_SERVO_HAT_ID = "m5_8_servo_hat_id"

m5stick_8_servo_hat_ns = cg.esphome_ns.namespace("m5stick_8_servo_hat")
M5Stick8ServoHat = m5stick_8_servo_hat_ns.class_("M5Stick8ServoHat", cg.Component)


MULTI_CONF = True
CONFIG_SCHEMA = (cv.Schema({
    cv.Required(CONF_ID): cv.declare_id(M5Stick8ServoHat),
})
                 .extend(i2c.i2c_device_schema(DEVICE_ADDRESS_I2C))
                 .extend(cv.COMPONENT_SCHEMA))


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)
