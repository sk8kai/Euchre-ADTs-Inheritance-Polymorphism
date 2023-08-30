// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"
using namespace std;
// add any necessary #include or using directives here

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

// add your code below
Card::Card() {
    rank = RANK_TWO;
    suit = SUIT_SPADES;
}

std::string Card::get_rank() const {
    return rank;
}

Card::Card(const std::string &rank_in, const std::string &suit_in) {
    rank = rank_in;
    suit = suit_in;
}

std::string Card::get_suit() const {
    return suit;
}

std::string Card::get_suit(const std::string &trump) const {
    //had a const here, had to remove
    if (is_left_bower(trump)) {
        return trump;
    }
    else {
        return get_suit();
    }
}

bool Card::is_face_or_ace() const {
    if (rank == RANK_JACK || rank == RANK_QUEEN || rank == RANK_KING
        || rank == RANK_ACE) {
        return true;
    }
    else {
        return false;
    }
}

bool Card::is_right_bower(const std::string &trump) const {
    if (get_suit() == trump) {
        if (get_rank() ==  RANK_JACK) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}


bool Card::is_left_bower(const std::string &trump) const {
    if (get_suit() == Suit_next(trump)) {
        if (get_rank() == Card::RANK_JACK) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
    /*
    string nextTrump = "";
    if (trump == SUIT_SPADES) {
<<<<<<< HEAD
=======
        return is_left_helper(SUIT_SPADES);
        
>>>>>>> e79418d79f377732b7965097c82bced0bca096ef
        nextTrump =  SUIT_CLUBS;
        if (get_suit() == nextTrump) {
            return (get_rank() == RANK_JACK);
        }
        else {
            return false;
        }
<<<<<<< HEAD
=======
         
>>>>>>> e79418d79f377732b7965097c82bced0bca096ef
    }
    else if (trump == SUIT_HEARTS) {
        nextTrump = SUIT_DIAMONDS;
        if (get_suit() == nextTrump) {
            return (get_rank() == RANK_JACK);
        }
        else {
            return false;
        }
    }
    else if (trump == SUIT_CLUBS) {
        nextTrump = SUIT_SPADES;
        if (get_suit() == nextTrump) {
            return (get_rank() == RANK_JACK);
        }
        else {
            return false;
        }
    }
    else if (trump == SUIT_DIAMONDS) {
        nextTrump = SUIT_HEARTS;
        if (get_suit() == nextTrump) {
            return (get_rank() == RANK_JACK);
        }
        else {
            return false;
        }
    }
    else {
        //cout << trump << endl; 
        assert(false);
        return false;
    }
    
    
    
    if (get_rank() == RANK_JACK) {
        return true;
    }
    else {
        return false;
    }
     */
    // had this instead of the return (get_rank() == RANK_JACK) at each line
}

bool Card::is_trump(const std::string &trump) const {
    if (get_suit() == trump) {
        return true;
    }
    else {
        if (is_left_bower(trump)) {
            return true;
        }
        else {
            return false;
        }
    }
    
    
    /*
    if (get_suit() == trump) {
        return true;
    }
    else if (get_suit() == SUIT_SPADES && get_rank() == RANK_JACK) {
        return true;
    }
    else if (get_suit() == SUIT_CLUBS && get_rank() == RANK_JACK) {
        return true;
    }
    else if (get_suit() == SUIT_HEARTS && get_rank() == RANK_JACK) {
        return true;
    }
    else if (get_suit() == SUIT_DIAMONDS && get_rank() == RANK_JACK) {
        return true;
    }
    else {
        return false;
    }
    */
    
}

bool operator<(const Card &lhs, const Card &rhs) {
    int lhsValue = 0;
    int rhsValue = 0;
    for (int i  = 0; i < NUM_RANKS; i++) {
        if (RANK_NAMES_BY_WEIGHT[i] == lhs.get_rank()) {
            lhsValue = i;
            if (RANK_NAMES_BY_WEIGHT[i] == rhs.get_rank()) {
                rhsValue = i;
            }
        }
        else if (RANK_NAMES_BY_WEIGHT[i] == rhs.get_rank()) {
            rhsValue = i;
        }
    }
    
    if (lhsValue < rhsValue) {
        return true;
    }
    else if (lhsValue == rhsValue) {
        int aSuitRank = -1;
        int bSuitRank = -1;
        for (int i = 0; i < NUM_SUITS; i++) {
            if (lhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
                aSuitRank = i;
            }
            if (rhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
                bSuitRank = i;
            }
        }
        if (aSuitRank == -1 || bSuitRank == -1) {
            //return NULL;
            assert(false);
            return false;
            // fix these return statements
        }
        else {
            if (aSuitRank < bSuitRank) {
                return true;
            }
            else {
                return false;
            }
            
        }
    }
    else {
        return false;
    }
}

//EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator<=(const Card &lhs, const Card &rhs) {
    if (operator<(lhs, rhs)) {
        return true;
    }
    else if (lhs.get_rank() == rhs.get_rank() && lhs.get_suit() == rhs.get_suit()) {
        return true;
    }
    else {
        return false;
    }
    /*
    int lhsValue = 0;
    int rhsValue = 0;
    for (int i  = 0; i < NUM_RANKS; i++) {
        if (RANK_NAMES_BY_WEIGHT[i] == lhs.get_rank()) {
            lhsValue = i;
            if (RANK_NAMES_BY_WEIGHT[i] == rhs.get_rank()) {
                rhsValue = i;
            }
        }
        else if (RANK_NAMES_BY_WEIGHT[i] == rhs.get_rank()) {
            rhsValue = i;
        }
    }
    
    if (lhsValue < rhsValue) {
        return true;
    }
    else if (lhsValue == rhsValue && lhs.get_suit() == rhs.get_suit()) {
        return true;
    }
    else if (lhsValue == rhsValue) {
        int aSuitRank = -1;
        int bSuitRank = -1;
        for (int i = 0; i < NUM_SUITS; i++) {
            if (lhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
                aSuitRank = i;
            }
            if (rhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
                bSuitRank = i;
            }
        }
        if (aSuitRank == -1 || bSuitRank == -1) {
            //return NULL;
            assert(false);
            return false;
        }
        else {
            if (aSuitRank < bSuitRank) {
                return true;
            }
            else {
                return false;
            }
            
        }
    }
    else {
        return false;
    }
     */
}

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card &lhs, const Card &rhs) {
    if (operator<(lhs, rhs)) {
        return false;
    }
    else if (lhs.get_rank() == rhs.get_rank() && lhs.get_suit() == rhs.get_suit()) {
        return false;
    }
    else {
        return true;
    }
    /*
    int lhsValue = 0;
    int rhsValue = 0;
    for (int i  = 0; i < NUM_RANKS; i++) {
        if (RANK_NAMES_BY_WEIGHT[i] == lhs.get_rank()) {
            lhsValue = i;
            if (RANK_NAMES_BY_WEIGHT[i] == rhs.get_rank()) {
                rhsValue = i;
            }
        }
        else if (RANK_NAMES_BY_WEIGHT[i] == rhs.get_rank()) {
            rhsValue = i;
        }
    }
    
    if (lhsValue > rhsValue) {
        return true;
    }
    else if (lhsValue == rhsValue) {
        int aSuitRank = -1;
        int bSuitRank = -1;
        for (int i = 0; i < NUM_SUITS; i++) {
            if (lhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
                aSuitRank = i;
            }
            if (rhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
                bSuitRank = i;
            }
        }
        if (aSuitRank == -1 || bSuitRank == -1) {
           // return NULL;
            assert(false);
            return false;
        }
        else {
            if (aSuitRank > bSuitRank) {
                return true;
            }
            else {
                return false;
            }
            
        }
    }
    else {
        return false;
    }
     */
}

//EFFECTS Returns true if lhs is higher value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator>=(const Card &lhs, const Card &rhs) {
    if (operator<(lhs, rhs)) {
        return false;
    }
    else if (lhs.get_rank() == rhs.get_rank() && lhs.get_suit() == rhs.get_suit()) {
        return true;
    }
    else {
        return true;
    }
    /*
    int lhsValue = 0;
    int rhsValue = 0;
    for (int i  = 0; i < NUM_RANKS; i++) {
        if (RANK_NAMES_BY_WEIGHT[i] == lhs.get_rank()) {
            lhsValue = i;
            if (RANK_NAMES_BY_WEIGHT[i] == rhs.get_rank()) {
                rhsValue = i;
            }
        }
        else if (RANK_NAMES_BY_WEIGHT[i] == rhs.get_rank()) {
            rhsValue = i;
        }
    }
    
    if (lhsValue > rhsValue) {
        return true;
    }
    else if (lhsValue == rhsValue && lhs.get_suit() == rhs.get_suit()) {
        return true;
    }
    else if (lhsValue == rhsValue) {
        int aSuitRank = -1;
        int bSuitRank = -1;
        for (int i = 0; i < NUM_SUITS; i++) {
            if (lhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
                aSuitRank = i;
            }
            if (rhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
                bSuitRank = i;
            }
        }
        if (aSuitRank == -1 || bSuitRank == -1) {
            //return NULL;
            assert(false);
            return false;
        }
        else {
            if (aSuitRank > bSuitRank) {
                return true;
            }
            else {
                return false;
            }
            
        }
    }
    else {
        return false;
    }
     */
}

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator == (const Card &lhs, const Card &rhs) {
    if (lhs.get_suit() == rhs.get_suit()) {
        if (lhs.get_rank() == rhs.get_rank()) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card &lhs, const Card &rhs) {
    /*
    if (lhs.get_suit() == rhs.get_suit()) {
        if (lhs.get_rank() == rhs.get_rank()) {
            return false;
        }
        else {
            return true;
        }
    }
    else {
        return true;
    }
     */
    if (operator==(lhs, rhs)) {
        return false;
    }
    else {
        return true;
    }
}

//REQUIRES suit is a valid suit
//EFFECTS returns the next suit, which is the suit of the same color
std::string Suit_next(const std::string &suit) {
    if (suit == Card::SUIT_CLUBS) {
        return Card::SUIT_SPADES;
    }
    else if (suit == Card::SUIT_SPADES) {
        return Card::SUIT_CLUBS;
    }
    else if (suit == Card::SUIT_HEARTS) {
        return Card::SUIT_DIAMONDS;
    }
    else if (suit == Card::SUIT_DIAMONDS) {
        return Card::SUIT_HEARTS;
    }
    else {
        assert(false);
        return "error";
    }
}

//EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream & operator<<(std::ostream &os, const Card &card) {
    os << card.get_rank() << " of " << card.get_suit();
    return os;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.

bool Card_less_helper(const Card &a, const Card &b, const std::string &trump) {
    if (a.is_right_bower(trump)) {
        return false;
    }
    else if (b.is_right_bower(trump)) {
        return true;
    }
    else if (a.is_left_bower(trump) && !b.is_right_bower(trump)) {
        return false;
    }
    else if (!a.is_right_bower(trump) && b.is_left_bower(trump)) {
        return true;
    }
    else if (a.is_face_or_ace() && !b.is_face_or_ace()) {
        return false;
    }
    else if (!a.is_face_or_ace() && b.is_face_or_ace()) {
        return true;
    }
    else if (a.is_face_or_ace() && b.is_face_or_ace()) {
        if (operator<(a, b)) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (!a.is_face_or_ace() && !b.is_face_or_ace()) {
       
        return operator<(a, b);
        //changed if statement to just returning operator value
        /*
        if (operator<(a, b)) {
            return true;
        }
        else {
            return false;
        }
        */
    }
    //not sure about these else statements yet
    else {
        return false;
    }
}

bool Card_less_helper2(const Card &a, const Card &b, const std::string &trump) {
    if (a.is_face_or_ace() && !b.is_face_or_ace()) {
        return false;
    }
    else if (!a.is_face_or_ace() && b.is_face_or_ace()) {
        return true;
    }
    else if (a.get_rank() == b.get_rank()) {
        int aSuitRank = -1;
        int bSuitRank = -1;
        for (int i = 0; i < NUM_SUITS; i++) {
            if (a.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
                aSuitRank = i;
            }
            if (b.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
                bSuitRank = i;
            }
        }
        if (aSuitRank == -1 || bSuitRank == -1) {
           // return NULL;
            assert(false);
            return false;
        }
        else {
            if (aSuitRank < bSuitRank) {
                return true;
            }
            else {
                return false;
            }
            
        }
    }
    else if (a.is_face_or_ace() && b.is_face_or_ace()) {
        if (operator<(a, b)) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (!a.is_face_or_ace() && !b.is_face_or_ace()) {
        if (operator<(a, b)) {
            return true;
        }
        /*
        else if (a.get_rank() == b.get_rank()) {
            int aSuitRank = -1;
            int bSuitRank = -1;
            for (int i = 0; i < NUM_SUITS; i++) {
                if (a.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
                    aSuitRank = i;
                }
                if (b.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
                    bSuitRank = i;
                }
            }
            
            
            if (aSuitRank == -1 || bSuitRank == -1) {
               // return NULL;
                assert(false);
                return false;
            }
            else {
                if (aSuitRank < bSuitRank) {
                    return true;
                }
                else {
                    return false;
                }
                
            }
        }
    */
        else {
            return false;
        }
    }
    assert(false);
    return false;
}



bool Card_less(const Card &a, const Card &b, const std::string &trump) {
    
    //if b is trump and a isn't
    if (!a.is_trump(trump) && b.is_trump(trump)) {
        return true;
    }
   
    //if a is trump and b isn't
    else if (a.is_trump(trump) && !b.is_trump(trump)) {
        return false;
    }
    
    //handles if both are trump
    else if (a.is_trump(trump) && b.is_trump(trump)) {
        //insert helper function below card_less_helper
        
        return Card_less_helper(a, b, trump);
        /*
        if (a.is_right_bower(trump)) {
            return false;
        }
        else if (b.is_right_bower(trump)) {
            return true;
        }
        else if (a.is_left_bower(trump) && !b.is_right_bower(trump)) {
            return false;
        }
        else if (!a.is_right_bower(trump) && b.is_left_bower(trump)) {
            return true;
        }
        else if (a.is_face_or_ace() && !b.is_face_or_ace()) {
            return false;
        }
        else if (!a.is_face_or_ace() && b.is_face_or_ace()) {
            return true;
        }
        else if (a.is_face_or_ace() && b.is_face_or_ace()) {
            if (operator<(a, b)) {
                return true;
            }
            else {
                return false;
            }
        }
        else if (!a.is_face_or_ace() && !b.is_face_or_ace()) {
           
            return operator<(a, b);
            //changed if statement to just returning operator value
            /^
            if (operator<(a, b)) {
                return true;
            }
            else {
                return false;
            }
            ^/
        }
        //not sure about these else statements yet
        else {
            return false;
        }
        */
    }
    //also not sure yet. how to handle both not trump. think this should work?
    else {
        return Card_less_helper2(a, b, trump);
       /*
        if (a.is_face_or_ace() && !b.is_face_or_ace()) {
            return false;
        }
        if (!a.is_face_or_ace() && b.is_face_or_ace()) {
            return true;
        }
        else if (a.is_face_or_ace() && b.is_face_or_ace()) {
            if (operator<(a, b)) {
                return true;
            }
            else if (a.get_rank() == b.get_rank()) {
                int aSuitRank = -1;
                int bSuitRank = -1;
                for (int i = 0; i < NUM_SUITS; i++) {
                    if (a.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
                        aSuitRank = i;
                    }
                    if (b.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
                        bSuitRank = i;
                    }
                }
                if (aSuitRank == -1 || bSuitRank == -1) {
                   // return NULL;
                    assert(false);
                    return false;
                }
                else {
                    if (aSuitRank < bSuitRank) {
                        return true;
                    }
                    else {
                        return false;
                    }
                    
                }
            }
            else {
                return false;
            }
        }
        else if (!a.is_face_or_ace() && !b.is_face_or_ace()) {
            if (operator<(a, b)) {
                return true;
            }
            /^
            else if (a.get_rank() == b.get_rank()) {
                int aSuitRank = -1;
                int bSuitRank = -1;
                for (int i = 0; i < NUM_SUITS; i++) {
                    if (a.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
                        aSuitRank = i;
                    }
                    if (b.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
                        bSuitRank = i;
                    }
                }
                
                
                if (aSuitRank == -1 || bSuitRank == -1) {
                   // return NULL;
                    assert(false);
                    return false;
                }
                else {
                    if (aSuitRank < bSuitRank) {
                        return true;
                    }
                    else {
                        return false;
                    }
                    
                }
            }
        ^/
            else {
                return false;
            }
        }
        assert(false);
        return false;
        */
    }
    
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card,
               const std::string &trump) {
    string leadSuit = led_card.get_suit();
    
    if (a.is_trump(trump) && !b.is_trump(trump)) {
        return Card_less(a, b, trump);
    }
    else if (!a.is_trump(trump) && b.is_trump(trump)) {
        return Card_less(a, b, trump);
    }
    else if (a.is_trump(trump) && b.is_trump(trump)) {
        return Card_less(a, b, trump);
    }
    else {
        if (a.get_suit() == leadSuit && b.get_suit() != leadSuit) {
            return false;
        }
        else if (a.get_suit() != leadSuit && b.get_suit() == leadSuit) {
            return true;
        }
        else if (a.get_suit() == leadSuit && b.get_suit() == leadSuit) {
            if ((a.is_right_bower(leadSuit) || a.is_left_bower(leadSuit)) &&
                (b.get_rank() == Card::RANK_ACE ||
                 b.get_rank() == Card::RANK_KING
                 || b.get_rank() == Card::RANK_QUEEN)) {
                return true;
            }
            else if ((b.is_right_bower(leadSuit) || b.is_left_bower(leadSuit))
                     && (a.get_rank() == Card::RANK_ACE
                         || a.get_rank() == Card::RANK_KING ||
                         a.get_rank() == Card::RANK_QUEEN)) {
                return false;
            }
            else {
               return Card_less(a, b, leadSuit);
            }
        }
        else {
            //should never happen
            return 1;
        }
    }
}

// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec before implementing
// the following operator overload functions:
//   operator<<
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=
