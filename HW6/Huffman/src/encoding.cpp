#include "pqueue.h"
#include "filelib.h"
#include "encoding.h"

void buildHuffmanTree(PriorityQueue<HuffmanNode*>& pqueue);
void buildEncodingMapHelper(HuffmanNode* encodingTree, Map<int, string>& encodingMap, string binaryDigit="");


Map<int, int> buildFrequencyTable(istream& input) {
    Map<int, int> freqTable;
    while(!input.eof()){
        int c = input.get();
        if(c==-1){
            break;
        }
        int val = freqTable.get(c);
        freqTable.add(c, val+1);
    }

    freqTable.add(PSEUDO_EOF, 1);

    return freqTable;
}

HuffmanNode* buildEncodingTree(const Map<int, int>& freqTable) {
    PriorityQueue<HuffmanNode*> pqueue;

    for(int charKey : freqTable){
        HuffmanNode* hNode = new HuffmanNode();
        hNode->character = charKey;
        hNode->count = freqTable.get(charKey); // frequency as priority

        pqueue.add(hNode, hNode->count);
    }

    buildHuffmanTree(pqueue);

    return pqueue.dequeue();
}

void buildHuffmanTree(PriorityQueue<HuffmanNode*>& pqueue){
    if(pqueue.size()<=1){
        return;
    }else{
        HuffmanNode* newNode=new HuffmanNode();
        newNode->character=NOT_A_CHAR;

        HuffmanNode* zeroHuffman;
        zeroHuffman=pqueue.peek();
        int k0_prio=pqueue.peekPriority();
        newNode->zero=zeroHuffman;
        pqueue.dequeue();

        HuffmanNode* oneHuffman;
        oneHuffman=pqueue.peek();
        int k1_prio=pqueue.peekPriority();
        newNode->one=oneHuffman;
        pqueue.dequeue();


        newNode->count=k0_prio+k1_prio;

        pqueue.add(newNode, newNode->count);

        buildHuffmanTree(pqueue);
    }
}

Map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    Map<int, string> encodingMap;
    buildEncodingMapHelper(encodingTree, encodingMap);

    return encodingMap;
}

void buildEncodingMapHelper(HuffmanNode* encodingTree, Map<int, string>& encodingMap, string binaryDigit){
    if(encodingTree==NULL){
        return;
    }else if(encodingTree->isLeaf()){
        encodingMap.add(encodingTree->character, binaryDigit);
    }

    binaryDigit += "0";
    buildEncodingMapHelper(encodingTree->zero, encodingMap, binaryDigit);
    binaryDigit.erase(binaryDigit.size()-1, 1);

    binaryDigit += "1";
    buildEncodingMapHelper(encodingTree->one, encodingMap, binaryDigit);
    binaryDigit.erase(binaryDigit.size()-1, 1);
}

void encodeData(istream& input, const Map<int, string>& encodingMap, obitstream& output) {
    while(1){
        int keyChar=input.get();
        string encodedData=encodingMap.get(keyChar);

        if(keyChar==-1){
            break;
        }

        while(!encodedData.empty()){
            output.writeBit(encodedData[0] - '0');
            encodedData.erase(0, 1);
        }

    }

    // put EOF to end of encoded data
    string encodedEOF=encodingMap.get(PSEUDO_EOF);
    while(!encodedEOF.empty()){
        output.writeBit(encodedEOF[0] - '0');
        encodedEOF.erase(0, 1);
    }

}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    HuffmanNode* tempTree=encodingTree;

    while(1){

        while(!tempTree->isLeaf()){
            int decodeBit=input.readBit();
            if(decodeBit==0){
                tempTree=tempTree->zero;
            }else if(decodeBit==1){
                tempTree=tempTree->one;
            }else{
                return;
            }
        }

        if(tempTree->character==PSEUDO_EOF){
            break;
        }

        const char c=tempTree->character;
        output.write(&c, sizeof(char));

        tempTree=encodingTree;
    }

}

void compress(istream& input, obitstream& output) {
    Map<int, int> freqTable = buildFrequencyTable(input);
    output << freqTable;
    rewindStream(input);

    HuffmanNode* node = buildEncodingTree(freqTable);
    Map<int, string> encoderMap = buildEncodingMap(node);
    encodeData(input, encoderMap, output);
}

void decompress(ibitstream& input, ostream& output) {
    Map<int, int> freqTable;
    input >> freqTable;
    HuffmanNode* huffmanNode = buildEncodingTree(freqTable);

    decodeData(input, huffmanNode, output);
}

void freeTree(HuffmanNode* node) {
    delete[] node;
}
