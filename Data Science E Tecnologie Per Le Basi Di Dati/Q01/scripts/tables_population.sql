INSERT INTO Location (Id, City, Province, Region) VALUES (1, 'Milan', 'Milan', 'Lombardy');
INSERT INTO Location (Id, City, Province, Region) VALUES (2, 'Rome', 'Rome', 'Lazio');
INSERT INTO Location (Id, City, Province, Region) VALUES (3, 'Naples', 'Naples', 'Campania');
INSERT INTO Location (Id, City, Province, Region) VALUES (4, 'Turin', 'Turin', 'Piedmont');
INSERT INTO Location (Id, City, Province, Region) VALUES (5, 'Florence', 'Florence', 'Tuscany');

INSERT INTO TypeOfDiscount (Id, Name) VALUES (1, 'Adult');
INSERT INTO TypeOfDiscount (Id, Name) VALUES (2, 'Student');
INSERT INTO TypeOfDiscount (Id, Name) VALUES (3, 'Senior');
INSERT INTO TypeOfDiscount (Id, Name) VALUES (4, 'Child');

INSERT INTO TimeSlot (Id, TimeSlot, IsPeakTime) VALUES (1, 'Morning', 1);
INSERT INTO TimeSlot (Id, TimeSlot, IsPeakTime) VALUES (2, 'Afternoon', 0);
INSERT INTO TimeSlot (Id, TimeSlot, IsPeakTime) VALUES (3, 'Evening', 1);
INSERT INTO TimeSlot (Id, TimeSlot, IsPeakTime) VALUES (4, 'Night', 0);

/*INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (1, TO_DATE('2024-01-01', 'YYYY-MM-DD'), 1, 1, 1, 2024);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (2, TO_DATE('2024-01-02', 'YYYY-MM-DD'), 1, 1, 1, 2024);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (3, TO_DATE('2024-01-03', 'YYYY-MM-DD'), 1, 1, 1, 2024);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (4, TO_DATE('2024-01-04', 'YYYY-MM-DD'), 1, 1, 1, 2024);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (5, TO_DATE('2024-01-05', 'YYYY-MM-DD'), 1, 1, 1, 2024);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (6, TO_DATE('2024-02-01', 'YYYY-MM-DD'), 2, 1, 1, 2024);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (7, TO_DATE('2024-02-02', 'YYYY-MM-DD'), 2, 1, 1, 2024);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (8, TO_DATE('2024-02-03', 'YYYY-MM-DD'), 2, 1, 1, 2024);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (9, TO_DATE('2024-02-04', 'YYYY-MM-DD'), 2, 1, 1, 2024);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (10, TO_DATE('2024-02-05', 'YYYY-MM-DD'), 2, 1, 1, 2024);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (11, TO_DATE('2024-02-06', 'YYYY-MM-DD'), 2, 1, 1, 2024);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (12, TO_DATE('2024-02-07', 'YYYY-MM-DD'), 2, 1, 1, 2024);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (13, TO_DATE('2024-02-08', 'YYYY-MM-DD'), 2, 1, 1, 2024);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (14, TO_DATE('2024-02-09', 'YYYY-MM-DD'), 2, 1, 1, 2024);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (15, TO_DATE('2024-02-10', 'YYYY-MM-DD'), 2, 1, 1, 2024);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (16, TO_DATE('2022-01-05', 'YYYY-MM-DD'), 1, 1, 1, 2022);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (17, TO_DATE('2022-01-10', 'YYYY-MM-DD'), 1, 1, 1, 2022);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (18, TO_DATE('2022-01-20', 'YYYY-MM-DD'), 1, 1, 1, 2022);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (19, TO_DATE('2022-04-03', 'YYYY-MM-DD'), 4, 2, 2, 2022);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (20, TO_DATE('2022-04-15', 'YYYY-MM-DD'), 4, 2, 2, 2022);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (21, TO_DATE('2022-04-28', 'YYYY-MM-DD'), 4, 2, 2, 2022);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (22, TO_DATE('2022-09-05', 'YYYY-MM-DD'), 9, 3, 5, 2022);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (23, TO_DATE('2022-09-12', 'YYYY-MM-DD'), 9, 3, 5, 2022);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (24, TO_DATE('2022-09-20', 'YYYY-MM-DD'), 9, 3, 5, 2022);*/

INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (1, TO_DATE('2024-01-01', 'YYYY-MM-DD'), '2024-01', '2024-01', '2024-01', 2024);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (2, TO_DATE('2024-01-02', 'YYYY-MM-DD'), '2024-01', '2024-01', '2024-01', 2024);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (3, TO_DATE('2024-01-03', 'YYYY-MM-DD'), '2024-01', '2024-01', '2024-01', 2024);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (4, TO_DATE('2024-01-04', 'YYYY-MM-DD'), '2024-01', '2024-01', '2024-01', 2024);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (5, TO_DATE('2024-01-05', 'YYYY-MM-DD'), '2024-01', '2024-01', '2024-01', 2024);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (6, TO_DATE('2024-02-01', 'YYYY-MM-DD'), '2024-02', '2024-01', '2024-01', 2024);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (7, TO_DATE('2024-02-02', 'YYYY-MM-DD'), '2024-02', '2024-01', '2024-01', 2024);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (8, TO_DATE('2024-02-03', 'YYYY-MM-DD'), '2024-02', '2024-01', '2024-01', 2024);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (9, TO_DATE('2024-02-04', 'YYYY-MM-DD'), '2024-02', '2024-01', '2024-01', 2024);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (10, TO_DATE('2024-02-05', 'YYYY-MM-DD'), '2024-02', '2024-01', '2024-01', 2024);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (11, TO_DATE('2024-02-06', 'YYYY-MM-DD'), '2024-02', '2024-01', '2024-01', 2024);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (12, TO_DATE('2024-02-07', 'YYYY-MM-DD'), '2024-02', '2024-01', '2024-01', 2024);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (13, TO_DATE('2024-02-08', 'YYYY-MM-DD'), '2024-02', '2024-01', '2024-01', 2024);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (14, TO_DATE('2024-02-09', 'YYYY-MM-DD'), '2024-02', '2024-01', '2024-01', 2024);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (15, TO_DATE('2024-02-10', 'YYYY-MM-DD'), '2024-02', '2024-01', '2024-01', 2024);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (16, TO_DATE('2022-01-05', 'YYYY-MM-DD'), '2022-01', '2022-01', '2022-01', 2022);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (17, TO_DATE('2022-01-10', 'YYYY-MM-DD'), '2022-01', '2022-01', '2022-01', 2022);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (18, TO_DATE('2022-01-20', 'YYYY-MM-DD'), '2022-01', '2022-01', '2022-01', 2022);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (19, TO_DATE('2022-04-03', 'YYYY-MM-DD'), '2022-04', '2022-02', '2022-02', 2022);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (20, TO_DATE('2022-04-15', 'YYYY-MM-DD'), '2022-04', '2022-02', '2022-02', 2022);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (21, TO_DATE('2022-04-28', 'YYYY-MM-DD'), '2022-04', '2022-02', '2022-02', 2022);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (22, TO_DATE('2022-09-05', 'YYYY-MM-DD'), '2022-09', '2022-03', '2022-05', 2022);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (23, TO_DATE('2022-09-12', 'YYYY-MM-DD'), '2022-09', '2022-03', '2022-05', 2022);
INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (24, TO_DATE('2022-09-20', 'YYYY-MM-DD'), '2022-09', '2022-03', '2022-05', 2022);


INSERT INTO Route (Id, DepartureStop, ArrivalStop, Wifi, SpecialSiting, AirConditioning) VALUES 
(1, 'Central Station', 'Airport', 1, 1, 1);
INSERT INTO Route (Id, DepartureStop, ArrivalStop, Wifi, SpecialSiting, AirConditioning) VALUES 
(2, 'Downtown', 'Suburb', 1, 0, 1);
INSERT INTO Route (Id, DepartureStop, ArrivalStop, Wifi, SpecialSiting, AirConditioning) VALUES 
(3, 'North Terminal', 'South Terminal', 0, 1, 1);
INSERT INTO Route (Id, DepartureStop, ArrivalStop, Wifi, SpecialSiting, AirConditioning) VALUES 
(4, 'City Center', 'University', 0, 0, 0);
INSERT INTO Route (Id, DepartureStop, ArrivalStop, Wifi, SpecialSiting, AirConditioning) VALUES 
(5, 'Port', 'Station', 1, 1, 0);

INSERT INTO TypeOfTransportMode (Id, Name) VALUES (1, 'Bus');
INSERT INTO TypeOfTransportMode (Id, Name) VALUES (2, 'Train');
INSERT INTO TypeOfTransportMode (Id, Name) VALUES (3, 'Tram');
INSERT INTO TypeOfTransportMode (Id, Name) VALUES (4, 'Metro');
INSERT INTO TypeOfTransportMode (Id, Name) VALUES (5, 'Ferry');

INSERT INTO TypeOfTicket (Id, Name) VALUES (1, 'One-way');
INSERT INTO TypeOfTicket (Id, Name) VALUES (2, 'Daily Pass');
INSERT INTO TypeOfTicket (Id, Name) VALUES (3, 'Weekly Pass');
INSERT INTO TypeOfTicket (Id, Name) VALUES (4, 'Monthly Pass');

INSERT INTO TicketPurchaseMode (Id, Name) VALUES (1, 'Online');
INSERT INTO TicketPurchaseMode (Id, Name) VALUES (2, 'Ticket Machine');
INSERT INTO TicketPurchaseMode (Id, Name) VALUES (3, 'Authorized Retailer');
INSERT INTO TicketPurchaseMode (Id, Name) VALUES (4, 'Driver');

INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (1, 2, 1, 1, 1, 1, 1, 1, 1500.00, 300, 60);
INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (2, 3, 2, 2, 2, 2, 2, 2, 2000.00, 400, 80);
INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (3, 4, 3, 3, 3, 3, 3, 3, 2500.00, 500, 100);
INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (4, 1, 4, 4, 4, 4, 4, 4, 1000.00, 200, 50);
INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (5, 4, 1, 5, 5, 5, 1, 1, 3000.00, 600, 120);
INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (1, 1, 2, 3, 2, 2, 2, 3, 1800.00, 360, 75);
INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (3, 2, 3, 4, 3, 3, 3, 1, 2500.00, 500, 90);
INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (2, 4, 1, 2, 1, 1, 4, 2, 2200.00, 440, 70);
INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (4, 3, 4, 5, 4, 4, 1, 4, 1600.00, 320, 60);
INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (5, 3, 3, 1, 5, 5, 3, 3, 1900.00, 380, 85);
INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (1, 4, 2, 3, 3, 2, 4, 2, 2000.00, 400, 80);
INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (2, 3, 1, 4, 2, 1, 2, 1, 1200.00, 240, 50);
INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (3, 3, 4, 5, 4, 3, 1, 4, 1400.00, 280, 65);
INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (5, 1, 2, 2, 5, 5, 4, 2, 1700.00, 340, 75);
INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (4, 2, 3, 1, 1, 4, 3, 1, 1300.00, 260, 55);
INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (3, 4, 2, 3, 3, 2, 1, 3, 1500.00, 300, 60);
INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (1, 1, 1, 4, 2, 1, 2, 2, 2200.00, 440, 70);
INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (1, 1, 2, 6, 1, 1, 1, 2, 1700.00, 340, 65);
INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (2, 2, 3, 7, 2, 2, 2, 1, 2100.00, 420, 80);
INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (3, 3, 1, 8, 3, 3, 3, 4, 1900.00, 380, 70);
INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (4, 4, 4, 9, 4, 4, 4, 3, 1400.00, 280, 50);
INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (5, 2, 2, 10, 5, 5, 2, 2, 2300.00, 460, 90);
INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (1, 2, 1, 11, 3, 2, 1, 1, 2000.00, 400, 75);
INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (2, 3, 4, 12, 2, 1, 3, 4, 1500.00, 300, 60);
INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (3, 4, 3, 13, 4, 3, 4, 2, 1700.00, 340, 65);
INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (4, 1, 2, 14, 5, 4, 1, 3, 1600.00, 320, 55);
INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (5, 2, 1, 15, 1, 5, 2, 1, 2200.00, 440, 80);
INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (1, 1, 1, 16, 1, 1, 1, 1, 1500.00, 300, 60);
INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (2, 2, 2, 16, 2, 2, 2, 2, 1200.00, 240, 50);
INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (3, 3, 3, 17, 3, 3, 3, 3, 1800.00, 360, 75);
INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (4, 4, 4, 17, 4, 4, 4, 4, 1400.00, 280, 55);
INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (5, 3, 1, 18, 5, 5, 1, 1, 2100.00, 420, 80);
INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (1, 2, 2, 18, 1, 1, 2, 2, 1600.00, 320, 70);
INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (2, 3, 3, 19, 2, 2, 3, 3, 1900.00, 380, 85);
INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (3, 4, 4, 19, 3, 3, 4, 4, 1700.00, 340, 65);
INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (4, 1, 1, 20, 4, 4, 1, 1, 1300.00, 260, 55);
INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (5, 2, 2, 20, 5, 5, 2, 2, 2000.00, 400, 75);
INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (1, 3, 3, 21, 1, 1, 3, 3, 2200.00, 440, 90);
INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (2, 4, 4, 21, 2, 2, 4, 4, 1500.00, 300, 60);
INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (3, 1, 1, 22, 3, 3, 1, 1, 1200.00, 240, 50);
INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (4, 2, 2, 22, 4, 4, 2, 2, 1600.00, 320, 70);
INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (5, 3, 3, 23, 5, 5, 3, 3, 1400.00, 280, 55);
INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (1, 4, 4, 23, 1, 1, 4, 4, 2000.00, 400, 75);
INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (2, 1, 1, 24, 2, 2, 1, 1, 1500.00, 300, 60);
INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (3, 1, 2, 24, 3, 3, 2, 2, 1800.00, 360, 85);




INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (25, TO_DATE('2021-09-20', 'YYYY-MM-DD'), '2021-09', '2021-03', '2021-05', 2021);

INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (3, 1, 2, 25, 3, 3, 2, 2, 1800.00, 360, 85);

INSERT INTO Timedim (Id, DayDate, DateMonth, DateThreeMonth, DateTwoMonth, Year) 
VALUES (31, TO_DATE('2031-09-20', 'YYYY-MM-DD'), '2031-09', '2031-03', '2031-05', 2031);

INSERT INTO Facts (LocationId, TypeOfDiscountId, TimeSlotId, TimedimId, RouteId, TypeOfTransportModeId, TypeOfTicketId, TicketPurchaseModeId, DayIncome, DayTicketsNumber, TravelDuration) 
VALUES (3, 1, 2, 31, 3, 3, 2, 2, 1800.00, 360, 85);
