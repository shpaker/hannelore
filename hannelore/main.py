import logging

from flask import Flask, render_template, request

from hannelore import Hannelore
from protocol import leds, motor


app = Flask(__name__)
car = Hannelore()


@app.route('/')
def index():
    return render_template('index.html')


@app.route('/lights', methods=['POST'])
def lights():
    """
    """
    if request.method == 'POST':
        data = request.json
        position = data['position']
        action = data['action']
        mode = data['mode']

        car.switch_lights(position=leds.Position[position.upper()],
                          action=leds.Action[action.upper()],
                          mode=leds.Mode[mode.upper()])

        return '{}'


@app.route('/power', methods=['POST'])
def power():
    """
    """
    if request.method == 'POST':
        mode = request.json['mode']

        car.shutdown()

        return '{}'


@app.route('/accelerator', methods=['POST'])
def accerator():
    """
    """
    if request.method == 'POST':
        data = request.json
        action = data['action']
        mode = data['mode']

        car.accelerate(action=motor.Action[action.upper()],
                       mode=motor.Mode[mode.upper()])

        return '{}'


@app.route('/steering', methods=['POST'])
def steering():
    """
    """
    if request.method == 'POST':
        data = request.json
        action = data['action']
        mode = data['mode']

        car.turn(action=motor.Action[action.upper()],
                 mode=motor.Mode[mode.upper()])

        return '{}'

if __name__ == '__main__':
    logging.basicConfig(format='%(asctime)s [%(levelname)8s] %(message)s',
                        level=logging.DEBUG)

    app.run(debug=True)
