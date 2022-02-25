/*
 * Net2.cpp
 *
 *  Created on: Dec 5, 2017
 *      Author: jgoeders
 */

#include <cassert>

#include "Net.h"
#include "Block.h"
#include "Design.h"

using namespace std;

Net::Net(int idx) :
		idx(idx) {
	// TODO Auto-generated constructor stub

}

Net::~Net() {
	// TODO Auto-generated destructor stub
}

void Net::addBlock(Block* block) {
//	assert(blocks.find(block) == blocks.end());
	blocks.push_back(block);
}

