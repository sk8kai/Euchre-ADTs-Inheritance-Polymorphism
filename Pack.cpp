//Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Pack.h"
#include "Card.h"
using namespace std;



Pack::Pack() {
    next = 0;
    int count = 0;
    for (int i = 0; i < NUM_SUITS; i++) {
        for (int j = 7; j < NUM_RANKS; j++) {
            Card input = Card(RANK_NAMES_BY_WEIGHT[j], SUIT_NAMES_BY_WEIGHT[i]);
            cards[count] = input;
            count++;
            
        }
    }

}

Pack::Pack(std::istream& pack_input) {
    next = 0;
    std::string rank;
    std::string of;
    std::string suit;
    
    for (int z = 0; z < PACK_SIZE; z++) {
        pack_input >> rank >> of >> suit;
        Card input = Card(rank, suit);
        cards[z] = input;
    }
}

Card Pack::deal_one() {
    Card correct;
    correct = cards[next];
    next++;
    return correct;

}

void Pack::reset() {
    next = 0;
}

void Pack::shuffle() {
    int halfPack = PACK_SIZE / 2;
    for(int x = 0; x < 7; x++) {
        std::array<Card, PACK_SIZE / 2> rightPack;
        std::array<Card, PACK_SIZE / 2> leftPack;
        
        for (int i = 0; i < halfPack; i++) {
            Card correct = cards[i];
            leftPack[i] = correct;
        }
        
        int loc = 0;
        for (int j = halfPack; j < PACK_SIZE; j++) {
            Card correct = cards[j];
            rightPack[loc] = correct;
            loc++;
        }
        
        int cardCount = 0;
        for(int z = 0; z < halfPack; z++) {
            cards[cardCount] = rightPack[z];
            cardCount++;
            cards[cardCount] = leftPack[z];
            cardCount++;
        }
    }
    next = 0;
}

bool Pack::empty() const {
    if (next >= PACK_SIZE) {
        return true;
    }
    else {
        return false;
    }
}
