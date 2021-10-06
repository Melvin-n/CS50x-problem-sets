num = str(input('Number: '))

#get input from user
def main():
    d = [int(digit) for digit in str(num)]
    length = True
    if len(d) == 16 or len(d) == 15 or len(d) == 13:
        length = True
    else:
        length = False
    type = checkType(d)

    total = luhnsAlgo(d)

    checkTotal(total, length, type)

#check the type of card based on first number(s)
def checkType(d):
    type = ''
    if (d[0] == 3 and d[1] == 4) or (d[0] == 3 and d[1] == 7):
        type = 'AMEX'
    elif d[0] == 5 and (d[1] >=1 and d[1] <=5):
        type = 'MASTERCARD'
    elif d[0] == 4:
        type = 'VISA'
    else:
        type = 'AMEX'
    return type

#luhns algorithm for finding if a card is valid by its number
def luhnsAlgo(d):
    list1 = []
    #reverse the order of the list so that it starts from the right end of the number
    d.reverse()
    for digit in d[1::2]:
        digit = digit * 2
        if digit < 10:
            list1.append(digit)
        elif digit > 9:
            #print(digit, 'ddub')
            for f in str(digit):
                list1.append(int(f))
    total = 0
    for num in list1:
        total += num
    #add the numbers which weren't added in the previous list (every second starting from 1)
    for digit2 in d[0::2]:
        #print(digit2)
        total += int(digit2)
    #print(total)
    return total

# check if the card is legit based on number, if it is print our type of card else print INVALID
def checkTotal(total, length, type):
    if total % 10 == 0 and length == True:
        print(type)
    else:
        print('INVALID')

main()



