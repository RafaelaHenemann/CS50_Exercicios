-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Find crime scene description
SELECT description FROM crime_scene_reports where month = 7 AND day = 28 AND street = 'Humphrey Street';

-- See information on bakery security log at the day of the crime
SELECT * FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28;

-- Find interviews transcript
SELECT name, transcript FROM interviews WHERE year = 2023 AND month = 7 AND day = 28;

-- See license plates that exits sometime within ten minutes of the theft
SELECT * FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 30 AND activity = 'exit';

-- See information on atm transactions at the day of the crime
SELECT account_number, amount FROM atm_transactions WHERE year = 2023 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';

-- See information about phone calls with less than one minute of duration at the day of the crime
SELECT caller, receiver FROM phone_calls WHERE year = 2023 AND month = 7 AND day = 28 AND duration < 60;

-- See information about flights on the next day
SELECT id, hour, minute FROM flights WHERE origin_airport_id IN(
    SELECT id FROM airports WHERE city = 'Fiftyville'
) AND year = 2023 AND month = 7 AND day = 29 ORDER BY hour, minute DESC;

-- See bank accounts information
SELECT person_id FROM bank_accounts WHERE account_number IN (
    SELECT account_number FROM atm_transactions
    WHERE year = 2023 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'
);

-- See information about people of the bank accounts founded
SELECT * FROM people WHERE id IN (
    SELECT person_id FROM bank_accounts WHERE account_number IN (
        SELECT account_number FROM atm_transactions
        WHERE year = 2023 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'
    )
);

-- Track names with the information untill now
SELECT name FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
JOIN phone_calls ON people.phone_number = phone_calls.caller
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
WHERE atm_transactions.year = 2023 AND atm_transactions.month = 7 AND atm_transactions.day = 28 AND atm_transactions.atm_location = 'Leggett Street' AND atm_transactions.transaction_type = 'withdraw'
AND phone_calls.year = 2023 AND phone_calls.month = 7 AND phone_calls.day = 28 AND phone_calls.duration < 60
AND bakery_security_logs.year = 2023 AND bakery_security_logs.month = 7 AND bakery_security_logs.day = 28 AND bakery_security_logs.hour = 10 AND bakery_security_logs.minute > 15 AND bakery_security_logs.minute < 30 AND bakery_security_logs.activity = 'exit';

-- See if passangers at flight 36 matches with Diana or Bruce
SELECT * FROM passengers WHERE flight_id = 36 AND (passport_number = 3592750733 OR passport_number = 5773159633);
-- Bruce is the thief

-- See destination of the flight
SELECT city FROM airports WHERE id IN (
    SELECT destination_airport_id FROM flights WHERE id = 36
);

-- See the ACCOMPLICE:
SELECT name FROM people WHERE phone_number IN (
    SELECT receiver FROM phone_calls WHERE caller = '(367) 555-5533' AND year = 2023 AND month = 7 AND day = 28 AND duration < 60
);

