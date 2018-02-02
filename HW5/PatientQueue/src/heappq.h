#ifndef _heappq_h   // do not modify these two lines
#define _heappq_h

#include <iostream>
#include <string>
#include "pnode.h"

using namespace std;

class HeapPQ {
public:
    HeapPQ();
    ~HeapPQ();
    void clear();
    string frontName();
    int frontPriority();
    bool isEmpty() const;
    void newPatient(string name, int priority);
    string processPatient();
    void upgradePatient(string name, int oldPriority, int newPriority);
    void debug();
    friend ostream& operator <<(ostream& out, const HeapPQ& queue);

private:
    // member variable(s)
    PNode* heapArr;
    int capacity;
    int size;

    void bubbleUp(int pos);
    void bubbleDown(int pos);
    bool isExist(int pos);
};

ostream& operator <<(ostream& out, const HeapPQ& queue);

#endif
