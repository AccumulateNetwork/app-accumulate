from abc import ABCMeta, abstractmethod
import socket

import requests

class Button(metaclass=ABCMeta):
    @abstractmethod
    def right_click(self):
        ...

    @abstractmethod
    def left_click(self):
        ...

    @abstractmethod
    def both_click(self):
        ...

    @abstractmethod
    def close(self):
        ...


class ButtonFake(Button):
    def right_click(self):
        pass

    def left_click(self):
        pass

    def both_click(self):
        pass

    def close(self):
        pass


class ButtonTCP(Button):
    def __init__(self, server: str, port: int) -> None:
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.connect((server, port))

    def right_click(self):
        self.socket.sendall(b"Rr")

    def left_click(self):
        self.socket.sendall(b"Ll")

    def both_click(self):
        self.socket.sendall(b"LRlr")

    def close(self):
        self.socket.close()

class ButtonCurl(Button):
    def __init__(self, server: str, port: int) -> None:
        self.url = "http://" + server + ":" + str(port)
        self.data = '{"action":"press-and-release"}'

    def right_click(self):
        requests.post(self.url + "/button/right", data=self.data, headers="", timeout=2.5)

    def left_click(self):
        requests.post(self.url + "/button/left", data=self.data, headers="", timeout=2.5)

    def both_click(self):
        requests.post(self.url + "/button/both", data=self.data, headers="", timeout=2.5)

    def close(self):
        pass
