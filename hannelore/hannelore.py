from enum import Enum, unique

from protocol.client import Client
from protocol.message import Message
from protocol import Detail
from protocol import LedAction, LedPosition, LedValue


class Hannelore():

    def __init__(self, port_name='/dev/cu.usbmodem1411', port_bods=9600):
        self.client = Client(port_name, port_bods)

    def switch_lights(self, position=LedPosition.FRONT, action=LedAction.LIGHT,
                      value=LedValue.OFF):
        message = Message(detail=Detail.LED, position=LedPosition.FRONT,
                          action=LedAction.LIGHT, value=LedValue.NORMAL)
        self.client.send(message)

    def set_speed(self, speed):
        pass

    def turn(self, direction):
        pass

    def shutdown(self):
        self.client.disconnect()
