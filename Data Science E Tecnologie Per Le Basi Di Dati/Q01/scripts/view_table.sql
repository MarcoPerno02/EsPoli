CREATE TABLE FACTS_TTM_DATEMONTH_VIEW_TABLE (
    Name VARCHAR(20),
    DateMonth NUMBER(2),
    Year NUMBER(4),
    MonthIncome NUMBER(10, 2),
    MonthTicketsNumber NUMBER,
    PRIMARY KEY (Name,DateMonth,Year)
)

INSERT INTO FACTS_TTM_DATEMONTH_VIEW_TABLE (Name, DateMonth, Year, MonthIncome, MonthTicketsNumber)
(
    SELECT TTM.Name, T.DateMonth, T.Year, SUM(F.DayIncome), SUM(DayTicketsNumber)
    FROM Facts F, TypeOfTransportMode TTM, Timedim T
    WHERE F.TypeOfTransportModeId = TTM.Id and F.TimedimId = T.Id
    GROUP BY  TTM.Name, T.DateMonth, T.Year
)

CREATE OR REPLACE TRIGGER TRIGGER_FACTS_TTM_DATEMONTH_VIEW_TABLE
AFTER INSERT ON Facts
FOR EACH ROW
DECLARE
    TmpName VARCHAR(20); 
    TmpDateMonth NUMBER(2); 
    TmpYear NUMBER(4);
    N INTEGER;
BEGIN
        SELECT Name INTO TmpName
        FROM TypeOfTransportMode
        WHERE Id = :NEW.TypeOfTransportModeId;

        SELECT DateMonth, Year INTO TmpDateMonth, TmpYear
        FROM Timedim
        WHERE Id = :NEW.TimedimId;

        SELECT COUNT(*) INTO N
        FROM FACTS_TTM_DATEMONTH_VIEW_TABLE
        WHERE Name = TmpName AND DateMonth = TmpDateMonth AND Year = TmpYear;

        IF N > 0 THEN
            UPDATE FACTS_TTM_DATEMONTH_VIEW_TABLE
            SET MonthTicketsNumber = MonthTicketsNumber + :NEW.DayTicketsNumber, 
                MonthIncome = MonthIncome + :NEW.DayIncome
            WHERE Name = TmpName AND DateMonth = TmpDateMonth AND Year = TmpYear;
        ELSE
            INSERT INTO FACTS_TTM_DATEMONTH_VIEW_TABLE (Name, DateMonth, Year, MonthIncome, MonthTicketsNumber)
            VALUES (TmpName, TmpDateMonth, TmpYear, :NEW.DayIncome, :NEW.DayTicketsNumber);
        END IF;
END;
/