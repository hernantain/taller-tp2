#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue> 
#include <vector>
#include <thread>
#include <mutex>    
#include <atomic>          
#include <condition_variable>
#include "heap.h"
#include "pool.h"
#include "interpreter.h"


Pool::Pool(int size, 
	Heap &heap,
	std::mutex &m,
	std::condition_variable &cond_var) : size_pool(size), queue(heap), m(m), cond_var(cond_var) {
	
	this->run = true;
	for (int i = 0; i < this->size_pool; ++i){
		this->threads.push_back(std::thread(&Pool::execute, this));
	}
}
	
void Pool::execute() {
	std::unique_lock<std::mutex> lock(m);
	while (this->run) {
		cond_var.wait(lock);

		if (this->queue.empty()){
			break;
		}
		
		while (!this->queue.empty()) {
			Script s = this->queue.get_first();
			Interpreter interpreter(s);
			interpreter.execute();
		}
	}
}

Pool::~Pool() {
	this->run = false;
	cond_var.notify_all();
	for (int i = 0; i < this->size_pool; ++i) 
		this->threads[i].join();
}
