#include <iostream>
#include <ctime>
#include <cstdlib>
#include "ac_int.h"
#include "ac_fixed.h"
#include "ac_channel.h"


static const int TESTS = 10;
static const int W = 8;
static const int Wout = 2 * W +1;


template <int W>
void csd_encode (ac_int<W,true> &num, ac_int<W,false> &x_p, ac_int<W,false>
&x_m){

    int carry = 0;
    ac_int<2,false> two_bits;

    for(int i=0; i < W; i++){
        two_bits = num.template slc<2>(i);

        if(carry == 0){
            if (two_bits[0] == 0){
                x_p[i] = 0;
                x_m[i] = 0;
            }else{
                if(two_bits[1] == 0){
                    x_p[i] = 1;
                    x_m[i] = 0;
                }else{
                    x_m[i] = 1;
                    x_p[i] = 0;
                    carry = 1;
                }
            }
        }else{
            if(two_bits[0] == 0){
               if(two_bits[1] == 0){
                    x_p[i] = 1;
                    x_m[i] = 0;
                    carry = 0;
               }else{
                    x_m[i] = 1;
                    x_p[i] = 0;
               }
            }else{
                x_p[i] = 0;
                x_m[i] = 0;
            }
        }

    }

}


ac_int<Wout,true> csd_mult (ac_int<W,true> &in, const ac_int<W,false> &csd_x_p, const ac_int<W,false>
&csd_x_m){

    ac_int<Wout,true> res = 0;
    ac_int<Wout, true> temp;
    for(int i=0; i < W; i++){
        temp = csd_x_p[i] * in;
        res += temp << i;
        temp = csd_x_m[i] * in;
        res -= temp << i;
    }
    return res;
}


int main(){
    ac_int<W,true> in;
    ac_int<W,true> num;
    ac_int<W,false> x_p;
    ac_int<W,false> x_m;


    std::srand(std::time(NULL));

    for(int i = 0; i < TESTS; i++){

        std::cout << "constant\n";
        for(int j = 0; j < W; j++){
            num[j] = std::rand() % 2;
            std::cout << num[j];
        }

        csd_encode(num, x_p, x_m);

        std::cout << "\nx_p\n";
        for(int j = 0; j < W; j++){
            std::cout << x_p[j];
        }

        std::cout << "\nx_m\n";
        for(int j = 0; j < W; j++){
            std::cout << x_m[j];
        }

        std::cout << "\ninput\n";
        for(int j = 0; j < W; j++){
            in[j] = std::rand() % 2;
            std::cout << in[j];
        }

        std::cout << "\nmult\n";
        std::cout << num * in <<"\n";
        std::cout << "csd_mult\n";
        std::cout << csd_mult(in, x_p, x_m) << "\n\n";

    }
    return 0;
 }

