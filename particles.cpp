
#include <iostream>
#include <bitset>

/*
An interesting problem: 

There are n particles in a chamber of m locations (n<=m). Each particle is marked L or R based on whether it moves left or right. Empty locations are marked as dot(.). If the initial state of the chamber is denoted as S, then given a speed w which measures number of steps a particle moves left/right every unit of time, list all states of the chamber starting from S until it is empty.

Particles can move through each other so each position in steps subsequent to S is marked as X if there is at least one particle in that postion. Otherwise it marked as dot(.)

Input: w=2, S="R....L"
Output: { 
          "X....X"
          "..XX..",
          ".X..X.",
          "......"
        }

*/
 
using namespace std;

/* Calculate number of bits to represent an integer n
   @param integer
   @return number of bits used to represent n
*/

int num2bits(int n) {
    return (1 << n) - 1;
}

/*
Print all states of the chamber. The function printSeq is invoked multiple times for each state.

@param s: unsigned long representing a state. Each bit represents a position in the chamber.
@param len: number of positions in chamber. When length is specified, it is cached inside the function and the first state(S) is printed. Subsequent calls to printSeq with length argument of 0 will print all subsequent states which are of length len.
@param iter represents the state number
@returns nothing

*/
void printSeq(unsigned long s, unsigned long length = 0, int iter = 0) {
    static int len = 0;
    if (length) {
        len = length;
        cout << "{  ";
    }
    cout << "\"";
    for (unsigned long i = 0; i < len; i++) {
        if ((1 << (len - 1 - i)) & s) {
            cout << "X";
        } else {
            cout << ".";
        }
    }
    if (iter) { 
        cout << "\"," << "\n";
    } else {
        cout << "\"" << "\n";
    }
}

/*
Function that determines all states of the chamber starting from initial state S
@param init: initial state
@param speed: speed of particles (how many positions they move to the left/right)
@returns nothing
*/

void animate(int speed, const char *init) {
    unsigned long resultL = 0;
    unsigned long resultR = 0;
    unsigned long resultAll = 0;

    const char *i = init;
    char c;
    unsigned long index = 0;
    /// compute first state, L/R is represented by X
    while ((c = *i)) {
        resultL <<= 1;
        resultR <<= 1;
        if (c == 'L') {
            resultL = resultL | 1 ;
        }
        if (c == 'R') {
            resultR = resultR | 1 ;
        }
        i++;
        index++;
    }

    cout << "{ " << "\n";
    int mask = num2bits(index);  /// mask is used to demarcate a window representing chamber's size
    resultL &= mask;
    resultR &= mask; 
    resultAll = (resultL | resultR);
    int iter = 0;
    printSeq(resultAll, index, iter); /// print the first state
    
    while (resultAll != 0) {
       resultL = (resultL << speed) & mask;
       resultR = (resultR >> speed) & mask;
       resultAll = (resultL | resultR);
       iter++;
       printSeq(resultAll, 0L, iter); /// print subsequent states
    } 
    cout << " }\n";
}

int main (int argc, char *argv[]) {

animate(2,"..R....");
animate(3,"RR..LRL");
animate(2,  "LRLR.LRLR");
animate(10,  "RLRLRLRLRL");
animate(1,  "...");
animate(1,  "LRRL.LR.LRR.R.LRRL.");
        
}

