#include <iostream>
#include <ctime>
#include <cstdlib>
#include "ac_int.h"
#include "ac_fixed.h"
#include "ac_channel.h"

static const int TESTS = 5;

typedef ac_int<4,false> dtype;

void runlength_encode(ac_channel<ac_int<4,false> > &in,
 ac_channel<ac_int<4,false> > &out) {
    dtype curr;
    dtype prev;

    if(in.available(10)){
        prev = in.read();
        ac_int<3,false> cnt = 1;

        //std::cout << "\nout\n";

        for(int i = 0; i < 9; i++){
            curr = in.read();

            if(curr == prev){
                cnt++;
            }else{
                out.write(prev);
                out.write(cnt);
                //std::cout << out.read() << " ";
                //std::cout << out.read() << " ";
                cnt = 1;
            }

            prev = curr;
        }
        out.write(prev);
        out.write(cnt);
        //std::cout << out.read() << " ";
        //std::cout << out.read() << "\n";
        //std::cout << "\n";
    }
 }

 int main(){
    ac_channel<dtype> in;
    ac_channel<dtype> out;

    std::srand(std::time(NULL));

    //for(int i = 0; i < TESTS; i++){

        for(int j = 0; j < 10 * TESTS; j++){
            in.write((std::rand() % 16));
            std::cout << "in\n" << in << "\n";
            runlength_encode(in, out);
        //}

        //std::cout << "\nin\n" << in << std::endl ;

       // runlength_encode(in, out);

        std::cout << "out\n";
        int sz = out.size();
        for(int j = 0; j < sz; j++){
            std::cout << out.read() << " ";
            //std::cout << out.read() << " ";
        }
        std::cout << "\n\n";

    }
    return 0;
 }
