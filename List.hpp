#ifndef LIST_HPP
#define LIST_HPP
/* List.hpp
 *
 * doubly-linked, double-ended list with Iterator interface
 * EECS 280 Project 4
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

// Default constructor
List() : first(nullptr), last(nullptr), size_(0) {}

// Destructor: Cleans up all dynamically allocated memory.
~List() {
        clear();
    }

// Copy Constructor: Creates a deep copy of another List.
List(const List<T>& other) : first(nullptr), last(nullptr), size_(0){
    copy_all(other);
  }

 // Copy Assignment Operator: Replaces current contents with a deep copy of another List.
List<T>& operator=(const List<T>& other) {
        if (this != &other) {
            clear();
            copy_all(other);
        }
        return *this;
    }

  
  //EFFECTS:  returns true if the list is empty
  bool empty() const{
    return first == nullptr;
  }

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow.  Instead, keep track of the size
  //         with a private member variable.  That's how std::list does it.
  int size() const {
    return size_;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T & front(){
    
    assert(!empty());
    return first->datum;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back(){
    assert(!empty());
    return last->datum;
  }

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum){
    Node *p = new Node;
    p->datum = datum;
    p->next = first;
    p->prev = nullptr;
    if (empty()) {
        last = p;  
    } else {
        first->prev = p; 
    }
    first = p;
    size_++;
  }

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum){
    Node *p = new Node;
    p->datum = datum;
    p->next = nullptr;
    p->prev = last;
    if (empty()){
      first = last = p;
    } else{
      last->next = p;
    }
    last = p;
    size_++;
    

  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
  void pop_front(){
    assert(!empty());

    Node *temp = first;
    if (first == last) {
        first = last = nullptr; 
    } else {
      first = first->next;
      first->prev = nullptr;
    }
    delete temp;
    size_--;



  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
  void pop_back(){
    assert(!empty());
    if (first == last) {
        delete last;
        first = last = nullptr; 
    } else {
      Node *temp = last;
      last = last-> prev;
      last->next = nullptr;
      delete temp;
    }
    size_--;
    
    
    
  }

  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
  void clear(){

    while (!empty()) {
      pop_front();
    }
      

  }

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you can omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists

private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other){
    assert(empty());
    
    for (Node *node_ptr = other.first; node_ptr; node_ptr = node_ptr->next) {
      push_back(node_ptr->datum);
    } 

  }

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty
  int size_;
public:
  ////////////////////////////////////////
  class Iterator {

    Iterator()
    : node_ptr(nullptr){}


    
    //OVERVIEW: Iterator interface to List

    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators: *,
    // ++ (prefix), default constructor, == and !=.

  public:
    // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.

    T& operator*() const {
      assert(node_ptr);
      return node_ptr->datum;
    }

    Iterator& operator++() {
      assert(node_ptr);
      node_ptr = node_ptr->next;
      return *this;
    }

    bool operator==(const Iterator& rhs) const {
      return node_ptr == rhs.node_ptr;
    }
    bool operator!=(const Iterator& rhs) const {
      return node_ptr != rhs.node_ptr;
    }

    Iterator& operator--() {
      assert(node_ptr);
      node_ptr = node_ptr->prev;
      return *this;
    }

  private:
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here

    // add any friend declarations here
    friend class List;

    // construct an Iterator at a specific position
    Iterator(Node *p)
    : node_ptr(p) {}

    

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const {
    return Iterator(first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const {
    return Iterator();
  }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
  void erase(Iterator i){
    assert(i != end());
    Node *remove = i.node_ptr;

    if (remove->prev) {
        remove->prev->next = remove->next;
    } else {
        first = remove->next; // If removing the first element
    }

    if (remove->next) {
        remove->next->prev = remove->prev;
    } else {
        last = remove->prev; // If removing the last element
    }
    delete remove;
    size_--;




      
    
  }


  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
  void insert(Iterator i, const T &datum){

    assert(i != end());

    Node *add = new Node;
    add->datum = datum;

    Node *now = i.node_ptr;

    add->next = now;
    add->prev = now->prev;

    if (now->prev) {
      now->prev->next = add;
    }else{
      first = add;
    }
    now->prev = add;
    size_++;




  }

};//List



////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.


#endif // Do not remove this. Write all your code above this line.