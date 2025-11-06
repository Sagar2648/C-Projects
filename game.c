#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int getUserChoice();
int getComputerChoice();
void checkWinner(int userChoice, int computerChoice);
void saveResult(int userChoice, int computerChoice, char* result);

int main(){

    srand(time(NULL));

    int userChoice = getUserChoice();
    int computerChoice = getComputerChoice();

    printf(" ### ROCK PAPER SCISSORS ### \n\n");

    switch (userChoice)
    {
        case 1:
          printf("YOU CHOOSE ROCK!!\n");
          break;

        case 2:
          printf("YOU CHOOSE PAPER!!\n");
          break;

        case 3:
          printf("YOU CHOOSE SCISSORS!!\n");
          break;
    
    default:
        break;
    }

    switch (computerChoice)
    {
        case 1:
          printf("COMPUTER CHOOSE ROCK!!\n");
          break;

        case 2:
          printf("COMPUTER CHOOSE PAPER!!\n");
          break;

        case 3:
          printf("COMPUTER CHOOSE SCISSORS!!\n");
          break;
    
    default:
        break;
    }

    checkWinner(userChoice, computerChoice);

    printf("\nThanks for playing!\n");

    return 0;
}

int getUserChoice(){
    int choice = 0;

    do
    {
        printf("Choose the number from 1-3: \n");
        printf("1.ROCK \n");
        printf("2.PAPER \n");
        printf("3.SCISSORS \n");
        scanf("%d", &choice);
    } while (choice < 1 || choice > 3);

    return choice;
    
}

int getComputerChoice(){
    return (rand() % 3) + 1;
}

void checkWinner(int userChoice, int computerChoice){

    char result[20];

    if(userChoice == computerChoice){
        printf("It's a TIE!!!\n");
        strcpy(result, "TIE");
    }
    else if((userChoice == 1 && computerChoice == 3) ||
            (userChoice == 2 && computerChoice == 1) ||
            (userChoice == 3 && computerChoice == 2)){
        printf("YOU WIN!!!\n");
        strcpy(result, "WIN");
    }
    else{
        printf("YOU LOSE!!!\n");
        strcpy(result, "LOSE");
    }

    // ✅ Save to file here
    saveResult(userChoice, computerChoice, result);
}

void saveResult(int userChoice, int computerChoice, char* result){

    FILE *psave = fopen("/Users/Sagar/Desktop/result.txt", "a");

    if(psave == NULL){
        printf("Problem Loading the file");
    }

    else{
        char userName[50];

        printf("Enter your name: ");
        scanf(" %[^\n]s", &userName);
        
        fprintf(psave, "%s choose %d and Computer choose %d\nresult: %s\n\n\n", userName, userChoice, computerChoice, result);
        printf("✅ Score saved to Desktop/guess.txt\n");
    }

    fclose(psave);
}