Классы:

1. Admin (полей: 4, методов: 2) -> User, Permission, Ban
2. Album (полей: 5, методов: 3) -> User, Photo, Video, Audio
3. Analytics (полей: 2, методов: 3) ->
4. App (полей: 4, методов: 3) ->
5. Attachment (полей: 4, методов: 1) ->
6. Audio (полей: 6, методов: 2) ->
7. BackupService (полей: 4, методов: 2) ->
8. Ban (полей: 4, методов: 2) -> User
9. BlockList (полей: 2, методов: 2) ->
10. CacheService (полей: 3, методов: 2) ->
11. Chat (полей: 3 методов: 1) -> User, Message
12. Comment (полей: 5, методов: 2) -> User
13. Currency (полей: 3, методов: 1) ->
14. Database (полей: 3, методов: 2) ->
15. DeviceInfo (полей: 6, методов: 3) ->
16. Emoji (полей: 2, методов: 1) ->
17. Event (полей: 5, методов: 1) -> User
18. FriendList (полей: 3, методов: 3) -> User
19. FriendRequest (полей: 5, методов: 2) -> User
20. GroupChat (полей: 4, методов: 3) -> User, GroupMember, Message
21. GroupMember (полей: 3, методов: 2) -> User
22. Invoice (полей: 4, методов: 1) -> User
23. Like (полей: 3, методов: 1) ->
24. Logger (полей: 2, методов: 3) ->
25. Media (полей: 5, методов: 2) ->
26. Message (полей: 7, методов: 1) -> User
27. ModerationLog (полей: 5, методов: 1) -> User
28. Moderator (полей: 3, методов: 2) -> User, Report
29. Notification (полей: 4, методов: 1) -> User
30. PasswordManager (полей: 3, методов: 3) ->
31. PaymentCard (полей: 6, методов: 3) ->
32. Permission (полей: 3, методов: 2) ->
33. Photo (полей: 4, методов: 2) ->
34. Poll (полей: 5, методов: 2) -> User
35. Post (полей: 12, методов: 2) -> User, Comment, Tag
36. Reaction (полей: 3, методов: 1) -> Emoji, Like
37. RecommendationEngine (полей: 3, методов: 2) -> User
38. Report (полей: 7, методов: 3) -> User
39. SearchEngine (полей: 5, методов: 2) ->
40. SecurityQuestion (полей: 2, методов: 1) ->
41. Session (полей: 4, методов: 3) -> User
42. Settings (полей: 7, методов: 4) ->
43. Story (полей: 4, методов: 2) -> Media
44. Subscription (полей: 6, методов: 2) ->
45. Tag (полей: 2, методов: 1) ->
46. Transaction (полей: 7, методов: 1) -> PaymentCard
47. User (полей: 12, методов: 4) -> UserProfile, Settings, Wallet, FriendList, BlockList, Permission
48. UserProfile (полей: 8, методов: 2) ->
49. Video (полей: 8, методов: 2) ->
50. Wallet (полей: 4, методов: 2) -> PaymentCard, Transaction, Currency

Исключения:

1. InvalidPasswordException
2. UserNotFoundException
3. DuplicateUsernameException
4. SeZsionExpiredException
5. InsufficientFundsException
6. CardExpiredException
7. SubscriptionExpiredException
8. InvalidMessageException
9. InvalidFileFormatException
10. DatabaseConnectionException
11. InvalidFontSizeException
12. InvalidEmailFormatException

Всего:  
Классов: 50 + 12 исключений  
Полей: 228  
Методов: 101 + Set и Get функции  
Ассоциаций: 43 (без исключений)

