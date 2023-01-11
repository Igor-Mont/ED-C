#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

char secretWord[WORD_LENGTH];
char kicks[26];
int kicksGiven = 0;

void welcome() {
  printf("/****************/\n");
  printf("/ HANGMAN GAME */\n");
  printf("/****************/\n\n");
}

void kickLetter() {
  char kick;
  scanf(" %c", &kick);

  kicks[kicksGiven] = kick;
  kicksGiven++; 
}

int wasKicked(char letter) {
  for(int j = 0; j < kicksGiven; j++) {
    if(kicks[j] == letter) {
      return 1;
    }
  }

  return 0;
}

void drawGame() {
  int errors = wrongKicks();

  printf("  _______       \n");
  printf(" |/      |      \n");
  printf(" |      %c%c%c  \n", (errors>=1?'(':' '), (errors>=1?'_':' '), (errors>=1?')':' '));
  printf(" |      %c%c%c  \n", (errors>=3?'\\':' '), (errors>=2?'|':' '), (errors>=3?'/': ' '));
  printf(" |       %c     \n", (errors>=2?'|':' '));
  printf(" |      %c %c   \n", (errors>=4?'/':' '), (errors>=4?'\\':' '));
  printf(" |              \n");
  printf("_|___           \n");
  printf("\n\n");


  for(int i = 0; i < strlen(secretWord); i++) {
    int find = wasKicked(secretWord[i]);

    if(find) {
      printf("%c ", secretWord[i]);
    } else {
      printf("_ ");
    }
  }

  printf("\n");
}

void chooseSecretWord() {
  FILE* f;

  f = fopen("words.txt", "r");

  if(f == 0) {
    printf("Sorry, database not available");
    exit(1);
  }

  int amountWords;
  fscanf(f, "%d", &amountWords);

  srand(time(0));
  int randomNum = rand() % amountWords;

  for(int i = 0; i <= randomNum; i++) {
    fscanf(f, "%s", secretWord);
  }

  fclose(f);
}

int wrongKicks() {
  int errors = 0;

  for(int i = 0; i < kicksGiven; i++) {
    int exists = 0;
    
    for(int j = 0; j < strlen(secretWord); j++) {
      if (kicks[i] == secretWord[j]) {
        exists = 1;
        break;
      }
    }

    if(!exists) errors++;
  }

  return errors;
}

int hanged() {
  return wrongKicks() >= 5;
}

int win() {
  for(int i = 1; i < strlen(secretWord); i++) {
    if(!wasKicked(secretWord[i])) {
      return 0;
    }
  }

  return 1;
}

void addWord() {
  char answer;

  printf("You want to add a new word to the database? (Y/N)");
  scanf(" %c", &answer);

  if(answer == 'Y') {
    char newWord[WORD_LENGTH];
    printf("What's the new word? ");
    scanf("%s", newWord);

    FILE* f;

    f = fopen("words.txt", "r+");

    if(f == 0) {
      printf("Sorry, database not available");
      exit(1);
    }

    int amountWords;
    fscanf(f, "%d", &amountWords);
    amountWords++;

    fseek(f, 0, SEEK_SET);
    fprintf(f, "%d", amountWords);

    fseek(f, 0, SEEK_END);
    fprintf(f, "\n%s", newWord);

    fclose(f);
  }
}

void winMessage() {
  printf("\nCongrats, you WIN!\n\n");

  printf("       ___________      \n");
  printf("      '._==_==_=_.'     \n");
  printf("      .-\\:      /-.    \n");
  printf("     | (|:.     |) |    \n");
  printf("      '-|:.     |-'     \n");
  printf("        \\::.    /      \n");
  printf("         '::. .'        \n");
  printf("           ) (          \n");
  printf("         _.' '._        \n");
  printf("        '-------'       \n\n");
}

void lossMessage() {
  printf("\nBad... you were HANGED!\n");
  printf("The word was **%s**\n\n", secretWord);

  printf("    _______________         \n");
  printf("   /               \\       \n"); 
  printf("  /                 \\      \n");
  printf("//                   \\/\\  \n");
  printf("\\|   XXXX     XXXX   | /   \n");
  printf(" |   XXXX     XXXX   |/     \n");
  printf(" |   XXX       XXX   |      \n");
  printf(" |                   |      \n");
  printf(" \\__      XXX      __/     \n");
  printf("   |\\     XXX     /|       \n");
  printf("   | |           | |        \n");
  printf("   | I I I I I I I |        \n");
  printf("   |  I I I I I I  |        \n");
  printf("   \\_             _/       \n");
  printf("     \\_         _/         \n");
  printf("       \\_______/           \n");
}

int main() {
  chooseSecretWord();
  welcome();

  do {
    drawGame();
    kickLetter();
  } while (!win() && !hanged());

  win() ? winMessage() : lossMessage();

  addWord();

  return 0;
} 