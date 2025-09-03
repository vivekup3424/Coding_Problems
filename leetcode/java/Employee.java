class Employee {
    private String name;
    private Float salary;
    public Employee(String _name, Float _salary){
        this.name = _name;
        this.salary = _salary;
    }
    public String getName(){
        return this.name;
    }
    public Float getSalary(){
        return this.salary;
    }
    public void setName(String name){
        this.name = name;
    }
    public void setSalary(Float newSalary){
        this.salary = newSalary;
    }
    public void displayDetails(){
        System.out.println("Employee: "+ name);
        System.out.println("Salary: "+ salary);
    }
    public static void main(String[] args){
        Employee jack = new Employee("Jack Jackson", 78686.0f);
        jack.displayDetails();
    }
}