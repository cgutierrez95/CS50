# Get the users input
credit_card = input("Number: ")


# Store the lenght of the credit card
lenght = len(credit_card)


# Store the first and second digit
first_digit = int(credit_card[0])
second_digit = int(credit_card[1])

check_sum = 0

# Calculate the Luhn's Algorithm
for i, number in enumerate(credit_card):
    if i % 2 == 0:
        check_sum += int(credit_card[lenght - i - 1])
    else:
        even = int(credit_card[lenght - i - 1]) * 2
        if even < 10:
            check_sum += even
        else:
            even = str(even)
            check_sum += int(even[0])
            check_sum += int(even[1])
        
# if valid, decide which credit card is
if check_sum != 20:
    print("INVALID")
    
    
# American Express    
if lenght == 15 and first_digit == 3 and (second_digit == 4 or second_digit == 7):
    print("AMEX")
    

# Mastercard
if lenght == 16 and first_digit == 5 and (second_digit > 0 and second_digit < 6):
    print("MASTERCARD")
    

# Visa
if (lenght == 13 or lenght == 16) and first_digit == 4:
    print("VISA")

