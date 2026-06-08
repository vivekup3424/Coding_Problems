package tictactoe.app;

public enum Symbol {
    X("1"),
    O("0"),
    EMPTY("");

    private final String value;

    Symbol(String value) {
        this.value = value;
    }

    public String getValue() {
        return value;
    }
}
