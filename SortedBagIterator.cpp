#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

//Theta(1)
SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	this->currentElement = b.head;
	this->currentFrequency = 1;
	this->count = 1;
}

//Theta(1)
TComp SortedBagIterator::getCurrent() {
	if (this->currentElement == -1)
		throw exception();
	return bag.node[this->currentElement].val;
}

//Theta(1)
bool SortedBagIterator::valid() {
	if (this->currentElement == -1)
		return false;
	return true;
}

//Theta(1)
void SortedBagIterator::next() {
	if (this->currentElement == -1)
		throw exception();
	if (this->bag.node[currentElement].frequency > this->currentFrequency) {
		this->currentFrequency += 1;
	}
	else {
		this->currentElement = bag.node[currentElement].next;
		this->currentFrequency = 1;
	}
	this->count++;
}

//Theta(1)
void SortedBagIterator::first() {
	this->currentElement = bag.head;
	this->currentFrequency = 1;
	this->count = 1;
}

//moves the current element from the iterator k steps backward, or makes the iterator invalid if there are less than k elements left until the beginning of the SortedBag.
//throws an exception if the iterator is invalid or k is negative or zero
//Total complexity: O(k)
void SortedBagIterator::jumpBackward(int k)
{
	if (k < 0 || k >= count)
		throw exception();

	while (k) {
		if (this->currentFrequency > 1) {
			this->currentFrequency -= 1;
		}
		else {
			this->currentElement = bag.node[currentElement].prev;
			this->currentFrequency = bag.node[currentElement].frequency;
		}
		this->count--;
		k--;
	}
}

