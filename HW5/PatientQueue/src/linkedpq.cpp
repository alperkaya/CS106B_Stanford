#include "linkedpq.h"

LinkedPQ::LinkedPQ() {
    front = NULL;
}

LinkedPQ::~LinkedPQ() {
    clear();
}

void LinkedPQ::clear() {
    if(isEmpty()){
        return;
    }else{
        PNode* iterator = front;
        while(iterator!=NULL){
            PNode* nodeToBeRemoved = iterator;
            iterator=iterator->next;
            delete nodeToBeRemoved;
        }
        front=NULL;
    }

}

string LinkedPQ::frontName() {
    if(!isEmpty()){
        return front->name;
    }

    throw "No patient is present..";
    return "";
}

int LinkedPQ::frontPriority() {
    if(!isEmpty()){
        return front->priority;
    }

    throw "No patient is present..";
    return 0;
}

bool LinkedPQ::isEmpty() const {
    if(front==NULL){
        return true;
    }
    return false;
}

void LinkedPQ::newPatient(string name, int priority) {
    if(isEmpty()){
        front=new PNode(name, priority);
    }else{
        PNode* newNode=new PNode(name, priority);
        PNode* iterator=front;
        PNode* prevNode=front;

        if(front->priority > newNode->priority){
            front=newNode;
            front->next=iterator;
        }else{
            while(1){
                if(iterator->priority > newNode->priority){
                    prevNode->next=newNode;
                    newNode->next=iterator;
                    break;
                }else if(iterator->next==NULL){
                    iterator->next=newNode;
                    break;
                }
                prevNode=iterator;
                iterator=iterator->next;
            }
        }

    }
}

string LinkedPQ::processPatient() {
    if(isEmpty()){
        throw "No patient is present..";
        return "";
    }

    string patientName=frontName();

    if(front->next==NULL){
        front=NULL;
    }else{
        PNode *nextNode=front->next;
        front=nextNode;
    }

    return patientName;

}

void LinkedPQ::upgradePatient(string name, int oldPriority, int newPriority) {
    if(isEmpty()){
        throw "No patient is present..";
        return;
    }

    PNode* iterator=front;
    PNode* prevNode=front;
    bool isFound=false;
    while(iterator!=NULL){
        if(iterator->name==name && iterator->priority==oldPriority){
            prevNode->next=iterator->next;
            delete iterator;
            newPatient(name, newPriority);
            isFound=true;
            return;
        }
        prevNode=iterator;
        iterator=iterator->next;
    }
    if(!isFound){
        throw "Error: The given value is not found in this priority queue";
    }
}

void LinkedPQ::debug() {
    // TODO: write this function (optional)
}

ostream& operator <<(ostream& out, const LinkedPQ& queue) {
    if(queue.isEmpty()){
        out << "{}";
    }else{
        PNode* iterator = queue.front;
        out << "{";
        while(iterator!=NULL){
            out << *iterator;
            iterator=iterator->next;

            if(iterator!=NULL){
                out << ", ";
            }
        }

        out << "}";
    }


    return out;
}
