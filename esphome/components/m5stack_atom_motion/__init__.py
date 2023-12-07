import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import automation
from esphome.components import i2c
from esphome.const import (
    CONF_ID,
)

DEVICE_ADDRESS_I2C = 0x38

CHANNEL_ID = 'channel_id'
ANGLE = 'angle'
PULSE = 'pulse'
CONF_ATOM_MOTION_ID = "atom_motion_id"

m5stack_atom_motion_ns = cg.esphome_ns.namespace("m5stack_atom_motion")
M5StackAtomMotion = m5stack_atom_motion_ns.class_("M5StackAtomMotion", cg.Component)
ServoAngleAction = m5stack_atom_motion_ns.class_("ServoAngleAction", automation.Action)
ServoPulseAction = m5stack_atom_motion_ns.class_("ServoPulseAction", automation.Action)

ANGLE_ACTION_SCHEMA = cv.Schema(
    {
        cv.Required(CONF_ID): cv.use_id(M5StackAtomMotion),
        cv.Required(CHANNEL_ID): cv.templatable(
            cv.int_range(1, 4, True, True)
        ),
        cv.Required('angle'): cv.templatable(
            cv.float_range(-180, 180, True, True)
        ),
    }
)
PULSE_ACTION_SCHEMA = cv.Schema(
    {
        cv.Required(CONF_ID): cv.use_id(M5StackAtomMotion),
        cv.Required(CHANNEL_ID): cv.templatable(
            cv.int_range(1, 4, True, True)
        ),
        cv.Required('pulse'): cv.templatable(
            cv.float_range(500, 2500, True, True)
        ),
    }
)

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


@automation.register_action("m5stack_atom_motion.angle", ServoAngleAction, ANGLE_ACTION_SCHEMA)
async def m5stack_atom_motion_angle_to_code(config, action_id, template_arg, args):
    paren = await cg.get_variable(config[CONF_ID])
    var = cg.new_Pvariable(action_id, template_arg, paren)
    if (CHANNEL_ID in config):
        template_ = await cg.templatable(config[CHANNEL_ID], args, int)
        cg.add(var.set_channel_id(template_))
    if (ANGLE in config):
        template_ = await cg.templatable(config[ANGLE], args, float)
        cg.add(var.set_angle(template_))
    return var


@automation.register_action("m5stack_atom_motion.pulse", ServoPulseAction, PULSE_ACTION_SCHEMA)
async def m5stack_atom_motion_angle_to_code(config, action_id, template_arg, args):
    paren = await cg.get_variable(config[CONF_ID])
    var = cg.new_Pvariable(action_id, template_arg, paren)
    if (CHANNEL_ID in config):
        template_ = await cg.templatable(config[CHANNEL_ID], args, int)
        cg.add(var.set_channel_id(template_))
    if (PULSE in config):
        template_ = await cg.templatable(config[PULSE], args, float)
        cg.add(var.set_pulse(template_))
    return var
