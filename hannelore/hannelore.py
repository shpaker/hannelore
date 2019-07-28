from enum import Enum, unique

from protocol.client import Client
from protocol.message import Message
from protocol import Detail
from protocol import leds, motor


class Hannelore():

    def __init__(self, port_name='/dev/cu.usbmodem1411', port_speed=19200):
        self.client = Client(name=port_name, speed=port_speed)

    def switch_lights(self,
                      position: leds.Position=leds.Position.FRONT,
                      action: leds.Action=leds.Action.LIGHT,
                      mode: leds.Mode=leds.Mode.NORMAL):

        message = Message(Detail.LEDS, position, action, mode)

        self.client.send(message)

    def accelerate(self,
                   action: motor.Action=motor.Action.FORWARD,
                   mode: motor.Mode=motor.Mode.NORMAL):

        message = Message(detail=Detail.MOTOR,
                          position=motor.Position.ACCELERATOR,
                          action=action,
                          mode=mode)

        self.client.send(message)

        # if action == motor.Action.BACKWARD:
        #     self.switch_lights(position=leds.Position.PARKING,
        #                        action=leds.Action.BLINK,
        #                        mode=leds.Mode.NORMAL)

        # if action == motor.Action.FORWARD:
        #     self.switch_lights(position=leds.Position.PARKING,
        #                        mode=leds.Mode.OFF)

        # if mode == motor.Mode.OFF:
        #     self.switch_lights(position=leds.Position.PARKING,
        #                        action=leds.Action.LIGHT,
        #                        mode=leds.Mode.NORMAL)

    def turn(self, action: motor.Action=motor.Action.RIGHT,
             mode: motor.Mode=motor.Mode.NORMAL):

        message = Message(detail=Detail.MOTOR,
                          position=motor.Position.STEERING,
                          action=action,
                          mode=mode)

        self.client.send(message)

    def shutdown(self):
        self.switch_lights(position=leds.Position.FRONT, mode=leds.Mode.OFF)
        self.switch_lights(position=leds.Position.PARKING, mode=leds.Mode.OFF)
        self.accelerate(mode=motor.Mode.OFF)
        self.turn(mode=motor.Mode.OFF)
        self.client.disconnect()
