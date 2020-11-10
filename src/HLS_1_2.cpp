#include <iostream>
#include <ctime>
#include <cstdlib>

static const int N = 4;
static const int TESTS = 5;

typedef unsigned int Data_t;
typedef Data_t Array[N];

int checksum(Data_t Num[N]){
    int sum = 0;
    int dig;

    for(int i = N-1; i > 0; i-=2){
        if(2 * Num[i-1] < 10){
            sum += Num[i] + 2 * Num[i-1];
        }else{
            dig = (2 * Num[i-1]) % 10;
            sum += Num[i] + 1 + dig;
        }
    }

    return sum;
}
int main(){
    Array Nums[TESTS];

    std::srand(std::time(NULL));

    for(int i = 0; i < TESTS; i++){
        std::cout << "input\n";

        for(int j = 0; j < N; j++){
            Nums[i][j] = std::rand() % 10;
            std::cout << Nums[i][j];
        }

        std::cout << "\nchecksum\n" << checksum(Nums[i]) << "\n\n";

    }
    return 0;
}
