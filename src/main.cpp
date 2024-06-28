#include <iostream>

int factorial(int n){
    int nums[n];
    nums[0] = 0;
    nums[1] = 1;
    for (int i = 2; i < n; ++i){
        nums[i] = nums[i-1] + nums[i-2];
    }
    return nums[n-1];
}

void main(){
    std::cout << "Hello World" << std::endl;
}