/*
 * CS 106B/X Patient Queue
 * This file declares the PNode structure.
 * Each PNode structure represents a single node in a linked list for a
 * priority queue, storing a string of data, an int of priority, and
 * a pointer to a next node (nullptr if none).
 *
 * Nodes can be printed to the console using the << operator.
 * This is not the same as printing a pointer to a node, which would just
 * print the node's memory address as a hexadecimal integer.
 *
 * Please do not modify this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 *
 * @author Marty Stepp
 * @version 2017/10/31
 */

#ifndef _pnode_h
#define _pnode_h

#include <iostream>
#include <string>

struct PNode {
public:
    std::string name;
    int priority;
    PNode* next;   // pointer to next node (NULL if none)

    /*
     * Constructor to initialize a new node with the given value,
     * priority, and next node pointer.
     * If any values are omitted, zero-equivalents will be used.
     */
    PNode(std::string name = "", int priority = 0, PNode* next = NULL);
};

/*
 * Overloaded operator to print a node to an output stream for debugging.
 */
std::ostream& operator <<(std::ostream& out, const PNode& node);

#endif
