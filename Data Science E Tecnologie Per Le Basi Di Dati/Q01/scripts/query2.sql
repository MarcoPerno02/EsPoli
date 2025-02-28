SELECT L.City, R.Id AS RouteId, R.DepartureStop, R.ArrivalStop, TTM.Name, AVG(F.TravelDuration) AS AvgTravelDuration,
    SUM(SUM(DayIncome)) OVER(PARTITION BY L.City) AS TotalIncomeForCity,
    SUM(DayIncome) / SUM(SUM(DayIncome)) OVER(PARTITION BY L.City, TTM.Name) * 100 AS PercIncomeRouteOnCity,
    RANK() OVER(PARTITION BY L.CITY, TTM.Name ORDER BY SUM(DayIncome) DESC) AS RankPercIncome
FROM Facts F, TypeOfTransportMode TTM, Location L, Timedim T, Route R
WHERE F.TypeOfTransportModeId = TTM.Id and F.LocationId = L.Id and F.TimedimId = T.Id and F.RouteId = R.Id and T.Year >= 2022
GROUP BY L.City, R.Id, R.DepartureStop, R.ArrivalStop, TTM.Name ORDER BY L.City, R.Id, R.DepartureStop, R.ArrivalStop, TTM.Name