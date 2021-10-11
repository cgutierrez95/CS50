# Import libraries
import csv
import sys
import pandas as pd

matches = {}

# Check for the right number of arguments.
if len(sys.argv) != 3:
    sys.exit("Usage: python dna.py")

# Store the name of the files.
str_file = sys.argv[1]
dna_sequence = sys.argv[2]

# Store the str counts in a dataframe.
str_counts = pd.read_csv(str_file)

# Store the dna_sequence in a variable.
with open(dna_sequence) as file:
    for rows in file:
        dna_sequence = rows

# Counts the total of columns to iterate
columns = str_counts.columns

# Iterate each column sequence of DNA looking for matches.
for i, column in enumerate(columns):
    
    if i == 0:
        continue
    
    start = 0
    dna_count = 0
    consecutives = []
    
    while True:
        
        consecutive = dna_sequence.find(column, start)
        
        if consecutive != -1:
            if consecutive > start + len(column):
                consecutives.append(dna_count)
                dna_count = 1
                start = consecutive + 1
            else:
                dna_count += 1
                start = consecutive + 1
        else:
            consecutives.append(dna_count)
            break

    for j in range(str_counts.shape[0]):   

        if max(consecutives) == str_counts[column].iloc[j]:
            try:
                matches[j] += 1
            except:
                matches[j] = 1
            
# Print out the results
for key, value in matches.items():
    if value == len(columns) - 1:
        print(str_counts["name"].iloc[key])
        sys.exit()
        
print("No match")