#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <iostream>
#include "ShortTest.h"
#include "ExtendedTest.h"
#include <cassert>

using namespace std;

bool relation10(TComp e1, TComp e2) {
	return e1 <= e2;
}
void testExtra() {
	SortedBag sb(relation10);
	sb.add(1);
	sb.add(2);
	sb.add(4);
	sb.add(3);
	sb.add(0);
	SortedBagIterator it = sb.iterator();
	try {
		it.jumpBackward(2);
		assert(false);
	}
	catch(exception&){
		assert(true);
	}
	try {
		it.jumpBackward(-2);
		assert(false);
	}
	catch (exception&) {
		assert(true);
	}
	try {
		it.jumpBackward(1);
		assert(false);
	}
	catch (exception&) {
		assert(true);
	}
	it.next();
	it.next();
	it.next();
	it.next();
	assert(it.getCurrent() == 4);
	it.jumpBackward(1);
	assert(it.getCurrent() == 3);
	it.jumpBackward(2);
	assert(it.getCurrent() == 1);
	try {
		it.jumpBackward(2);
		assert(false);
	}
	catch (exception&) {
		assert(true);
	}
}

void testLong() {
	SortedBag sb(relation10);
	int i = 0;
	while (i < 100) {
		sb.add(i);
		i++;
	}
	i = 0;
	SortedBagIterator it = sb.iterator();
	while (i>98) {
		assert(it.getCurrent() == i);
		i++;
		it.next();
	}
	while (i > 0) {
		assert(it.getCurrent() == i);
		i--;
		it.jumpBackward(1);
	}
}


int main() {
	testAll();
	testAllExtended();
	testExtra();
	testLong();

	cout << "Test over" << endl;
	system("pause");
}
