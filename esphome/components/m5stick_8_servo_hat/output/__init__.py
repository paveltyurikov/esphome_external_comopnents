import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c, output
from esphome.const import CONF_ID, CONF_CHANNEL

from .. import m5stick_8_servo_hat_ns, M5Stick8ServoHat, CONF_8_SERVO_HAT_ID

DEPENDENCIES = ["m5stick_8_servo_hat"]

M5Stick8ServoHatOutput = m5stick_8_servo_hat_ns.class_(
    "M5Stick8ServoHatOutput", cg.Component, i2c.I2CDevice, output.FloatOutput
)

CONFIG_SCHEMA = output.FLOAT_OUTPUT_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(M5Stick8ServoHatOutput),
        cv.GenerateID(CONF_8_SERVO_HAT_ID): cv.use_id(M5Stick8ServoHat),
        cv.Required(CONF_CHANNEL): cv.hex_int_range(min=0, max=3),
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await output.register_output(var, config)

    await cg.register_parented(var, config[CONF_8_SERVO_HAT_ID])

    cg.add(var.set_channel(config[CONF_CHANNEL]))
