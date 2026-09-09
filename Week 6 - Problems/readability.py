
def count_grade(text):
    number_words = 1
    number_letters = 0
    number_sentences = 0

    for i in range(len(text)):
        if ((text[i] >= 'A' and text[i] <= 'Z') or (text[i] >= 'a' and text[i] <= 'z')):
            number_letters += 1
        elif (text[i] == '.' or text[i] == '!' or text[i] == '?'):
            number_sentences += 1
        elif (text[i] == ' '):
            number_words += 1

    L = (number_letters / number_words) * 100
    S = (number_sentences / number_words) * 100

    grade = 0.0588 * L - 0.296 * S - 15.8

    return grade


text = input("Text: ")
grade = count_grade(text)
grade = round(grade)

if (grade < 1):
    print("Before Grade 1")
elif (grade >= 16):
    print("Grade 16+")
else:
    print(f"Grade {grade}")
