#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//function prototypes
void create_deck(int new_deck[52][2]);
void print_deck(int deck[52][2]);
char number_to_character_for_deck(int num);
char number_to_suit(int num);
void shuffle_deck(int deck[52][2]);
void split_deck(int original_deck[52][2], int deck1[52][2], int deck2[52][2]);
void move_cards_up_in_hand(int hand[52][2]);
int add_cards_to_hand(int hand[52][2], int cards_to_add[2][2]);

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
    int player_hand[52][2];
    int opponent_hand[52][2];
    split_deck(first_deck, player_hand, opponent_hand);

    int player_wins = 0;
    int opponent_wins = 0;
    int cards_won[2][2];
    int player_won = 0;

    //start war
    while (1) {
        printf("\n");
        int current_player_card[2] = {player_hand[0][0], player_hand[0][1]};
        int current_opponent_card[2] = {opponent_hand[0][0], opponent_hand[0][1]};
        if (current_player_card[0] == -1 || current_opponent_card[0] == -1) {
            break;
        }
        printf("Player's card: %d of %d\n", current_player_card[0], current_player_card[1]);
        printf("Opponent's card: %d of %d\n", current_opponent_card[0], current_opponent_card[1]);

        if (current_player_card[0] > current_opponent_card[0]) {
            player_won = 1;
            //print_deck(player_hand);
        } else {
            player_won = 0;
        }

        move_cards_up_in_hand(player_hand);
        move_cards_up_in_hand(opponent_hand);
        cards_won[0][0] = current_player_card[0];
        cards_won[0][1] = current_player_card[1];
        cards_won[1][0] = current_opponent_card[0];
        cards_won[1][1] = current_opponent_card[1];

        if (current_player_card[0] > current_opponent_card[0]) {
            printf("Player wins!\n");
            add_cards_to_hand(player_hand, cards_won);
            player_wins++;
        } else {
            printf("Opponent wins!\n");
            add_cards_to_hand(opponent_hand, cards_won);
            opponent_wins++;
        }

    }
    printf("\nPlayer wins: %d\nOpponent wins: %d\n", player_wins, opponent_wins);
    printf("%s Wins War!\n", player_wins > opponent_wins ? "Player" : "Opponent");

    return 0;
}

void create_deck(int new_deck[52][2]) {
    int suits[4] = {0, 1, 2, 3}; //hearts, diamonds, clubs, spades
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            int current_iteration = (i*13) + j; //current iteration out of 52
            new_deck[current_iteration][0] = (current_iteration % 13) + 1; //only using numbers 1 through 13
            new_deck[current_iteration][1] = suits[i];
        }
    }
}

void print_deck(int deck[52][2]) {
    printf("Current deck: \n");
    int current_card;
    for (int i = 0; i < 52; i++) { //looping through every card
        current_card = deck[i][0];
        if (current_card == 1 || current_card >= 11) { //if it's a ace, jack, queen, or king
            printf("Card #%d: %c of %c\n", i + 1, number_to_character_for_deck(deck[i][0]), number_to_suit(deck[i][1])); //it's going to run it through the function translator
        } else {
            printf("Card #%d: %d of %c\n", i + 1, deck[i][0], number_to_suit(deck[i][1]));
        }
    }
}

char number_to_character_for_deck(int num) { //tranlator for the suits
    switch (num) {
        case 1:
            return 'A';
        case 11:
            return 'J';
        case 12:
            return 'Q';
        case 13:
            return 'K';
        default:
            return num;
    }
}

char number_to_suit(int num) { //tranlator for the values
    switch(num) {
        case 0:
            return 'H';
        case 1:
            return 'D';
        case 2:
            return 'C';
        case 3:
            return 'S';
        default:
            return num;
    }
}

void shuffle_deck(int deck[52][2]) {
    int copy_deck[52][2];
    for (int i = 0; i < 52; i++) {
        for (int j = 0; j < 2; j++) {
            copy_deck[i][j] = deck[i][j]; //creating an exact copy of the deck array
            deck[i][j] = -1; //filling the original deck array with only -1
        }
    }
    int random_num = 0;
    for (int k = 0; k < 52; k++) {
        do {
            random_num = rand() % 52;
        } while (deck[random_num][0] != -1); //keeps looping until it finds a spot in the deck array filled with a -1
        deck[random_num][0] = copy_deck[k][0];
        deck[random_num][1] = copy_deck[k][1];
    }
}

void split_deck(int original_deck[52][2], int deck1[52][2], int deck2[52][2]) {
    for (int i = 0; i < 26; i++) {
        deck1[i][0] = original_deck[i][0];
        deck1[i][1] = original_deck[i][1];
        deck2[i][0] = original_deck[51-i][0];
        deck2[i][1] = original_deck[51-i][1];

        deck1[51-i][0] = -1;
        deck1[51-i][1] = -1;
        deck2[51-i][0] = -1;
        deck2[51-i][1] = -1;
    }
}

void move_cards_up_in_hand(int hand[52][2]) { //assuming every empty spot in a hand is filled with -1
    for (int i = 0; i < 51; i++) {
        hand[i][0] = hand[i+1][0];
        hand[i][1] = hand[i+1][1];
    }
    hand[51][0] = -1;
    hand[51][1] = -1;
}

int add_cards_to_hand(int hand[52][2], int cards_to_add[2][2]) {
    int cards_added = 0;
    for (int i = 0; i < 52; i++) {
        if (cards_added == 2) {
            return 0;
        }
        if (hand[i][0] == -1) {
            hand[i][0] = cards_to_add[cards_added][0];
            hand[i][1] = cards_to_add[cards_added][1];
            cards_added++;

        }
    }
}