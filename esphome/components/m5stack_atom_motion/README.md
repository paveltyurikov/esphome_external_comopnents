# M5STACK Atom Motion for ESPHome

Component adds output platform for servos and dc-motors

# Configuration example

### Add repo to external components

```yaml
external_components:
  - source:
      type: git
      url: "https://github.com/paveltyurikov/esphome_external_comopnents"
      ref: main
    components: [ m5stack_atom_motion ]
```

### Add `servo`s and `output`s

```yaml
output:
  - platform: m5stack_atom_motion
    id: ${device_name}_servo_0_output
    atom_motion_id: ${device_name}_i2c_device
    channel: 0
    zero_means_zero: true
    min_power: 0 # value important for calculations
    max_power: 1 # value important for calculations
  - platform: m5stack_atom_motion
    id: ${device_name}_servo_1_output
    atom_motion_id: ${device_name}_i2c_device
    channel: 1
    zero_means_zero: true
    min_power: 0 # value important for calculations
    max_power: 1 # value important for calculations
  - platform: m5stack_atom_motion
    id: ${device_name}_servo_2_output
    atom_motion_id: ${device_name}_i2c_device
    channel: 2
    zero_means_zero: true
    min_power: 0 # value important for calculations
    max_power: 1 # value important for calculations
  - platform: m5stack_atom_motion
    id: ${device_name}_servo_3_output
    atom_motion_id: ${device_name}_i2c_device
    channel: 3
    zero_means_zero: true
    min_power: 0 # value important for calculations
    max_power: 1 # value important for calculations


servo:
  - id: ${device_name}_servo_0
    output: ${device_name}_servo_0_output
    min_level: 0 # value important for calculations
    max_level: 0.18 # value important for calculations
    idle_level: 0.09 # value important for calculations
  - id: ${device_name}_servo_1
    output: ${device_name}_servo_1_output
    min_level: 0 # value important for calculations
    max_level: 0.18 # value important for calculations
    idle_level: 0.09 # value important for calculations
  - id: ${device_name}_servo_2
    output: ${device_name}_servo_2_output
    min_level: 0 # value important for calculations
    max_level: 0.18 # value important for calculations
    idle_level: 0.09 # value important for calculations
  - id: ${device_name}_servo_3
    output: ${device_name}_servo_3_output
    min_level: 0 # value important for calculations
    max_level: 0.18 # value important for calculations
    idle_level: 0.09 # value important for calculations
```

## Add tricky api-service

```yaml
api:
  encryption:
    key: {{ your_api_key }}
  services:
    - service: set_servo_angle
      variables:
        my_channel_id: int
        my_angle: int
      then:
        - m5stack_atom_motion.angle:
            id: ${device_name}_i2c_device
            channel_id: !lambda 'return my_channel_id;'
            angle: !lambda 'return my_angle;'
    - service: set_servo_pulse
      variables:
        my_channel_id: int
        my_pulse: int
      then:
        - m5stack_atom_motion.pulse:
            id: ${device_name}_i2c_device
            channel_id: !lambda 'return my_channel_id;'
            pulse: !lambda 'return my_pulse;'
    - service: set_servo_level
      variables:
        my_level: float
        my_channel: int
      then:
        - if:
            condition:
              lambda: |-
                return my_channel == 0;
            then:
              - servo.write:
                  id: ${device_name}_servo_0
                  level: !lambda 'return my_level;'
        - if:
            condition:
              lambda: |-
                return my_channel == 1;
            then:
              - servo.write:
                  id: ${device_name}_servo_1
                  level: !lambda 'return my_level;'
        - if:
            condition:
              lambda: |-
                return my_channel == 2;
            then:
              - servo.write:
                  id: ${device_name}_servo_2
                  level: !lambda 'return my_level;'
        - if:
            condition:
              lambda: |-
                return my_channel == 3;
            then:
              - servo.write:
                  id: ${device_name}_servo_3
                  level: !lambda 'return my_level;'
```

### Now test servos with `esphomeapi`

```python
import asyncio
from time import sleep

import aioesphomeapi

STOP_SERVO_ANGLE_PAYLOAD = 90

SET_SERVO_LEVEL_SERVICE = aioesphomeapi.UserService(name='set_servo_level', key=778842734, args=[
    aioesphomeapi.UserServiceArg(name="my_level", type=aioesphomeapi.UserServiceArgType.FLOAT),
    aioesphomeapi.UserServiceArg(name="my_channel", type=aioesphomeapi.UserServiceArgType.INT),
])


async def list_services(cli):
    """Prints entities and services to console"""
    entities, services = await cli.list_entities_services()
    for e in entities:
        print('[entities]: ', e.name, e.key)

    for s in services:
        print('[services]: ', s.name, s.key)


async def execute_servo_level_service(cli, channel, level):
    """Call servo.write level service on device channel"""
    await cli.execute_service(SET_SERVO_LEVEL_SERVICE, data=
    {
        "my_channel": channel,
        "my_level": level
    })



async def test_servo_level(cli, channel):
    await execute_servo_level_service(cli, channel, 1)
    sleep(1)
    await execute_servo_level_service(cli, channel, 0)


async def main():
    """Connect to an ESPHome device and wait for state changes."""
    cli = aioesphomeapi.APIClient("m5_atom_motion.local", 6053, "",
                                  noise_psk="LFpvKP3GAhSj8XDTBYBuCaiQGAniReaIpB4/NEcCwj0=")

    await cli.connect(login=True)
    await list_services(cli)

    await test_servo_level(cli, 0)
    sleep(2)
    await test_servo_level(cli, 1)
    sleep(2)
    await test_servo_level(cli, 2)
    sleep(2)
    await test_servo_level(cli, 3)


loop = asyncio.get_event_loop()
try:
    asyncio.ensure_future(main())
    loop.run_forever()
except KeyboardInterrupt:
    pass
finally:
    loop.close()
```