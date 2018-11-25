#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
void print_hand(deck_t * hand){
  for (int i = 0; i < hand->n_cards; i++) {
    print_card(*hand->cards[i]);
    printf(" ");
  }
}

int deck_contains(deck_t * d, card_t c) {
  card_t * curr = NULL;
  for (int i = 0; i < d->n_cards; i++) {
    curr = d->cards[i];
    if (c.value == curr->value && c.suit == curr->suit)
      return 1;
  }
  return 0;
}

void shuffle(deck_t * d){
  card_t * swap = NULL;
  int random = 0;
  int cards = d->n_cards;
  for (int i = 0; i < cards; i++) {
    random = rand() % cards;
    swap = d->cards[i];
    d->cards[i] = d->cards[random];
    d->cards[random] = swap;
  }
}

void assert_full_deck(deck_t * d) {
  for (int i = 0; i < d->n_cards; i++)
    assert(deck_contains(d, card_from_num(i)));
}
