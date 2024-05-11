#include <bits/stdc++.h>
using namespace std;

void optimalPage(int pg[], int pn, int fn) {
    // Create an array for given number of
    // frames and initialize it as empty.
    int fr[fn];
    memset(fr, -1, sizeof(fr)); // set all elements of fr to -1

    // Traverse through page reference array
    // and check for miss and hit.
    int hit = 0;
    for (int i = 0; i < pn; i++) {
        // Page found in a frame: HIT
        bool found = false;
        for (int j = 0; j < fn; j++) {
            if (fr[j] == pg[i]) {
                hit++;
                found = true;
                break;
            }
        }

        if (found)
            continue;

        // Page not found in a frame: MISS

        // If there is space available in frames.
        bool emptyFrame = false;
        for (int j = 0; j < fn; j++) {
            if (fr[j] == -1) {
                fr[j] = pg[i];
                emptyFrame = true;
                break;
            }
        }

        if (emptyFrame)
            continue;

        // Find the page to be replaced.
        int farthest = -1, replaceIndex = -1;
        for (int j = 0; j < fn; j++) {
            int k;
            for (k = i + 1; k < pn; k++) {
                if (fr[j] == pg[k]) {
                    if (k > farthest) {
                        farthest = k;
                        replaceIndex = j;
                    }
                    break;
                }
            }
            if (k == pn) {
                replaceIndex = j;
                break;
            }
        }
        fr[replaceIndex] = pg[i];
    }
    cout << "No. of hits = " << hit << endl;
    cout << "No. of misses = " << pn - hit << endl;
}

int main() {
    int pn, fn;

    cout << "Enter the number of pages: ";
    cin >> pn;
    int pg[pn];

    cout << "Enter the page references: ";
    for (int i = 0; i < pn; i++)
        cin >> pg[i];

    cout << "Enter the number of frames: ";
    cin >> fn;

    optimalPage(pg, pn, fn);

    return 0;
}

   //Enter frame size: 4
//Enter the number of references: 13
//Enter the page references: 7 0 1 2 0 3 0 4 2 3 0 3 2

