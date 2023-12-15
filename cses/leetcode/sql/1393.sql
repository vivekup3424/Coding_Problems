// add case statement inside the sum statement

1.
SELECT stock_name, SUM(
    CASE
    WHEN operation = "Buy" THEN -price
    WHEN operation = "Sell" THEN price
    END
) AS capital_gain_loss
FROM stocks
GROUP BY stock_name;

2. Using if/else
SELECT stock_name, SUM(
    IF(operation="Buy",-1,1)
)*price as capital_gain_loss
FROM stocks
GROUP BY stock_name;