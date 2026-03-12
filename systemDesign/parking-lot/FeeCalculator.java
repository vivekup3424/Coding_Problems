public class FeeCalculator {
    // Rates in dollars per hour
    private static final double BIKE_RATE  = 1.0;
    private static final double CAR_RATE   = 2.0;
    private static final double TRUCK_RATE = 3.0;

    public static double calculate(ParkingTicket ticket, VehicleType type) {
        int durationSeconds = ticket.getParkingDuration();
        double hours = durationSeconds / 3600.0;
        // Charge at least 1 hour minimum
        hours = Math.max(hours, 1.0);

        switch (type) {
            case BIKE:  return hours * BIKE_RATE;
            case CAR:   return hours * CAR_RATE;
            case TRUCK: return hours * TRUCK_RATE;
            default: throw new IllegalArgumentException("Unknown vehicle type: " + type);
        }
    }
}
