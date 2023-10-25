#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N;
    cout << "Enter a positive integer N ( N <= 92):";
    cin >> N;

    if (N > 92 || N <= 0) {
        cout << "Invalid input. Please enter a positive integer N <= 92" <<endl;
        return 1; 
    }

    vector <long long> fibonacci (N) ;
    fibonacci[0] = 1;
    fibonacci[1] = 1;

    for (int i =2; i < N ; ++i) {
        fibonacci[i] = fibonacci [i- 1] + fibonacci[i - 2];
    }

    cout << "Fibonacci sequence up to N:" << endl;
    for (int i = 0; i < N; ++i){
        cout << fibonacci[i] << " ";
    }

    cout << "\nFactor pairs with smallest difference for febonacci number:"<< endl;
    for (int i = 0; i < N; ++i) {
        long long num = fibonacci[i];
        long long factor1 = 1, factor2 = num;
        for (long long j = 2; j * j <= num; ++j){
            if (num % j == 0){
                factor1=j;
                factor2 = num /j;
                break;
            } 
        }
        cout << "F(" << i + 1 << "): " << factor1 << "*" <<factor2 << endl;
    }
    return 0;
}
