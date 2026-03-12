import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class ParkingLot {
    private final List<ParkingFloor> floors;

    // licensePlate -> ticket (to track entry time)
    private final Map<String, ParkingTicket> activeTickets;
    // licensePlate -> spot (to free it on exit)
    private final Map<String, ParkingSpot> occupiedSpots;

    public ParkingLot() {
        this.floors = new ArrayList<>();
        this.activeTickets = new HashMap<>();
        this.occupiedSpots = new HashMap<>();
    }

    public void addFloor(ParkingFloor floor) {
        floors.add(floor);
    }

    // Returns a ticket on success, null if no spot available or already parked.
    public ParkingTicket parkVehicle(Vehicle vehicle) {
        String plate = vehicle.getlicensePlate();
        if (activeTickets.containsKey(plate)) {
            System.out.println("Vehicle " + plate + " is already parked.");
            return null;
        }

        ParkingSpot spot = findAvailableSpot(vehicle.getType());
        if (spot == null) {
            System.out.println("No available spot for " + vehicle.getType());
            return null;
        }

        spot.parkVehicle(vehicle);

        ParkingTicket ticket = new ParkingTicket(System.currentTimeMillis() / 1000);
        activeTickets.put(plate, ticket);
        occupiedSpots.put(plate, spot);

        System.out.println("Parked " + plate + " at spot " + spot.getId());
        return ticket;
    }

    // Returns the fee charged; -1 if vehicle was not found.
    public double unparkVehicle(Vehicle vehicle) {
        String plate = vehicle.getlicensePlate();
        ParkingTicket ticket = activeTickets.get(plate);
        ParkingSpot spot = occupiedSpots.get(plate);

        if (ticket == null || spot == null) {
            System.out.println("Vehicle " + plate + " not found in the lot.");
            return -1;
        }

        ticket.setExitTimeStamp(System.currentTimeMillis() / 1000);
        double fee = FeeCalculator.calculate(ticket, vehicle.getType());

        spot.unparkVehicle();
        activeTickets.remove(plate);
        occupiedSpots.remove(plate);

        System.out.printf("Vehicle %s unparked. Fee: $%.2f%n", plate, fee);
        return fee;
    }

    public int getAvailableSpots(VehicleType type) {
        int count = 0;
        for (ParkingFloor floor : floors) {
            count += floor.getAvailableCount(type);
        }
        return count;
    }

    private ParkingSpot findAvailableSpot(VehicleType type) {
        for (ParkingFloor floor : floors) {
            ParkingSpot spot = floor.findAvailableSpot(type);
            if (spot != null) return spot;
        }
        return null;
    }

    // --- simple demo ---
    public static void main(String[] args) throws InterruptedException {
        ParkingLot lot = new ParkingLot();

        ParkingFloor f1 = new ParkingFloor(1);
        f1.addSpot(new ParkingSpot("1-A1", VehicleType.CAR));
        f1.addSpot(new ParkingSpot("1-A2", VehicleType.CAR));
        f1.addSpot(new ParkingSpot("1-B1", VehicleType.BIKE));
        f1.addSpot(new ParkingSpot("1-C1", VehicleType.TRUCK));
        lot.addFloor(f1);

        Vehicle car   = new Vehicle("KA-01-1234", VehicleType.CAR);
        Vehicle bike  = new Vehicle("KA-02-5678", VehicleType.BIKE);
        Vehicle truck = new Vehicle("KA-03-9999", VehicleType.TRUCK);

        lot.parkVehicle(car);
        lot.parkVehicle(bike);
        lot.parkVehicle(truck);

        System.out.println("Available CAR spots: " + lot.getAvailableSpots(VehicleType.CAR));

        Thread.sleep(2000); // simulate 2 seconds of parking

        lot.unparkVehicle(car);
        lot.unparkVehicle(bike);

        System.out.println("Available CAR spots after exit: " + lot.getAvailableSpots(VehicleType.CAR));
    }
}
