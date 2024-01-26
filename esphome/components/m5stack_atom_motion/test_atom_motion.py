import asyncio
from time import sleep

import aioesphomeapi

STOP_SERVO_ANGLE_PAYLOAD = 90

ATOM_ADDRESS = "{{ node_dns_or_ip_address }}"
ATOM_API_KEY = "{{ node_api:key }}"

SET_SERVO_LEVEL_SERVICE = aioesphomeapi.UserService(
    name='set_servo_level',  # how you defined in api:services section in your config
    key=778842734,  # can see after list_services printed it to console
    args=[
        aioesphomeapi.UserServiceArg(
            name="channel", # this goes to api:services:vars:channel
            type=aioesphomeapi.UserServiceArgType.INT
        ),
        aioesphomeapi.UserServiceArg(
            name="level", # this goes to api:services:vars:channel
            type=aioesphomeapi.UserServiceArgType.FLOAT
        ),
    ])


async def list_services(cli):
    """ Useful hook to see how services named """
    entities, services = await cli.list_entities_services()
    for e in entities:
        print('[entities]: ', e.name, e.key)

    for s in services:
        print('[services]: ', s.name, s.key)


async def execute_servo_level_service(cli, channel, level):
    await cli.execute_service(SET_SERVO_LEVEL_SERVICE, data=
    {
        "channel": channel,
        "level": level
    })


async def test_servo_level(cli, channel):
    await execute_servo_level_service(cli, channel, -1)
    sleep(1)
    await execute_servo_level_service(cli, channel, 1)
    sleep(1)
    await execute_servo_level_service(cli, channel, 0)
    sleep(1)


async def main():
    """Connect to an ESPHome device and wait for state changes."""
    cli = aioesphomeapi.APIClient(ATOM_ADDRESS, 6053, "", noise_psk=ATOM_API_KEY)
    await cli.connect(login=True)

    await list_services(cli)

    await test_servo_level(cli, 0)
    sleep(1)
    await test_servo_level(cli, 1)
    sleep(1)
    await test_servo_level(cli, 3)
    sleep(1)
    await test_servo_level(cli, 4)


loop = asyncio.get_event_loop()
try:
    asyncio.ensure_future(main())
    loop.run_forever()
except KeyboardInterrupt:
    pass
finally:
    loop.close()
