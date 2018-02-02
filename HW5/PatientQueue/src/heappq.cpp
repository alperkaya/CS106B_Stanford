#include "heappq.h"

HeapPQ::HeapPQ() {
    capacity=10;
    size=0;
    heapArr = new PNode[capacity];
}

HeapPQ::~HeapPQ() {
    clear();
    delete[] heapArr;
}

void HeapPQ::clear() {
    size=0;
}

string HeapPQ::frontName() {
    if(!isEmpty()){
        return heapArr[1].name;
    }
    throw "No patient is present..";
    return "";
}

int HeapPQ::frontPriority() {
    if(!isEmpty()){
        return heapArr[1].priority;
    }
    throw "No patient is present..";
    return 0;
}

bool HeapPQ::isEmpty() const{
    if(size==0){
        return true;
    }

    return false;
}

void HeapPQ::newPatient(string name, int priority) {

    if(size+1==capacity){
        capacity*=2;
        PNode* newArr=new PNode[capacity];

        for(int i=1; i<=size; i++){
            newArr[i]=heapArr[i];
        }

        delete[] heapArr;
        heapArr=newArr;
    }


    heapArr[size+1].name=name;
    heapArr[size+1].priority=priority;
    size++;
    bubbleUp(size);

}

void HeapPQ::bubbleUp(int pos){
    if(pos<=0){
        return;
    }else if(heapArr[pos/2].priority > heapArr[pos].priority){
        swap(heapArr[pos], heapArr[pos/2]);
        bubbleUp(pos/2);
    }

}


string HeapPQ::processPatient() {
    string patientName=frontName();


    swap(heapArr[1], heapArr[size]);
    size--;
    bubbleDown(1);

    return patientName;
}

bool HeapPQ::isExist(int pos){
    if(pos<=size){
        return true;
    }
    return false;
}


void HeapPQ::bubbleDown(int pos){
    if(!isExist(pos)){
        return;
    }

    if(isExist(pos*2+1) && heapArr[pos*2+1].priority < heapArr[pos*2].priority){
        if(heapArr[pos*2+1].priority < heapArr[pos].priority){
            swap(heapArr[pos], heapArr[pos*2+1]);
            bubbleDown(pos*2+1);
        }
    }

    if(isExist(pos*2) && heapArr[pos*2].priority < heapArr[pos].priority){
        swap(heapArr[pos], heapArr[pos*2]);
        bubbleDown(pos*2);
    }

    return;
}

void HeapPQ::upgradePatient(string name, int oldPriority, int newPriority) {
    if(isEmpty()){
        throw "No patient is present..";
        return;
    }

    bool isFound=false;
    for(int i=1; i<=size; i++){
        if(heapArr[i].priority==oldPriority && heapArr[i].name==name){
            heapArr[i].priority=newPriority;
            bubbleUp(i);
            return;
        }
    }

    if(!isFound){
        throw "Error: The given value is not found in this priority queue";
    }
}

void HeapPQ::debug() {
    // TODO: write this function (optional)
}

ostream& operator <<(ostream& out, const HeapPQ& queue) {
    if(queue.isEmpty()){
        out << "{}";
    }else{
        PNode* iterator = queue.heapArr;
        out << "{";
        for(int i=1; i<=queue.size; i++){
            out << iterator[i];

            if(i<queue.size){
                out << ", ";
            }
        }

        out << "}";
    }

    return out;
}
