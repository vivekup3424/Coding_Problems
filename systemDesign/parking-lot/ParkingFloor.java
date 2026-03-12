import java.util.ArrayList;
import java.util.List;

public class ParkingFloor {
    private int floorNumber;
    private List<ParkingSpot> spots;

    public ParkingFloor(int floorNumber) {
        this.floorNumber = floorNumber;
        this.spots = new ArrayList<>();
    }

    public void addSpot(ParkingSpot spot) {
        spots.add(spot);
    }

    public ParkingSpot findAvailableSpot(VehicleType type) {
        for (ParkingSpot spot : spots) {
            if (spot.getParkingSpotType() == type && spot.isAvailble()) {
                return spot;
            }
        }
        return null;
    }

    public int getFloorNumber() {
        return floorNumber;
    }

    public List<ParkingSpot> getSpots() {
        return spots;
    }

    public int getAvailableCount(VehicleType type) {
        int count = 0;
        for (ParkingSpot spot : spots) {
            if (spot.getParkingSpotType() == type && spot.isAvailble()) {
                count++;
            }
        }
        return count;
    }
}
