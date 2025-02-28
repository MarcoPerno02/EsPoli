SELECT T.Year, T.DateMonth,TTM.Name,
    SUM(SUM(F.DayTicketsNumber)) OVER(PARTITION BY T.DateMonth, TTM.Name) / COUNT(DISTINCT T.DayDate) AS AvgDayTicketsNumber,
	SUM(SUM(F.DayTicketsNumber)) OVER(PARTITION BY T.Year, TTM.Name ORDER BY T.Year, T.DateMonth ROWS UNBOUNDED PRECEDING) AS CumulativeTicketsSumForMonth,
    SUM(F.DayTicketsNumber) / SUM(SUM(F.DayTicketsNumber)) OVER(PARTITION BY T.YEAR, T.DateMonth) * 100 AS PercentualTicketsForTypeTransportaionModeForMonth
FROM Facts F, TypeOfTransportMode TTM, Timedim T
WHERE F.TypeOfTransportModeId = TTM.Id and F.TimedimId = T.Id
GROUP BY TTM.Name, T.DateMonth, T.Year ORDER BY T.Year, T.DateMonth, TTM.Name
