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
    components: [ m5stick_axp192, m5stick_8_servo_hat ]
```

### Add `servo`s and `output`s

```yaml
output:
  - platform: m5stick_8_servo_hat
    id: ${device_name}_servo_0_output
    m5_8_servo_hat_id: ${device_name}_i2c_device
    channel: 0

  - platform: m5stick_8_servo_hat
    id: ${device_name}_servo_1_output
    m5_8_servo_hat_id: ${device_name}_i2c_device
    channel: 1
# ... and so on till 7

servo:
  - id: ${device_name}_servo_0
    output: ${device_name}_servo_0_output
    min_level: 0
    max_level: 0.18 # this values matters
    idle_level: 0.09  # this values matters

  - id: ${device_name}_servo_1
    output: ${device_name}_servo_1_output
    min_level: 0
    max_level: 0.18
    idle_level: 0.09
# ... and so on till 7
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
        - m5stick_8_servo_hat_id.angle:
            id: ${device_name}_i2c_device
            channel_id: !lambda 'return my_channel_id;'
            angle: !lambda 'return my_angle;'
    - service: set_servo_pulse
      variables:
        my_channel_id: int
        my_pulse: int
      then:
        - m5stick_8_servo_hat_id.pulse:
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
        # ... and so on till 7

```

### Now test servos with `esphomeapi`

Define `HOST` and `NOISE_PSK` variables in `test_8_servo_hat.py` script and run it

```shell
python3 test_8_servo_hat.py
```
