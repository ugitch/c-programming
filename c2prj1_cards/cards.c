#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"


void assert_card_valid(card_t c) {
  assert(c.value >= 2 && c.value <= VALUE_ACE);
  assert(c.suit >= SPADES && c.suit <= CLUBS);
}

const char * ranking_to_string(hand_ranking_t r) {
  char * ranking = "";
  switch(r) {
  case STRAIGHT_FLUSH:
    ranking = "STRAIGHT_FLUSH";
    break;
  case FOUR_OF_A_KIND:
    ranking = "FOUR_OF_A_KIND";
    break;
  case FULL_HOUSE:
    ranking = "FULL_HOUSE";
    break;
  case FLUSH:
    ranking = "FLUSH";
    break;
  case STRAIGHT:
    ranking = "STRAIGHT";
    break;
  case THREE_OF_A_KIND:
    ranking = "THREE_OF_A_KIND";
    break;
  case TWO_PAIR:
    ranking = "TWO_PAIR";
    break;
  case PAIR:
    ranking = "PAIR";
    break;
  case NOTHING:
    ranking = "NOTHING";
    break;
  default:
    break;
  }   
  return ranking;
}

char value_letter(card_t c) {
  if (c.value == 10)
    return '0';
  else if (c.value >= 2 && c.value <= 9)
    return '0' + c.value;

  switch (c.value) {
  case VALUE_JACK: return 'J';
  case VALUE_QUEEN: return 'Q';
  case VALUE_KING: return 'K';
  case VALUE_ACE: return 'A';
  default: break;
  }
  return EXIT_FAILURE;
}


char suit_letter(card_t c) {
  switch(c.suit) {
  case SPADES: return 's';
  case HEARTS: return 'h';
  case DIAMONDS: return 'd';
  case CLUBS: return 'c';
  case 4: return 'x';
  default: break;
  }
  return 'x';
}

void print_card(card_t c) {
  printf("%c%c", value_letter(c), suit_letter(c));
}

card_t card_from_letters(char value_let, char suit_let) {
  card_t temp;

  if (value_let >= 50 && value_let <= 57)
    temp.value = value_let - 48;
  else if (value_let == 48)
    temp.value = 10;
  else {
    switch (value_let) {
    case 'J':
      temp.value = VALUE_JACK;
      break;
    case 'Q':
      temp.value = VALUE_QUEEN;
      break;
    case 'K':
      temp.value = VALUE_KING;
      break;
    case 'A':
      temp.value = VALUE_ACE;
      break;
    default:
      break;      
    }
  }

  switch (suit_let) {
  case 's':
    temp.suit = SPADES;
    break;
  case 'h':
    temp.suit = HEARTS;
    break;
  case 'd':
    temp.suit = DIAMONDS;
    break;
  case 'c':
    temp.suit = CLUBS;
    break;
  default:
    break;
  }

  assert_card_valid(temp);

  return temp;
}

card_t card_from_num(unsigned c) {
  unsigned value = c % 13 + 2;
  suit_t suit = c / 13;
  card_t temp;

  temp.suit = suit;
  temp.value = value;

  assert_card_valid(temp);
  
  return temp;
}
