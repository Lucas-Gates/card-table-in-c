#include <stdio.h>

//function prototypes
void create_deck(int new_deck[52][2]);
void print_deck(int new_deck[52][2]);
char number_to_character_for_deck(int num);

int main() {
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

    return 0;
}

void create_deck(int new_deck[52][2]) {
    char suits[4] = {'H', 'D', 'C', 'S'};
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
    for (int i = 0; i < 52; i++) {
        // int current_card = (i % 13) + 1;
        // if (current_card == 1 || current_card == 11 || current_card == 12 || current_card == 13) {
        //     printf("Card #%d: %c of %c\n", i + 1, number_to_character_for_deck(deck[i][0]), deck[i][1]);
        // } else {
            printf("Card #%d: %d of %c\n", i + 1, deck[i][0], deck[i][1]);
        // }
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