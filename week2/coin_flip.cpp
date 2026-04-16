#include <iostream>
#include <cstdlib>  // For rand()
#include <ctime>    // For time()
using namespace std;

int main() {
    srand(time(0));

    int flips;
    int heads = 0;
    int tails = 0;

    cout << "Coin Flip Simulator" << endl;
    cout << "How many flips would you like to simulate? ";
    cin >> flips;

    for (int i = 0; i < flips; i++) {
        int result = rand() % 2;
        if (result ==0) {
            heads++;
        } else {
            tails++;
        }
    }

    float HeadP = (float)heads / flips * 100;
    float TailP = (float)tails / flips * 100;

    printf ("results:");
    printf ("Heads: %d (%.2f%%)\n", heads, HeadP);
    printf ("tails: %d (%.2f%%)\n", tails, TailP);

    return 0;
}