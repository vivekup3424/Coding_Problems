
public class ParkingSpot {
    private String id;
    private VehicleType parkingSpotType;
    private Vehicle parkedVehicle;
    private Boolean isOccupied;

    public ParkingSpot(String id, VehicleType type){
        this.id = id;
        this.parkingSpotType = type;
        this.parkedVehicle = null;
        this.isOccupied = false;
    }

    public String getId() {
        return id;
    }

    public VehicleType getParkingSpotType() {
        return parkingSpotType;
    }

    public Vehicle getParkedVehicle() {
        return parkedVehicle;
    }

    public void setId(String id) {
        this.id = id;
    }

    public void setParkingSpotType(VehicleType parkingSpotType) {
        this.parkingSpotType = parkingSpotType;
    }

    public boolean canFitVehicle(Vehicle vehicle){
        return (isOccupied == false && parkingSpotType == vehicle.getType());
    }

    public boolean parkVehicle(Vehicle vehicle) {
        if(vehicle.getType() != parkingSpotType){
            return false;
        }
        parkedVehicle = vehicle;
        isOccupied = true;
        return true;
    }

    public void unparkVehicle(){
        parkedVehicle = null;
        isOccupied = false;
    }

    public boolean isAvailble(){
        return isOccupied == false;
    }
}
