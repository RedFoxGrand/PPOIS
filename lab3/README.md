Классы:
1. Account (полей: 6, методов: 2) -> Passenger, PaymentCard
2. Aircraft (полей: 5, методов: 3) -> AircraftModel, Schedule
3. AircraftMaintenanceSystem (полей: 2, методов: 3) -> Aircraft, MaintenanceLog
4. AircraftModel (полей: 7, методов: 1) ->
5. AirlineCompany (полей: 8, методов: 3) -> Airport, Aircraft, Employee, FlightManager, BookingManager, PassengerManager
6. Airport (полей: 4, методов: 3) -> Gate, Runway, Flight
7. AirTrafficController (полей: 2, методов: 0) : Employee -> Employee, Flight
8. Baggage (полей: 6, методов: 4) -> Passenger, BaggageTag
9. BaggageHandler (полей: 1, методов: 0) : GroundStaff -> GroundStaff, Baggage
10. BaggageTag (полей: 4, методов: 1) ->
11. Booking (полей: 6 методов: 2) -> Passenger, Ticket, Account
12. BookingManager (полей: 1, методов: 2) -> Booking
13. Cargo (полей: 3, методов: 0) -> Passenger
14. CateringOrder (полей: 5, методов: 2) -> Passenger
15. CheckIn (полей: 4, методов: 2) -> Passenger
16. ContactInfo (полей: 3, методов: 1) ->
17. ConveyorBelt (полей: 5, методов: 5) -> Baggage
18. Employee (полей: 2, методов: 1) : Person -> Person
19. ExchangeRate (полей: 4, методов: 2) ->
20. Fare (полей: 5, методов: 3) ->
21. FeedbackForm (полей: 3, методов: 2) ->
22. Flight (полей: 7, методов: 2) -> Aircraft, Schedule
23. FlightAttendant (полей: 2, методов: 1) : Employee -> Employee, Passenger
24. FlightManager (полей: 1, методов: 2) -> Flight, Employee
25. FlightPlan (полей: 4, методов: 2) -> Flight, Airport, WeatherCondition
26. FuelRecord (полей: 4, методов: 1) -> Aircraft
27. Gate (полей: 3, методов: 4) ->
28. GroundStaff (полей: 3, методов: 0) : Employee -> Employee, Gate, Passenger, Cargo
29. Hangar (полей: 4, методов: 2) -> Aircraft
30. Invoice (полей: 5, методов: 1) -> Passenger
31. LostAndFound (полей: 5, методов: 3) -> Baggage, Passenger
32. LoyaltyProgram (полей: 5, методов: 3) -> Passenger
33. MaintenanceLog (полей: 4, методов: 2) -> Aircraft
34. Notification (полей: 4, методов: 1) -> Passenger
35. Passenger (полей: 3, методов: 2) : Person -> Person, Passport, Flight
36. PassengerManager (полей: 1, методов: 3) -> Passenger
37. Passport (полей: 7, методов: 2) -> Visa
38. PaymentCard (полей: 5, методов: 2) ->
39. Person (полей: 4, методов: 2) -> ContactInfo
40. Pilot (полей: 2, методов: 2) : Employee -> Employee, Flight, AircraftModel
41. Runway (полей: 4, методов: 4) -> Schedule
42. Schedule (полей: 6, методов: 4) ->
43. Seat (полей: 4, методов: 2) ->
44. SecurityOfficer (полей: 3, методов: 2) : Employee -> Employee, Passenger
45. SecuritySystem (полей: 4, методов: 2) -> SecurityOfficer
46. Shift (полей: 4, методов: 4) -> Employee
47. Ticket (полей: 7, методов: 1) -> Passenger, Seat, Fare
48. Transaction (полей: 4, методов: 2) -> Account
49. Visa (полей: 5, методов: 2) ->
50. WeatherCondition (полей: 5, методов: 4) ->

Исключения:

1. EmptyObjectException
2. ExpiredException
3. FlightNotFound
4. InvadRateException
5. InvalidAmountException
6. InvalidBalanceException
7. InvalidCapacityException
8. InvalidException
9. InvalidFuelException
10. InvalidStatusException
11. PassengerHistoryNotFound
12. PassengerNotFound

Всего:  
Классов: 50 + 12 исключений  
Полей: 205  
Методов: 106 + Set и Get функции  
Ассоциаций: 69 (без исключений)

