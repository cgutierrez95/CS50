# Get user input
text = input("Text: ")

lenght = len(text)
letters = 0
words = 1
sentences = 0

# Examine the text looking for letters, words and sentences
for element in text:
    if element.isalpha():
        letters += 1 
    
    if element.isspace():
        words += 1
        
    if element == '.' or element == '!' or element == '?':
        sentences += 1
        
# Evaluate the results with Coleman-Liau index

L = (letters / words) * 100
    
S = (sentences / words) * 100
    
index = (0.0588 * L) - (0.296 * S) - 15.8

index = round(index)
    
# Print the final result.
if (index >= 16):
    print("Grade 16+")

    
if (index < 1):
    print("Before Grade 1")

    
if (index >= 1 and index < 16):
    print(f"Grade {index}")