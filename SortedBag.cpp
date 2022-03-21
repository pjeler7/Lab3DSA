#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <iostream>
using namespace std;

SortedBag::SortedBag(Relation r) {
	this->rel = r;
	this->capacity = 10;
	this->length = 0;

	this->head = -1;
	this->tail = -1;
	this->firstEmpty = 0;

	this->node = new Node[this->capacity];
	for (int i = 0; i < this->capacity - 1; i++) {
		this->node[i].next = i + 1;
	}
	for (int i = 1; i < this->capacity; i++) {
		this->node[i].prev = i - 1;
	}
	this->node[this->capacity - 1].next = -1;
	this->node[0].prev = -1;
}

//Total complexity: O(n)
void SortedBag::add(TComp e) {
	int current = this->head;
	while (current != -1 && this->rel(this->node[current].val, e) == true && this->node[current].val != e)
		current = this->node[current].next;

	if (current!=-1 && this->node[current].val == e) {
		this->node[current].frequency++;
		this->length++;
		return;
	}

	int pos = this->allocate();
	if (pos == -1) {
		this->resize();
		pos = this->allocate();
	} 

	if (this->head == -1 && this->tail == -1) {//empty
		//int pos = this->firstEmpty;
		//this->firstEmpty = this->node[this->firstEmpty].next;
		this->node[pos].val = e;
		this->node[pos].frequency = 1;
		this->head = pos;
		this->tail = this->head;
		this->length++;
		return;
	}

	else if (current == this->head) {
		this->node[pos].val = e;
		this->node[pos].frequency = 1;
		this->node[current].prev = pos;
		this->node[pos].next = this->head;
		this->head = pos;
		this->length++;
	}
	else if (current != -1) {
		int prev = this->node[current].prev;
		this->node[pos].val = e;
		this->node[pos].frequency = 1;
		this->node[pos].prev = prev;
		this->node[pos].next = current;
		this->node[current].prev = pos;
		this->node[prev].next = pos;
		this->length++;
	}
	else if (current == -1) {
		this->node[pos].val = e;
		this->node[pos].frequency = 1;
		this->node[this->tail].next = pos;
		this->node[pos].prev = this->tail;
		this->tail = pos;
		this->node[this->tail].next = -1;
		this->length++;
	}
}

//Total complexity: O(n)
bool SortedBag::remove(TComp e) {
	if (this->head == -1 && this->tail == -1)
		return false;

	int current = this->head;

	if (this->head == this->tail && this->node[head].val == e) {
		if (this->node[head].frequency > 1) {
			this->node[head].frequency--;
			this->length--;
			return true;
		}
		else {
			this->node[this->head].next = firstEmpty;
			this->node[this->head].prev = -1;

			this->firstEmpty = this->head;
			this->head = this->tail = -1;
			this->length--;
			return true;
		}
	}

	if (this->node[this->head].val == e) {
		if (this->node[this->head].frequency > 1) {
			this->node[this->head].frequency--;
			this->length--;
			return true;
		}
		else {
			this->node[this->node[this->head].next].prev = -1;

			int aux = this->node[this->head].next;

			this->node[this->head].next = firstEmpty;
			this->node[this->head].prev = -1;

			this->firstEmpty = this->head;
			this->head = aux;
			this->length--;
			return true;
		}
	}

	while (current != -1 && this->node[current].val != e)
		current = this->node[current].next;

	if (current == -1)
		return false;

	if (current == this->tail) {
		if (this->node[current].frequency > 1) {
			this->node[current].frequency--;
			this->length--;
			return true;
		}
		else {
			this->node[this->node[this->tail].prev].next = -1;

			int aux = this->node[this->tail].prev;

			this->node[this->tail].next = firstEmpty;
			this->node[this->tail].prev = -1;

			this->firstEmpty = this->tail;
			this->tail = aux;
			this->length--;
			return true;
		}
	}
	else {
		if (this->node[current].frequency > 1) {
			this->node[current].frequency--;
			this->length--;
			return true;
		}
		else {
			int next = this->node[current].next;
			int prev = this->node[current].prev;
			this->node[prev].next = next;
			this->node[next].prev = prev;

			this->node[current].next = firstEmpty;
			this->node[current].prev = -1;

			this->firstEmpty = current;
			this->length--;
			return true;
		}
	}
}

//Total complexity: O(n)
bool SortedBag::search(TComp elem) const {
	int current = this->head;
	while (current != -1 && this->node[current].val != elem)
		current = this->node[current].next;
	if (current != -1)
		return true;
	else
		return false;
}

//Total complexity: O(n)
int SortedBag::nrOccurrences(TComp elem) const {
	int current = this->head;
	int nr = 0;

	while (current != -1) {
		if (this->node[current].val == elem)
			return this->node[current].frequency;
		current = this->node[current].next;
	}
	return 0;
}

//Total complexity:Theta(1)
int SortedBag::size() const {
	return this->length;
}

//Total complexity:Theta(1)
bool SortedBag::isEmpty() const {
	return this->length == 0;
}


//Total complexity: Theta(1)
int SortedBag::allocate()
{
	int newElem = this->firstEmpty;
	if (newElem != -1) {
		this->firstEmpty = this->node[this->firstEmpty].next;
		if (this->firstEmpty != -1) {
			this->node[this->firstEmpty].prev = -1;
		}
		this->node[newElem].next = -1;
		this->node[newElem].prev = -1;
	}
	return newElem;
}

//Total complexity:Theta(1)
void SortedBag::free(int poz)
{

	/*if (poz == 0)
		this->head = this->node[this->head].next;
	if (poz == this->tail)
		this->tail = this->node[this->tail].prev;*/
	this->node[poz].next = this->firstEmpty;
	this->node[poz].prev = -1;
	if (this->firstEmpty != -1)
		this->node[this->firstEmpty].prev = poz;
	this->firstEmpty = poz;
}

//Total complexity:O(1)
//void SortedBag::resize()
//{
//	this->capacity *= 2;
//	Node* aux = new Node[this->capacity];
//	for (int i = 0; i < this->length; i++)
//		aux[i] = this->node[i];
//	//	delete[] this->node;
//	this->node = aux;
//	for (int i = length; i < this->capacity; i++) {
//		this->node[i].next = i + 1;
//		this->node[i].prev = i - 1;
//	}
//	this->node[this->capacity - 1].next = -1;
//	this->firstEmpty = this->length;
//}

void SortedBag::resize() {
	Node* newElems = new Node[this->capacity * 2];
	//make copy of initial elements
	for (int i = 0; i < this->capacity; i++) {
		newElems[i] = this->node[i];
	}
	for (int i = this->capacity; i < this->capacity * 2 - 1; i++) {
		newElems[i].next = i + 1;
	}
	newElems[2 * this->capacity - 1].next = -1;
	for (int i = this->capacity + 1; i < this->capacity * 2; i++) {
		newElems[i].prev = i - 1;
	}
	newElems[this->capacity].prev = -1;
	this->firstEmpty = this->capacity;
	this->capacity *= 2;
	//delete[] this->node;
	this->node = newElems;
}

//Total complexity: Theta(1)
SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}


SortedBag::~SortedBag() {
//	delete[] this->node;
}

void SortedBag::printN()
{//Total complexity:O(n)
	for (int i = 0; i < this->capacity; i++) {
		cout << this->node[i].val << "->" << this->node[i].frequency << "   ";
	}
	cout << endl;
	for (int i = 0; i < this->capacity; i++) {
		cout << this->node[i].next << "  ";
	}
	cout << endl;
	for (int i = 0; i < this->capacity; i++) {
		cout << this->node[i].prev << "  ";
	}
	cout << endl;
	cout << this->head << endl << this->tail << endl;
}
