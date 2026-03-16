#include <iostream>
#include <deque>
#include <string>
using namespace std;

void printDeque(deque<int> dq) {
    if(dq.empty()) {
        cout << "Line is empty" << endl;
        return;
    }
    for(int x : dq) {
        cout << x << " ";
    }
    cout << endl;
}

int main() {
    deque<int> line;
    int Q; // number of operations
    cout << "Enter number of operations: ";
    cin >> Q;

    for(int i = 0; i < Q; i++) {
        string op;
        cin >> op;

        if(op == "push_front") {
            int x;
            cin >> x;
            line.push_front(x);
        } else if(op == "push_back") {
            int x;
            cin >> x;
            line.push_back(x);
        } else if(op == "pop_front") {
            if(!line.empty()) line.pop_front();
        } else if(op == "pop_back") {
            if(!line.empty()) line.pop_back();
        }

        // Print current state of the line
        printDeque(line);
    }

    return 0;
}