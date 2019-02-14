from enum import Enum, unique


@unique
class Detail(Enum):
    LED = 0
    MOTOR = 1


@unique
class LedPosition(Enum):
    FRONT = 0
    PARKING = 1


@unique
class LedAction(Enum):
    LIGHT = 0
    BLINK = 1


@unique
class LedValue(Enum):
    OFF = 0
    SLOW = 1
    NORMAL = 2
    FAST = 3
