#include "cards.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  card_t c;
  c.value = VALUE_ACE;
  c.suit = SPADES;
  assert_card_valid(c);

  for (int i = 0; i <= 8; i++) {
    hand_ranking_t deal = i;
    printf("%s\n", ranking_to_string(deal));
  }

  print_card(c);

  card_t new_card = card_from_letters('9','H');
  print_card(new_card);

  return EXIT_SUCCESS;
}
