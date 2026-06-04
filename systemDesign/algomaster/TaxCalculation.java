// Before: Each processor duplicates tax calculation

interface TaxCalculator{
    public Double getTotal(double amount);
}
class USTaxCalculator implements TaxCalculator{
    public Double getTotal(double amount){
        return amount * 1.1;
    }
}
class EUTaxCalculator implements TaxCalculator{
    public Double getTotal(double amount){
        return amount * 1.2;
    }
}
class UKTaxCalculator implements TaxCalculator{
    public Double getTotal(double amount){
        return amount * 1.15;
    }
}
class USOrderProcessor {
    public void processOrder(double amount, TaxCalculator taxCalculator) {
        double total = taxCalculator.getTotal(amount);
        System.out.println("US Order - Subtotal: $" + amount
            + ", Tax: $" + tax + ", Total: $" + total);
    }
}

class EUOrderProcessor {
    public void processOrder(double amount, TaxCalculator taxCalculator) {
        double total = taxCalculator.getTotal(amount);
        System.out.println("EU Order - Subtotal: $" + amount
            + ", Tax: $" + tax + ", Total: $" + total);
    }
}

class UKOrderProcessor {
    public void processOrder(double amount, TaxCalculator taxCalculator) {
        double total = taxCalculator.getTotal(amount);
        System.out.println("UK Order - Subtotal: $" + amount
            + ", Tax: $" + tax + ", Total: $" + total);
    }
}

// TODO: Extract a TaxCalculator interface and region implementations.
// TODO: Refactor OrderProcessor to accept a TaxCalculator.

public class TaxCalculation {
    public static void main(String[] args) {
        // After refactoring, usage should look like:
        // OrderProcessor usProcessor = new OrderProcessor(new USTaxCalculator());
        // usProcessor.processOrder(100.0);
    }
}