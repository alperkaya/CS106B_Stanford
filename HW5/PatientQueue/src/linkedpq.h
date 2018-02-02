#ifndef _linkedpq_h   // do not modify these two lines
#define _linkedpq_h

#include <iostream>
#include <string>
#include "pnode.h"
using namespace std;

class LinkedPQ {
public:
    LinkedPQ();
    ~LinkedPQ();
    void clear();
    string frontName();
    int frontPriority();
    bool isEmpty() const;
    void newPatient(string name, int priority);
    string processPatient();
    void upgradePatient(string name, int oldPriority, int newPriority);
    void debug();
    friend ostream& operator <<(ostream& out, const LinkedPQ& queue);

private:
    // member variable
    PNode* front;
    // TODO: add necessary member functions
    // TODO: make members 'const' as appropriate

};

ostream& operator <<(ostream& out, const LinkedPQ& queue);

#endif
