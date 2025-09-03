
abstract class Vehicle{
    void startEngine(){
        System.out.println("engine started");
    }
    abstract void accelarate();
    abstract void brake();
}

class Car extends Vehicle{
    @Override
    void accelarate(){
        System.out.println("Car is accelerating");
    }

    @Override
    void brake(){
        System.out.println("Car is braking...");
    }
}