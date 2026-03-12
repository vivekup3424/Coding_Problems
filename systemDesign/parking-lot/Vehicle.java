enum VehicleType{
    BIKE, CAR, TRUCK
}
public class Vehicle {
    private String licensePlate;
    private VehicleType type;

    public Vehicle(String licensePlate, VehicleType type){
        this.licensePlate = licensePlate;
        this.type = type;
    }

    public String getlicensePlate() {
        return licensePlate;
    }

    public VehicleType getType() {
        return type;
    }

    public void setLicensePlate(String licensePlate) {
        this.licensePlate = licensePlate;
    }

    public void setType(VehicleType type) {
        this.type = type;
    }
}
