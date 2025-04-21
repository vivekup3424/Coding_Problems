from abc import ABC
from enum import Enum
from typing import Optional


class VehicleType(Enum):
    """
    Enum representing different types of vehicles.
    """
    CAR = 1
    MOTORCYCLE = 2
    TRUCK = 3


class Vehicle(ABC):
    """
    Abstract base class for all vehicles.
    """
    def __init__(self, license_plate: str, vehicle_type: VehicleType):
        """
        Initialize a vehicle with a license plate and its type.
        """
        self.license_plate = license_plate
        self.type = vehicle_type


class Car(Vehicle):
    """
    Represents a car vehicle.
    """
    def __init__(self, license_plate: str):
        super().__init__(license_plate, VehicleType.CAR)


class Truck(Vehicle):
    """
    Represents a truck vehicle.
    """
    def __init__(self, license_plate: str):
        super().__init__(license_plate, VehicleType.TRUCK)


class MotorCycle(Vehicle):
    """
    Represents a motorcycle vehicle.
    """
    def __init__(self, license_plate: str):
        super().__init__(license_plate, VehicleType.MOTORCYCLE)


class ParkingSpot:
    """
    Represents a parking spot which can hold a vehicle of a certain type.
    """
    def __init__(self, spot_number: int):
        self.spot_number = spot_number
        self.vehicle_type = VehicleType.CAR  # Can be extended to support different types
        self.parked_vehicle: Optional[Vehicle] = None

    def is_available(self) -> bool:
        """
        Check if the spot is available.
        """
        return self.parked_vehicle is None

    def park_vehicle(self, vehicle: Vehicle) -> None:
        """
        Park a vehicle in the spot if it matches the type and is available.
        """
        if self.is_available() and vehicle.type == self.vehicle_type:
            self.parked_vehicle = vehicle
        else:
            raise ValueError("Invalid vehicle type or spot already occupied")

    def unpark_vehicle(self) -> None:
        """
        Remove the vehicle from the parking spot.
        """
        self.parked_vehicle = None


class Level:
    """
    Represents a level in the parking lot with multiple parking spots.
    """
    def __init__(self, floor: int, num_spots: int):
        self.floor = floor
        self.parking_spots = [ParkingSpot(i) for i in range(num_spots)]

    def park_vehicle(self, vehicle: Vehicle) -> bool:
        """
        Try to park a vehicle in the first available matching spot.
        """
        for spot in self.parking_spots:
            if spot.is_available() and spot.vehicle_type == vehicle.type:
                spot.park_vehicle(vehicle)
                return True
        return False

    def unpark_vehicle(self, vehicle: Vehicle) -> bool:
        """
        Unpark the specified vehicle from the level.
        """
        for spot in self.parking_spots:
            if not spot.is_available() and spot.parked_vehicle == vehicle:
                spot.unpark_vehicle()
                return True
        return False

    def display_availability(self) -> None:
        """
        Display availability of all parking spots on the level.
        """
        print(f"Level {self.floor} Availability:")
        for spot in self.parking_spots:
            status = "Available" if spot.is_available() else "Occupied"
            print(f"  Spot {spot.spot_number}: {status}")


class ParkingLot:
    """
    Singleton class representing the entire parking lot with multiple levels.
    """
    _instance = None

    def __init__(self):
        """
        Initialize the parking lot.
        """
        ParkingLot._instance = self
        self.levels: list[Level] = []

    @staticmethod
    def get_instance():
        """
        Return the singleton instance of the parking lot.
        """
        if ParkingLot._instance is None:
            ParkingLot()
        return ParkingLot._instance

    def add_level(self, level: Level) -> None:
        """
        Add a level to the parking lot.
        """
        self.levels.append(level)

    def park_vehicle(self, vehicle: Vehicle) -> bool:
        """
        Try to park a vehicle in any of the levels.
        """
        for level in self.levels:
            if level.park_vehicle(vehicle):
                return True
        return False

    def display_availibility(self) -> None:
        """
        Display the availability of all levels in the parking lot.
        """
        for level in self.levels:
            level.display_availability()

