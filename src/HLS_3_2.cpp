#include <iostream>
#include <ctime>
#include <cstdlib>
#include "ac_int.h"
#include "ac_fixed.h"
#include "ac_channel.h"

static const int ROUNDS = 10;

typedef ac_int<4,false> Card;


class BlackJack {
private:
 // internal state
    Card card;
    ac_int<5,false> sum;
    ac_int<3,false> cnt;
public:
 // constructor - init internal state
    BlackJack() {
        sum = 0;
        cnt = 0;
    }
 // top-level interface
    void run (ac_channel<Card> &in_card,bool &end_round, bool &win) {
        if(in_card.available(1)){
            card = in_card.read();
            cnt++;

            if(card == 1){
                card = 11;
            }

            sum += card;

            // if 2 first cards = 2 aces that means first ace becomes 1
            if(sum == 22 && cnt == 2){
                sum = 12;
            }

            if(sum == 21){
                end_round = true;
                win = true;
                sum = 0;
                cnt = 0;
            }else if(sum > 21){
                end_round = true;
                win = false;
                sum = 0;
                cnt = 0;
            }

            if(cnt == 5){
                end_round = true;
                win = true;
                sum = 0;
                cnt = 0;
            }
        }
    }
};


int main(){
    ac_channel<Card> in_card;
    bool end_round = false;
    bool win;
    BlackJack bj;

    std::srand(std::time(NULL));


    for(int i = 0; i < ROUNDS; i++){
        std::cout << "\nRound " << i << "\n";

        while(end_round == false){
            in_card.write(1 + (std::rand() % 10));
            std::cout << " in_card\n " << in_card << "\n";
            bj.run(in_card, end_round, win);

            if(end_round){
                if(win){
                    std::cout << " win\n";
                }else{
                    std::cout << " loss\n";
                }

            }
        }
        end_round = false;
    }

    return 0;
}


