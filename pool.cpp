#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue> 
#include <vector>
#include <thread>

#include "heap.h"
#include "pool.h"
#include "interpreter.h"


Pool::Pool(int size, Heap &heap) : size_pool(size), queue(heap) {
	this->run = true;
	for (int i = 0; i < this->size_pool; ++i){
		this->threads.push_back(std::thread(&Pool::execute, this));
	}
}
	
void Pool::execute() {
	while (this->run) {
		Script s = this->queue.pop();
		if (s.is_dummy) {
			break;
		}
		Interpreter interpreter(s);
		interpreter.execute();
	}
}

Pool::~Pool() {
	this->queue.unblock();
	//this->run = false;
	for (int i = 0; i < this->size_pool; ++i) 
		this->threads[i].join();
}
