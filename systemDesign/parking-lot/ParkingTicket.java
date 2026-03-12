public class ParkingTicket {
    private Long entryTimeStamp;
    private Long exitTimeStamp;
    public ParkingTicket(Long time){
        this.entryTimeStamp = time;
    }
    public Integer getParkingDuration() {
        return (int)(exitTimeStamp - entryTimeStamp);
    }
    public void setExitTimeStamp(Long exitTimeStamp) {
        this.exitTimeStamp = exitTimeStamp;
    }
}
