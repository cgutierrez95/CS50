-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Get to know the report of the crime scene
    select a.*
        from crime_scene_reports a
        where a.year = 2020 and a.month = 7 and a.day = 28 and street = "Chamberlin Street";

-- Read the interviews from the witnesess
    select a.*
        from interviews a
        where a.year = 2020 and a.month = 7 and a.day = 28;

-- Look for the matches where someone had use the atm and had a call less than 60 seconds the same day and who has been in the courthouse that same day..
    select c.*, d.*, e.*
        from atm_transactions a
        left join bank_accounts b on .account_number=b.account_number
        left join people c on b.person_id=c.id
        left join phone_calls d  on c.phone_number=d.caller
        where a.year = 2020 and a.month = 7 and a.day = 28 and a.atm_location ="Fifer Street" and d.year =2020 and d.month =7 and d.day =28 and d.duration <=60;

-- Look for the next day earliest flight and Compare which passengers matches with the previous search.
    select b.*
        from flights a
        left join passengers b on a.id=b.flight_id
        where a.year =2020 and a.month = 7 and a.day =29 and origin_airport_id =8 and a.hour = 8 order by a.hour;

-- Look for the name of the partner, the phone number is the receiving number of tha phone call
    select a.*
        from people a 
        where a.phone_number ="(375) 555-8161";