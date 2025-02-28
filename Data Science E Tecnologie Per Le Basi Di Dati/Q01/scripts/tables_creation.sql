CREATE TABLE Location (
    Id NUMBER PRIMARY KEY,
    City VARCHAR2(100),
    Province VARCHAR2(100),
    Region VARCHAR2(100)
);

CREATE TABLE TypeOfDiscount (
    Id NUMBER PRIMARY KEY,
    Name VARCHAR2(100)
);

CREATE TABLE TimeSlot (
    Id NUMBER PRIMARY KEY,
    TimeSlot VARCHAR2(50),
    IsPeakTime NUMBER(1) -- Usa 0 (FALSE) e 1 (TRUE)
);

/*CREATE TABLE Timedim (
    Id NUMBER PRIMARY KEY,
    DayDate DATE,
    DateMonth NUMBER(2),
    DateThreeMonth NUMBER(2),
    DateTwoMonth NUMBER(2),
    Year NUMBER(4)
);*/

CREATE TABLE Timedim (
    Id NUMBER PRIMARY KEY,
    DayDate DATE,
    DateMonth VARCHAR2(50),
    DateThreeMonth VARCHAR2(50),
    DateTwoMonth VARCHAR2(50),
    Year NUMBER(4)
);

CREATE TABLE Route (
    Id NUMBER PRIMARY KEY,
    DepartureStop VARCHAR2(100),
    ArrivalStop VARCHAR2(100),
    Wifi NUMBER(1), -- Usa 0 (FALSE) e 1 (TRUE)
    SpecialSiting NUMBER(1), -- Usa 0 (FALSE) e 1 (TRUE)
    AirConditioning NUMBER(1) -- Usa 0 (FALSE) e 1 (TRUE)
);

CREATE TABLE TypeOfTransportMode (
    Id NUMBER PRIMARY KEY,
    Name VARCHAR2(100)
);

CREATE TABLE TicketPurchaseMode (
    Id NUMBER PRIMARY KEY,
    Name VARCHAR2(100)
);

CREATE TABLE TypeOfTicket (
    Id NUMBER PRIMARY KEY,
    Name VARCHAR2(100)
);

CREATE TABLE Facts (
    LocationId NUMBER,
    TypeOfDiscountId NUMBER,
    TimeSlotId NUMBER,
    TimedimId NUMBER,
    RouteId NUMBER,
    TypeOfTransportModeId NUMBER,
    TypeOfTicketId NUMBER,
    TicketPurchaseModeId NUMBER,
    DayIncome NUMBER(10, 2),
    DayTicketsNumber NUMBER,
    TravelDuration NUMBER,
    PRIMARY KEY (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId),
    FOREIGN KEY (LocationId) REFERENCES Location(Id),
    FOREIGN KEY (TypeOfDiscountId) REFERENCES TypeOfDiscount(Id),
    FOREIGN KEY (TimeSlotId) REFERENCES TimeSlot(Id),
    FOREIGN KEY (TimedimId) REFERENCES Timedim(Id),
    FOREIGN KEY (RouteId) REFERENCES Route(Id),
    FOREIGN KEY (TypeOfTransportModeId) REFERENCES TypeOfTransportMode(Id),
    FOREIGN KEY (TypeOfTicketId) REFERENCES TypeOfTicket(Id),
    FOREIGN KEY (TicketPurchaseModeId) REFERENCES TicketPurchaseMode(Id)
);
