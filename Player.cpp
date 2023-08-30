//Project UID 1d9f47bfc76643019cfbf037641defe1
#include <cassert>
#include <iostream>
#include <string>
#include "Player.h"
#include <vector>
#include <algorithm>
using namespace std;



class SimplePlayer : public Player {
private:
    std::vector<Card> hand;
    std::string name;
    
    void rightLeftSuit(const Card& upcard, int &upSuitCount, string upSuit) const {
        const Card contrastCard = Card("Ten", upcard.get_suit());
        for (int i = 0; i < hand.size(); i++) {
            if (hand[i].is_right_bower(upSuit) == true) {
                upSuitCount++;
            }
            else if (hand[i].is_left_bower(upSuit) == true) {
                upSuitCount++;
            }
            else if (hand[i].get_suit() == upSuit) {
                if (operator>(hand[i], contrastCard)) {  //this is just
                                                        //counting
                    upSuitCount++;                      //face cards
                
                }
            }
        }
    }
    
public:
    SimplePlayer(string playerName) : name(playerName) {
    }
    
    virtual const std::string & get_name() const override {
        return name;
    }
    
    virtual void add_card(const Card &c) override {
        if (hand.size() < MAX_HAND_SIZE) {
            hand.push_back(c);
        }
    }
    
    virtual bool make_trump(const Card &upcard, bool is_dealer,
                        int round, std::string &order_up_suit)const override{
        //i should use card less
        int upSuitCount = 0;
        string upSuit = upcard.get_suit();
        if (round == 1) {
            
            rightLeftSuit(upcard, upSuitCount, upSuit);
            //literally just copy paste the code from this function if error
            
            //above is set up counting, below is execution
            if (upSuitCount >= 2) {
                order_up_suit = upcard.get_suit();
                return true;
            }
            else {
                //passing turn
                return false;
            }
        }
        
        else if (round == 2) {
            if (is_dealer == true) {
                //screw the dealer
                
                order_up_suit = Suit_next(upcard.get_suit());
                return true;
            }
            else {
            string possTrump = Suit_next(upcard.get_suit());
            rightLeftSuit(upcard, upSuitCount, possTrump);
                //literally just copy paste the code from this function if error
                
                //above is set up counting, below is execution
                if (upSuitCount >= 1) {
                    order_up_suit = possTrump;
                    return true;
                }
                else {
                    //passing turn
                    return false;
                }
            }
        }
        assert(false);
    }
    virtual void add_and_discard(const Card &upcard) override {
      
            int lowestIndex = 0;
            for (int i = 1; i < hand.size(); i++) {
                Card currentLow = hand[lowestIndex];
                Card next = hand[i];
                if (Card_less(currentLow, next, upcard.get_suit())) {
                    //do nothing
                }
                else {
                    lowestIndex = i;
                }
            }
        
        if (Card_less(upcard, hand[lowestIndex], upcard.get_suit())) {
            //just doesn't add upcard
        }
        else {
            hand.erase(hand.begin() + lowestIndex);
            hand.push_back(upcard);
        }
       
       // sort(hand.begin(), hand.end());
        
    }
    
    virtual Card lead_card(const std::string &trump) override {
        bool onlyTrump = false;
        int matchedSuit = 0;
        for (int i = 0; i < hand.size(); i++) {
            if (hand[i].get_suit() == trump || hand[i].is_left_bower(trump)) {
                matchedSuit++;
            }
        }
        
        if (matchedSuit == hand.size()) {
            onlyTrump = true;
        }
        
        //above code determines if a players hand entirely matched trump suit
        //sort(hand.begin(), hand.end());
        
        if (onlyTrump == true) {
            Card high = hand[0];
            int lowestIndex = 0;
            for (int i = 1; i < hand.size(); i++) {
                if (Card_less(high, hand[i], trump)) {  //plays highest trump
                    high = hand[i];
                    lowestIndex = i;
                }
            }
            hand.erase(hand.begin() + lowestIndex);
            return high;
        }
        
        
            int j = 0;
            while(hand[j].get_suit() == trump || hand[j].is_left_bower(trump)) {
                j++;
            }
            
            //if (hand[j].is_left_bower(trump)) {
              //  j++;
            //}
            Card firstNoT = hand[j];
            int Index = j;
            for (int i = 0; i < hand.size(); i++) {
                if (hand[i].get_suit() != trump && !hand[i].is_left_bower(trump)) {
                    if (operator>(hand[i], firstNoT)) {
                        firstNoT = hand[i];
                        Index = i;
                    }
                }
            }
            Card high = hand[Index];
            hand.erase(hand.begin() + Index);
            return high;
            
            /*
            while(hand[j].get_suit() == trump) {
                j++;
            }
            
            Card highNoT = hand[j];
            int lowestIndex = j;
            
            for (int i = j; i < hand.size(); i++) {
                if (hand[i].get_suit() != trump) {
                    if (operator>(hand[i], highNoT)) { //play highest non
             trump card
                        highNoT = hand[i];
                        lowestIndex = i;
                    }
                }
            }
            hand.erase(hand.begin() + lowestIndex);
            return highNoT;
        }
        assert(false);
             */
        
    }
    bool follow(const Card &led_card, const std::string &trump) {
        bool canFollow = false;
        
        for (int i = 0; i < hand.size(); i++) {
            
            if (led_card.is_left_bower(trump)) {
                if (hand[i].get_suit() == trump) {
                    canFollow =  true;  //did this to fix euchretest01
                }               ///is this ok now?
            }
            else if (hand[i].is_left_bower(trump)) {
                if (led_card.get_suit() == trump) {
                    canFollow = true;
                }
                // it it isnt trump, do nothing, this is why we split it up
            }
            else if (hand[i].get_suit() == led_card.get_suit()) {
                if (!hand[i].is_left_bower(trump)) {
                    canFollow = true;
                }
            }
        }
        return canFollow;
    }
    
    int jHelper(const Card &led_card, const std::string &trump) {
        int j = 0;
        if (led_card.is_left_bower(trump)) {
            while(hand[j].get_suit() != trump && j < hand.size()) {
                j++;
            }
        }
        else if (hand[j].is_left_bower(trump)) {
            if (led_card.is_trump(trump)) {
                j = 0;
            }
            else if (hand[j].get_suit() == led_card.get_suit()){
                j++;
            
                while(hand[j].get_suit() != led_card.get_suit()) {
                    j++;
                }
            }
            else {
                while(hand[j].get_suit() != led_card.get_suit()) {
                    j++;
                }
            }
            
        }
        else {
            while(hand[j].get_suit() != led_card.get_suit()) {
                j++;
            }
        }
        return j;
    }
    
    
    virtual Card play_card(const Card &led_card, const std::string &trump)
    override {
        bool canFollow = follow(led_card, trump);
        if (canFollow != true) {
            Card lowest = hand[0];
            int lowestIndex = 0;
            for (int i = 1; i < hand.size(); i++) {
                if (Card_less(hand[i], lowest, trump)) {
                    lowest = hand[i];
                    lowestIndex = i;
                }
            }
            hand.erase(hand.begin() + lowestIndex);
            return lowest;
        }
        int j = jHelper(led_card, trump);
        if (j >= hand.size()) {
            Card lowest = hand[0];
            int lowestIndex = 0;
            for (int i = 1; i < hand.size(); i++) {
                if (Card_less(hand[i], lowest, trump)) {
                    lowest = hand[i];
                    lowestIndex = i;
                }
            }
            hand.erase(hand.begin() + lowestIndex);
            return lowest;
        }
        Card highLedSuit = hand[j];
        int highestIndex = j;
        for (int i = j; i < hand.size(); i++) {
            if (hand[i].get_suit() == led_card.get_suit() &&
                !hand[i].is_left_bower(trump)) {
                if (Card_less(highLedSuit, hand[i], led_card, trump)) {
                    highLedSuit = hand[i];
                    highestIndex = i;
                }
            }
            else if (led_card.is_left_bower(trump)) {
                if (Card_less(highLedSuit, hand[i], led_card, trump)) {
                    highLedSuit = hand[i];
                    highestIndex = i;
                }
            }
        }
        hand.erase(hand.begin() + highestIndex);
        return highLedSuit;
        assert(false);
    }
};





class HumanPlayer : public Player {
private:
    std::vector<Card> hand;
    std::string name;
    void printHuman() const {
        for (int i = 0; i < hand.size(); i++) {
            cout << "Human player " << name << "'s hand: [" << i << "] ";
            cout << hand[i].get_rank() << " of " << hand[i].get_suit() << endl;
        }
    }
    
public:
    HumanPlayer(string playerName) : name(playerName) {
    }
    
    virtual const std::string & get_name() const override {
        return name;
    }
    
    virtual void add_card(const Card &c) override {
        if (hand.size() < MAX_HAND_SIZE) {
            hand.push_back(c);

            sort(hand.begin(), hand.end());
        }
    }
    virtual bool make_trump(const Card &upcard, bool is_dealer,
                            int round, std::string &order_up_suit)
    const override {
        
        printHuman();
        cout << "Human player " << name << ", please enter a suit, or \"pass\":"
        << endl;
        string input;
        cin >> input;
        
        //if pass, return false
        if (input == "hearts" ||input == "Hearts") {
            order_up_suit = Card::SUIT_HEARTS;
        }
        if (input == "spades" ||input == "Spades") {
            order_up_suit = Card::SUIT_SPADES;
        }
        if (input == "clubs" || input == "Clubs") {
            order_up_suit = Card::SUIT_CLUBS;
        }
        if (input == "diamonds" || input == "Diamonds") {
            order_up_suit = Card::SUIT_DIAMONDS;
        }
        
        if (input == "pass") {
            //cout << name << " passes" << endl << endl;
            return false;
        }
         
        //else if valid suit, run the static case to recognize suit and
        //spit output
        else if (input == "Hearts" || input == "Spades" || input == "Diamonds"
                 || input == "Clubs" || input == "hearts" || input == "spades"
                 || input == "diamonds" || input == "clubs") {

                        // cout << name << " orders up " << input << endl <<
           // endl;

                         //cout << name << " orders up " << input << endl <<
            //endl;

                         return true;
                     }
        

            else {
                //should this return false?
                //placeholder return statement
                cout << "ERROR: INVALID COMMAND" << endl;
                assert(false);
                return false;
            }
      
        
        //original
        /*
        printHuman();
                cout << "Human player " << name << ", please enter a suit,
         or \"pass\":" << endl;
                string input;
                cin >> input;
                if (input == "pass") {
                    cout << name << " passes" << endl << endl;
                    return false;
                }
                
                char first = input[0];
                int real = static_cast<int>(first - '0');
                
                if (real >= 0 && real < hand.size()) {
                    for (int i = 0; i < hand.size(); i++) {
                        if(real == i) {
                            order_up_suit = hand[i].get_suit();
                            cout << name << " orders up " << order_up_suit
         << endl << endl;
                            return true;
                        }
                    }
                }
                cout << "ERROR: INVALID COMMAND" << endl;
                assert(false);
        */
        
        //second
        /*
        printHuman();
        cout << "Human player " << name << ", please enter a suit, or \"pass\
         ":" << endl;
        string input;
        cin >> input;
        
        //if pass, return false
        if (input == "pass") {
            cout << name << " passes" << endl << endl;
            return false;
        }
        //else if valid suit, run the static case to recognize suit and
        //spit output
        char first = input[0];
        int real = static_cast<int>(first - '0');
        if (real >= 0 && real < hand.size()) {
            for (int i = 0; i < hand.size(); i++) {
                if (real == i) {
                    order_up_suit = hand[i].get_suit();
                    cout << name << " orders up " << order_up_suit << endl <<
         endl;
                    return true;
                }
            }
            cout << "ERROR INVALID INPUT" << endl << endl << endl;
            return false;
        }
        
        cout << "ERROR INVALID INPUT" << endl << endl << endl;
        return false;

        
            //char first = input[0];
            //int real = static_cast<int>(first - '0');
            if (real >= 0 && real < hand.size()) {
                 for (int i = 0; i < hand.size(); i++) {
                     if (real == i) {
                         order_up_suit = hand[i].get_suit();
                         cout << name << " orders up " << order_up_suit <<
         endl << endl;
                         return true;
                     }
                 }
                //been trying to figure out this error. why is it saying
                //expected expression, and when i take it out it says not
                //an output for every path. kms
                if (!(real >= 0) && !(real < hand.size())) {
                    return false;
                }
             }
            else {
                //should this return false?
                //placeholder return statement
                cout << "ERROR: INVALID COMMAND" << endl;
                assert(false);
                return false;
            }
        }
        else {
            cout << "ERROR: INVALID COMMAND" << endl;
            assert(false);
            return false;
        }
<<<<<<< HEAD
         */
    

       /*  if (input != "Hearts" || input != "Spades" || input != "Diamonds" ||
        input != "Clubs" || input != "hearts" || input != "spades" || input !=
        "diamonds" || input != "clubs" ) { */
        //cout << "ERROR: INVALID COMMAND" << endl;
       // assert(false);
    }
    
    virtual void add_and_discard(const Card &upcard) override {
        //sort(hand.begin(), hand.end());
        printHuman();
        cout << "Discard upcard: [-1]" << endl;
        cout << "Human player " << name << ", please select a card to discard:"
        << endl;
        int input;
        cin >> input;
        if (input == -1) {
            //remove/don't add upcard
        }
        else {
            for (int i = 0; i < hand.size(); i++) {
                if (input == i) {
                    hand.erase(hand.begin() + i);
                    //don't need to say what card was discarded
                   // cout << "Discarded card " << i << endl;   //UNDO
                }
            }
            hand.push_back(upcard);
        }
        //sorts human hand again after adding/discarding for human player
        sort(hand.begin(), hand.end());
    }
    
    virtual Card lead_card(const std::string &trump) override {
        //sort(hand.begin(), hand.end());
        int input;
        if (inputHelp(input)) {
            return playAndErase(input);
        }
        else {
            cout << "ERROR: INVALID INPUT" << endl;
            assert(false);
        }
        
    }
    
    bool inputHelp(int &choice) {
        printHuman();
        cout << "Human player " << name << ", please select a card:" << endl;
        int input;
        bool validInput = false;
        cin >> input;
        for (int i = 0; i < hand.size(); i++) {
            if (input == i) {
                validInput = true;
                choice = i;
            }
        }
        return validInput;
    }
    
    Card playAndErase(int input) {
        Card copy = hand[input];
        hand.erase(hand.begin() + input);
        return copy;
    }
    
    virtual Card play_card(const Card &led_card, const std::string &trump)
    override {
        //sort(hand.begin(), hand.end());
        /*
        printHuman();
        cout << "Human player " << name << ", please select a card:" << endl;
        int input;
        bool validInput = false;
        cin >> input;
        for (int i = 0; i < hand.size(); i++) {
            if (input == i) {
                validInput = true;
            }
        }
         */
    
        int input;
        if (inputHelp(input)) {
            //if (follow)
            return playAndErase(input);
            /*
            Card copy = hand[input];
            
            hand.erase(hand.begin() + input);
            return copy;
             */
        }
        else {
            cout << "ERROR: INVALID INPUT" << endl;
            assert(false);
        }
    }
};


//Player_factory("NotRobot", "Human");

//class Human : public Player {
    
//};


//Player * Player_factory(const std::string &name, const std::string &strategy);
Player * Player_factory(const std::string &name,
                        const std::string &strategy) {
  // We need to check the value of strategy and return
  // the corresponding player type.
    if (strategy == "Simple") {
    // The "new" keyword dynamically allocates an object.
    //return new SimplePlayer(name);
        return new SimplePlayer(name);
  }
  // Repeat for each other type of Player
    if (strategy == "Human") {
        return new HumanPlayer(name);

    }
  // Invalid strategy if we get here
  assert(false);
  return nullptr;
    
}

std::ostream & operator<<(std::ostream &os, const Player &p) {
    string printName = p.get_name();
    os << p.get_name();
    return os;
}


