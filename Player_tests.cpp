// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

TEST(test_add_and_discard_same_suit) {
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

    Card newCard = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    bob->add_and_discard(newCard);
    //Trump Suit Would become Spades now, since he picked up a Spade
    Card correctLead = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_EQUAL(bob->lead_card(Card::SUIT_SPADES), correctLead);
    
    Card PlayOne = Card(Card::RANK_ACE, Card::SUIT_SPADES);
    
    string trumpSuit = Card::SUIT_SPADES;
    ASSERT_EQUAL(bob->play_card(correctLead, trumpSuit), PlayOne);
    
    Card PlayTwo = Card(Card::RANK_KING, Card::SUIT_SPADES);
    ASSERT_EQUAL(bob->play_card(correctLead, trumpSuit), PlayTwo);
    
    Card PlayThree = Card(Card::RANK_QUEEN, Card::SUIT_SPADES);
    ASSERT_EQUAL(bob->play_card(correctLead, trumpSuit), PlayThree);
    
    Card PlayFour = Card(Card::RANK_TEN, Card::SUIT_SPADES);
    ASSERT_EQUAL(bob->play_card(correctLead, trumpSuit), PlayFour);
    
    delete bob;
}

TEST(test_add_and_discard_diff_hand) {
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
    bob->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
    bob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    
    Card newCard = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    bob->add_and_discard(newCard);
    
    Card correctLead = Card(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(bob->lead_card(Card::SUIT_SPADES), correctLead);
    
    Card PlayOne = Card(Card::RANK_KING, Card::SUIT_HEARTS);
    
    string trumpSuit = Card::SUIT_SPADES;
    ASSERT_EQUAL(bob->play_card(correctLead, trumpSuit), PlayOne);
    
    Card PlayTwo = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    ASSERT_EQUAL(bob->play_card(correctLead, trumpSuit), PlayTwo);
    
    Card PlayThree = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_EQUAL(bob->play_card(correctLead, trumpSuit), PlayThree);
    
    Card PlayFour = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_EQUAL(bob->play_card(correctLead, trumpSuit), PlayFour);
    
    delete bob;
}

TEST(test_add_and_discard_no_trump) {
    //defaulted against a correct implementation
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
    bob->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
    bob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    
    Card newCard = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    bob->add_and_discard(newCard);   //should discard Jack of Clubs
    //would this cause error because it is tied between the jacks?
    //D > C > H > S
    
    Card correctLead = Card(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(bob->lead_card(Card::SUIT_DIAMONDS), correctLead);
    
    Card oneLead = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card PlayOne = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    
    string trumpSuit = Card::SUIT_DIAMONDS;
    ASSERT_EQUAL(bob->play_card(oneLead, trumpSuit), PlayOne);
    
    Card PlayTwo = Card(Card::RANK_JACK, Card::SUIT_CLUBS);   //just changed this
                        // used to return suit_spades
    ASSERT_EQUAL(bob->play_card(oneLead, trumpSuit), PlayTwo);
    
    
    
    
    Card PlayThree = Card(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    ASSERT_EQUAL(bob->play_card(oneLead, trumpSuit), PlayThree);
    
    Card PlayFour = Card(Card::RANK_KING, Card::SUIT_HEARTS);
    ASSERT_EQUAL(bob->play_card(oneLead, trumpSuit), PlayFour);
    
    delete bob;
}

TEST(test_trump_test_neg_one) {
    //defaulted against a correct implementation
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
    bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
    bob->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));
    bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    
    Card ten_spades(Card::RANK_TEN, Card::SUIT_SPADES);
    string trump = "";
    bool orderup = bob->make_trump(
      ten_spades,    // Upcard
      true,           // Bob is also the dealer
      1,              // First round
      trump           // Suit ordered up (if any)
    );

    // Verify Bob's order up and trump suit
    ASSERT_FALSE(orderup);
    ASSERT_EQUAL(trump, "");
    
    bool orderupTwo = bob->make_trump(  //scew the dealer round
      ten_spades,    // Upcard
      true,           // Bob is also the dealer
      2,              // 2nd round
      trump           // Suit ordered up (if any)
    );
    
    ASSERT_TRUE(orderupTwo);
    ASSERT_EQUAL(trump, Card::SUIT_CLUBS);    //POSSSIBLE ERROR
                        // SHOULD ORDER UP CLUBS ACCORDING TO OFFICE HOURS
    //round 1 upcard-- anyone orders up, upcard suit becomes trump
    //round 2-- the only suit being considered for trump is the next color
    
    bool orderupThree = bob->make_trump(
      ten_spades,    // Upcard
      false,           // Bob is also the dealer
      2,              // 2nd round
      trump           // Suit ordered up (if any)
    );
    
    ASSERT_TRUE(orderupThree);
    ASSERT_EQUAL(trump, Card::SUIT_CLUBS);

    delete bob;
}






//TESTS COPIED FROM PUBLIC TESTS

TEST(test_player_insertion) {
  // Create a Human player
  Player * human = Player_factory("NotRobot", "Human");


  // Print the player using the stream insertion operator
  ostringstream oss1;
    oss1 << * human;

  // Verify that the output is the player's name
  ASSERT_EQUAL(oss1.str(), "NotRobot");

  // Create a Simple player
  Player * alice = Player_factory("Alice", "Simple");

  // Print the player using the stream insertion operator
  ostringstream oss2;
  oss2 << *alice;
  ASSERT_EQUAL(oss2.str(), "Alice");

  // Clean up players that were created using Player_factory()
  delete human;
  delete alice;
}


TEST(test_simple_player_make_trump) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob makes tump
  Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
  string trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_SPADES);

  delete bob;
}

TEST(test_simple_player_lead_card) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(Card::RANK_NINE, Card::SUIT_HEARTS) // upcard
  );

  // Bob leads
  Card card_led = bob->lead_card(Card::SUIT_HEARTS);

  // Verify the card Bob selected to lead
  Card ace_spades(Card::RANK_ACE, Card::SUIT_SPADES);
  ASSERT_EQUAL(card_led, ace_spades); //check led card

  delete bob;
}

TEST(test_simple_player_play_card) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob plays a card
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    "Hearts"        // Trump suit
  );

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_NINE, Card::SUIT_SPADES));
  delete bob;
}

// Add more tests here

TEST_MAIN()
