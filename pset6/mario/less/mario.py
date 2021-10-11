# Initialize height
height = 0

# Get an integer between 1 and 8
while(height < 1) or (height > 8):
    try:
        height = int(input("Height: "))
    except:
        height = 0


# Loop through the height printing each row. 
for h in range(height):
    print(" " * (height - (h + 1)), end="")
    print("#" * (h + 1))