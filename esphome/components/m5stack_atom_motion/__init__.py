import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c
from esphome.const import (
    CONF_ID,
)

DEVICE_ADDRESS_I2C = 0x38

CHANNEL_ID = 'channel_id'
CONF_ATOM_MOTION_ID = "atom_motion_id"

m5stack_atom_motion_ns = cg.esphome_ns.namespace("m5stack_atom_motion")
M5StackAtomMotion = m5stack_atom_motion_ns.class_("M5StackAtomMotion", cg.Component)

MULTI_CONF = True
CONFIG_SCHEMA = (cv.Schema({
    cv.Required(CONF_ID): cv.declare_id(M5StackAtomMotion),
})
                 .extend(i2c.i2c_device_schema(DEVICE_ADDRESS_I2C))
                 .extend(cv.COMPONENT_SCHEMA))


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)
