#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue> 
#include <vector>
#include <thread>
#include <mutex>           
#include <condition_variable>
#include "script.h"
#include "heap.h"


bool ComparePriority::operator()(const Script& s1, const Script& s2) {
	return s1.priority < s2.priority;
}	


Heap::Heap() {
	this->blocked = true;
}

void Heap::push(Script s) {
	std::unique_lock<std::mutex> lock(this->m);
	
	this->protected_queue.push(s);
    
    this->cond_var.notify_one();
}

bool Heap::empty() {
	std::unique_lock<std::mutex> lock(this->m);
	return protected_queue.empty();
}

Script Heap::pop() {
	std::unique_lock<std::mutex> lock(this->m);
	while (this->blocked) 
		this->cond_var.wait(lock);
	
	
	if (this->protected_queue.empty()) {
		Script dummy(true);
		return dummy;
	}

	Script first = this->protected_queue.top();

	this->protected_queue.pop();
	
	return first;
}

void Heap::unblock(){
	this->blocked = false;
	this->cond_var.notify_all();
}
