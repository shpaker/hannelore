import logging

import serial
from serial import SerialException

from protocol.message import Message


class Client():

    def __init__(self, name: str, speed: int):
        self.name = name
        self.speed = speed
        self.connection = None

    def connect(self):
        logging.debug(f'Connect to {self.name} (speed {self.speed} bit/s)')

        try:
            self.connection = serial.Serial(self.name, self.speed)
        except SerialException as err:
            logging.warning(err)

    def disconnect(self):
        self.connection.close()

    def send(self, message: Message):
        if not self.connection or not self.connection.is_open:
            self.connect()

        if self.connection.is_open:
            raw_bytes = chr(message.raw).encode()
            try:
                byte_sended = self.connection.write(raw_bytes)
            except SerialException:
                self.connection.close()

            return message, byte_sended

        logging.warning('Unable to send {} to {}'.format(message.action.name,
                                                         message.detail.name))
