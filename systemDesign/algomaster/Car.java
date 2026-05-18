public class Car{
    private String brand;
    private String model;
    private int speed;
    public Car(String brand, String model){
        this.brand = brand;
        this.model = model;
    }
    public void accelerate(int increment){
        speed += increment;
    }

    public void displayStatus(){
        System.out.printf("Car = %s %s is running at: %d kmph", brand, model, speed);
    }
    public static void main(String[] args) throws InterruptedException {
        String[] brands = {"Ferrari", "Lamborghini", "Bugatti", "McLaren"};
        String[] models = {"F40", "Huracán", "Chiron", "720S"};

        System.out.println("=== Street Race ===\n");

        Car[] racers = new Car[brands.length];
        for (int i = 0; i < brands.length; i++) {
            racers[i] = new Car(brands[i], models[i]);
        }

        for (int lap = 1; lap <= 3; lap++) {
            System.out.println("--- Lap " + lap + " ---");
            for (Car car : racers) {
                int boost = (int)(Math.random() * 60) + 20;
                car.accelerate(boost);
                car.displayStatus();
                System.out.println();
            }
            Thread.sleep(500);
        }

        System.out.println("\nRace over! Who won? Check the speeds above!");
    }
}