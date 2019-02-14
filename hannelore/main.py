import logging
from time import sleep
from time import sleep
from hannelore import Hannelore
from protocol import LedAction, LedPosition, LedValue


if __name__ == '__main__':
    logging.basicConfig(format='%(asctime)s [%(levelname)8s] %(message)s',
                        level=logging.DEBUG)
    car = Hannelore()
    car.switch_lights(position=LedPosition.FRONT,
                      action=LedAction.BLINK,
                      value=LedValue.FAST)
    # sleep(5)
    # while(True):
    #     car.switch_lights(value=LedValue.OFF)
    #     sleep(.1)
    #     car.switch_lights(value=LedValue.NORMAL)
    #     sleep(.1)
