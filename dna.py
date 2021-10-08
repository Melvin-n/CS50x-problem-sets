from sys import argv
import csv

def main():
    names = get_names()
    sequence = get_sequence()
    highest = checkRepeats(names, sequence)
    match = 'No match'
    # check each value in the names dict
    for i in range(len(names)):
        # check for a match to highest, removing the name. if match found, print name
        if highest == names[i][1:]:
            match = names[i][0]
            break
    print(match)


def get_names():
    # check if correct number of arguments have been passed
    if len(argv) != 3:
        print('Usage: python dna.py data.csv sequence.txt')
    # open the csv file
    with open(argv[1], 'r') as f:
        reader = csv.reader(f)
        # append each line to the name list
        name_list = []
        for line in reader:
            name_list.append(line)
        # delete 'name' keyword from the list
        del name_list[0][0]
        return name_list

# save the sequence of letters (or STR's) from the file to memory
def get_sequence():
    with open(argv[2], 'r') as f:
        reader = csv.reader(f)
        sequence = ''
        for line in reader:
            sequence = line
        sequence = sequence[0]
    return sequence

# function to hceck the amount of times the substring repeats consecutively in sequence
def checkRepeats(names, sequence):
    # set substr from list
    substr = names[0][0]
    # initalise list to keep max amounts
    highest = []
    for STR in range(len(names[0])):
        #set amount to 0 at the start of each loop initstr will only contain 1 substr while substr while add on
        amount = 0
        # initstr will only contain 1 substring while substr will add the initstr to the end each time its found
        initstr = names[0][STR]
        substr = names[0][STR]
        # when substr is found, add another of the substring to substr e.g AGTC becomes AGTCAGTC and so on
        # if found again, do the same, this will leave amount at the max consecutive found
        while substr in sequence:
            amount += 1
            substr += initstr
        # change amount type to str to match type in names array
        highest.append(str(amount))
    return highest

main()




