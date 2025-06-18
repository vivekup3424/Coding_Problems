enum NotificationStatus{
    PENDING = 'PENDING',
    SENT = 'SENT',
    FAILED = 'FAILED',
    READ = 'READ'
}
class Notification{
    public id: string;
    public subscriberId: string;
    public data: Record<string, any>; 
    constructor(
        id: string,
        subscriberId: string,
        data: Record<string, any>
    ){
        this.id = id;
        this.subscriberId = subscriberId;
        this.data = data;
    }
}