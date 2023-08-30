// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Pack.h"
#include "unit_test_framework.h"
#include "Card.h"

#include <iostream>

using namespace std;

TEST(test_pack_default_ctor) {
    Pack pack;
    Card first = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_NINE, first.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, first.get_suit());
}

TEST(test_pack_reset) {
    Pack pack1;
    Card firstCard = pack1.deal_one();
    for (int i = 0; i < 22; i++) {
        firstCard = pack1.deal_one();
    }
    pack1.reset();
    firstCard = pack1.deal_one();
    ASSERT_EQUAL(Card::RANK_NINE, firstCard.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, firstCard.get_suit());
    
}



// Add more tests here

TEST_MAIN()
