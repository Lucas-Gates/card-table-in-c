#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//function prototypes
void create_deck(int new_deck[52][2]);
void print_deck(int deck[52][2]);
char number_to_character_for_deck(int num);
char number_to_suit(int num);
void shuffle_deck(int deck[52][2]);

int main() {
    srand(time(NULL));
    printf("Welcome to the Card Table!\n");
    int choice;
    int game_selected = 0;
    do {
        printf("What game do you want to play?\n");
        printf("[1] War\n");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                game_selected = 1;
                break;
            default:
                printf("Invalid input; try again.\n");
                break;
        }
    } while (!(game_selected));

    int first_deck[52][2];
    create_deck(first_deck);
    print_deck(first_deck);
    shuffle_deck(first_deck);
    print_deck(first_deck);

    return 0;
}

void create_deck(int new_deck[52][2]) {
    int suits[4] = {0, 1, 2, 3};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            int current_iteration = (i*13) + j;
            new_deck[current_iteration][0] = (current_iteration % 13) + 1;
            new_deck[current_iteration][1] = suits[i];
        }
    }
}

void print_deck(int deck[52][2]) {
    printf("Current deck: \n");
    int current_card;
    for (int i = 0; i < 52; i++) {
        current_card = deck[i][0];
        if (current_card == 1 || current_card >= 11) {
            printf("Card #%d: %c of %c\n", i + 1, number_to_character_for_deck(deck[i][0]), number_to_suit(deck[i][1]));
        } else {
            printf("Card #%d: %d of %c\n", i + 1, deck[i][0], number_to_suit(deck[i][1]));
        }
    }
}

char number_to_character_for_deck(int num) {
    switch (num) {
        case 1:
            return 'A';
        case 11:
            return 'J';
        case 12:
            return 'Q';
        case 13:
            return 'K';
    }
}

char number_to_suit(int num) {
    switch(num) {
        case 0:
            return 'H';
        case 1:
            return 'D';
        case 2:
            return 'C';
        case 3:
            return 'S';
    }
}

void shuffle_deck(int deck[52][2]) {
    int copy_deck[52][2];
    for (int i = 0; i < 52; i++) {
        for (int j = 0; j < 2; j++) {
            copy_deck[i][j] = deck[i][j];
            deck[i][j] = -1;
        }
    }
    int random_num = 0;
    for (int k = 0; k < 52; k++) {
        do {
            random_num = rand() % 52;
        } while (deck[random_num][0] != -1);
        deck[random_num][0] = copy_deck[k][0];
        deck[random_num][1] = copy_deck[k][1];
    }
}