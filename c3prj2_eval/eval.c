#include "eval.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int card_ptr_comp(const void * vp1, const void * vp2) {
  if (vp1 == NULL || vp2 == NULL)
    return EXIT_FAILURE;

  const card_t * const * card1 = vp1;
  const card_t * const * card2 = vp2;

  if ((*card1)->value != (*card2)->value)
    return (*card2)->value - (*card1)->value;
  else
    return (*card1)->suit - (*card2)->suit;
  return 0;
}

suit_t flush_suit(deck_t * hand) {
  for (suit_t suit = SPADES; suit <= CLUBS; suit++) {
    int suit_cards = 0;
    for (int i = 0; i < hand->n_cards; i++) {
      if (hand->cards[i]->suit == suit)
        suit_cards++;
      if (suit_cards == 5)
        return suit;
    }
  }
  return NUM_SUITS;
}

unsigned get_largest_element(unsigned * arr, size_t n) {
  unsigned largest = arr[0];
  for (int i = 1; i < n; i++) {
    if (arr[i] > largest)
      largest = arr[i];
  }
  return largest;
}

size_t get_match_index(unsigned * match_counts, size_t n, unsigned n_of_akind){
  for (int i = 0; i < n; i++) {
    if (match_counts[i] == n_of_akind)
      return i;
  }
  return 0;
}

ssize_t  find_secondary_pair(deck_t * hand,
			     unsigned * match_counts,
			     size_t match_idx) {
  
  for (int i = 0; i < hand->n_cards; i++) {
    if (match_counts[i] > 1 && hand->cards[i]->value != hand->cards[match_idx]->value)
      return i;
  }
  return -1;
}

// helper function for is_straight_at
int check_ace_low(deck_t * hand, size_t index, suit_t fs) {
  if (hand->cards[index]->value == VALUE_ACE &&
     (fs == NUM_SUITS || hand->cards[index]->suit == fs))
    return 1;
  return 0;
}

// helper function for is_straight_at
int is_n_length_straight_at(deck_t * hand, size_t index, suit_t fs, int n) {
  int straight_cards = 0;
  unsigned nextv = 5;
  for (int i = index + 1; i < hand->n_cards; i++) {
    if (hand->cards[i]->value == nextv && 
        (fs == NUM_SUITS || hand->cards[i]->suit == fs)) {
      straight_cards++;
      nextv--;
    }
    if (straight_cards == n)
      return 1;
  }
  return 0;
}

// helper function for is_straight_at (regular straight)
int is_reg_straight_at(deck_t * hand, size_t index, suit_t fs, int n) {
  int straight_cards = 1;
  int nextv = hand->cards[index]->value - 1;
  
  if (fs != NUM_SUITS && fs != hand->cards[index]->suit)
    return 0;

  for (int i = index + 1; i < hand->n_cards; i++) {
    if ((hand->cards[i]->value == nextv) && 
        (fs == NUM_SUITS || (hand->cards[i]->suit) == fs)) {
      straight_cards++;
      nextv--;
    }
    if (straight_cards == n)
      return 1;
  }
  return 0;
}

int is_straight_at(deck_t * hand, size_t index, suit_t fs) {
  // regular straight
  if (is_reg_straight_at(hand, index, fs, 5))
    return 1;  

  // ace low straight (flush)
  if (check_ace_low(hand, index, fs) && is_n_length_straight_at(hand, index, fs, 4))
    return -1;
  
  return 0;
}

hand_eval_t build_hand_from_match(deck_t * hand,
				  unsigned n,
				  hand_ranking_t what,
				  size_t idx) {

  hand_eval_t ans;
  ans.ranking = what;
  int index = 0;
  int more_cards = 5 - n;
  int n_of_a_kind = hand->cards[idx]->value;

  for (int i = idx; i < idx + n; i++, index++)
    ans.cards[index] = hand->cards[i];

  for (int i = 0; i < hand->n_cards; i++) {
    if (hand->cards[i]->value != n_of_a_kind) {
      ans.cards[index] = hand->cards[i];
      more_cards--;
      index++;
    }
    if (more_cards == 0)
      break;
  }
  return ans;
}


int compare_hands(deck_t * hand1, deck_t * hand2) {
  qsort(hand1->cards, hand1->n_cards, sizeof(card_t *), card_ptr_comp);
  qsort(hand2->cards, hand2->n_cards, sizeof(card_t *), card_ptr_comp);

  hand_eval_t hand_1 = evaluate_hand(hand1);
  hand_eval_t hand_2 = evaluate_hand(hand2);

  if (hand_1.ranking < hand_2.ranking)
    return 1;
  else if (hand_2.ranking < hand_1.ranking)
    return -1;

  for (int i = 0; i < 5; i++) {
    if (hand_1.cards[i]->value > hand_2.cards[i]->value)
      return 1;
    else if (hand_1.cards[i]->value < hand_2.cards[i]->value)
      return -1;
  }
  return 0;
}



//You will write this function in Course 4.
//For now, we leave a prototype (and provide our
//implementation in eval-c4.o) so that the
//other functions we have provided can make
//use of get_match_counts.
unsigned * get_match_counts(deck_t * hand) ;

// We provide the below functions.  You do NOT need to modify them
// In fact, you should not modify them!


//This function copies a straight starting at index "ind" from deck "from".
//This copies "count" cards (typically 5).
//into the card array "to"
//if "fs" is NUM_SUITS, then suits are ignored.
//if "fs" is any other value, a straight flush (of that suit) is copied.
void copy_straight(card_t ** to, deck_t *from, size_t ind, suit_t fs, size_t count) {
  assert(fs == NUM_SUITS || from->cards[ind]->suit == fs);
  unsigned nextv = from->cards[ind]->value;
  size_t to_ind = 0;
  while (count > 0) {
    assert(ind < from->n_cards);
    assert(nextv >= 2);
    assert(to_ind <5);
    if (from->cards[ind]->value == nextv &&
	(fs == NUM_SUITS || from->cards[ind]->suit == fs)){
      to[to_ind] = from->cards[ind];
      to_ind++;
      count--;
      nextv--;
    }
    ind++;
  }
}


//This looks for a straight (or straight flush if "fs" is not NUM_SUITS)               
// in "hand".  It calls the student's is_straight_at for each possible                 
// index to do the work of detecting the straight.                                     
// If one is found, copy_straight is used to copy the cards into                       
// "ans".                                                                              
int find_straight(deck_t * hand, suit_t fs, hand_eval_t * ans) {
  if (hand->n_cards < 5){
    return 0;
  }
  for(size_t i = 0; i <= hand->n_cards -5; i++) {
    int x = is_straight_at(hand, i, fs);
    if (x >0){
      copy_straight(ans->cards, hand, i, fs,5);
      return 1;
    }
  }
  //we have to check ace low straights LAST since                                      
  // Ac 6c 5c 4c 3c 2c will give the ace low otherwise                                 
  for(size_t i = 0; i <= hand->n_cards -5; i++) {
    int x = is_straight_at(hand, i, fs);
    if (x < 0) { //ace low straight                                                    
      assert(hand->cards[i]->value == VALUE_ACE &&
             (fs == NUM_SUITS || hand->cards[i]->suit == fs));
      ans->cards[4] = hand->cards[i];
      size_t cpind = i+1;
      while(hand->cards[cpind]->value != 5 ||
            !(fs==NUM_SUITS || hand->cards[cpind]->suit ==fs)){
        cpind++;
        assert(cpind < hand->n_cards);
      }
      copy_straight(ans->cards, hand, cpind, fs,4) ;
      return 1;
    }
  }
  return 0;
}


//This function puts all the hand evaluation logic together.
//This function is longer than we generally like to make functions,
//and is thus not so great for readability :(
hand_eval_t evaluate_hand(deck_t * hand) {
  suit_t fs = flush_suit(hand);
  hand_eval_t ans;
  if (fs != NUM_SUITS) {
    if(find_straight(hand, fs, &ans)) {
      ans.ranking = STRAIGHT_FLUSH;
      return ans;
    }
  }
  unsigned * match_counts = get_match_counts(hand);
  unsigned n_of_a_kind = get_largest_element(match_counts, hand->n_cards);
  assert(n_of_a_kind <= 4);
  size_t match_idx = get_match_index(match_counts, hand->n_cards, n_of_a_kind);
  ssize_t other_pair_idx = find_secondary_pair(hand, match_counts, match_idx);
  free(match_counts);
  if (n_of_a_kind == 4) { //4 of a kind
    return build_hand_from_match(hand, 4, FOUR_OF_A_KIND, match_idx);
  }
  else if (n_of_a_kind == 3 && other_pair_idx >= 0) {     //full house
    ans = build_hand_from_match(hand, 3, FULL_HOUSE, match_idx);
    ans.cards[3] = hand->cards[other_pair_idx];
    ans.cards[4] = hand->cards[other_pair_idx+1];
    return ans;
  }
  else if(fs != NUM_SUITS) { //flush
    ans.ranking = FLUSH;
    size_t copy_idx = 0;
    for(size_t i = 0; i < hand->n_cards;i++) {
      if (hand->cards[i]->suit == fs){
        ans.cards[copy_idx] = hand->cards[i];
        copy_idx++;
        if (copy_idx >=5){
          break;
        }
      }
    }
    return ans;
  }
  else if(find_straight(hand,NUM_SUITS, &ans)) {     //straight
    ans.ranking = STRAIGHT;
    return ans;
  }
  else if (n_of_a_kind == 3) { //3 of a kind
    return build_hand_from_match(hand, 3, THREE_OF_A_KIND, match_idx);
  }
  else if (other_pair_idx >=0) {     //two pair
    assert(n_of_a_kind ==2);
    ans = build_hand_from_match(hand, 2, TWO_PAIR, match_idx);
    ans.cards[2] = hand->cards[other_pair_idx];
    ans.cards[3] = hand->cards[other_pair_idx + 1];
    if (match_idx > 0) {
      ans.cards[4] = hand->cards[0];
    }
    else if (other_pair_idx > 2) {  //if match_idx is 0, first pair is in 01
      //if other_pair_idx > 2, then, e.g. A A K Q Q
      ans.cards[4] = hand->cards[2];
    }
    else {       //e.g., A A K K Q
      ans.cards[4] = hand->cards[4]; 
    }
    return ans;
  }
  else if (n_of_a_kind == 2) {
    return build_hand_from_match(hand, 2, PAIR, match_idx);
  }
  return build_hand_from_match(hand, 0, NOTHING, 0);
}
