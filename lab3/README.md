Классы:  
Account (полей: 6, методов: 2) -> Passenger, PaymentCard  
Aircraft (полей: 5, методов: 3) -> AircraftModel, Schedule  
AircraftMaintenanceSystem (полей: 2, методов: 3) -> Aircraft, MaintenanceLog  
AircraftModel (полей: 7, методов: 1) ->  
AirlineCompany (полей: 8, методов: 3) -> Airport, Aircraft, Employee, FlightManager, BookingManager, PassengerManager  
Airport (полей: 4, методов: 3) -> Gate, Runway, Flight  
AirTrafficController (полей: 2, методов: 0) : Employee -> Employee, Flight  
Baggage (полей: 6, методов: 4) -> Passenger, BaggageTag  
BaggageHandler (полей: 1, методов: 0) : GroundStaff -> GroundStaff, Baggage  
BaggageTag (полей: 4, методов: 1) ->  
Booking (полей: 6 методов: 2) -> Passenger, Ticket, Account  
BookingManager (полей: 1, методов: 2) -> Booking  
Cargo (полей: 3, методов: 0) -> Passenger  
CateringOrder (полей: 5, методов: 2) -> Passenger  
CheckIn (полей: 4, методов: 2) -> Passenger   
ContactInfo (полей: 3, методов: 1) ->  
ConveyorBelt (полей: 5, методов: 5) -> Baggage  
Employee (полей: 2, методов: 1) : Person -> Person  
ExchangeRate (полей: 4, методов: 2) ->  
Fare (полей: 5, методов: 3) ->  
FeedbackForm (полей: 3, методов: 2) ->  
Flight (полей: 7, методов: 2) -> Aircraft, Schedule  
FlightAttendant (полей: 2, методов: 1) : Employee -> Employee, Passenger  
FlightManager (полей: 1, методов: 2) -> Flight, Employee  
FlightPlan (полей: 4, методов: 2) -> Flight, Airport, WeatherCondition  
FuelRecord (полей: 4, методов: 1) -> Aircraft  
Gate (полей: 3, методов: 4) ->  
GroundStaff (полей: 3, методов: 0) : Employee -> Employee, Gate, Passenger, Cargo  
Hangar (полей: 4, методов: 2) -> Aircraft  
Invoice (полей: 5, методов: 1) -> Passenger  
LostAndFound (полей: 5, методов: 3) -> Baggage, Passenger  
LoyaltyProgram (полей: 5, методов: 3) -> Passenger  
MaintenanceLog (полей: 4, методов: 2) -> Aircraft  
Notification (полей: 4, методов: 1) -> Passenger  
Passenger (полей: 3, методов: 2) : Person -> Person, Passport, Flight  
PassengerManager (полей: 1, методов: 3) -> Passenger  
Passport (полей: 7, методов: 2) -> Visa  
PaymentCard (полей: 5, методов: 2) ->  
Person (полей: 4, методов: 2) -> ContactInfo  
Pilot (полей: 2, методов: 2) : Employee -> Employee, Flight, AircraftModel  
Runway (полей: 4, методов: 4) -> Schedule  
Schedule (полей: 6, методов: 4) ->  
Seat (полей: 4, методов: 2) ->  
SecurityOfficer (полей: 3, методов: 2) : Employee -> Employee, Passenger  
SecuritySystem (полей: 4, методов: 2) -> SecurityOfficer  
Shift (полей: 4, методов: 4) -> Employee  
Ticket (полей: 7, методов: 1) -> Passenger, Seat, Fare  
Transaction (полей: 4, методов: 2) -> Account  
Visa (полей: 5, методов: 2) ->  
WeatherCondition (полей: 5, методов: 4) ->  

Исключения:  
EmptyObjectException  
ExpiredException  
FlightNotFound  
InvadRateException  
InvalidAmountException  
InvalidBalanceException  
InvalidCapacityException  
InvalidException  
InvalidFuelException  
InvalidStatusException  
PassengerHistoryNotFound  
PassengerNotFound  

Всего:  
Классов: 50 + 12 исключений  
Полей: 205  
Методов: 106 + Set и Get функции  
Ассоциаций: 69 (без исключений)  

