class BankAccount {
    private String accountNumber;
    private String ownerName;
    private Integer balance;

    public BankAccount(String _accountNumber, String _ownerName){
        this.accountNumber = _accountNumber;
        this.ownerName = _ownerName;
    }
    void deposit(Integer sum){
        balance += sum;
    }
    void withdraw(Integer diff){
        if(diff >  balance) throw new RuntimeException("insufficient balance");
        balance -= diff;
    }
    Integer getBalance(){
        return balance;
    }
    
}
