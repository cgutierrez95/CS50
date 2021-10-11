# Declares the variable change_owed
change_owed = -1


# Loops until the correct input os passed.
while (change_owed < 0):
    try:
        change_owed = float(input("Change_owed: "))
    except:
        change_owed = -1
    
# Returns the quantity of coins needed.
counter = 0

change_owed *= 100

while (change_owed >= 25):
    change_owed -= 25
    counter += 1
    
while (change_owed >= 10):
    change_owed -= 10
    counter += 1
    
while (change_owed >= 5):
    change_owed -= 5
    counter += 1
    
while (change_owed >= 1):    
    change_owed -= 1    
    counter += 1

# Prints the result    
print(counter)  