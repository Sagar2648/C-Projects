#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

//Define the maximum number of incorrect guesses allowed 
#define MAX_TRIES 6

void CLEAR_SCREEN() {
    //Determine which system command to use
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

//Global list of words for the game 
const char *wordlist[] = {
    "programming",
    "hangman",
    "computer",
    "software",
    "keyboard",
    "monitor",
    "aldorithm",
    "developer",
    "database",
    "student",
    "project",
    "learning"
};

// calculate the number of words in the list
const int wordCount = sizeof(wordlist) / sizeof(wordlist[0]);

void displaySplashScreen(){
    printf("\n");
    printf("================================================\n");
    printf("||   WELCOME TO THE HANGMAN GAME IN C!   ||\n");
    printf("================================================\n");
    printf("|| The goal is to guess the hidden word ||\n");
    printf("|| You have %d tries before the Hangman ||\n", MAX_TRIES);
    printf("|| is complete!                       ||\n     ");
    printf("================================================\n");

    sleep(2);  // wait a couple of seconds so the user can see the splash screen
}

void displayHangman(int tries) {
    // Array of ASCII art representations for each try count (0 to MAX_TRIES)
    const char *hangmanStages[] = {
        // Stage 0: No mistakes
        "   +---+\n"
        "   |   |\n"
        "       |\n"
        "       |\n"
        "       |\n"
        "=========\n",

        // Stage 1: Head
        "   +---+\n"
        "   |   |\n"
        "   O   |\n"
        "       |\n"
        "       |\n"
        "=========\n",

        // Stage 2: Body
        "   +---+\n"
        "   |   |\n"
        "   O   |\n"
        "   |   |\n"
        "       |\n"
        "=========\n",

        // Stage 3: Left arm
        "   +---+\n"
        "   |   |\n"
        "   O   |\n"
        "  /|   |\n"
        "       |\n"
        "=========\n",

        // Stage 4: Right arm
        "   +---+\n"
        "   |   |\n"
        "   O   |\n"
        "  /|\\  |\n"
        "       |\n"
        "=========\n",

        // Stage 5: Left leg
        "   +---+\n"
        "   |   |\n"
        "   O   |\n"
        "  /|\\  |\n"
        "  /    |\n"
        "=========\n",

        // Stage 6: Complete Hangman (Loss)
        "   +---+\n"
        "   |   |\n"
        "   O   |\n"
        "  /|\\  |\n"
        "  / \\  |\n"
        "=========\n"
    };

    if(tries >= 0 && tries <= MAX_TRIES){
        printf("%s\n", hangmanStages[tries]);
    }
}

 // @brief Generates an initial fill-in-the-blank version of the word.
 // This function creates a blank string of the same length, possibly revealing
 // one or two characters to offer a hint, similar to the project description.
 // @param word The hidden word.
 // @param blank The character array to store the masked word.
 // @param length The length of the word.

 void generateFillInTheBlank(const char *word, char *blank, int length){
    // Initialize the blank array with underscores
    for (int i = 0; i < length; i++)
    {
        blank[i] = '_';
    }
    blank[length] = '\0';

    //Reveal one random character as a hint 
    int numBlanks = (length > 2) ? 1 : 0; //Reveal 1 if length > 2
    for (int i = 0; i < numBlanks; i++)
    {
        int randomIndex = rand() % length;
        blank[randomIndex] = word[randomIndex];
    }
 }

 int main(){

    // seed the random number generator using current time
    srand(time(NULL));

    // select a random word
    const char *word = wordlist[rand() % wordCount];
    int wordLength = strlen(word);

    //variables for the game state
    char blank[wordLength + 1]; //The word shown to user
    char guess[wordLength + 1]; //user's input guess
    int tries = 0;              // Current number of inccorect tries

    generateFillInTheBlank(word, blank, wordLength);

    //display welcome screen
    displaySplashScreen();

    //start the main game loop
    while(tries < MAX_TRIES) {
        CLEAR_SCREEN();
        displayHangman(tries);

        //Display Current status
        printf("================================================\n");
        printf("The Word to guess is: %s\n", blank);
        printf("You have %d tries left.\n", MAX_TRIES - tries);
        printf("================================================\n");

        printf("Enter your word guess (all lowercase, max %d characters. ---\n)", wordLength);
        scanf("%s", guess);  

        if (strlen(guess) != wordLength) {
            printf("\n--- Please enter a word with exactly %d characters. ---\n", wordLength);
            // Don't increment tries for a format error, just prompt again
            printf("Press ENTER to continue...");
            while (getchar() != '\n'); // Consume newline left by scanf
            getchar(); // Wait for user to press enter
            continue;
        } 

        //If strcmp returns 0, the strings are identical
        if (strcmp(guess, word) == 0) {
            CLEAR_SCREEN();
            displayHangman(tries);
            printf("================================================\n");
            printf("  CONGRATULATIONS! You've guessed the word: %s\n", word);
            printf("================================================\n");

            // Save score
              FILE *pfile = fopen("/Users/sagar/Desktop/hangman.txt", "a");
                  if (pfile == NULL) {
        printf("⚠ Error opening the file.\n");
    } else {
        char name[50];
        printf("\n--- Enter your name to save the result --- : \n");
        scanf(" %[^\n]", name);  // Read full name including spaces
        fprintf(pfile, "%s guessed the word '%s' in %d tries\n", name, word, tries);
        fprintf(pfile, "----------------------------------------\n");
        fclose(pfile);
        printf("✅ Score saved to Desktop/hangman.txt\n");
    }

            break;
        }
        else{
            tries ++;

            printf("\n--- Wrong guess! The word was not '%s' . ---\n", guess);
            printf("Press ENTER to continue ...");

            //wait for user input to clear the feedback screen
            while(getchar() != '\n');
            getchar();

            if (tries >= MAX_TRIES)
            {
                CLEAR_SCREEN();
                displayHangman(tries);
                printf("================================================\n");
                printf("  SORRY! You've lost! The word was: %s\n", word);
                printf("================================================\n");
                break;
            }   
        }
    }

        printf("\nGameOver. Thanks for Playing!\n");

    return 0;
 }
 