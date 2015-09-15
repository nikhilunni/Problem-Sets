#include <iostream>
#include <string>
#include "priority_queue.h"
using namespace std;

int main(int argc, char* argv[])
{
    PriorityQueue<int> queue;

    queue.insert(47);
    queue.insert(42);
    queue.insert(49);
    queue.insert(45);

    cout << "Empty? " << queue.isEmpty() << endl;
    cout << "pop: " << queue.pop() << endl;
    cout << "top: " << queue.top() << endl;

    return 0;
}
