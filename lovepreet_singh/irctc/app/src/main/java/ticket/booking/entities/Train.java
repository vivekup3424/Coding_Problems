package ticket.booking.entities;

import java.sql.Time;
import java.util.Map;

public class Train {
    private String trainID;
    private String trainNo;
    private Date departTime;
    private Date arrivalTime;
    private List<List<Boolean>> seats;
    private Map<String,Time> stationTime;
    private List<String> stations;
}