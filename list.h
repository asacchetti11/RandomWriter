// list.h					
/*******************************
Assignment:  Build the list data structure described herein. *******************************/	
#include <cstdlib>
#include <iostream>

typedef int ldata;

struct lnode{
    ldata data;
    lnode * next;
    lnode * prev;
    
    lnode();  //empty node with NULL prev & next
    lnode(lnode* p, lnode* n);  // create node w/ given prev and next pointers
    lnode(lnode* p, const ldata & d, lnode * n);	// or all 3. 
};

class list{
private:    

    // data fields:
    mutable lnode* curr;   //points to a node in the list beyond 
      //the front sentinel
    mutable size_t currIndex; //corresponds to current.

    void _init();              //for use in constructor, overloaded
    void _copy(const list & orig); //equals, deep copy,
    void _destroy();           //and destructor

    size_t _size;
    lnode * front;
    lnode * rear;

  
    size_t _computeIndex(int index) const;
    // return the effective non-negative index  

    void _setCurrIndex(size_t index) const;
     // PRE: 0 <= index <= size()
     // POST: (1) current points to the node holding the element at 
     //        position index, or to the rear sentinel.
     //        (2) currIndex is index
     // This is accomplished as quickly as possible.  
     //(One of front, rear,
     // or current is closest to index.)   
      
public:
    
    list();
    // Create an empty doubly-linked list with front and rear sentinels,
    // current points to rear, and current_index = 0;
    
    
    ~list();
    // Delete all nodes (including the sentinels)    
    

    list(const list & orig);
     // Make a (deep) copy of a list.
    // currIndex and current can be set arbitrarily in the copy
                    
    list & operator=(const list & rhs);
     // Support list assignment, with deep copy.  Similarly, currIndex
     // and current are set arbitrarily.


  
    void add(const ldata & item, int index);
    // Insert a new element at a position (k) given by index.              
    //      If index is non-negative, k is index; otherwise
    //      k is size() + index.
    // PRE:  this list contains <v0, v1, ..., vk, ...>               
    //      0 <= k <= size()
    // POST: this list contains <v0, v1, ..., item, vk, ... >
     //        current points to new node containing item.          
     //        currIndex is k.                 
     // Guarantees constant time access to either end or vicinity of
     // currIndex.

           	 
 
    void removeAt(int index);
    // Remove an element from this list.
    // index indicates a position k in the manner described in (add).
    // Pre: 0 <= k < size()
    //      This list contains <v0, v1, ..., vk, v(k+1), ... >
    // Post: This list contains <v0, v1, ..., v(k+1), ... >  
    //       current points to v(k+1) (or the rear sentinel)
    // Guarantees constant time access to either end or vicinity of
    // currIndex.
    
    
    void remove(const ldata & item);
    // Let i be the smallest non-negative integer where get(i)==item.
    // Post: same as for removeAt(i)
    // If no such i exists, no change to the list. 
    
    
    size_t find(const ldata & item) const;
    // return smallest non-negative integer where get(i)==item,
    // or size() if no such integer  
    
    
    ldata get(int index) const;
    // index indicates a position k in the manner described in (add).
    // return the element at position k.
    // Guarantees constant time access to either end or vicinity of
    // currIndex.
    
     
    size_t size() const;
    // return the number of elements of the list
    // runs in constant time    
    
    
    void output(std::ostream & ostr) const;
    // output the list to ostr using format
    // <v0, v1, v2, ..., vn-1>   
};
