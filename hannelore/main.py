import logging
from time import sleep

from hannelore import Hannelore


if __name__ == '__main__':
    logging.basicConfig(format='%(asctime)s [%(levelname)8s] %(message)s',
                        level=logging.DEBUG)
    car = Hannelore()
    car.switch_lights()
    # sleep(5)
    # car.switch_lights('front', False)
