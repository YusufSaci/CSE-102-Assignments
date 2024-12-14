#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_0F_CARD 52


struct card{

     const char *face;
     const char *suit;
};

/* creates a deck of cards.*/
void initializeDeck(struct card *deck) {

    const char *faces[] = {"Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};
    const char *suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    int i;

    for (i = 0; i < NUM_0F_CARD; ++i) {
        deck[i].face = faces[i % 13];
        deck[i].suit = suits[i / 13];
    }
}

/* Shuffles the deck. */
void shuffleDeck(struct card *deck) {

    int i,j;
    srand(time(NULL));

    for ( i = 0; i < NUM_0F_CARD; ++i) {
         j = rand() % NUM_0F_CARD;
      
        struct card temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

/* Prints the shuffled deck.*/
void printDeck(struct card deck[]) {

    int i;
    for ( i = 0; i < NUM_0F_CARD; i+=2) {
        printf("%5s of %-8s ", deck[i].face, deck[i].suit);
        printf("%10s of %-1s\n", deck[i+1].face, deck[i+1].suit);
       
    }
}

int main(){

    struct card deck[NUM_0F_CARD];

    initializeDeck(deck);
    shuffleDeck(deck);
    printDeck(deck);

    return 0;
}
