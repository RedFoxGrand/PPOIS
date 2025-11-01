Классы:  
Admin (полей: 4, методов: 2) -> User, Permission, Ban  
Album (полей: 5, методов: 3) -> User, Photo, Video, Audio  
Analytics (полей: 2, методов: 3) ->  
App (полей: 4, методов: 3) ->  
Attachment (полей: 4, методов: 1) ->  
Audio (полей: 6, методов: 2) ->  
BackupService (полей: 4, методов: 2) ->   
Ban (полей: 4, методов: 2) -> User  
BlockList (полей: 2, методов: 2) ->  
CacheService (полей: 3, методов: 2) ->  
Chat (полей: 3 методов: 1) -> User, Message  
Comment (полей: 5, методов: 2) -> User  
Currency (полей: 3, методов: 1) ->  
Database (полей: 3, методов: 2) ->  
DeviceInfo (полей: 6, методов: 3) ->  
Emoji (полей: 2, методов: 1) ->  
Event (полей: 5, методов: 1) -> User  
FriendList (полей: 3, методов: 3) -> User  
FriendRequest (полей: 5, методов: 2) -> User  
GroupChat (полей: 4, методов: 3) -> User, GroupMember, Message  
GroupMember (полей: 3, методов: 2) -> User  
Invoice (полей: 4, методов: 1) -> User  
Like (полей: 3, методов: 1) ->  
Logger (полей: 2, методов: 3) ->  
Media (полей: 5, методов: 2) ->  
Message (полей: 7, методов: 1) -> User  
ModerationLog (полей: 5, методов: 1) -> User  
Moderator (полей: 3, методов: 2) -> User, Report  
Notification (полей: 4, методов: 1) -> User  
PasswordManager (полей: 3, методов: 3) ->  
PaymentCard (полей: 6, методов: 3) ->  
Permission (полей: 3, методов: 2) ->  
Photo (полей: 4, методов: 2) ->  
Poll (полей: 5, методов: 2) -> User  
Post (полей: 12, методов: 2) -> User, Comment, Tag  
Reaction (полей: 3, методов: 1) -> Emoji, Like  
RecommendationEngine (полей: 3, методов: 2) -> User  
Report (полей: 7, методов: 3) -> User  
SearchEngine (полей: 5, методов: 2) ->  
SecurityQuestion (полей: 2, методов: 1) ->  
Session (полей: 4, методов: 3) -> User  
Settings (полей: 7, методов: 4) ->  
Story (полей: 4, методов: 2) -> Media  
Subscription (полей: 6, методов: 2) ->  
Tag (полей: 2, методов: 1) ->  
Transaction (полей: 7, методов: 1) -> PaymentCard  
User (полей: 12, методов: 4) -> UserProfile, Settings, Wallet, FriendList, BlockList, Permission  
UserProfile (полей: 8, методов: 2) ->  
Video (полей: 8, методов: 2) ->  
Wallet (полей: 4, методов: 2) -> PaymentCard, Transaction, Currency  

Исключения:  
InvalidPasswordException  
UserNotFoundException  
DuplicateUsernameException  
SessionExpiredException  
InsufficientFundsException  
CardExpiredException  
SubscriptionExpiredException  
InvalidMessageException  
InvalidFileFormatException  
DatabaseConnectionException  
InvalidFontSizeException  
InvalidEmailFormatException  

Всего:  
Классов: 50 + 12 исключений  
Полей: 228  
Методов: 101 + Set и Get функции  
Ассоциаций: 43 (без исключений)  
