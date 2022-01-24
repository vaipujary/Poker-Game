// Author: Vaidehi Pujary
// Date created: 11/12/21
// Poker - Two Pairs or Better

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define CLUBS "\u2663"
#define DIAMONDS "\u2666"
#define HEARTS "\u2665"
#define SPADES "\u2660"
#define RANDOM "\u25A0"

typedef struct card_s { //defining a user-defined type for the cards
    
    char suit[10];
    int face;
    struct card_s *next;
    
} card;

void create_cards(int face, char suit[], card * temp); // declaring all user-defined functions
void initialize_cards(card **headp, card **tail);
void print_deck(card *headp);
void shuffle_cards (card *headp,int seed);
void player_hand(card **player_headp, card **headp);
void print_player_hand(card **player_headp);
void free_cards(card *headp);
void print_welcome(char name[]);
void print_total_coins(char name[], int coins);
void new_player_hand(card **headp, card **player_headp, int picked_cards[]);
void swap_cards (card *headp, card *player_headp, int index);
int count_cards(card *headp);
int flush(card *player_headp);
int royal_flush(card *player_headp);
int straight_flush(card *player_headp);
int four_of_a_kind(card *player_headp);
int full_house(card *player_headp);
int straight(card *player_headp);
int three_of_a_kind(card *player_headp);
int two_pairs(card *player_headp);
int payout(int num, int bet);
void player_hand_copy(card *player_headp, card **player_headp_copy);

int main(int argc, const char * argv[]) {
  
    srand((int)time(0));
    card *headp = NULL; // declaring required variables
    card *player_headp = headp; // initializing head pointer of the player hand to the head pointer of the deck of cards
    card *tail = NULL;
    card *player_headp_copy = NULL;
    int total_coins = 100;
    int bet = 0;
    int bet_match = 0;
    int picked_cards[5];
    int picked_cards_copy[5];
    int match = 0;
    int picked_cards_count = 0;
    char user_key = '\n';
    int total_payout = 0;
    char player_name[100];
   
    printf("Enter your name: ");
    fgets(player_name, 20, stdin);
    unsigned long player_name_length = strlen(player_name);
    player_name[player_name_length-1] = '\0';
    
    printf("\n");
    print_welcome(player_name);
    initialize_cards(&headp, &tail); // creating a deck of 52 cards
    shuffle_cards(headp, 1); // shuffling cards in the deck
    
    while(user_key == '\n') { // executed if user presses Enter key to continue playing after the first round
     
    print_total_coins(player_name, total_coins); // prints the total number of coins the player has remaining
        match = 0;
        
        if(count_cards(headp) < 20) { // a new deck of 52 cards is created if less than 20 cards are remaining in the deck
            
            initialize_cards(&headp, &tail);
            shuffle_cards(headp, 1);
            
        }
    
        for(int i = 0; i < 5; ++i) {
            
            picked_cards[i] = 0;
            picked_cards_copy[i] = 0;
            
        }
        
        printf("Place your bet (1-%d) coins (-1 to quit playing): ", total_coins); // prompting the user to enter a bet between 1 and the number of coins they have remaining
        scanf("%d", &bet);
    
        if(bet == -1) { // program ends if they enter -1
        
            break;
            
        }
        
        while((bet < 1) || (bet > total_coins)) { // the program only accepts a bet between 1 and the total coins the player has remaining
            
            if(bet == -1) {
                
                bet_match = 1;
                break;
                
            }
            
        printf("Place your bet (1-%d) coins (-1 to quit playing): ", total_coins);
        scanf("%d", &bet);
        
        }
        
        if(bet_match == 1) {
            
            break;
            
        }
    
        printf("\nYou bet %d coins\n\n", bet);
    
        printf("%s's hand:\n", player_name);
        
        player_hand(&player_headp, &headp); // creating the player's hand of 5 cards
        print_player_hand(&player_headp);
    
        for(int i = 0; i < 5; ++i) {
        
            printf("Pick cards (between 1-5) to hold (-1 to stop): ");
            scanf("%d", &picked_cards[i]);
        
            if(picked_cards[i] == -1) { // if the user does not choose all cards in their hand
            
                match = 1;
                picked_cards[i] = 0;
                
                for(int k = 0 ; k < 5; ++k) {
                    
                    picked_cards_copy[k] = picked_cards[k];
                    
                }
                
                for(int j = 0; j < 5; ++j) {
                    
                    if(picked_cards[j] != 0) {
                        
                        picked_cards_count += 1;
                        
                        if(picked_cards_copy[j] == picked_cards[j]) {
                        
                            picked_cards_copy[j] = 0;
                            
                        }
                     
                        picked_cards_copy[picked_cards[j]-1] = picked_cards[j]; // placing the numbers of the picked cards sequentially
                        
                    }
                    
                }

                break;
                
            }
            
            while(picked_cards[i] < 1 || picked_cards[i] > 5) {
            
                printf("Pick cards (between 1-5) to hold (-1 to stop): ");
                scanf("%d", &picked_cards[i]);
                
                }
            
        }
        
        if(match == 0) { // executed if the user picks all cards in their hand
            
            for(int k = 0 ; k < 5; ++k) {
                
                picked_cards_copy[k] = picked_cards[k];
                
            }
            
            for(int j = 0; j < 5; ++j) {
                
                if(picked_cards[j] != 0) {
                    
                    picked_cards_count += 1;
                    
                    if(picked_cards_copy[j] == picked_cards[j]) {
                        
                        picked_cards_copy[j] = 0;
                        
                    }
                 
                    picked_cards_copy[picked_cards[j]-1] = picked_cards[j]; // sorting the numbers of the picked cards based on the index
                    
                }
            
            }

        }
        
       new_player_hand(&headp, &player_headp, picked_cards_copy); // a new player hand is created based on the cards the player decides to keep
       player_hand_copy(player_headp, &player_headp_copy);
        
        if(royal_flush(player_headp) == 1) { // executed if the player's hand has achieved Royal Flush
            
            printf("\n%s's hand: (Royal Flush)\n", player_name);
            print_player_hand(&player_headp_copy);
            
            total_payout = payout(1,bet);
            total_coins += total_payout;
            
            printf("You WON %d coins and you now have %d coins\n", total_payout, total_coins);
           
        }
        
        else if(straight_flush(player_headp) == 1) { // executed if the player's hand has achieved Straight Flush
          
            printf("\n%s's hand: (Straight Flush)\n", player_name);
            print_player_hand(&player_headp_copy);
            total_payout = payout(2,bet);
            total_coins += total_payout;
            
            printf("You WON %d coins and you now have %d coins\n", total_payout, total_coins);
            
        }
        
        else if(four_of_a_kind(player_headp) == 1) { // executed if the player's hand has achieved Four of a Kind
          
            printf("\n%s's hand: (Four of a Kind)\n", player_name);
            print_player_hand(&player_headp_copy);
            total_payout = payout(3,bet);
            total_coins += total_payout;
            
            printf("You WON %d coins and you now have %d coins\n", total_payout, total_coins);
            
        }
        
        else if(full_house(player_headp) == 1) { // executed if the player's hand has achieved Full House
            
            printf("\n%s's hand: (Full House)\n", player_name);
            print_player_hand(&player_headp_copy);
            total_payout = payout(4,bet);
            total_coins += total_payout;
            
            printf("You WON %d coins and you now have %d coins\n", total_payout, total_coins);
            
        }
        
        else if(flush(player_headp) == 1) { // executed if the player's hand has achieved Flush
           
            printf("\n%s's hand: (Flush)\n", player_name);
            print_player_hand(&player_headp_copy);
            total_payout = payout(5,bet);
            total_coins += total_payout;
            
            printf("You WON %d coins and you now have %d coins\n", total_payout, total_coins);
            
        }
        
        else if(straight(player_headp) == 1) { // executed if the player's hand has achieved Straight
           
            printf("\n%s's hand: (Straight)\n", player_name);
            print_player_hand(&player_headp_copy);
            total_payout = payout(6,bet);
            total_coins += total_payout;
            
            printf("You WON %d coins and you now have %d coins\n", total_payout, total_coins);
            
        }
        
        else if(three_of_a_kind(player_headp) == 1) { // executed if the player's hand has achieved Three of a Kind
           
            printf("\n%s's hand: (Three of a Kind)\n", player_name);
            print_player_hand(&player_headp_copy);
            total_payout = payout(7,bet);
            total_coins += total_payout;
            
            printf("You WON %d coins and you now have %d coins\n", total_payout, total_coins);
            
        }
        
        else if(two_pairs(player_headp) == 1) { // executed if the player's hand has achieved Two Pairs
           
            printf("\n%s's hand: (Two Pairs)\n", player_name);
            print_player_hand(&player_headp_copy);
            total_payout = payout(8,bet);
            total_coins += total_payout;
            
            printf("You WON %d coins and you now have %d coins\n", total_payout, total_coins);
            
        }
        
        else { // executed if the player's hand has not achieved any winning condition
            
            printf("\n%s's hand: ", player_name);
            print_player_hand(&player_headp_copy);
            total_coins -= bet;
            printf("You LOST and you now have %d coins\n\n", total_coins);
            
        }
       
        if(total_coins == 0) { // the game ends if the player has no coins remaining
            
            printf("You lost all your coins. Game Over!\n");
            break;
        }
        
        printf("Hit Enter key to continue: \n");
        scanf("%*c%c", &user_key);
    
    }
    
        printf("Goodbye %s\n", player_name);
        free_cards(headp); // freeing dynamically allocated memory
        free_cards(player_headp_copy);
    
    return 0;
}

void print_deck(card *headp) { // function to print the deck of cards
    
    int count = 0;
    card *temp = headp;
    
    while(temp != NULL) {
            
            if(temp->face == 1) {
                
                printf("A%s ", temp->suit);
            
            }
            
            else if (temp->face == 11) {
                
                printf("J%s ", temp->suit);
            }
            
            else if (temp->face == 12) {
                
                printf("Q%s ", temp->suit);
            }
            
            else if (temp->face == 13) {
                
                printf("K%s ", temp->suit);
            }
            
            else {
                
                printf("%d%s ", temp->face, temp->suit);
            }
        
            temp = temp->next;
            
            count++;
        
            if(count == 13) {
        
                printf("\n");
            
                count = 0;
            
            }
        
    }
    
    printf("\n");
}

void create_cards(int face, char suit[], card *temp) { // function to assign the face and suit to each card in the deck
    
    temp->face = face;
    strcpy(temp->suit,suit);
    
}

void initialize_cards(card **headp, card **tail) { // function to initialize 52 cards in the deck
    
    int count = 0;
    card *temp;
    
    for(int j = 0; j < 4; ++j) {
            
        for (int i = 1; i < 14; ++i) {
            
            count++;
            
            temp = (card*)malloc(sizeof(card));
           
            if (j == 0) {
           
                create_cards(i, SPADES, temp);
                
            }
            
            else if (j == 1) {
                
                create_cards(i, DIAMONDS, temp);
                
            }
            
            else if (j == 2) {
                
                create_cards(i, HEARTS, temp);
                
            }
            
            else if (j == 3) {
                
                create_cards(i, CLUBS, temp);
                
            }
       
            if (count == 1) {
                
                *headp = temp;
                
            }
            
            else {
                
                (*tail)->next = temp;
                
            }
            
            *tail = temp;
           (*tail)->next = NULL;
        }
    
    }

}

void shuffle_cards(card *headp, int seed) { // function to shuffle cards in the deck
    
    card *pt;
    card *temp;
    
    int temp_face;
    char temp_suit[10];
    
    for (int j = 0; j < 10000; ++j) {
        
        pt = headp;
        
        while (pt != NULL) {
        
            temp = headp;
        
            int card = rand() % 52;
        
            for (int i = 0; i < card; ++i) {
            
                temp = temp->next;
            
            }
            
        temp_face = pt->face;
        pt->face = temp->face;
        temp->face = temp_face;
            
        strcpy(temp_suit, pt->suit);
            
        if(strcmp(pt->suit, temp->suit)!=0) {
                
            strcpy(pt->suit, temp->suit);
                
         }
            
        strcpy((temp)->suit,temp_suit);
            
        pt = pt->next;

      }
        
   }

}

void print_player_hand(card **player_headp){ // function to print the cards in the player's hand
    
    card *player_temp = *player_headp;
    player_temp->next->next->next->next->next = NULL;
    
    while(player_temp != NULL) {
        
        if(player_temp->face == 1) {
            
            printf("A%s ", player_temp->suit);
        
        }
        
        else if (player_temp->face == 11) {
            
            printf("J%s ", player_temp->suit);
            
        }
        
        else if (player_temp->face == 12) {
            
            printf("Q%s ", player_temp->suit);
            
        }
        
        else if (player_temp->face == 13) {
            
            printf("K%s ", player_temp->suit);
            
        }
        
        else {
            printf("%d%s ", player_temp->face, player_temp->suit);
            
        }
    
        player_temp = player_temp->next;
        
    }
    
    printf("\n\n");
    
}

void player_hand(card **player_headp, card **headp) { // function to create the player's hand from the first five cards in the deck
    
    *player_headp = *headp;
    
    card *temp = *headp;
    
    for(int i = 1; i < 5; ++i) {
    
        temp = temp->next;
        
    }
    
    *headp = temp->next;
    temp->next = NULL;
    
}

void player_hand_copy(card *player_headp, card **player_headp_copy) { // function to create a copy of the player's hand
    
    card *player_temp = player_headp;
    
    *player_headp_copy = (card*)malloc(sizeof(card));
    
    (*player_headp_copy)->face = player_temp->face;
    strcpy((*player_headp_copy)->suit, player_temp->suit);
    card *player_temp_copy = *player_headp_copy;
    
    player_temp = player_temp->next;
    
    while(player_temp != NULL) {
     
         player_temp_copy->next = (card*)malloc(sizeof(card));
         player_temp_copy = player_temp_copy->next;
         
         player_temp_copy->face = player_temp->face;
         strcpy(player_temp_copy->suit, player_temp->suit);
         
        player_temp = player_temp->next;
     
     }
    
}

void free_cards(card *headp) { // function to free dynamically allocated memory in the 52 card deck
    
    card *temp;
    
    while (headp != NULL) {
        
        temp = headp;
        headp = headp->next;
        free(temp);
        
    }
    
}

void print_welcome(char name[]) { // function to greet user and display all the winning conditions
    
    printf("$$$$$$$$$ $$$$$$$$$ $$$$$$$$$ $$$$$$$$$ $$$$$$$$$\n\t\t\t$$$$$$$$$ $$$$$$$$$ $$$$$$$$$\n");
    printf("%s,\n Let's play Two pairs or Better\n\t\t$$$$$$$$$ $$$$$$$$$ $$$$$$$$$\n$$$$$$$$$ $$$$$$$$$ $$$$$$$$$ $$$$$$$$$ $$$$$$$$$\n$$$$$$$$$\tRank of winning\t  $$$$$$$$$\n\t\t\t\t\t\t\t\tPay\n", name);
    printf("Royal Flush\t\t10\u2660 J\u2660 Q\u2660 K\u2660 A\u2660\t250*bet\n");
    printf("Straight Flush\t2\u2663 3\u2663 4\u2663 5\u2663 6\u2663\t100*bet\n");
    printf("Four of a Kind\t9\u2660 9\u2663 9\u2666 9\u2660 \u25A0\t50*bet\n");
    printf("Full House\t\t9\u2666 9\u2665 9\u2660 3\u2663 3\u2665\t25*bet\n");
    printf("Flush\t\t\t\u25A0\u2663 \u25A0\u2663 \u25A0\u2663 \u25A0\u2663 \u25A0\u2663\t10*bet\n");
    printf("Straight\t\t4\u25A0 5\u25A0 6\u25A0 7\u25A0 8\u25A0\t5*bet\n");
    printf("Three of a Kind\t9\u2660 9\u2663 9\u2666 \u25A0 \u25A0\t\t4*bet\n");
    printf("Two Pair\t\tK\u2660 K\u2666 6\u2666 6\u2665 \u25A0\t2*bet\n\n");
    
}

void print_total_coins(char name[], int coins) { // function to print the total number of coins the player has remaining 
    
    printf("********* ********* ********* ********* *********\n********* ");
    printf("%s, you have %d coins ", name, coins);
    printf("*********\n********* ********* ********* ********* *********\n\n");
    
}

void swap_cards (card *headp, card *player_headp, int index) { // function to swap unpicked cards with cards from the deck
    
    card *player_temp = player_headp;
    card *temp = headp;
    
    if(index == 0) {
        
        player_headp->face = temp->face;
        strcpy(player_headp->suit, temp->suit);
        
    }
    
    else {
        
        for(int i = 0; i < index; ++i) {
            
            player_temp = player_temp->next;
        
        }
        
        player_temp->face = temp->face;
        strcpy(player_temp->suit, temp->suit);
        
    }
    
    if(index == 4) {
        
        (player_temp)->next = NULL;
        
    }
    
}

void sort_cards(card *player_headp) { //sorting cards from minimum to maximum face value
    
    card *player_temp = player_headp;
    card *minimum_face_value = player_headp;
    int temp_face;
    char temp_suit[10];
    
    player_temp = player_temp->next;
    
    while(minimum_face_value != NULL) {
        
        while(player_temp != NULL) {
        
            if((player_temp->face)<(minimum_face_value->face)) {
            
            temp_face = minimum_face_value->face;
            minimum_face_value->face = player_temp->face;
            player_temp->face = temp_face;
                
            strcpy(temp_suit, minimum_face_value->suit);
            strcpy(minimum_face_value->suit, player_temp->suit);
            strcpy(player_temp->suit,temp_suit);
            
            }
            
            player_temp = player_temp->next;
            
        }
        
        minimum_face_value = minimum_face_value->next;
        player_temp = minimum_face_value;
        
    }
    
}

void new_player_hand(card **headp, card **player_headp, int picked_cards[]) { // function to create a new player hand based on the cards the user picked
    
    for(int i = 0; i < 5 ; ++i) {
        
        if(*picked_cards == 0) {
            
            swap_cards(*headp, *player_headp,i);
            *headp = (*headp)->next;
            
       }
        
        picked_cards += 1;
    
    }
    
}

int four_of_a_kind(card *player_headp){ // function to check if the player's hand has Four of a Kind
    
    card *player_temp = player_headp;
    player_temp->next->next->next->next->next = NULL;
    card *pt = player_headp;
    int same_face_count = 0;
    
    player_temp = pt->next;
    
    while (player_temp != NULL) {
        
        
        if(player_temp->face == pt->face) {
            
            same_face_count += 1;
            
        }
        
        player_temp = player_temp->next;
        
    }
    
    if (same_face_count == 3) {
        
        return 1;
        
    }
    
    else {
        
        pt = pt->next;
        player_temp = pt->next;
        same_face_count = 0;
        
        while (player_temp != NULL) {
            
            if(player_temp->face == pt->face) {
                
                same_face_count += 1;
                
            }
            
            player_temp = player_temp->next;
            
        }
        
        if (same_face_count == 3) {
            
            return 1;
            
        }
        
        else {
            
            return 0;
            
        }
        
    }
    
    
}

int full_house(card *player_headp) { // function to check if the player's hand has Full House
    
    card *player_temp = player_headp;
    player_temp->next->next->next->next->next = NULL;
    int face_value_count1 = 0;
    int face_value_count2 = 0;
    
    if(player_temp->face == player_temp->next->face) {
        
        face_value_count1 = 1;
        player_temp = player_temp->next->next;
        
    if(player_temp->face == player_temp->next->face && player_temp->face == player_temp->next->next->face) {
            
            face_value_count2 = 1;
            
        }
        
        
    if ((face_value_count1 + face_value_count2) == 2) {
            
            return 1;
            
    }
        
    else {
        
        face_value_count1 = 0;
            face_value_count2 = 0;
            player_temp = player_headp;
    }
        
    }
    
    if(player_temp->face == player_temp->next->face && player_temp->face == player_temp->next->next->face) {
            
            face_value_count2 = 1;
        
            player_temp = player_temp->next->next->next;
        
            if(player_temp->face == player_temp->next->face) {
            
                face_value_count1 = 1;
            
                }
        
            }
        
    if ((face_value_count1 + face_value_count2) == 2) {
            
            return 1;
            
    }
        
    else {
            
        return 0;
            
    }
    
}

int flush(card *player_headp) { // function to check if the player's hand has Flush
    
    card *player_temp = player_headp;
    player_temp->next->next->next->next->next = NULL;
    int count = 0;
    
    for(int i = 0; i < 4; ++i) {
        
        if(strcmp(player_temp->suit,player_temp->next->suit) == 0) {
            
            count++;
        }
        
        player_temp = player_temp->next;
        
    }
    
    if(count == 4) {
        
        return 1;
    }
    
    else {
        
        return 0;
        
    }
    
}

int straight_flush(card *player_headp){ // function to check if the player's hand has Straight Flush
  
    card *player_temp = player_headp;
    player_temp->next->next->next->next->next = NULL;
    int match = 1;
    
    if(flush(player_headp) == 0) {
        
        return 0;
        
    }
    
    else {
     
        while (player_temp->next != NULL) {
            
            if(player_temp->face != ((player_temp->next->face) - 1)) {
                
                match = 0;
                break;
                
            }
            
            player_temp = player_temp ->next;
        }
        
        if (match == 0) {
            
            return 0;
            
        }
        
        else {
            
            return 1;
            
        }
    }
    
}

int royal_flush(card *player_headp) { // function to check if the player's hand has Royal Flush
    
    sort_cards(player_headp);
    
   if(flush(player_headp) == 0) {
        
        return 0;
        
    }
    
   else {
       
    
        if((player_headp->face == 1) && (player_headp->next->face == 10) && (player_headp->next->next->face == 11) && (player_headp->next->next->next->face == 12) && (player_headp->next->next->next->next->face == 13))
        {
            
            return 1;
        }
        
        else {
            
            return 0;
            
        }
        
    }
    
}

int straight(card *player_headp){ // function to check if the player's hand has Straight
 
    card *player_temp = player_headp;
    player_temp->next->next->next->next->next = NULL;
    int match = 1;
    
    while (player_temp->next != NULL) {
        
        if(player_temp->face != (player_temp->next->face-1)) {
            
            match = 0;
            break;
        }
        
        player_temp = player_temp ->next;
        
    }
    
    if (match == 0) {
        
        return 0;
        
    }
    
    else {
        
        return 1;
        
    }
}

int three_of_a_kind(card *player_headp){ // function to check if the player's hand has Three of a Kind
 
    card *player_temp = player_headp;
    player_temp->next->next->next->next->next = NULL;
    card *pt = player_headp;
    int same_face_count = 0;
    
    player_temp = pt->next;
    
    while (player_temp!=NULL) {
        
        if(player_temp->face == pt->face) {
            
            same_face_count +=1;
            
        }
        
        player_temp = player_temp->next;
        
    }
    
    if (same_face_count == 2) {
        
        return 1;
    }
    
    else {
        
        pt = pt->next;
        player_temp = pt->next;
        same_face_count = 0;
        
        while (player_temp != NULL) {
            
            if(player_temp->face == pt->face) {
                
                same_face_count += 1;
                
            }
            
            player_temp = player_temp->next;
            
        }
        
        if (same_face_count == 2) {
            
            return 1;
            
        }
        
        else {
            
            pt = pt->next;
            player_temp = pt->next;
            same_face_count = 0;
            
            while (player_temp!=NULL) {
            
                if(player_temp->face == pt->face) {
                
                    same_face_count +=1;
                    
            }
            
            player_temp = player_temp->next;
                
        }
            
            if (same_face_count == 2) {
                
                return 1;
                
            }
            
            else {
                
                return 0;
                
            }
            
        }
    
    }
    
}

int two_pairs(card *player_headp){ // function to check if the player's hand has Two Pairs
  
    card *player_temp = player_headp;
    player_temp->next->next->next->next->next = NULL;
    int pair1_match = 0;
    int pair2_match = 0;
  
    while (player_temp->next != NULL) {
            
        if(player_temp->face == player_temp->next->face) {
            
            pair1_match = 1;
            break;
            
        }
        
        player_temp = player_temp->next;
        
    }
        
    if ((pair1_match == 1) && (player_temp->next->next != NULL)) {
        
        player_temp = player_temp->next->next;
        
        while (player_temp->next != NULL) {
            
            if(player_temp->face == player_temp->next->face) {
                
                pair2_match = 1;
                break;
                
            }
            
            player_temp = player_temp->next;
            
        }
        
    }
    
    if(pair1_match + pair2_match == 2) {
        
        return 1;
        
    }
    
    else {
        
        return 0;
        
    }

}

int payout(int num, int bet) { // function to calculate the payout if the player achieves a winning condition
    
    int payout = 0;
    
    if(num == 1) {
        
        payout = 250 * bet;
        
    }
    
    else if(num == 2) {
        
        payout = 100 * bet;
        
    }
    
    else if(num == 3) {
        
        payout = 50 * bet;
        
    }
    
    else if(num == 4) {
        
        payout = 25 * bet;
        
    }
    
    else if(num == 5) {
        
        payout = 10 * bet;
        
    }
    
    else if(num == 6) {
        
        payout = 5 * bet;
        
    }
    
    else if(num == 7) {
        
        payout = 4 * bet;
        
    }
    
    else {
        
        payout = 2 * bet;
        
    }
    
    return payout;
    
}

int count_cards(card *headp) { // function to count the total number of cards in the deck
    
    card *temp = headp;
    
    int count = 0;
    
    while(temp != NULL) {
        
        count += 1;
        temp = temp->next;
        
    }
    
    return count;
    
}
