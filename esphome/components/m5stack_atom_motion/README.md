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
    key: {{ api_key }}
  services:
    - service: set_servo_level
      variables:
        level: float
        channel: int
      then:
        - if:
            condition:
              lambda: |-
                return channel == 0;
            then:
              - servo.write:
                  id: ${device_name}_servo_0
                  level: !lambda 'return level;'
        - if:
            condition:
              lambda: |-
                return channel == 1;
            then:
              - servo.write:
                  id: ${device_name}_servo_1
                  level: !lambda 'return level;'
        - if:
            condition:
              lambda: |-
                return channel == 2;
            then:
              - servo.write:
                  id: ${device_name}_servo_2
                  level: !lambda 'return level;'
        - if:
            condition:
              lambda: |-
                return channel == 3;
            then:
              - servo.write:
                  id: ${device_name}_servo_3
                  level: !lambda 'return level;'
```

### Now test servos with `esphomeapi`

Define `ATOM_ADDRESS` and `ATOM_API_KEY` variables in `test_atom_motion.py` script and run it

```python

python test_atom_motion.py
```