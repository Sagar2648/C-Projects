#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

    srand(time(NULL));

    int guess = 0;
    int tries = 0;
    int min = 1;
    int max = 100;
    int answer = rand() % (max - min + 1) + min;

    printf("\n### GUESS THE NUMBER GAME ###\n");
    printf("I have chosen a number between %d and %d.\nTry to guess it!\n\n", min, max);

    do {
        printf("Enter your guess: ");
        scanf("%d", &guess);
        tries++;

        if (guess < answer) {
            printf("TOO LOW! Try again.\n\n");
        }
        else if (guess > answer) {
            printf("TOO HIGH! Try again.\n\n");
        }
        else {
            printf("🎉 CORRECT!\n");
        }

    } while (guess != answer);

    printf("\nThe number was %d\n", answer);
    printf("You guessed it in %d tries!\n\n", tries);

    // Save score
    FILE *pfile = fopen("/Users/sagar/Desktop/guess.txt", "a");

    if (pfile == NULL) {
        printf("⚠ Error opening the file.\n");
    }
    else {
        char name[50];
        printf("Enter your name: ");
        scanf(" %[^\n]", name); // allow full name

        fprintf(pfile, "Player %s guessed the number in %d tries.\n", name, tries);
        fprintf(pfile, "----------------------------------------\n");

        fclose(pfile);
        printf("✅ Score saved to Desktop/guess.txt\n");
    }

    printf("\nThanks for playing!\n");

    return 0;
}
