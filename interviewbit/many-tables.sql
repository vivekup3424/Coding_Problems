SELECT SUM(Count) as A
FROM ENGINEER
INNER JOIN DATA
ON ENGINEER.ID = DATA.ID
GROUP BY DATA.Type
ORDER BY A ASC;
