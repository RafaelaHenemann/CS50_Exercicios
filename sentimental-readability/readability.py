# Prompt the user for some text
text = input('Text: ')

# Count the number of letters, words, and sentences in the text
letters = 0
for letter in text:
    if letter.isalpha():
        letters += 1

words = int(text.count(' ') + 1)

sentences = int(text.count('.') + text.count('!') + text.count('?'))

# Compute the Coleman-Liau index
L = (letters/words) * 100.0
S = (sentences/words) * 100.0
grade = int(round(0.0588 * L - 0.296 * S - 15.8))

# Print the grade level
if grade < 1:
    print('Before Grade 1')
elif grade > 16:
    print('Grade 16+')
else:
    print(f'Grade {grade}')
