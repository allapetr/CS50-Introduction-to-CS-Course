# from cs50 import get_string

# This function returns number of alphabets in text
def count_letters(text):
    total_letters = 0

    # Loop through characters
    for c in text:
        if c.isalpha():
            total_letters += 1

    return total_letters

# Get number of words
def count_words(text):
    total_words = 1

    # Loop through words
    for c in text:
        if c == " ":
            total_words += 1

    return total_words

# Get number of sentences
def count_sentences(text):
    total_sentences = 0

    # Loop through sentences
    for c in text:
        if c == "." or c == "!" or c == "?":
            total_sentences += 1

    return total_sentences


def main():
    # Get text as input from user
    text = input("Text: ")
    print(text)

    # Call functions for counting
    letters = count_letters(text)
    print(f"Letters: {letters}")

    words = count_words(text)
    print(f"Words: {words}")

    sentences = count_sentences(text)
    print(f"Sentences: {sentences}")

    # Calculate averages per 100
    L = (letters / words) * 100
    print(f"Av letters: {L}")

    S = (sentences / words) * 100
    print(f"Av words: {S}")

    # Calculate Coleman-Liau index
    index = 0.0588 * L - 0.296 * S - 15.8
    print(f"Index: {index}")

    # Print result
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {int(round(index))}")


main()
