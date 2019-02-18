from enum import Enum, unique


@unique
class Position(Enum):
    STEERING = 0
    ACCELERATOR = 1


# @unique
class Action(Enum):
    FORWARD = 0
    BACKWARD = 1
    LEFT = 0
    RIGHT = 1


@unique
class Mode(Enum):
    OFF = 0
    SLOW = 1
    NORMAL = 2
    FAST = 3
