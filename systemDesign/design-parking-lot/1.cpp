#include <string>
#include <vector>
enum ParkingType {
  Small,
  Medium,
  Large,
};
enum ParkingStatus { Occupied, Empty };
class ParkingSpot {
public:
  ParkingType type;
  std::string name;
  ParkingStatus status;
};
class ParkingSystem{
public:
	virtual void removeVehicle(std::string licensePlate){}
	virtual void addVehicle(std::string licensePlate){}
};
class ParkingLot : public ParkingSystem{
public:
	ParkingLot(std::vector<ParkingSpot>spots){}
};
