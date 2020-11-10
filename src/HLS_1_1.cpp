#include <iostream>
#include <ctime>
#include <cstdlib>

static const int N = 32;
static const int TESTS = 5;

typedef unsigned int Data_t;
typedef Data_t Array[N];

int count_ones(Data_t Num[N]){
    unsigned short int cnt = 0;

    for(int i = 0; i < N; i++){
        cnt += Num[i];
    }

    return cnt;
}
int main(){
    Array Nums[TESTS];

    std::srand(std::time(NULL));

    for(int i = 0; i < TESTS; i++){
        std::cout << "input\n";

        for(int j = 0; j < N; j++){
            Nums[i][j] = std::rand() % 2;
            std::cout << Nums[i][j];
        }

        std::cout << "\nNumber of ones\n" << count_ones(Nums[i]) << "\n\n";

    }
    return 0;
}
