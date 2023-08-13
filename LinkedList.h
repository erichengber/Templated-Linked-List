//
// Created by Eric Hengber on 2/18/2023.
//
#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <typename  T>
class LinkedList{
public:
    struct Node{
        T data;
        Node* next;
        Node* prev;
    };
    Node* head;
    Node* tail;
    unsigned int nodes;
    // Behaviors
    void PrintForward() const;
    void PrintReverse() const;
    void PrintForwardRecursive(const Node* node) const;
    void PrintReverseRecursive(const Node* node) const;

    // Insertion
    void AddHead(const T& data);
    void AddTail(const T& data);
    void AddNodesHead(const T* data, unsigned int count);
    void AddNodesTail(const T* data, unsigned int count);
    void InsertAfter(Node* node, const T& data);
    void InsertBefore(Node* node, const T& data);
    void InsertAt(const T& data, unsigned int index);

    // Removal
    bool RemoveHead();
    bool RemoveTail();
    unsigned int Remove(const T& data);
    bool RemoveAt(unsigned int index);
    void Clear();

    // Accessors
    const Node* GetNode(unsigned int index) const;
    Node* GetNode(unsigned int index);
    unsigned int NodeCount() const;
    Node* Head();
    const Node* Head() const;
    Node* Tail();
    const Node* Tail() const;
    const Node* Find(const T& data) const;
    Node* Find(const T& data);
    void FindAll(vector<Node*>& outData, const T& value) const;

    // Operators
    const T& operator[](unsigned int index) const;
    T& operator[](unsigned int index);
    LinkedList<T>& operator=(const LinkedList<T>& rhs);
    bool operator==(const LinkedList<T>& rhs) const;

    // Construction / Destruction
    LinkedList();
    LinkedList(const LinkedList<T>& list);
    ~LinkedList();
};

// Removers
template<typename T>
void LinkedList<T>::Clear() {
    Node* node = head;
    Node* nextNode;
    while(node != nullptr){
        nextNode = node->next;
        delete node;
        node = nextNode;
    }
    nodes = 0;
    head = nullptr;
    tail = nullptr;
}

template<typename T>
bool LinkedList<T>::RemoveAt(unsigned int index) {
    Node* node = head;
    if (index > (nodes-1)){
        return false;
    }else{
        for (unsigned int i = 0; i < index; ++i) {
            node = node->next;
        }
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete node;
        nodes--;
        return true;
    }
}

template<typename T>
unsigned int LinkedList<T>::Remove(const T &data) {
    Node* node = head;
    unsigned int count = 0;
    while (node != nullptr){
        Node* holder = node->next;
        if (node->data == data){
            if (node->prev == nullptr){ // removing at head
                node->next->prev = nullptr;
                head = node->next;
            }
            else if (node->next == nullptr){ // removing at tail
                node->prev->next = nullptr;
                tail = node->next;
            } else{ // removing in list
                node->prev->next = node->next;
                node->next->prev = node->prev;
            }
            delete node;
            nodes--;
            count++;
        }
        node = holder;
    }
    return count;
}


template<typename T>
bool LinkedList<T>::RemoveHead() {
    if(nodes > 0) {
        if (head->next == nullptr) {
            Node *node = head;
            //cout << "Node: "  << node->data << endl;
            delete node;
            tail = nullptr;
            head = nullptr;
            //cout << "New Tail: " << tail->data << endl;
            //cout << "After Tail: " << tail->next->data << endl;
            nodes--;
            return true;
        } else {
            Node *node = head->next;
            delete head;
            head = node;
            nodes--;
            return true;
        }
    }else{
        return false;
        }
}


template<typename T>
bool LinkedList<T>::RemoveTail() {
    if(nodes > 0){ // check if list has elements
        if (head->next == nullptr){
            Node* node = tail;
            //cout << "Node: "  << node->data << endl;
            delete node;
            tail = nullptr;
            head = nullptr;
            //cout << "New Tail: " << tail->data << endl;
            //cout << "After Tail: " << tail->next->data << endl;
            nodes--;
            return true;
        }else{
            Node* node = tail->prev;
            //cout << "Node: "  << node->data << endl;
            delete tail;
            tail = node;
            tail->next = nullptr;
            //cout << "New Tail: " << tail->data << endl;
            //cout << "After Tail: " << tail->next->data << endl;
            nodes--;
            return true;
        }
    }else{
        return false;
    }
}

// Operators

template<typename T>
T &LinkedList<T>::operator[](unsigned int index) {
    if(index > (nodes - 1)){
        throw out_of_range("Index larger than Linked List");
    }
    else{
        Node* node = head;
        for(unsigned int i = 0; i <= index; i++){
            node = node->next;
        }
        return node->data;
    }
}

template<typename T>
const T &LinkedList<T>::operator[](unsigned int index) const {
    if(index > (nodes - 1)){
        throw out_of_range("Index larger than Linked List");
    }
    else{
        Node* node = head;
        for(unsigned int i = 0; i <= index; i++){
            node = node->next;
        }
        return node->data;
    }
}

template<typename T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs) {
    // delete any nodes that may already exist
    Node* current = head;
    while (current) {
        head = head->next;
        delete current;
        current = head;
    }

    nodes = 0;
    head = nullptr;
    tail = nullptr;
    for (unsigned int i = 0; i < rhs.nodes; ++i) {
        AddTail(rhs[i]);
    }
    return *this;
}

template<typename T>
bool LinkedList<T>::operator==(const LinkedList<T> &rhs) const {
    if(nodes != rhs.NodeCount()){ // check if the number of nodes are equal
        cout << nodes;
        cout << rhs.NodeCount();
        return false;
    }
    Node* node = head;
    for (unsigned int i = 0; i < nodes; ++i) { // traverse through linked list
        cout << node->data;
        cout << i;
        cout << rhs.GetNode(i)->data;
        if(node->data != rhs.GetNode(i)->data){ // if nodes are not equal
            return false; // return false
        }
        node = node->next; // move to next node
    }
    return true; // if all nodes are equal, return true
}


// Construction / Destruction

template<typename T>
LinkedList<T>::~LinkedList() {
    Node* node = head;
    Node* nextNode;
    while(node != nullptr){
        nextNode = node->next;
        delete node;
        node = nextNode;
    }
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &list) {
    nodes = 0;
    head = nullptr;
    tail = nullptr;
    for (unsigned int i = 0; i < list.nodes; ++i) {
        AddTail(list[i]);
    }
}

template<typename T>
LinkedList<T>::LinkedList() {
    this->nodes = 0;
    this->head = nullptr;
    this->tail = nullptr;
}

// Behaviors

template<typename T>
void LinkedList<T>::PrintReverse() const {
    Node* currentNode = tail;
    while(currentNode != nullptr){
        cout << currentNode->data << endl;
        currentNode = currentNode->prev;
    }
}

template<typename T>
void LinkedList<T>::PrintForward() const {
    //cout << "Printing Forward" << endl;
    Node* currentNode = head;
    while(currentNode != nullptr){
        cout << currentNode->data << endl;
        currentNode = currentNode->next;
    }
}

template<typename T>
void LinkedList<T>::PrintForwardRecursive(const LinkedList::Node *node) const {
    if (node != nullptr){
        cout << node->data << endl;
        PrintForwardRecursive(node->next);
    }
}

template<typename T>
void LinkedList<T>::PrintReverseRecursive(const LinkedList::Node *node) const {
    if (node != nullptr){
        cout << node->data << endl;
        PrintReverseRecursive(node->prev);
    }
}

// Accessors

template<typename T>
typename LinkedList<T>::Node *LinkedList<T>::GetNode(unsigned int index) {
    if(index > (nodes-1)){
        throw out_of_range("Index larger than Linked List");
    }
    else{
        Node* node = head;
        for(unsigned int i = 0; i < index; i++){
            node = node->next;
        }
        return node;
    }
}

template<typename T>
const typename LinkedList<T>::Node *LinkedList<T>::GetNode(unsigned int index) const {
    if(index > (nodes - 1)){
        throw out_of_range("Index larger than Linked List");
    }
    else{
        Node* node = head;
        for(unsigned int i = 0; i < index; i++){
            node = node->next;
        }
        return node;
    }
}

template<typename T>
const typename LinkedList<T>::Node *LinkedList<T>::Tail() const {
    return tail;
}

template<typename T>
typename LinkedList<T>::Node *LinkedList<T>::Tail() {
    return tail;
}

template<typename T>
const typename LinkedList<T>::Node *LinkedList<T>::Head() const {
    return head;
}

template<typename T>
typename LinkedList<T>::Node *LinkedList<T>::Head() {
    return head;
}

template<typename T>
unsigned int LinkedList<T>::NodeCount() const {
    return nodes;
}


template<typename T>
void LinkedList<T>::FindAll(vector<Node *> &outData, const T &value) const {
    Node* node = head;
    for(unsigned int i = 0; i < nodes; i++){
        if (node->data == value){
            outData.push_back(node);
            node = node->next;
        }
        else{
            node = node->next;
        }
    }
}

template<typename T>
const typename LinkedList<T>::Node *LinkedList<T>::Find(const T &data) const {
    Node* node = head;
    for(unsigned int i = 0; i < nodes; i++){
        if (node->data == data){
            return node;
        }
        else{
            node = node->next;
        }
    }
    return nullptr;
}

template<typename T>
typename LinkedList<T>::Node *LinkedList<T>::Find(const T &data) {
    Node* node = head;
    for(unsigned int i = 0; i < nodes; i++){
        if (node->data == data){
            return node;
        }
        else{
            node = node->next;
        }
    }
    return nullptr;
}

// Insertion

template<typename T>
void LinkedList<T>::AddNodesTail(const T *data, unsigned int count) {
    for (unsigned int i = 0; i < count; i++) {
        AddTail(data[i]);
    }
}

template<typename T>
void LinkedList<T>::AddNodesHead(const T *data, unsigned int count) {
    for (unsigned int i = 1; i < count+1; i++) {
        AddHead(data[count-i]);
    }

}

template<typename T>
void LinkedList<T>::AddTail(const T &data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = nullptr;
    if(tail == nullptr){
        head = newNode;
        tail = newNode;
        //cout << "Here" << endl;
    }
    else{
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
        //cout << "Here 1" << endl;
    }
    nodes ++;
    //cout << "Tail Added: " << tail->data << endl;
}

template<typename T>
void LinkedList<T>::AddHead(const T &data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = head;
    if(head == nullptr){
        head = newNode;
        tail = newNode;
    }
    else{
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    nodes++;
}

template<typename T>
void LinkedList<T>::InsertAfter(LinkedList::Node *node, const T &data) {
    Node* insert = new Node;
    insert->data = data;

    insert->next = node->next;
    insert->prev = node;

    node->next = insert;
    node = node->next->next;
    node->prev = insert;
    nodes++;
}


template<typename T>
void LinkedList<T>::InsertBefore(LinkedList::Node *node, const T &data) {
    Node* insert = new Node;
    insert->data = data;

    insert->next = node;
    insert->prev = node->prev;

    node->prev = insert;
    node = node->prev->prev;
    node->next = insert;
    nodes++;
}

template<typename T>
void LinkedList<T>::InsertAt(const T &data, unsigned int index) {
    if (index > nodes){
        throw out_of_range("Index is out of range");
    }
    else if(index == 0){ // if inserted at head
        //cout << "head" << endl;
        Node* insert = new Node;
        insert->data = data;
        nodes++;

        head->prev = insert;
        insert->prev = nullptr;
        insert->next = head;
        head = insert;
    }
    else if(index == nodes){ // if inserted at tail
        //cout << "tail" << endl;
        Node* insert = new Node;
        insert->data = data;
        nodes++;

        tail->next = insert;
        insert->prev = tail;
        insert->next = nullptr;
        tail = insert;
    }
    else{ // if inserted elsewhere in list
        //cout << "index: " << index << endl;
        Node* insert = new Node;
        insert->data = data;
        //cout << "insert: " << insert->data << endl;


        Node* search = head;
        //cout << search->data << endl;
        for (unsigned int i = 0; i < index; ++i) {
            search = search->next;
        }
        insert->prev = search->prev;
        insert->next = search;

        search->prev = insert;
        search = search->prev->prev;
        search->next = insert;

        nodes++;
    }
}