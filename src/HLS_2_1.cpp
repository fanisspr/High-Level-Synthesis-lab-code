#include <iostream>
#include "ac_int.h"
#include "ac_fixed.h"

ac_int<8,false> a = 255, b = 255; // 8−bit unsigned integer
ac_int<9,true> c = 255, d = 255; // 9−bit signed integer
ac_int<18,true> e = a * b + c * d; // How many bits

ac_fixed<5,2,false> f = 3.999; //5−bit unsigned fixed−point type with 2 integer bits
ac_fixed<5,4,true> g = 7.9; // 5−bit signed fixed−point type with 4 integer bits
ac_fixed<10,6,true> h = f * g; // How many bits

int main(){
    std::cout << "a:" << a << std::endl;
    for(int i = 7; i >=0 ; i--){
        std::cout << a[i] ;
    }

    std::cout << "\nc:" << c << std::endl;
    for(int i = 8; i >=0 ; i--){
        std::cout << c[i] ;
    }

    std::cout << "\ne:" << e << std::endl;
    for(int i = 17; i >=0 ; i--){
        std::cout << e[i] ;
    }

    std::cout << "\nf:" << f << std::endl;
    for(int i = 4; i >=0 ; i--){
        std::cout << f[i] ;
    }

    std::cout << "\ng:" << g << std::endl;
    for(int i = 4; i >=0 ; i--){
        std::cout << g[i] ;
    }

    std::cout << "\nh:" << h << std::endl;
    for(int i = 9; i >=0 ; i--){
        std::cout << h[i] ;
    }

    return 0;
}
