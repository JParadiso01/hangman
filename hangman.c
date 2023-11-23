#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void youwin(char *, int);

int main(void) {

  char *words[] = {
      "blow",    "bog",   "house",   "horse",  "frog", "shark",  "lion",
      "dolphin", "queue", "country", "short",  "boss", "corpse", "chat",
      "charter", "block", "chopped", "warts",  "slob", "polish", "scarf",
      "walrus",  "print", "slapped", "quartz", "butterfly", "sports", "show"};
  int wordsLen = *(&words + 1) - words;
  srand(time(0));
  int randomNum = rand();
  char *word = words[randomNum % wordsLen];
  int size = strlen(word);

  int guessesLeft = (int)size * 1.5;
  char guess;
  char guessedLetters[27] = "";
  bool isGuessCorrect = false;
  bool alreadyGuessed = false;

  // creates dashed word
  char dashedWord[size];
  for (int i = 0; i < size; i++) {
    dashedWord[i] = '_';
  }

  // main game loop
  while (guessesLeft != 0) {

    // checks if user won
    if (!strncmp(word, dashedWord, size)) {
      youwin(word, guessesLeft);
    }

    printf("You have %d guesses left\n", guessesLeft);

    // printing the guessed letters
    if (strlen(guessedLetters) != 0) {
      printf("You have guessed:");
      for (int i = 0; i < strlen(guessedLetters); i++) {
        printf(" %c,", guessedLetters[i]);
      }
      printf("\n");
    }

    // fixes weird printing error
    for (int i = 0; i < size; i++) {
      printf("%c", dashedWord[i]);
    }

    // gets users' guess
    printf("\n");
    printf("Guess a character: ");
    scanf(" %c", &guess);
    printf("\n");

    // checks if letter was already guessed
    while (alreadyGuessed) {

      for (int i = 0; i < strlen(guessedLetters); i++) {
        if (guess == guessedLetters[i]) {
          printf("You already guessed %c. Pick a new letter: ", guess);
          scanf(" %c", &guess);
          alreadyGuessed = true;
          break;
        } else {
          alreadyGuessed = false;
        }
      }
    }

    // seeing if guess is in word
    for (int i = 0; i < strlen(word); i++) {
      if (guess == word[i]) {
        dashedWord[i] = guess;
        isGuessCorrect = true;
      }
    }

    if (isGuessCorrect) {
      isGuessCorrect = false;
    } else {
      guessesLeft -= 1;
    }

    strncat(guessedLetters, &guess, 1);
    alreadyGuessed = true;
  }

  printf("You Lost!\n");
  printf("The correct word was \"%s\"\n", word);
  return 0;
}

void youwin(char *word, int guessesLeft) {
  printf("Congratulations! You won with %d guesses left!\n", guessesLeft);
  printf("The correct word was \"%s\"\n", word);
  exit(0);
}
