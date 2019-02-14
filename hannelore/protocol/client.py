import logging
import serial


class Client():
    """
    """

    def __init__(self, name='/dev/cu.usbmodem1411', bods=9600):
        self.name = name
        self.bods = bods
        self.connection = None

    def connect(self):
        logging.info(f'Connect to {self.name} with {self.bods} bods')
        self.connection = serial.Serial(self.name, self.bods)
        logging.debug(f'Port is openned == {self.connection.is_open}')

    def disconnect(self):
        self.connection.close()

    def send(self, message):

        if not self.connection:
            self.connect()

        send_bytes = self.connection.write(chr(message.raw).encode())

        logging.debug(f'Sended {send_bytes} bytes')

        # raw = self.connection.readline(96)

        # logging.debug(f'Response: {raw}')

        # return raw
