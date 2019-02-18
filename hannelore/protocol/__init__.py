from enum import Enum, unique


@unique
class Detail(Enum):
    LEDS = 0
    MOTOR = 1
