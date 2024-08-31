package ticket.booking.entities;
import java.sql.Date;

public class Ticket {
    private String ticketId;
    private String userId;
    private String source;
    private String destination;
    private Date dateOfTravel;
    private Train train;
    public static void main(){
        System.out.println("Hello, from ticket");
    }
}