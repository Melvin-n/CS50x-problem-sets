def main():
    # get string input
    textString = str(input('Enter string: '))

    # run counting functions
    letters = countLetters(textString)
    words = countWords(textString)
    sentences = countSentences(textString)

    # run formula function for getting grade
    grade = coleLiauIndex(letters, words, sentences)

    # print out result
    if grade >= 16:
        print("Grade 16+")
    elif grade <= 1:
        print("Before Grade 1")
    else:
        print(f'Grade {round(grade)}')

# count number of letters
def countLetters(textString):
    letters = 0
    for letter in textString:
        if letter.isalpha():
            letters += 1
    return letters

# count number of words, words will be 1 less than actual number as there is no space after the last word
def countWords(textString):
    words = 1
    for letter in textString:
        if letter == ' ':
            words += 1
    return words

# count number of sentences
def countSentences(textString):
    sentences = 0
    for letter in textString:
        if letter == '.' or letter == '!' or letter == '?':
            sentences += 1
    return sentences

# coleman-liau index, get average words (L) and sentences (S) per 100 letter
# formula: index = 0.0588 * L - 0.296 * S - 15.8
def coleLiauIndex(letters, words, sentences):
    L = (letters / words) * 100
    S = (sentences / words) * 100
    grade = 0.0588 * L - 0.296 * S - 15.8
    return grade

main()
