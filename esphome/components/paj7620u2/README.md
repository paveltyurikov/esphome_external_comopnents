# esphome m5stack PAJ7620U2 Gesture sensor

### example configuration:

```yaml
external_components:
  - source:
      type: git
      path: https://github.com/paveltyurikov/esphome_external_comopnents
      rev: main
    components: [ paj7620u2 ]
    
...
...
...

text_sensor:
  - platform: paj7620u2
    id: ${device_name}_gesture
    name: "${friendly_name} Gesture"
    update_interval: 1s
```