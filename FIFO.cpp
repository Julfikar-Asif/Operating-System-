#include <iostream>
using namespace std;

const int MAX_FRAMES = 100;
const int MAX_PAGES = 1000;

int faults = 0, hits = 0, frame_size, page_count, frames[MAX_FRAMES], pages[MAX_PAGES], pointer = 0;

void print() {
    for (int i = 0; i < frame_size; i++) {
        if (frames[i] == -1)
            cout << " - ";
        else
            cout << " " << frames[i] << " ";
    }
    cout << endl;
}

void FIFO() {
    for (int i = 0; i < page_count; i++) {
        bool alloted = false;
        for (int j = 0; j < frame_size; j++) {
            if (frames[j] == pages[i]) {
                alloted = true;
                cout << "Hit for " << pages[i] << " | ";
                hits++;
                break;
            } else if (frames[j] == -1) {
                alloted = true;
                frames[j] = pages[i];
                cout << "Fault for " << pages[i] << " | ";
                faults++;
                break;
            }
        }
        if (!alloted) {
            faults++;
            cout << "Fault for " << pages[i] << " | ";
            frames[pointer] = pages[i];
            pointer = (pointer + 1) % frame_size;
        }
        print();
    }
}

int main() {
    cout << "Enter frame size: ";
    cin >> frame_size;

    cout << "Enter the number of references: ";
    cin >> page_count;

    cout << "Enter the page references: ";
    for (int i = 0; i < page_count; i++)
        cin >> pages[i];

    for (int i = 0; i < frame_size; i++)
        frames[i] = -1;

    FIFO();
    double hit_r=(double)hits/page_count*100;
    double miss_r=(double)faults/page_count*100;

    cout << "\nNumber of faults: " << faults << "\nNumber of hits: " << hits << "\n";
    cout<< "Hit ratio "<< hit_r<< "%\n";
    cout<< "miss ratio "<< miss_r<< "%\n";
    return 0;
}

//Enter frame size: 3
// Enter the number of references: 7
// Enter the page references: 1 3 0 3 5 6 3
