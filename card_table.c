#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//function prototypes
void create_deck(int new_deck[52][2]);
void print_deck(int deck[][2], int deck_size);
char number_to_character_for_deck(int num);
char number_to_suit(int num);
void shuffle_deck(int deck[52][2]);
void split_deck(int original_deck[52][2], int deck1[52][2], int deck2[52][2]);
void move_cards_up_in_hand(int hand[52][2]);
int add_cards_to_hand(int hand[52][2], int cards_to_add[2][2]);
int check_amount_of_cards(int hand[52][2]);
int war_tie(int player_hand[52][2], int opponent_hand[52][2], int prize_cards[6][2]);
void war(int deck[52][2], int max_turns);

int main() {
    srand(time(NULL));
    printf("Welcome to the Card Table!\n");
    int choice;
    int game_selected = 0;

    while (1) {
        do {
            printf("What game do you want to play?\n");
            printf("[1] War\n");
            printf("[0] Quit\n");
            scanf("%d", &choice);
            switch(choice) {
                case 1:
                    game_selected = 1;
                    break;
                case 0:
                    printf("Thanks for playing!\n");
                    return 0;
                default:
                    printf("Invalid input; try again.\n");
                    break;
            }
        } while (!game_selected);

        int first_deck[52][2];
        create_deck(first_deck);
        print_deck(first_deck, 52);
        shuffle_deck(first_deck);
        print_deck(first_deck, 52);
        int turns = 1000;

        printf("What would you like the turn limit to be?\n");
        scanf("%d", &turns);
        //start war
        war(first_deck, turns);
        printf("\n");
    }
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

void print_deck(int deck[][2], int deck_size) {
    int current_card;
    for (int i = 0; i < deck_size; i++) { //looping through every card
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
    //print_deck(hand);
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

int check_amount_of_cards(int hand[52][2]) { //assumes the hand is sorted
    for (int i = 0; i < 52; i++) {
        if (hand[i][0] == -1) {
            return i;
        }
    }
}

int war_tie(int player_hand[52][2], int opponent_hand[52][2], int prize_cards[6][2]) {
    int player_won = 0;
    int cards_not_filled = 0;

    for (int i = 0; i < 3; i++) {
        if (player_hand[1][0] != -1) {
            prize_cards[0][0] = player_hand[0][0];
            prize_cards[0][1] = player_hand[0][1];
            move_cards_up_in_hand(player_hand);
        } else {
            cards_not_filled++;
        }
        if (opponent_hand[i+1][0] != -1) {
            prize_cards[i][0] = opponent_hand[i][0];
            prize_cards[i][1] = opponent_hand[i][1];
            move_cards_up_in_hand(opponent_hand);
        } else {
            cards_not_filled++;
        }
    }

    for (int j = 0; j < cards_not_filled; j++) {
        prize_cards[5-j][0] = -1;
        prize_cards[5-j][1] = -1;
    }

    int prize_cards2[6][2];
    if (player_hand[0][0] > opponent_hand[0][0]) {
        player_won = 1;
    } else if (player_hand[0][0] < opponent_hand[0][0]) {
        player_won = 0;
    } else {
        war_tie(player_hand, opponent_hand, prize_cards2);
    }
    return player_won;
}

void war(int deck[52][2], int max_turns) {
    int player_hand[52][2];
    int opponent_hand[52][2];
    int player_wins = 0;
    int opponent_wins = 0;
    int cards_won[2][2];
    int player_won = 0;
    int current_player_card[2];
    int current_opponent_card[2];
    int turns = 0;    

    split_deck(deck, player_hand, opponent_hand);

    while ((check_amount_of_cards(player_hand)) && (check_amount_of_cards(opponent_hand)) && (turns < max_turns)) {
        printf("\n");
        current_player_card[0] = player_hand[0][0];
        current_player_card[1] = player_hand[0][1];
        current_opponent_card[0] = opponent_hand[0][0];
        current_opponent_card[1] = opponent_hand[0][1];
        printf("Player's card: %d of %d\n", current_player_card[0], current_player_card[1]);
        printf("Opponent's card: %d of %d\n", current_opponent_card[0], current_opponent_card[1]);
        int prize_cards[6][2];

        if (current_player_card[0] > current_opponent_card[0]) {
            player_won = 1;
        } else if (current_player_card[0] < current_opponent_card[0]){
            player_won = 0;
        } else {
            war_tie(player_hand, opponent_hand, prize_cards);
        }
        player_hand[0][0] = -1;
        player_hand[0][1] = -1;
        opponent_hand[0][0] = -1;
        opponent_hand[0][1] = -1;
        move_cards_up_in_hand(player_hand);
        move_cards_up_in_hand(opponent_hand);
        cards_won[0][0] = current_player_card[0];
        cards_won[0][1] = current_player_card[1];
        cards_won[1][0] = current_opponent_card[0];
        cards_won[1][1] = current_opponent_card[1];

        if (player_won) {
            printf("Player wins!\n");
            add_cards_to_hand(player_hand, cards_won);
            player_wins++;
        } else {
            printf("Opponent wins!\n");
            add_cards_to_hand(opponent_hand, cards_won);
            opponent_wins++;
        }
        turns++;
    }

    printf("\nPlayer wins: %d\nOpponent wins: %d\n", player_wins, opponent_wins);
    printf("%s Wins War!\n", player_wins > opponent_wins ? "Player" : "Opponent");    
}