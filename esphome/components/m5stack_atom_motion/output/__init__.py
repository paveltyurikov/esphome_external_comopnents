import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c, output
from esphome.const import CONF_ID, CONF_CHANNEL

from .. import m5stack_atom_motion_ns, M5StackAtomMotion, CONF_ATOM_MOTION_ID

DEPENDENCIES = ["m5stack_atom_motion"]

M5StackMotionOutput = m5stack_atom_motion_ns.class_(
    "M5StackMotionOutput", cg.Component, i2c.I2CDevice, output.FloatOutput
)

CONFIG_SCHEMA = output.FLOAT_OUTPUT_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(M5StackMotionOutput),
        cv.GenerateID(CONF_ATOM_MOTION_ID): cv.use_id(M5StackAtomMotion),
        cv.Required(CONF_CHANNEL): cv.hex_int_range(min=0, max=3),
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await output.register_output(var, config)

    await cg.register_parented(var, config[CONF_ATOM_MOTION_ID])

    cg.add(var.set_channel(config[CONF_CHANNEL]))
