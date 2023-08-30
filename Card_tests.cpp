// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}

TEST(test_is_face_or_ace) {
    Card j(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card q(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card k(Card::RANK_KING, Card::SUIT_SPADES);
    Card a(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card num(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card numTwo(Card::RANK_NINE, Card::SUIT_CLUBS);
    
    ASSERT_TRUE(j.is_face_or_ace());
    ASSERT_TRUE(q.is_face_or_ace());
    ASSERT_TRUE(k.is_face_or_ace());
    ASSERT_TRUE(a.is_face_or_ace());
    ASSERT_TRUE(!num.is_face_or_ace());
    ASSERT_TRUE(!numTwo.is_face_or_ace());
}

TEST(test_is_right_bower) {
    Card yes(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card noRank(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    Card noSuit(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card noAll(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    string trumpNow = Card::SUIT_CLUBS;
    
    ASSERT_TRUE(yes.is_right_bower(trumpNow));
    ASSERT_TRUE(!noRank.is_right_bower(trumpNow));
    ASSERT_TRUE(!noSuit.is_right_bower(trumpNow));
    ASSERT_TRUE(!noAll.is_right_bower(trumpNow));
}

TEST(test_is_left_bower) {
    Card yesOne(Card::RANK_JACK, Card::SUIT_SPADES);
    Card noRank(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card noSuit(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card noAll(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    string trumpNow = Card::SUIT_CLUBS;
    
    ASSERT_TRUE(yesOne.is_left_bower(trumpNow));
    ASSERT_TRUE(!noRank.is_left_bower(trumpNow));
    ASSERT_TRUE(!noSuit.is_left_bower(trumpNow));
    ASSERT_TRUE(!noAll.is_left_bower(trumpNow));
    
    trumpNow = Card::SUIT_DIAMONDS;
    
    ASSERT_TRUE(noSuit.is_left_bower(trumpNow));
    
    Card rightBower(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    
    ASSERT_TRUE(!rightBower.is_left_bower(trumpNow));
}

TEST(test_is_trump) {
    Card yesOne(Card::RANK_JACK, Card::SUIT_SPADES);
    Card lowRankOne(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card lowRankTwo(Card::RANK_NINE, Card::SUIT_SPADES);
    Card noSuitOne(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card noSuitTwo(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card noSuitThree(Card::RANK_FIVE, Card::SUIT_CLUBS);
    Card lowerBower(Card::RANK_JACK, Card::SUIT_CLUBS);
    
    string trumpNow = Card::SUIT_SPADES;
    
    ASSERT_TRUE(yesOne.is_trump(trumpNow));
    ASSERT_TRUE(lowRankOne.is_trump(trumpNow));
    ASSERT_TRUE(lowRankTwo.is_trump(trumpNow));
    ASSERT_TRUE(!noSuitOne.is_trump(trumpNow));
    ASSERT_TRUE(!noSuitTwo.is_trump(trumpNow));
    ASSERT_TRUE(!noSuitThree.is_trump(trumpNow));
    ASSERT_TRUE(lowerBower.is_trump(trumpNow));
}

TEST(test_less_than) {
    Card One(Card::RANK_JACK, Card::SUIT_SPADES);
    Card Two(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card Low(Card::RANK_THREE, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(operator<(One, Two));
    ASSERT_TRUE(!operator<(Two, One));
    ASSERT_TRUE(!operator<(Two, Two));
    ASSERT_TRUE(operator<(Low, Two));
    ASSERT_TRUE(!operator<(One, Low));
    
    ASSERT_TRUE(!operator<(One, One));
}

TEST(test_less_than_or_equal) {
    Card One(Card::RANK_JACK, Card::SUIT_SPADES);
    Card Two(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card Low(Card::RANK_THREE, Card::SUIT_DIAMONDS);
    Card OneCopy(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_TRUE(operator<(One, Two));
    ASSERT_TRUE(!operator<(Two, One));
    ASSERT_TRUE(!operator<(Two, Two));
    ASSERT_TRUE(operator<(Low, Two));
    ASSERT_TRUE(!operator<(One, Low));
    
    //equal specific tests
    ASSERT_TRUE(operator<=(One, OneCopy));
    ASSERT_TRUE(operator<=(OneCopy, One));
    ASSERT_TRUE(operator<=(One, Two));
    ASSERT_TRUE(!operator<=(Two, One));
    ASSERT_TRUE(operator<=(Low, Two));
    ASSERT_TRUE(!operator<=(One, Low));
}

TEST(test_greater_than_or_equal) {
    Card One(Card::RANK_JACK, Card::SUIT_SPADES);
    Card Two(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card Low(Card::RANK_THREE, Card::SUIT_DIAMONDS);
    Card OneCopy(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_FALSE(operator>(One, Two));
    ASSERT_TRUE(operator>(Two, One));
    ASSERT_FALSE(operator>(Two, Two));
    ASSERT_FALSE(operator>(Low, Two));
    ASSERT_TRUE(operator>(One, Low));
    
    //equal specific tests
    ASSERT_TRUE(operator>=(One, OneCopy));
    ASSERT_TRUE(operator>=(OneCopy, One));
    ASSERT_FALSE(operator>=(One, Two));
    ASSERT_TRUE(operator>=(Two, One));
    ASSERT_FALSE(operator>=(Low, Two));
    ASSERT_TRUE(operator>=(One, Low));

}

TEST(test_greater_or_equal_to) {
    //INSERT TEST CASE HERE
}

TEST(test_same_card) {
    Card One(Card::RANK_NINE, Card::SUIT_SPADES);
    Card Two(Card::RANK_NINE, Card::SUIT_SPADES);
    ASSERT_TRUE(operator==(One, Two));
    
    Card offSuit(Card::RANK_NINE, Card::SUIT_HEARTS);
    ASSERT_TRUE(!operator==(One, offSuit));
    
    Card offNum(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_TRUE(!operator==(One, offNum));
    
    
}

TEST(test_diff_card) {
    Card One(Card::RANK_NINE, Card::SUIT_SPADES);
    Card Two(Card::RANK_NINE, Card::SUIT_SPADES);
    ASSERT_TRUE(!operator!=(One, Two));
    
    Card offSuit(Card::RANK_NINE, Card::SUIT_HEARTS);
    ASSERT_TRUE(operator!=(One, offSuit));
    
    Card offNum(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_TRUE(operator!=(One, offNum));
}

TEST(test_suit_next) {
    string suitNow = Card::SUIT_SPADES;
    ASSERT_TRUE(Suit_next(suitNow) == Card::SUIT_CLUBS);
    
    suitNow = Card::SUIT_CLUBS;
    ASSERT_TRUE(Suit_next(suitNow) == Card::SUIT_SPADES);
    
    suitNow = Card::SUIT_HEARTS;
    ASSERT_TRUE(Suit_next(suitNow) == Card::SUIT_DIAMONDS);
    
    suitNow = Card::SUIT_DIAMONDS;

    ASSERT_TRUE(Suit_next(suitNow) == Card::SUIT_HEARTS);

}

TEST(Card_less_test) {
    const string trump = Card::SUIT_HEARTS;
    Card a(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card b(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_TRUE(Card_less(a, b, trump) == false);

    
    const string trump2 = Card::SUIT_DIAMONDS;
    Card a2(Card::RANK_TWO, Card::SUIT_DIAMONDS);
    Card b2(Card::RANK_SIX, Card::SUIT_HEARTS);
    ASSERT_TRUE(Card_less(a2, b2, trump2) == false);
    
    const string trump3 = Card::SUIT_SPADES;
    Card a3(Card::RANK_TWO, Card::SUIT_DIAMONDS);
    Card b3(Card::RANK_SIX, Card::SUIT_SPADES);
    ASSERT_TRUE(Card_less(a3, b3, trump3) == true);
}

TEST(Card_less_leadSuit_test) {
    string trump1 = Card::SUIT_CLUBS;
    const Card leadCard1(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card a1(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card b1(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_TRUE(Card_less(a1, b1, leadCard1, trump1) == true);
    
    string trump2 = Card::SUIT_CLUBS;
    const Card leadCard2(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card a2(Card::RANK_TWO, Card::SUIT_DIAMONDS);
    Card b2(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_TRUE(Card_less(a2, b2, leadCard2, trump2) == false);
    
    string trump3 = Card::SUIT_CLUBS;
    const Card leadCard3(Card::RANK_NINE, Card::SUIT_CLUBS);
    Card a3(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card b3(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_TRUE(Card_less(a3, b3, leadCard3, trump3) == true);
        
}

TEST(test_card_suit_and_rank) {
    Card two_spades = Card();
    ASSERT_EQUAL(two_spades.get_rank(), Card::RANK_TWO);
    ASSERT_EQUAL(two_spades.get_suit(), Card::SUIT_SPADES);

    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    ASSERT_EQUAL(three_spades.get_rank(), Card::RANK_THREE);
    ASSERT_EQUAL(three_spades.get_suit(), Card::SUIT_SPADES);
    ASSERT_EQUAL(three_spades.get_suit(Card::SUIT_CLUBS), Card::SUIT_SPADES);
}

TEST(test_card_type) {
    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    ASSERT_FALSE(three_spades.is_face_or_ace());
    ASSERT_FALSE(three_spades.is_right_bower(Card::SUIT_CLUBS));
    ASSERT_FALSE(three_spades.is_left_bower(Card::SUIT_CLUBS));
    ASSERT_FALSE(three_spades.is_trump(Card::SUIT_CLUBS));
}

TEST(test_card_self_comparison) {
    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    ASSERT_FALSE(three_spades < three_spades);
    ASSERT_TRUE(three_spades <= three_spades);
    ASSERT_FALSE(three_spades > three_spades);
    ASSERT_TRUE(three_spades >= three_spades);
    ASSERT_TRUE(three_spades == three_spades);
    ASSERT_FALSE(three_spades != three_spades);
}

TEST(test_Suit_next) {
    ASSERT_EQUAL(Suit_next(Card::SUIT_CLUBS), Card::SUIT_SPADES);
}

TEST(test_Card_less_self) {
    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    ASSERT_FALSE(Card_less(three_spades, three_spades, Card::SUIT_CLUBS));
    ASSERT_FALSE(Card_less(three_spades, three_spades, three_spades,
                           Card::SUIT_CLUBS));
}

TEST(test_card_insertion) {
    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    ostringstream oss;
    oss << three_spades;
    ASSERT_EQUAL(oss.str(), "Three of Spades");
}

TEST(test_card_less_than_same_card_diff_suit) {
    Card ten_spades = Card(Card::RANK_TEN, Card::SUIT_SPADES);
    Card ten_hearts = Card(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ten_clubs = Card(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card ten_diamonds = Card(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    string irrelevantTrump = Card::SUIT_DIAMONDS;

    ASSERT_TRUE(Card_less(ten_spades, ten_hearts, irrelevantTrump));
    ASSERT_TRUE(Card_less(ten_spades, ten_clubs, irrelevantTrump));
    ASSERT_TRUE(Card_less(ten_hearts, ten_clubs, irrelevantTrump));
    
    irrelevantTrump = Card::SUIT_HEARTS;
    
    ASSERT_TRUE(Card_less(ten_spades, ten_diamonds, irrelevantTrump));
    ASSERT_TRUE(Card_less(ten_clubs, ten_diamonds, irrelevantTrump));
    ASSERT_TRUE(Card_less(ten_spades, ten_clubs, irrelevantTrump));
    
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card jack_hearts = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    
    string relevantTrump = Card::SUIT_DIAMONDS;
    
    ASSERT_TRUE(Card_less(jack_spades, jack_hearts, relevantTrump));
    ASSERT_TRUE(Card_less(jack_hearts, jack_diamonds, relevantTrump));
    ASSERT_TRUE(Card_less(jack_spades, jack_clubs, relevantTrump));
    ASSERT_FALSE(Card_less(jack_diamonds, jack_hearts, relevantTrump));
}

TEST(test_operators) {
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card jack_hearts = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    
    ASSERT_TRUE(operator<(jack_spades, jack_hearts));
    ASSERT_TRUE(operator<(jack_spades, jack_clubs));
    ASSERT_TRUE(operator<(jack_hearts, jack_diamonds));
    ASSERT_FALSE(operator<(jack_diamonds, jack_hearts));
    
    ASSERT_TRUE(operator>(jack_diamonds, jack_hearts));
    ASSERT_TRUE(operator>(jack_clubs, jack_hearts));
    ASSERT_TRUE(operator>(jack_hearts, jack_spades));
    ASSERT_FALSE(operator>(jack_diamonds, jack_diamonds));
    
    ASSERT_TRUE(operator>=(jack_spades, jack_spades));
    ASSERT_TRUE(operator>=(jack_diamonds, jack_diamonds));
    ASSERT_FALSE(operator>=(jack_hearts, jack_diamonds));
}


// Add more test cases here

TEST_MAIN()
