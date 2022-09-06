-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT *
FROM crime_scene_reports
WHERE month = '7'AND day = '28' AND year = '2020';

SELECT *
FROM courthouse_security_logs
WHERE month = '7' AND day = '28';

SELECT *
FROM interviews
WHERE month = '7' AND day = '28';
--10:15-10:25 thief exits carpark
--that morning thief withdrew money from ATM on Fifer St
--thief called accomplice < 1min
--thief booked earliest flight out of 50ville on July 29th

SELECT minute, license_plate
FROM courthouse_security_logs
WHERE month = '7' AND day = '28' AND activity = 'exit' AND hour = '10';
--8 possible license plates: 5P2BI95, 94KL13X, 6P58WS2, 4328GD8, G412CB7, L93JTIZ, 322W7JE, 0NTHK55

SELECT *
FROM atm_transactions
WHERE month = '7' AND day = '28' AND year = '2020' AND atm_location = 'Fifer Street';

SELECT account_number, amount
FROM atm_transactions
WHERE month = '7' AND day = '28' AND year = '2020' AND atm_location = 'Fifer Street' AND transaction_type = "withdraw";
--8 possible account_numbers 28500762, 28296815, 76054385, 49610011, 16153065, 25506511, 81061156,26013199
--8 possible license plates: 5P2BI95, 94KL13X, 6P58WS2, 4328GD8, G412CB7, L93JTIZ, 322W7JE, 0NTHK55


SELECT *
FROM phone_calls
WHERE month = '7' AND day = '28' AND year = '2020';

SELECT *
FROM phone_calls
WHERE month = '7' AND day = '28' AND year = '2020' AND duration < 60;

SELECT caller, receiver, duration
FROM phone_calls
WHERE month = '7' AND day = '28' AND year = '2020' AND duration < 60;
--9 possible phone-calls: (130) 555-0289 | (996) 555-8899 | 51
--(499) 555-9472 | (892) 555-8872 | 36
--(367) 555-5533 | (375) 555-8161 | 45
--(499) 555-9472 | (717) 555-1342 | 50
--(286) 555-6063 | (676) 555-6554 | 43
--(770) 555-1861 | (725) 555-3243 | 49
--(031) 555-6622 | (910) 555-3251 | 38
--(826) 555-1652 | (066) 555-9701 | 55
--(338) 555-6650 | (704) 555-2131 | 54


SELECT *
FROM airports
WHERE city = "Fiftyville";
--50ville airport id= 8

SELECT *
FROM flights
WHERE month = '7' AND day = '29' AND year = '2020' AND origin_airport_id = 8;

SELECT destination_airport_id, hour, minute
FROM flights
WHERE month = '7' AND day = '29' AND year = '2020' AND origin_airport_id = 8;
--destination_airport_id =4

SELECT *
FROM airports
WHERE id = "4";
--The thieves escaped to London!

SELECT *
FROM interviews
WHERE month = '7' AND day = '28';

SELECT *
FROM people
WHERE phone_number IN
('(130) 555-0289',
'(499) 555-9472 ',
'(367) 555-5533',
'(499) 555-9472',
'(286) 555-6063',
'(770) 555-1861',
'(031) 555-6622',
'(826) 555-1652',
'(338) 555-6650')
AND
license_plate IN
('5P2BI95',
'94KL13X',
'6P58WS2',
'4328GD8',
'G412CB7',
'L93JTIZ',
'322W7JE',
'0NTHK55');
--There are 4 suspects: Roger, Russell, Evelyn and Ernest.
--id | name | phone_number | passport_number | license_plate
--398010 | Roger | (130) 555-0289 | 1695452385 | G412CB7
--514354 | Russell | (770) 555-1861 | 3592750733 | 322W7JE
--560886 | Evelyn | (499) 555-9472 | 8294398571 | 0NTHK55
--686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X


SELECT *
FROM bank_accounts
WHERE account_number IN
('28500762',
'28296815',
'76054385',
'49610011',
'16153065',
'25506511',
'81061156',
'26013199');

SELECT *
FROM people
WHERE passport_number IN
('1695452385',
'3592750733',
'8294398571',
'5773159633');

SELECT *
FROM people
WHERE phone_number IN
('(130) 555-0289',
'(499) 555-9472 ',
'(367) 555-5533',
'(499) 555-9472',
'(286) 555-6063',
'(770) 555-1861',
'(031) 555-6622',
'(826) 555-1652',
'(338) 555-6650')
AND
license_plate IN
('5P2BI95',
'94KL13X',
'6P58WS2',
'4328GD8',
'G412CB7',
'L93JTIZ',
'322W7JE',
'0NTHK55')
AND passport_number IN
(
    SELECT passport_number
    FROM passengers
);

SELECT *
FROM flights
WHERE destination_airport_id = '4';
--Flight id to London is 36.

SELECT *
FROM passengers
WHERE flight_id = '36';

SELECT *
FROM people
WHERE passport_number IN
(
    SELECT passport_number
    FROM passengers
    WHERE flight_id = '36'
)
AND
phone_number IN
('(130) 555-0289',
'(499) 555-9472 ',
'(367) 555-5533',
'(499) 555-9472',
'(286) 555-6063',
'(770) 555-1861',
'(031) 555-6622',
'(826) 555-1652',
'(338) 555-6650')
AND
license_plate IN
('5P2BI95',
'94KL13X',
'6P58WS2',
'4328GD8',
'G412CB7',
'L93JTIZ',
'322W7JE',
'0NTHK55');
--Suspects are: Roger, Evelyn and Ernest.
--398010 | Roger | (130) 555-0289 | 1695452385 | G412CB7
--560886 | Evelyn | (499) 555-9472 | 8294398571 | 0NTHK55
--686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X


SELECT *
FROM phone_calls
WHERE caller IN ('(130) 555-0289', '(499) 555-9472', '(367) 555-5533')
AND month = '7' AND day = '28' AND year = '2020' AND duration < 60;
--The accomplice's phone number is either (996) 555-8899, (892) 555-8872, (375) 555-8161, (717) 555-1342.

SELECT *
FROM people
WHERE phone_number IN ('(996) 555-8899', '(892) 555-8872', '(375) 555-8161', '(717) 555-1342');
--Accomplice suspects: Larry, Jack, Melissa, Berthold.

SELECT *
FROM passengers
WHERE flight_id = '36' AND passport_number IN ('2312901747', '9029462229', '7834357192');
--Larry, Jack and Melissa were on the flight to London, so through a process of elimination Berthold is the accomplice!

SELECT *
FROM phone_calls
WHERE caller IN ('(130) 555-0289', '(499) 555-9472', '(367) 555-5533')
AND receiver = '(375) 555-8161'
AND month = '7' AND day = '28' AND year = '2020' AND duration < 60;
--Berthold spoke with Ernest 45 seconds, so Ernest is the thief!
