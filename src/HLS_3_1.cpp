#include <iostream>
#include <ctime>
#include <cstdlib>
#include "ac_int.h"
#include "ac_fixed.h"
#include "ac_channel.h"

static const int TESTS = 50;

typedef ac_int<4,false> dtype;

class RunLengthEncoder {
private:
 // internal state
    dtype curr;
    dtype prev;
    dtype cnt;
public:
 // constructor - init internal state
    RunLengthEncoder() {
        cnt = 0;
    }
 // top-level interface
    void run (ac_channel<dtype> &in, ac_channel<dtype> &out) {
        if(in.available(1)){
            curr = in.read();

            if (cnt > 0){
                //std::cout << "\nout\n";
                if(curr != prev){
                    out.write(prev);
                    out.write(cnt);
                    //std::cout << out.read() << " ";
                    //std::cout << out.read() << " ";
                    cnt = 0;
                }

            }
            cnt++;
            prev = curr;
        }
    }
};


 int main(){
    ac_channel<dtype> in;
    ac_channel<dtype> out;
    RunLengthEncoder en;

    std::srand(std::time(NULL));


    for(int j = 0; j < TESTS; j++){
        in.write((std::rand() % 16));
        std::cout << "in\n" << in << "\n";
        en.run(in, out);

        std::cout << "out\n";
        int sz = out.size();
        for(int j = 0; j < sz; j++){
            std::cout << out.read() << " ";
        }
        std::cout << "\n\n";

    }

    return 0;
 }

