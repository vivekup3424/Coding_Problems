import java.util.ArrayList;
import java.util.List;

class TemperatureSensor {
    private List<Double> readings = new ArrayList<>();

    public void addReading(double value){
        readings.add(value);
    }
    
    public double getAverage(){
        int n = readings.size();
        double total = 0;
        for(double reading : readings){
            total += reading;
        }
        return total / n;
    }

    public int getReadingCount(){
        return readings.size();
    }

    public List<Double> getReadings(){
        return readings;
    }
}
