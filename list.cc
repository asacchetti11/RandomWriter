/*
list.cc
Alessandro Sacchetti
10/25/2018
"doubly linked list data structure"
dependencies: list.h
*/
#include "list.h"
#include <cstdlib>
#include <iostream>

using namespace std;


//---------------NODE FUNCTIONS---------------//
lnode::lnode(){
	prev = NULL;
	next = NULL;
}

lnode::lnode(lnode* p, lnode* n){
	prev = p;
	next = n;
}

lnode::lnode(lnode* p, const ldata & d, lnode * n){
	prev = p;
	next = n;
	data = d;
}

//---------------PRIVATE FUNCTIONS---------------//

void list::_init(){
	_size=0;
	front = new lnode();
	rear = new lnode();
	front->next=rear;
	rear->prev=front;

	curr = rear;
	currIndex = _size;
}

void list::_copy(const list & orig){
	//loop through orig 
	for(int i = 0; i<orig.size(); i++){
		add(orig.get(i),i);
	}

}

void list::_destroy(){
	while(front!=rear){//loops through the list until we are at rear
		front = front -> next;//move to the next node in the stack
		delete front->prev;//delete the prev node
	}
	delete rear;//rear doesnt have a node infront so we must just delete it

}

size_t list::_computeIndex(int index) const{
	if(index<0){
		return _size+index;
	}
	return index;
}

void list::_setCurrIndex(size_t index) const{//could be shorter - should do
	index = _computeIndex(index);

	//calculate distance from each index
	int dFront = index;
	int dCurr = currIndex - index; // if neg it is behind it

	bool dCurrInfront = dCurr>0;//true if index is infront of dCurr - also the variable that tells which way to go
	if(!dCurrInfront){//absolute value
		dCurr *= -1;
	}
	int dRear = _size - index;

	//cases: 
	if(dFront<=dRear and dFront<=dCurr){	//if index is closest to front
		//starts from front
		currIndex = 0;
		curr = front->next;
		dCurrInfront=false;

	}else if(dRear<=dFront and dRear<=dCurr){//if index is closest to rear
		currIndex = _size;
		curr = rear;
		dCurrInfront=true;
	}

	if(dCurrInfront){//backward
		while(curr!=front and index != currIndex){
			currIndex--;
			curr=curr->prev;
		}
	}else{//forward
		while(curr!=rear and index != currIndex){
			currIndex++;
			curr=curr->next;
		}
	}

	if(curr==front){
		curr=rear;
		currIndex=_size;
	}

}
 
//---------------PUBLIC FUNCTIONS---------------//
list::list(){
	_init();

}

list::~list(){
	_destroy();

}

list::list(const list & orig){
	_init();
	_copy(orig);

}

list & list::operator=(const list & rhs){
	_destroy();
	_init();
	_copy(rhs);
	return *this;
}

void list::add(const ldata & item, int index){

	if(index<0 and _size > 0){//makes it work with negative indices
		index = _computeIndex(index) + 1;
	}

	_setCurrIndex(index);


	lnode *val = new lnode();
	val -> data=item;

	//curr points to node next index */

	val->prev=curr->prev;
	val->next=curr;
	curr->prev->next=val;
	curr->prev=val;

	currIndex++;
	_size++;

}

void list::removeAt(int index){
	_setCurrIndex(index);
	lnode *temp = curr;
	curr = curr->next;
	currIndex++;

	temp->next->prev=temp->prev;
	temp->prev->next=temp->next;
	delete temp;
	_size--;
}

void list::remove(const ldata & item){
	int index = find(item);
	if(index!=_size)
		removeAt(index);
	
}

size_t list::find(const ldata & item) const{
	size_t index=0;
	lnode *temp = front->next;
	while(temp!=rear){
		if(temp->data==item){
			return index;
		}
		index++;
		temp = temp->next;
	}
	return _size;
}

ldata list::get(int index) const{
	_setCurrIndex(index);
	return curr->data;
}

size_t list::size() const{
	return _size;
}

void list::output(ostream & ostr) const{//wont use curr pointer because it would just always reset it to the back
	cout<<"< ";

	lnode *temp = front->next;
	while(temp != rear){//loops through the stack until the pointer is NULL

		cout << (*temp).data;

		if( (temp->next!=rear) ){//if it is not the last node
			cout<<", ";
		}
		temp = temp -> next;//move to the next node in the stack
		
	}
	cout<<" >"<<endl;
}