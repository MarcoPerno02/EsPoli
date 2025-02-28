CREATE MATERIALIZED VIEW FACTS_TTM_DateMonth
BUILD IMMEDIATE
REFRESH FAST ON COMMIT
AS
SELECT TTM.Name, T.DateMonth, T.Year, SUM(F.DayIncome) AS MonthIncome, SUM(DayTicketsNumber) AS MonthTicketsNumber
FROM Facts F, TypeOfTransportMode TTM, Timedim T
WHERE F.TypeOfTransportModeId = TTM.Id and F.TimedimId = T.Id
GROUP BY  TTM.Name, T.DateMonth, T.Year