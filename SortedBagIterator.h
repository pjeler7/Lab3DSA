#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	SortedBagIterator(const SortedBag& b);
	int currentElement;
	int currentFrequency;
	int count;
	

public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();
	//moves the current element from the iterator k steps backward, or makes the iterator invalid if there are less than k elements left until the beginning of the SortedBag.
	//throws an exception if the iterator is invalid or k is negative or zero
	void jumpBackward(int k);

};

