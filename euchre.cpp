// Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Card.h"
#include "Player.h"
#include "Pack.h"
#include <cassert>
#include <fstream>
#include <vector>
#include <string>
using namespace std;



class Game {
public:
    static const int NUM_PLAYERS = 4;
    //Initializes a game, sets rounds, shuffles deck, generates players
    Game() {

    }
    
    //changed parameters
    Game(vector<Player*> playerVec, Pack in,
         string shuff, int points) {
        //load in players, pack and shuff
        onePoint = 0;
        twoPoint = 0;
       
       
        players.push_back(playerVec[0]);
        players.push_back(playerVec[1]);
        players.push_back(playerVec[2]);
        players.push_back(playerVec[3]);
        deck = in;
        if (shuff == "shuffle") {
            shuffGame = true;
        }
        else if (shuff == "noshuffle") {
            shuffGame = false;
        }
        pointToWin = points;
        dealerNum = 0;
        //set points/tricks to 0?
        //set teams?
    }
    
    void add_player(Player * input) {
        players.push_back(input);
    }
    
    void playGame() {
        int roundCount = 0;
        bool winner = false;
        while (winner == false) {
            playRound(roundCount);
            cout << players[0]->get_name() << " and " << players[2]->get_name();
            cout << " have " << onePoint << " points" << endl;
            cout << players[1]->get_name() << " and " << players[3]->get_name();
            cout << " have " << twoPoint << " points" << endl << endl;
            
            if (onePoint >= pointToWin) {
                cout << endl;
                cout << players[0]->get_name() << " and "
                << players[2]->get_name();
                cout << " win!" << endl;
                winner = true;
            }
            else if (twoPoint >= pointToWin) {
                cout << endl;
                cout << players[1]->get_name() << " and "
                << players[3]->get_name();
                cout << " win!" << endl;
                winner = true;
            }
            roundCount++;
            
            
            
        }
        players.clear();
        //needs more work
    }
    
    void announce(int t1TrickPoints, int t2TrickPoints) {
        if (t1TrickPoints > t2TrickPoints) {
            cout << players[0]->get_name() << " and " << players[2]->get_name();
            cout << " win the hand" << endl;
        }
        else if (t1TrickPoints < t2TrickPoints) {
            cout << players[1]->get_name() << " and " << players[3]->get_name();
            cout << " win the hand" << endl;
        }
    }
    
    void incrementDealer() {
        dealerNum++;
        if (dealerNum == NUM_PLAYERS) {
            dealerNum = 0;
        }
    }
    
    void pointsDeal(int t1TrickPoints, int t2TrickPoints, string whoPicked) {
        if (t1TrickPoints == 5 || t2TrickPoints == 5) {
            if (t1TrickPoints == 5 && whoPicked == "T2") {
                cout << "euchred!" << endl;
                onePoint = onePoint + 2;
            }
            else if (t2TrickPoints == 5 && whoPicked == "T1") {
                cout << "euchred!" << endl;
                twoPoint = twoPoint + 2;
            }
           
            else if (t1TrickPoints == 5) {
                cout << "march!" << endl;
                onePoint = onePoint + 2;
            }
            else if (t2TrickPoints == 5) {
                cout << "march!" << endl;
                twoPoint = twoPoint + 2;
            }
        }
        //euchered
        else if (t1TrickPoints < 3 && whoPicked == "T1") {
            cout << "euchred!" << endl;
            twoPoint = twoPoint + 2;
        }
        else if (t2TrickPoints < 3 && whoPicked == "T2") {
            cout << "euchred!" << endl;
            onePoint = onePoint + 2;
        }
        else if (t1TrickPoints > t2TrickPoints) {
            onePoint++;
        }
        else if (t1TrickPoints < t2TrickPoints) {
            twoPoint++;
        }
        else {
            assert(false);
        }
    }
    
    void playRound(int hand) {
        
        //special cases, euching, all 5 hands
        
        //shuffle within play round
        //deal cards
        
        //trump rounds
        
        //implement mechanics of picking up cards or passing between plauers
        if (shuffGame) {
            shuffle();
        }
        else {
            deck.reset();
        }
        int t1TrickPoints = 0;
        int t2TrickPoints = 0;
        cout << "Hand " << hand << endl;
        //cout << dealerNum << endl << endl << endl;
        deal(dealerNum);
        for (int i = 0; i < NUM_PLAYERS; i++) {
            if (i == dealerNum) {
                cout << players[i]->get_name() << " deals" << endl;
            }
        }
        
        cout << upCard.get_rank() << " of " << upCard.get_suit() <<
        " turned up" << endl;
        
        //cout << endl;
        
        string whoPicked;
        make_trump(dealerNum, whoPicked);
        if (whoPicked == "Error") {
            assert(false);
        }
        //5 tricks
        string pWinner = "";
        play_trick(orderUpSuit, t1TrickPoints, t2TrickPoints, pWinner);

        play_trick(orderUpSuit, t1TrickPoints, t2TrickPoints, pWinner);
     
        play_trick(orderUpSuit, t1TrickPoints, t2TrickPoints, pWinner);
  
        play_trick(orderUpSuit, t1TrickPoints, t2TrickPoints, pWinner);
        
        play_trick(orderUpSuit, t1TrickPoints, t2TrickPoints, pWinner);
        
        announce(t1TrickPoints, t2TrickPoints);
        
        pointsDeal(t1TrickPoints, t2TrickPoints, whoPicked);
        
        incrementDealer();
    }
    

    
    
    
    
    
    
    
private:
    Pack deck;
    vector<Player*> players;
    Card upCard;
    string dealer;
    
    //need to be initialized?
    int dealerNum;
    string orderUpSuit;
    
    int pointToWin;
    bool shuffGame;
    
    int onePoint;
    int twoPoint;
 
    void shuffle() {
        deck.shuffle();
    }
    
    void orderStore(int playNow, string &pick, bool &order) {
        cout << players[playNow]->get_name() << " orders up ";
        cout <<  orderUpSuit << endl << endl;
        
        if (playNow == 0 || playNow == 2) {
            pick = "T1";
        }
        else if (playNow == 1 || playNow == 3) {
            pick = "T2";
        }
        else {
            pick = "Error";
        }
        order = true;
    }
    
    void trumpRoundOne(int dealerIndex, string &pick, bool &order) {
        int round = 1;

        //while we cycle through and ordered up
        //while loop w two conditions
        //if statement

            int playNow =  dealerIndex + 1;
            
            while (playNow < NUM_PLAYERS && order == false) {
                //since it starts to left of dealer, dealer will never come up
                //in this while loop

                if (players[playNow]->make_trump(upCard, false, round, orderUpSuit)) {
                    orderStore(playNow, pick, order);
                    players[dealerIndex]->add_and_discard(upCard);
                    //orderStore(playNow, pick, order);

                }
                else {
                    cout << players[playNow]->get_name() << " passes" << endl;
                    //<< endl;
                }

                playNow++;
            }
            
            playNow = 0;
            while (playNow < dealerIndex + 1 && order == false) {
                //account for dealer and regular players
                if (playNow == dealerIndex) {
                    if (players[playNow]->make_trump(upCard, true, round,
                                                     orderUpSuit)){
                        orderStore(playNow, pick, order);
                        players[dealerIndex]->add_and_discard(upCard);
                       // orderStore(playNow, pick, order);

                    }
                    else {
                        cout << players[playNow]->get_name() << " passes" <<
                       endl;
                    }
                    
                }
                else if (players[playNow]->make_trump(upCard, false, round,
                                                      orderUpSuit)){
                    orderStore(playNow, pick, order);
                    players[dealerIndex]->add_and_discard(upCard);
                    //orderStore(playNow, pick, order);

                }
                else {
                    cout << players[playNow]->get_name() << " passes" << endl;
                }
                playNow++;
            }
    }
    
    void trumpRoundTwo(int dealerIndex, string &pick, bool &order) {
        int playNow =  dealerIndex + 1;
        int round = 2;
        while (playNow < NUM_PLAYERS && order == false) {
            //since it starts to left of dealer, dealer will never come up
            //in this while loop
            if (players[playNow]->make_trump(upCard, false, round,
                                             orderUpSuit)) {
                //players[dealerIndex]->add_and_discard(upCard);

                orderStore(playNow, pick, order);

            }
            else {
                cout << players[playNow]->get_name() << " passes" << endl;
            }
            playNow++;
        }
        playNow = 0;
        while (playNow < dealerIndex + 1 && order == false) {
            //account for dealer and regular players
            if (playNow == dealerIndex) {
                if (players[playNow]->make_trump(upCard, true, round,
                                                 orderUpSuit)) {
                    //players[dealerIndex]->add_and_discard(upCard);
                    orderStore(playNow, pick, order);
                    
                }
                else {
                    cout << players[playNow]->get_name() << " passes" << endl;
                }
            }
            else if (players[playNow]->make_trump(upCard, false, round,
                                                  orderUpSuit)){
                //players[dealerIndex]->add_and_discard(upCard);
                orderStore(playNow, pick, order);
            }
            else {
                cout << players[playNow]->get_name() << " passes" << endl;
            }
            playNow++;
        }

    cout << endl;
    }
    
    //wrong because it assigns teams based on playNow positioning rather than
    //input other
    void make_trump(int dealerIndex, string &pick) {
        bool order = false;
        int round = 1;
        trumpRoundOne(dealerIndex, pick, order);
        
        //while we cycle through and ordered up
        //while loop w two conditions
        //if statement

            //end of round one
        round++;
        if (order == false) {
            trumpRoundTwo(dealerIndex, pick, order);
        }
    }
/*
    void play_trick(string &trump, int &t1points, int &t2points,
                    string &winner) {
        int eldest = dealerNum + 1;
        if (eldest == NUM_PLAYERS) {
            eldest = 0;
        }
        
        if (winner == "") {}
        else if (winner != "") {
            for (int i = 0; i < NUM_PLAYERS; i++) {
                if (players[i]->get_name() == winner) {
                    eldest = i;
                }
            }
        }
        
        Card ledCard = players[eldest]->lead_card(trump);
        cout << ledCard.get_rank() << " of " << ledCard.get_suit() << " led by ";
        cout << players[eldest]->get_name() << endl;
        array<Card, NUM_PLAYERS> cPlay;
        cPlay[eldest] = ledCard;
        
        int playNow = eldest + 1;
       
        while (playNow < NUM_PLAYERS) {
            cPlay[playNow] = players[playNow]->play_card(ledCard, trump);
            cout << cPlay[playNow].get_rank() << " of " <<
            cPlay[playNow].get_suit();
            cout << " played by " << players[playNow]->get_name() << endl;
            playNow++;
            
        }
        playNow = 0;
        
        while (playNow < eldest) {
            cPlay[playNow] = players[playNow]->play_card(ledCard, trump);
            cout << cPlay[playNow].get_rank() << " of " <<
            cPlay[playNow].get_suit();
            cout << " played by " << players[playNow]->get_name() << endl;
            playNow++;
        }
        
        //look through all 4 cards, who wins?
        int playerWon = eldest;
        Card StrongestCard = ledCard;
        
        for (int i = 0; i < NUM_PLAYERS; i++) {
            if (Card_less(StrongestCard, cPlay[i], ledCard, trump)) {
                StrongestCard = cPlay[i];
                playerWon =  i;
            }
        }
        
        cout << players[playerWon]->get_name() << " takes the trick" << endl;
        winner = players[playerWon]->get_name();
        //specify teams and incrememt trock wins
        if (playerWon == 0 || playerWon == 2) {
            t1points++;
        }
        else if (playerWon == 1 || playerWon == 3) {
            t2points++;
        }
        //one or two endl here? I took out one
        cout << endl;
    }
*/
    void play_trick_help(int &eldest, string &winner) {
            if (winner == "") {}
            else if (winner != "") {
                for (int i = 0; i < NUM_PLAYERS; i++) {
                    if (players[i]->get_name() == winner) {
                        eldest = i;
                    }
                }
            }
        }


        void play_trick(string &trump, int &t1points, int &t2points,
                        string &winner) {
            int eldest = dealerNum + 1;
            if (eldest == NUM_PLAYERS) {
                eldest = 0;
            }
            play_trick_help(eldest, winner);
            /*
            if (winner == "") {}
            else if (winner != "") {
                for (int i = 0; i < NUM_PLAYERS; i++) {
                    if (players[i]->get_name() == winner) {
                        eldest = i;
                    }
                }
            }
            */
            Card ledCard = players[eldest]->lead_card(trump);
            cout << ledCard.get_rank() << " of " << ledCard.get_suit() <<
            " led by ";
            cout << players[eldest]->get_name() << endl;
            array<Card, NUM_PLAYERS> cPlay;
            cPlay[eldest] = ledCard;
            
            int playNow = eldest + 1;
           
            while (playNow < NUM_PLAYERS) {
                cPlay[playNow] = players[playNow]->play_card(ledCard, trump);
                cout << cPlay[playNow].get_rank() << " of " <<
                cPlay[playNow].get_suit();
                cout << " played by " << players[playNow]->get_name() << endl;
                playNow++;
                
            }
            playNow = 0;
            
            while (playNow < eldest) {
                cPlay[playNow] = players[playNow]->play_card(ledCard, trump);
                cout << cPlay[playNow].get_rank() << " of " <<
                cPlay[playNow].get_suit();
                cout << " played by " << players[playNow]->get_name() << endl;
                playNow++;
            }
            
            //look through all 4 cards, who wins?
            int playerWon = eldest;
            Card StrongestCard = ledCard;
            
            for (int i = 0; i < NUM_PLAYERS; i++) {
                if (Card_less(StrongestCard, cPlay[i], ledCard, trump)) {
                    StrongestCard = cPlay[i];
                    playerWon =  i;
                }
            }
            
            cout << players[playerWon]->get_name() << " takes the trick" << endl;
            winner = players[playerWon]->get_name();
            //specify teams and incrememt trock wins
            if (playerWon == 0 || playerWon == 2) {
                t1points++;
            }
            else if (playerWon == 1 || playerWon == 3) {
                t2points++;
            }
            //one or two endl here? I took out one
            cout << endl;
        }


    void deal_two_cards(int index) {
        //assert(0 <= index && index < NUM_PLAYERS);
        //cout << index << index << index << index << endl << endl;
        
        players.at(index) -> add_card(deck.deal_one());
        players.at(index) -> add_card(deck.deal_one());
    }
    
    void deal_three_cards(int index) {
        //assert(0 <= index && index < NUM_PLAYERS);
        //cout << index << index << index << index << endl << endl;
        players.at(index) -> add_card(deck.deal_one());
        players.at(index) -> add_card(deck.deal_one());
        players.at(index) -> add_card(deck.deal_one());
    }
    
    void deal(int dealerIndex) {
        //deals in proper order and assigns the upcard
        //cout << dealerIndex << endl << endl;
        //assert(0 <= dealerIndex && dealerIndex < NUM_PLAYERS);
        /*
        int nowIndex = dealerIndex + 1;
        bool firstEven = false;
        if (nowIndex % 2 == 0) {
            firstEven = true;
            while (nowIndex < NUM_PLAYERS) {
                if (nowIndex % 2 == 0) {
                    players[nowIndex]->add_card(deck.deal_one());
                    players[nowIndex]->add_card(deck.deal_one());
                    players[nowIndex]->add_card(deck.deal_one());
                    nowIndex++;
                }
                else if (nowIndex % 2 == 1) {
                    players[nowIndex]->add_card(deck.deal_one());
                    players[nowIndex]->add_card(deck.deal_one());
                    nowIndex++;
                }
                else {
                    assert(false);
                }
            }
            nowIndex = 0;
            while (nowIndex < dealerIndex + 1) {
                if (nowIndex % 2 == 0) {
                    players[nowIndex]->add_card(deck.deal_one());
                    players[nowIndex]->add_card(deck.deal_one());
                    players[nowIndex]->add_card(deck.deal_one());
                    nowIndex++;
                }
                else if (nowIndex % 2 == 1) {
                    players[nowIndex]->add_card(deck.deal_one());
                    players[nowIndex]->add_card(deck.deal_one());
                    nowIndex++;
                }
                else {
                    assert(false);
                }
            }
            
            //round 1 done
            
            if (nowIndex != dealerIndex + 1) {
                assert(false);
            }
            
            while (nowIndex < NUM_PLAYERS) {
                if (nowIndex % 2 == 0) {
                    players[nowIndex]->add_card(deck.deal_one());
                    players[nowIndex]->add_card(deck.deal_one());
                    nowIndex++;
                }
                else if (nowIndex % 2 == 1) {
                    players[nowIndex]->add_card(deck.deal_one());
                    players[nowIndex]->add_card(deck.deal_one());
                    players[nowIndex]->add_card(deck.deal_one());
                    nowIndex++;
                }
                else {
                    assert(false);
                }
            }
            nowIndex = 0;
            while (nowIndex < dealerIndex + 1) {
                if (nowIndex % 2 == 0) {
                    players[nowIndex]->add_card(deck.deal_one());
                    players[nowIndex]->add_card(deck.deal_one());
                    nowIndex++;
                }
                else if (nowIndex % 2 == 1) {
                    players[nowIndex]->add_card(deck.deal_one());
                    players[nowIndex]->add_card(deck.deal_one());
                    players[nowIndex]->add_card(deck.deal_one());
                    nowIndex++;
                }
                else {
                    assert(false);
                }
            }
        }
        else {
            while (nowIndex < NUM_PLAYERS) {
                if (nowIndex % 2 == 1) {
                    players[nowIndex]->add_card(deck.deal_one());
                    players[nowIndex]->add_card(deck.deal_one());
                    players[nowIndex]->add_card(deck.deal_one());
                    nowIndex++;
                }
                else if (nowIndex % 2 == 0) {
                    players[nowIndex]->add_card(deck.deal_one());
                    players[nowIndex]->add_card(deck.deal_one());
                    nowIndex++;
                }
                else {
                    assert(false);
                }
            }
            nowIndex = 0;
            while (nowIndex < dealerIndex + 1) {
                if (nowIndex % 2 == 1) {
                    players[nowIndex]->add_card(deck.deal_one());
                    players[nowIndex]->add_card(deck.deal_one());
                    players[nowIndex]->add_card(deck.deal_one());
                    nowIndex++;
                }
                else if (nowIndex % 2 == 0) {
                    players[nowIndex]->add_card(deck.deal_one());
                    players[nowIndex]->add_card(deck.deal_one());
                    nowIndex++;
                }
                else {
                    assert(false);
                }
            }
            
            //round 1 done
            
            if (nowIndex != dealerIndex++) {
                assert(false);
            }
            
            while (nowIndex < NUM_PLAYERS) {
                if (nowIndex % 2 == 1) {
                    players[nowIndex]->add_card(deck.deal_one());
                    players[nowIndex]->add_card(deck.deal_one());
                    nowIndex++;
                }
                else if (nowIndex % 2 == 0) {
                    players[nowIndex]->add_card(deck.deal_one());
                    players[nowIndex]->add_card(deck.deal_one());
                    players[nowIndex]->add_card(deck.deal_one());
                    nowIndex++;
                }
                else {
                    assert(false);
                }
            }
            nowIndex = 0;
            while (nowIndex < dealerIndex + 1) {
                if (nowIndex % 2 == 1) {
                    players[nowIndex]->add_card(deck.deal_one());
                    players[nowIndex]->add_card(deck.deal_one());
                    nowIndex++;
                }
                else if (nowIndex % 2 == 0) {
                    players[nowIndex]->add_card(deck.deal_one());
                    players[nowIndex]->add_card(deck.deal_one());
                    players[nowIndex]->add_card(deck.deal_one());
                    nowIndex++;
                }
                else {
                    assert(false);
                }
            }
            
            
        }
         */
        

        //first deal
        deal_three_cards((dealerIndex + 1) % 4);
        //cout << (dealerIndex + 1) % 4 << endl;
        
        deal_two_cards((dealerIndex + 2) % 4);
        //cout << (dealerIndex + 2) % 4 << endl;
        
        deal_three_cards((dealerIndex + 3) % 4);
       // cout << (dealerIndex + 3) % 4 << endl;
        
        deal_two_cards(dealerIndex);
        //cout << (dealerIndex) << endl;
        
        //second deal
        deal_two_cards((dealerIndex + 1) % 4);
        //cout << (dealerIndex + 1) % 4 << endl;
        
        deal_three_cards((dealerIndex + 2) % 4);
       // cout << (dealerIndex + 2) % 4 << endl;
        
        deal_two_cards((dealerIndex + 3) % 4);
        //cout << (dealerIndex + 3) % 4 << endl;
        
        deal_three_cards(dealerIndex);
        //cout << (dealerIndex) << endl;
        //reveal card to be picked up/passed
        upCard = deck.deal_one();
    }
};


//Junior helped me break this part down
int main(int argc, char* argv[]) {
    if (argc != 12) {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
             << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
             << "NAME4 TYPE4" << endl;
        return 1;
    }
    string packfile = argv[1];
    ifstream fin;
    fin.open(packfile);
    if (!(fin.is_open())) {
        cout << "Error opening file: " << packfile << endl;
        return 1;
    }
    Pack in = Pack(fin);
    
    
    string shuffleyes = argv[2];
    
    if (shuffleyes != "shuffle" && shuffleyes != "noshuffle") {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
             << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
             << "NAME4 TYPE4" << endl;
        return 1;
    }
    //int toWin = argv[3] - '0';
    //int toWin =  static_cast<int>(argv[3])
    char * test = argv[3];
    //if (test.size() > 2) {

    char next = *test;
    char digitTwo = *(++test);
    //char digitThree = *(test + 2); fix later for triple digits
    int points;
    if (digitTwo == '\0') {
        points = static_cast<int>(next - '0');
    }
    else {
        int one = static_cast<int>(next - '0') * 10;
        int two = static_cast<int>(digitTwo - '0');
        points = one + two;
    }
    
    Player * one = Player_factory(argv[4], argv[5]);
    Player * two = Player_factory(argv[6], argv[7]);
    Player * three = Player_factory(argv[8], argv[9]);
    Player * four = Player_factory(argv[10], argv[11]);
    
    
    //new vector
    vector<Player*> pVec {one, two, three, four};
    //idek bruh
    
    Game euchre = Game(pVec, in, shuffleyes, points);
    
    cout << "./euchre.exe ";
    for (int i = 1; i < 12; i++) {
        cout << argv[i] << " ";
    }
    cout << endl;
    euchre.playGame();
    

    
    
    
    delete one;
    delete two;
    delete three;
    delete four;
    
    
    
    
    
    
    //read these arguments into
    //count arguments etc
    //make sure its correct
    
    //open file
    
    //create players
    //create game
    //play game

}





/*
Things we need:
 1. A system of dealing after shuffle (read in pack.in and then shuffle).
 Probably a class and we can store cards dealt into vectors for each player
 2. Store remaining cards in another vector, use first card in vector as reveal
 card
 3. Have each player decide whether to pass or pick up on flipped card
 4. If picked up, that card is trump, and dealer drops lowest off suit card
 (need to idetify lowest off suit prior to for the simple game)
    a. If not picked up, another round of decision for trump and then misdeal,
 repeat 1-4
 5. Some sort of card decision process based on trump/leadsuit card thrown
 6. Compare all cards (this is done), add trick win to corresponding team
    a. All 5 hands +2
    b. Euching, +2
 7. Keep repeating, adding total points to team score
 8. Once a team reaches 10 points, game over
 
 Also need a mechanic to rotate between players clockwise for dealer and the
 person to left of dealer needs to play/make decisions first.
 
 Kai: I think a lot of 2-4
 
 
 //Junior helped me break this part down
 int main(int argv, char ** argc) {
     //read these arguments into
     //count arguments etc
     //make sure its correct
     
     //open file
 if (!nsjdnasjdn) {
    return null;  //error   pack file i believe
 }
     
     //create players
    player one = player_factory(jfdnbfjd);
    player two = player_factoru(dnfjdn);
    player...
 player....
    game(nsdjnskd);
    Playgame;
     //create game
     //play game
 };

 
 
*/

