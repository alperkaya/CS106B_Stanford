/*
 * CS 106B/X Patient Queue
 * This file implements the members of the PNode structure.
 * See PNode.h for declaration and documentation of each member.
 *
 * Please do not modify this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 *
 * @author Marty Stepp
 * @version 2017/10/31
 */

#include "pnode.h"

PNode::PNode(std::string name, int priority, PNode* next) {
    this->name = name;
    this->priority = priority;
    this->next = next;
}

std::ostream& operator <<(std::ostream& out, const PNode& node) {
    return out << node.priority << ":" << node.name;
}
