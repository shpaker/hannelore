import logging


class Message():
    """
    | detail | position | action | value |
    """

    def __init__(self, detail, position, action, mode):
        self.detail = detail
        self.position = position
        self.action = action
        self.mode = mode

    @property
    def raw(self):
        raw = self.detail.value << 6 | self.position.value << 4
        raw = raw | self.action.value << 2 | self.mode.value

        logmsg = 'Prepared {0}|{1}|{2}|{3} ({4:08b})'
        logging.debug(logmsg.format(self.detail.name, self.position.name,
                                    self.action.name, self.mode.name, raw))

        return raw
