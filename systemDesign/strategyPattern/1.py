from abc import ABC, ABCMeta, abstractmethod
from typing import List
class MyABC(ABC):
    def my_method(self):
        pass
class AnotherABC(metaclass = ABCMeta):
    @abstractmethod
    def my_method(self):
        pass