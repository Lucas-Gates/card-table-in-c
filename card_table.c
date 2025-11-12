#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//function prototypes
void create_deck(int new_deck[52][2], int is_normal_deck);
void print_deck(int deck[][2], int deck_size);
char number_to_character_for_deck(int num);
char number_to_suit(int num);
void shuffle_deck(int deck[52][2]);
void split_deck(int original_deck[52][2], int deck1[52][2], int deck2[52][2]);
void move_cards_up_in_hand(int hand[52][2]);
int add_cards_to_hand(int hand[52][2], int cards_to_add[][2], int amount_to_add);
int check_amount_of_cards(int hand[52][2]);
int war_tie(int player_hand[52][2], int opponent_hand[52][2], int prize_cards[8][2]);
void war(int deck[52][2], int max_turns);
void memory(int deck[52][2]);
void memory_print(int deck[25][2], int card_to_flip[2], int card_to_flip2[2]);
// void create_memory_deck(int new_deck[25][2]);
void print_memory_deck(int deck[25][2]);
void shuffle_memory_deck(int deck[25][2]);

int main() {
    srand(time(NULL));
    printf("Welcome to the Card Table!\n");
    int choice;
    int game_selected = 0;

    while (1) {
        do {
            printf("What game do you want to play?\n");
            printf("[1] War\n");
            printf("[2] Memory\n");
            printf("[0] Quit\n");
            scanf("%d", &choice);
            switch(choice) {
                case 1:
                    game_selected = 1;
                    break;
                case 2:
                    game_selected = 2;
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
        create_deck(first_deck, 1);
        print_deck(first_deck, 52);
        shuffle_deck(first_deck);
        print_deck(first_deck, 52);
        if (game_selected == 1) {
            int turns = 1000;
            printf("What would you like the turn limit to be?\n");
            scanf("%d", &turns);
            // war(first_deck, turns);
        } else if (game_selected == 2) {
            // memory(first_deck);
        }

        printf("\n");
    }
}

void create_deck(int new_deck[][2], int is_normal_deck) { //new_deck is pointer to new_deck[0][0]
    int suits[4] = {1, 2, 3, 4}; //hearts, diamonds, clubs, spades
    int num_of_suits;
    int num_of_unique_cards;

    if (is_normal_deck) {
        num_of_suits = 4;
        num_of_unique_cards = 13;
    } else {
        num_of_suits = 2;
        num_of_unique_cards = 12;        
    }

    for (int i = 0; i < num_of_suits; i++) {
        for (int j = 0; j < num_of_unique_cards; j++) {
            int current_iteration = (i*num_of_unique_cards) + j; //current iteration
            new_deck[current_iteration][0] = (current_iteration % num_of_unique_cards) + 1; //only using numbers 1 through 13
            new_deck[current_iteration][1] = suits[i];
        }
    }
}

// void create_memory_deck(int new_deck[25][2]) {
//     for (int i = 0; i < 2; i++) {
//         for (int j = 0; j < 12; j++) {
//             int current_iteration = (i*12) + j; //current iteration out of 24
//             new_deck[current_iteration][0] = (current_iteration % 12) + 1; 
//             new_deck[current_iteration][1] = i + 1;
//         }
//     }    
//     new_deck[24][0] = 13;
//     new_deck[24][1] = 0;
// }

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
        case 1:
            return 'H';
        case 2:
            return 'D';
        case 3:
            return 'C';
        case 4:
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

int add_cards_to_hand(int hand[52][2], int cards_to_add[][2], int amount_to_add) {
    int cards_added = 0;
    for (int i = 0; i < 52; i++) {
        if (cards_added == amount_to_add) {
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
    return 52;
}

int war_tie(int player_hand[52][2], int opponent_hand[52][2], int prize_cards[8][2]) {
    int player_won = 0;
    int player_amount_of_cards = check_amount_of_cards(player_hand);
    int opponent_amount_of_cards = check_amount_of_cards(opponent_hand);
    int prizes = 8;
    int lowest_cards = 5;

    printf("It's a War!\n");
    printf("Player's prize cards:\n");

    if (player_amount_of_cards < 5 || opponent_amount_of_cards < 5) {
        if (player_amount_of_cards > opponent_amount_of_cards) {
            lowest_cards = opponent_amount_of_cards;
        } else {
            lowest_cards = player_amount_of_cards;
        }
        prizes = (lowest_cards -1 )* 2;
    }

    for (int i = 0; i < prizes; i++) {
        if (i < (prizes / 2)) {
            printf("%d of %d\n", player_hand[0][0], player_hand[0][1]);
            prize_cards[i][0] = player_hand[0][0];
            prize_cards[i][1] = player_hand[0][1];
            move_cards_up_in_hand(player_hand);
        } else {
            if (i == (prizes / 2)) {
                printf("Opponent's prize cards:\n");
            }
            printf("%d of %d\n", opponent_hand[0][0], opponent_hand[0][1]);
            prize_cards[i][0] = opponent_hand[0][0];
            prize_cards[i][1] = opponent_hand[0][1];
            move_cards_up_in_hand(opponent_hand);
        }
    }

    printf("Player's card: %d of %d\n", player_hand[0][0], player_hand[0][1]);
    printf("Opponent's card: %d of %d\n", opponent_hand[0][0], opponent_hand[0][1]);    

    int prize_cards2[8][2];
    if (player_hand[0][0] > opponent_hand[0][0]) {
        player_won = 1;
        printf("Player Wins\n");
        add_cards_to_hand(player_hand, prize_cards, prizes);
    } else if (player_hand[0][0] < opponent_hand[0][0]) {
        player_won = 0;
        printf("Opponent Wins\n");
        add_cards_to_hand(opponent_hand, prize_cards, prizes);
    } else {
        player_won = war_tie(player_hand, opponent_hand, prize_cards2);
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
    int manual_mode = 0;
    int player_cards_left = 26;
    int opponent_cards_left = 26;

    split_deck(deck, player_hand, opponent_hand);

    printf("Would you like automatic or manual mode?\n[1] Auto\n[2] Manual\n");
    scanf("%d", &manual_mode);
    manual_mode--;

    while (player_cards_left && opponent_cards_left && (turns < max_turns)) {
        printf("\nTurn %d\n", turns + 1);
        current_player_card[0] = player_hand[0][0];
        current_player_card[1] = player_hand[0][1];
        current_opponent_card[0] = opponent_hand[0][0];
        current_opponent_card[1] = opponent_hand[0][1];
        printf("Player's card: %d of %d\n", current_player_card[0], current_player_card[1]);
        printf("Opponent's card: %d of %d\n", current_opponent_card[0], current_opponent_card[1]);
        int prize_cards[8][2];

        if (current_player_card[0] > current_opponent_card[0]) {
            player_won = 1;
        } else if (current_player_card[0] < current_opponent_card[0]){
            player_won = 0;
        } else {
            player_won = war_tie(player_hand, opponent_hand, prize_cards);
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
            add_cards_to_hand(player_hand, cards_won, 2);
            player_wins++;
        } else {
            printf("Opponent wins!\n");
            add_cards_to_hand(opponent_hand, cards_won, 2);
            opponent_wins++;
        }
        player_cards_left = check_amount_of_cards(player_hand);
        opponent_cards_left = check_amount_of_cards(opponent_hand);
        printf("Player has %d card%s; Opponent has %d card%s.\n", player_cards_left, (player_cards_left > 1 || player_cards_left == 0) ? "s" : "", 
            opponent_cards_left, (opponent_cards_left > 1 || opponent_cards_left == 0) ? "s" : "");
        turns++;

        if (manual_mode) {
            printf("\n");
            printf("Enter 1 to continue or 2 to exit manual mode: ");
            scanf("%d", &manual_mode);
            if (manual_mode == 2) {
                manual_mode -= 2;
            }
        }
    }

    printf("\nPlayer wins: %d\nOpponent wins: %d\n", player_wins, opponent_wins);
    printf("%s Wins War!\n", player_wins > opponent_wins ? "Player" : "Opponent");    
}

void memory(int deck[52][2]) {
    printf("Welcome to Memory!\n");
    int card_to_flip[2] = {-1, -1};
    int card_to_flip2[2] = {-1, -1};
    int memory_deck[25][2];
    // create_memory_deck(memory_deck);
    memory_print(memory_deck, card_to_flip, card_to_flip2);
    int row;
    int col;
    while (1) {
        for (int i = 0; i < 2; i++) {
            printf("Card #%d row?\n", i+1);
            scanf("%d", &row);
            printf("Card #%d column?\n", i+1);
            scanf("%d", &col);
            if (i == 0) {
                card_to_flip[0] = row;
                card_to_flip[1] = col;
            } else {
                card_to_flip2[0] = row;
                card_to_flip2[1] = col;
            }
            memory_print(deck, card_to_flip, card_to_flip2);
        }
    }
}

void memory_print(int deck[25][2], int card_to_flip[2], int card_to_flip2[2]) {
    for (int i = 0; i < 6; i++) {
        if (i > 0) {
            printf("R%d ", i);
        }
        for (int j = 0; j < 5; j++) {
            if (i == 0) {
                if (j == 0) {
                    printf("   ");
                }
                printf("C%d ", j+1);
            } else {
                if (card_to_flip[0] == i && card_to_flip[1] == j + 1) {
                    printf("%d%d ", deck[(i*5) + j][0], deck[(i*5) + j][1]);
                } else if (card_to_flip2[0] == i && card_to_flip2[1] == j + 1) {
                    printf("%d%d ", deck[(i*5) + j][0], deck[(i*5) + j][1]);
                } else {
                    printf("[] ");
                }
            }
        }
        printf("\n");
    }
}

void print_memory_deck(int deck[25][2]) {
    int current_card;
    for (int i = 0; i < 25; i++) { //looping through every card
        current_card = deck[i][0];
        if (current_card == 1 || current_card >= 11) { //if it's a ace, jack, queen, or king
            printf("Card #%d: %c of %c\n", i + 1, number_to_character_for_deck(deck[i][0]), number_to_suit(deck[i][1])); //it's going to run it through the function translator
        } else {
            printf("Card #%d: %d of %c\n", i + 1, deck[i][0], number_to_suit(deck[i][1]));
        }
    }
}

void shuffle_memory_deck(int deck[25][2]) {
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