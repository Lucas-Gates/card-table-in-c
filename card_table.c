#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//function prototypes
void create_deck(int new_deck[52][2], int is_normal_deck);
void print_deck(int deck[][2], int is_normal_deck);
char number_to_character_for_deck(int num);
char number_to_suit(int num);
void shuffle_deck(int deck[][2], int is_normal_deck);
void split_deck(int original_deck[52][2], int deck1[52][2], int deck2[52][2]);
void move_cards_up_in_hand(int hand[52][2]);
int add_cards_to_hand(int hand[52][2], int cards_to_add[][2], int amount_to_add);
int check_amount_of_cards(int hand[52][2]);
int war_tie(int player_hand[52][2], int opponent_hand[52][2], int prize_cards[8][2]);
void war(int deck[52][2], int max_turns);
void memory(int deck[52][2]);
void memory_print(int deck[25][2], int card_to_flip[2], int card_to_flip2[2], int matches[5][5]);
void initialize_matches_array(int matches[5][5]);
int compare_two_memory_positions(int deck[25][2], int card1_pos[2], int card2_pos[2]);
int card_value_from_position(int deck[25][2], int card_pos[2]);
int check_if_matches_is_filled(int matches[5][5]);
void go_fish(int deck[52][2]);
void deal_cards(int deck[52][2], int new_hand[52][2], int num_of_cards);
void print_hand_as_list(int hand[52][2]);
void initialize_hand(int new_hand[][2], int num_of_cards);
void bubble_sort(int array_to_sort[], int size_of_array);
int check_if_card_in_hand(int hand[52][2], int card_value, int cards_in_hand[3][2]);

int main() {
    srand(time(NULL));
    printf("Welcome to the Card Table!\n");
    int choice;
    int game_selected = 0;
    int type_of_deck;
    int amount_of_cards_in_deck;

    while (1) {
        do {
            printf("What game do you want to play?\n");
            printf("[1] War\n");
            printf("[2] Memory\n");
            printf("[3] Go Fish\n");
            printf("[0] Quit\n");
            scanf("%d", &choice);
            switch(choice) {
                case 1:
                    game_selected = 1;
                    type_of_deck = 1;
                    amount_of_cards_in_deck = 52;
                    break;
                case 2:
                    game_selected = 2;
                    type_of_deck = 0;
                    amount_of_cards_in_deck = 25;
                    break;
                case 3:
                    game_selected = 3;
                    type_of_deck = 1;
                    amount_of_cards_in_deck = 52;
                    break;
                case 0:
                    printf("Thanks for playing!\n");
                    return 0;
                default:
                    printf("Invalid input; try again.\n");
                    break;
            }
        } while (!game_selected);

        int first_deck[amount_of_cards_in_deck][2];
        create_deck(first_deck, type_of_deck);
        //print_deck(first_deck, type_of_deck); // (for debugging)
        shuffle_deck(first_deck, type_of_deck);
        //print_deck(first_deck, type_of_deck); // (for debugging)
        if (game_selected == 1) {
            int turns = 1000;
            printf("What would you like the turn limit to be?\n");
            scanf("%d", &turns);
            war(first_deck, turns);
        } else if (game_selected == 2) {
            memory(first_deck);
        } else if (game_selected == 3) {
            go_fish(first_deck);
        }

        printf("\n");
    }
}

void create_deck(int new_deck[][2], int is_normal_deck) {
    int suits[4] = {1, 2, 3, 4}; //hearts, diamonds, clubs, spades
    int num_of_suits;
    int num_of_unique_cards;

    if (is_normal_deck) {
        num_of_suits = 4;
        num_of_unique_cards = 13;
    } else {
        num_of_suits = 2;
        num_of_unique_cards = 12;       
        new_deck[24][0] = 13;
        new_deck[24][1] = 1; 
    }

    for (int i = 0; i < num_of_suits; i++) {
        for (int j = 0; j < num_of_unique_cards; j++) {
            int current_iteration = (i*num_of_unique_cards) + j; //current iteration
            new_deck[current_iteration][0] = (current_iteration % num_of_unique_cards) + 1; 
            new_deck[current_iteration][1] = suits[i];
        }
    }
}

void print_deck(int deck[][2], int is_normal_deck) {
    int current_card;
    int num_of_cards_in_deck;

    if (is_normal_deck) {
        num_of_cards_in_deck = 52;
    } else {
        num_of_cards_in_deck = 25;
    }

    for (int i = 0; i < num_of_cards_in_deck; i++) { //looping through every card
        current_card = deck[i][0];
        if (is_normal_deck) {
            if (current_card == 1 || current_card >= 11) { //if it's a ace, jack, queen, or king
                printf("Card #%d: %c of %c\n", i + 1, number_to_character_for_deck(deck[i][0]), number_to_suit(deck[i][1])); //it's going to run it through the function translator
            } else {
                printf("Card #%d: %d of %c\n", i + 1, deck[i][0], number_to_suit(deck[i][1]));
            }
        } else {
            int num_of_cards_of_given_value = 2;

            if (deck[i][0] == 13) {
                num_of_cards_of_given_value = 1;
            }

            printf("Card #%d: %d (%d of %d)\n", i + 1, deck[i][0], deck[i][1], num_of_cards_of_given_value);
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

void shuffle_deck(int deck[][2], int is_normal_deck) {
    int num_of_cards_in_deck;

    if (is_normal_deck) {
        num_of_cards_in_deck = 52;
    } else {
        num_of_cards_in_deck = 25;
    }

    int copy_deck[num_of_cards_in_deck][2];
    for (int i = 0; i < num_of_cards_in_deck; i++) {
        for (int j = 0; j < 2; j++) {
            copy_deck[i][j] = deck[i][j]; //creating an exact copy of the deck array
            deck[i][j] = -1; //filling the original deck array with only -1
        }
    }
    int random_num = 0;
    for (int k = 0; k < num_of_cards_in_deck; k++) {
        do {
            random_num = rand() % num_of_cards_in_deck;
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

void memory(int deck[25][2]) {
    int card_to_flip[2];
    int card_to_flip2[2];
    int rounds = 0;
    int row;
    int col;
    int matches[5][5];
    int valid_card = 1;
    int keep_playing = 1;
    int win = 0;
    initialize_matches_array(matches);
    print_deck(deck, 0);
    printf("\nWelcome to Memory!\n");

    while (keep_playing) {
        rounds++;
        card_to_flip[0] = -1;
        card_to_flip[1] = -1;
        card_to_flip2[0] = -1;
        card_to_flip2[1] = -1;
        printf("----- Round %d -----\n", rounds);
        memory_print(deck, card_to_flip, card_to_flip2, matches);

        for (int i = 0; i < 2; i++) {
            do {
                printf("Card #%d row?\n", i+1);
                scanf("%d", &row);
                printf("Card #%d column?\n", i+1);
                scanf("%d", &col);

                if (((card_to_flip[0] == row) && (card_to_flip[1] == col)) || (matches[row-1][col-1] > 0) || (row > 5) || (row < 1) || (col > 5) || (col < 1)) {
                    printf("Invalid card; try again.\n");
                    valid_card = 0;
                } else {
                    valid_card = 1;
                }
            } while (!valid_card);

            if (i == 0) {
                card_to_flip[0] = row;
                card_to_flip[1] = col;
                if ((card_value_from_position(deck, card_to_flip) == 13) && (check_if_matches_is_filled(matches))) {
                    memory_print(deck, card_to_flip, card_to_flip2, matches);
                    printf("You won in %d rounds!\n", rounds);
                    return;
                }
            } else {
                card_to_flip2[0] = row;
                card_to_flip2[1] = col;
            }
            memory_print(deck, card_to_flip, card_to_flip2, matches);
        }
        //printf("Card 1's value: %d; Card 2's value: %d\n", card_value_from_position(deck, card_to_flip), card_value_from_position(deck, card_to_flip2));
        int match_card_value = compare_two_memory_positions(deck, card_to_flip, card_to_flip2);
        //printf("Match card value: %d\n", match_card_value);
        if (match_card_value) {
            printf("You got a match!\n");
            // printf("CTF1[0]: %d; CTF1[1]: %d; CTF2[0]: %d; CTF2[1]: %d\n", card_to_flip[0], card_to_flip[1], card_to_flip2[0], card_to_flip2[1]);
            matches[card_to_flip[0]-1][card_to_flip[1]-1] = match_card_value;
            matches[card_to_flip2[0]-1][card_to_flip2[1]-1] = match_card_value;
        } else {
            printf("No match.\n");
        }
        // printf("Matches array:\n");
        // for (int a = 0; a < 5; a++) {
        //     for (int b = 0; b < 5; b++) {
        //         printf("%d ", matches[a][b]);
        //     }
        //     printf("\n");
        // }
        printf("Enter 1 to continue; enter 0 to quit: ");
        scanf("%d", &keep_playing);
        if (keep_playing) {
            printf("\n");
        }
    }
}

void memory_print(int deck[25][2], int card_to_flip[2], int card_to_flip2[2], int matches[5][5]) {
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
                int current_card = (((i-1)*5) + (j));
                if (card_to_flip[0] == i && card_to_flip[1] == j + 1) {
                    printf("%s%d ", deck[current_card][0] < 10 ? "0" : "", deck[current_card][0]);
                } else if (card_to_flip2[0] == i && card_to_flip2[1] == j + 1) {
                    printf("%s%d ", deck[current_card][0] < 10 ? "0" : "", deck[current_card][0]);
                } else if (matches[i-1][j] > 0) {
                    printf("%s%d ", deck[current_card][0] < 10 ? "0" : "", deck[current_card][0]);
                } else {
                    //printf("%d%d ", deck[current_card][0], deck[current_card][1]);
                    printf("[] ");
                }
            }
        }
        printf("\n");
    }
}

void initialize_matches_array(int matches[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            matches[i][j] = 0;
        }
    }
}

int compare_two_memory_positions(int deck[25][2], int card1_pos[2], int card2_pos[2]) {
    int card1_value = card_value_from_position(deck, card1_pos);
    int card2_value = card_value_from_position(deck, card2_pos);
    
    if (card1_value == card2_value) {
        return card1_value;
    }
    return 0;
}

int card_value_from_position(int deck[25][2], int card_pos[2]) {
    int row = card_pos[0] - 1;
    int col = card_pos[1] - 1;

    return deck[(row*5) + col][0];
}

int check_if_matches_is_filled(int matches[5][5]) {
    int spots_not_filled = 0;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matches[i][j] == 0) {
                spots_not_filled++;
            }
        }
    }

    if (spots_not_filled == 1) {
        return 1;
    } 
    return 0;
}

void go_fish(int deck[52][2]) {
    printf("Welcome to Go Fish!\n");
    int player_hand[52][2];
    int opponent_hand[52][2];
    int ask_choice;

    deal_cards(deck, player_hand, 7);
    deal_cards(deck, opponent_hand, 7);

    //print_deck(player_hand, 1);
    //while (1) {
        printf("Choose a card to ask for:\n");
        print_hand_as_list(player_hand);
        scanf("%d", &ask_choice);
    //}
}

void deal_cards(int deck[52][2], int new_hand[52][2], int num_of_cards) {
    initialize_hand(new_hand, 52);
    for (int i = 0; i < num_of_cards; i++) {
        new_hand[i][0] = deck[0][0];
        new_hand[i][1] = deck[0][1];
        move_cards_up_in_hand(deck);
    }
}

void print_hand_as_list(int hand[52][2]) {
    int unique_cards[13];
    int unique = 1;
    int times_run = 0;
    int size_of_unique_cards = 0;

    for (int i = 0; i < 13; i++) {
        unique_cards[i] = -1;
    }

    for (int j = 0; j < 52; j++) {
        if (hand[j][0] != -1) {
            unique = 1;
            for (int k = 0; k < 13; k++) {
                if (unique_cards[k] == hand[j][0]) {
                    unique = 0;
                }
            }
            if (unique) {
                for (int l = 0; l < 13; l++) {
                    if (unique_cards[l] == -1 && times_run == 0) {
                        unique_cards[l] = hand[j][0];
                        times_run++;
                        size_of_unique_cards++;
                    }
                }
                times_run = 0;
            }
        }
    }

    bubble_sort(unique_cards, size_of_unique_cards);
    for (int m = 0; m < size_of_unique_cards; m++) {
        printf("%d ", unique_cards[m]);
    }
    printf("\n");
}

void initialize_hand(int new_hand[][2], int num_of_cards) {
    for (int i = 0; i < num_of_cards; i++) {
        new_hand[i][0] = -1;
        new_hand[i][1] = -1;
    }
}

void bubble_sort(int array_to_sort[], int size_of_array) {
    int copy_array;
    for (int i = 0; i < size_of_array; i++) {
        for (int j = 0; j < size_of_array-1; j++) {
            if (array_to_sort[j] > array_to_sort[j+1]) {
                copy_array = array_to_sort[j];
                array_to_sort[j] = array_to_sort[j+1];
                array_to_sort[j+1] = copy_array;
            }
        }
    }
}

int check_if_card_in_hand(int hand[52][2], int card_value, int cards_in_hand[3][2]) {
    initialize_hand(cards_in_hand, 3);
    int amount_of_same_cards = 0;

    for (int i = 0; i < 52; i++) {
        if (hand[i][0] == card_value) {
            cards_in_hand[amount_of_same_cards][0] = card_value;
            cards_in_hand[amount_of_same_cards][1] = hand[i][1];
            amount_of_same_cards++;
        }
    }

    return amount_of_same_cards;
}