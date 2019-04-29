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

using namespace std;


bool ComparePriority::operator()(const Script& s1, const Script& s2) {
	return s1.priority < s2.priority;
}	


Heap::Heap(std::mutex &m, std::condition_variable &cond_var) : m(m), cond_var(cond_var) {}

void Heap::add(Script s) {
	std::unique_lock<std::mutex> lock(m);
	this->queue.push(s);
	//lock.unlock();
    cond_var.notify_one();
    //lock.lock();
}

bool Heap::empty() {
	return queue.empty();
}

Script Heap::get_first() {
	// Notify all tiene que ir aca, igual que el run
	Script first = this->queue.top();
	this->queue.pop();
	return first;
}


