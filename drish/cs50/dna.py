import csv
from sys import argv
import re

# check for correct number of arguments
if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")

# open csv file
csvfile = open(argv[1], newline='')
# lists of elements in each row saved to reader
reader = csv.reader(csvfile, delimiter=',')

# open test sequence in read mode
toTest = open(argv[2], "r")
# read test txt to string
testString = toTest.read()

# create dict of keys STR and value length
dictResults = {}
firstrow = next(reader)  # gets first row of reader as a list
for item in firstrow:
    dictResults[item] = 0  # initialise values of dict to 0

# read test sequence for longest instance of each str (found in DB), and count n reapeats (store as dict? --> str // n(repeat))
for i in dictResults:
    my_regex = "(?:" + i + ")+"
    allRepeats = re.findall(my_regex, testString)  # creates list of all repeating sequences of the STR
    if len(allRepeats) > 0:  # if length of list of repeats in testString not 0
        dictResults[i] = (len(max(allRepeats))) / len(i)  # sets value of dict entry as n(repeats) of STR in key

# iterate over rows in csvfile, checking each item of the row for the value in dictResults corresponding to the key for the column of the item

for row in reader:  # iterate over rows
    for i in range(len(row) - 1):  # minus one off becase first item skipped
        i += 1  # offset i by one to skip first column
        correct = False  # initialise bool correct to false
        if float(row[i]) == dictResults[firstrow[i]]:  # if ith item of row = value for key firstrow[i] (corresponding STR)
            correct = True
        else:
            corect = False
            break
    if correct == True:
        print(row[0])
        break

if correct == False:
    print("No match")
