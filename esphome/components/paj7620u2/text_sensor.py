import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import text_sensor, i2c
from esphome.const import (
    ENTITY_CATEGORY_DIAGNOSTIC,
    ICON_MOTION_SENSOR,
)
# definitions and constants
DEVICE_ADDRESS_I2C = 0x73
DEFAULT_POLLING_PERIOD = "1s"
CONF_SENSOR_MODE = 'mode'
CONF_SENSOR_MODE_GAME = 'game_mode'
CONF_SENSOR_MODE_NORMAL = 'game_normal'
CONF_GESTURE = 'gesture'


version_ns = cg.esphome_ns.namespace("paj7620u2")
PAJ7620U2Component = version_ns.class_(
    "PAJ7620U2Component", text_sensor.TextSensor, cg.PollingComponent, i2c.I2CDevice
)
SENSOR_MODE_SCHEMA = cv.one_of(CONF_SENSOR_MODE_GAME, CONF_SENSOR_MODE_NORMAL)

CONFIG_SCHEMA = (
    text_sensor.text_sensor_schema(
        icon=ICON_MOTION_SENSOR,
        entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
    )
    .extend(
        {
            cv.GenerateID(): cv.declare_id(PAJ7620U2Component),
            cv.Optional(CONF_SENSOR_MODE, default=CONF_SENSOR_MODE_NORMAL): SENSOR_MODE_SCHEMA,
        }
    )
    .extend(cv.polling_component_schema(DEFAULT_POLLING_PERIOD))
    .extend(i2c.i2c_device_schema(DEVICE_ADDRESS_I2C))
)


async def to_code(config):
    var = await text_sensor.new_text_sensor(config)
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)
