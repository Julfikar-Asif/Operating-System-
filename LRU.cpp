#include <iostream>
using namespace std;

int faults = 0, hits = 0, frame_size, page_count, frames[100], pages[1000];

void print(int frame_size, int frames[]) {
    for (int i = 0; i < frame_size; i++) {
        if (frames[i] == -1)
            cout << " - ";
        else
            cout << " " << frames[i] << " ";
    }
    cout << endl;
}

int LRU_predict(int current_page_pos) {
    int frame_priority[100]; // Assuming maximum frame size of 100
    for (int i = 0; i < frame_size; i++) {
        int priority = 0;
        for (int j = current_page_pos - 1; j >= 0; j--) {
            priority++;
            if (frames[i] == pages[j]) {
                frame_priority[i] = priority;
                break;
            }
        }
    }
    // Find the index of the maximum element in frame_priority array
    int max_index = 0;
    for (int i = 1; i < frame_size; i++) {
        if (frame_priority[i] > frame_priority[max_index]) {
            max_index = i;
        }
    }
    return max_index;
}

void LRU() {
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
            int pos = LRU_predict(i); // predicting the frame position to replace with the current page at position i.
            cout << "Predicted position: " << pos << " | ";
            alloted = true;
            frames[pos] = pages[i];
            cout << "Fault for " << pages[i] << " | ";
            faults++;
        }
        print(frame_size, frames);
    }
}

int main() {
    cout << "Enter frame size: ";
    cin >> frame_size;
    for (int i = 0; i < frame_size; i++)
        frames[i] = -1;

    cout << "Enter the number of references: ";
    cin >> page_count;
    cout << "Enter the page references: ";
    for (int i = 0; i < page_count; i++)
        cin >> pages[i];

    LRU();

    cout << "\nNumber of faults: " << faults << "\nNumber of hits: " << hits << "\n";
    return 0;
}

// Enter frame size: 4
//Enter the number of references: 14
//Enter the page references: 7 0 1 2 0 3 0 4 2 3 0 3 2 3


