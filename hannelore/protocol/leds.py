from enum import Enum, unique


@unique
class Position(Enum):
    FRONT = 0
    PARKING = 1


@unique
class Action(Enum):
    LIGHT = 0
    BLINK = 1


@unique
class Mode(Enum):
    OFF = 0
    SLOW = 1
    NORMAL = 2
    FAST = 3
