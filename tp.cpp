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
#include "script.h"
#include "heap.h"
#include "pool.h"
#include "interpreter.h"


#define INTERPRETER "interprete"
#define POOL "thread-pool"
#define EXACT_ARGS 3
#define COMMAND_LINE_ERROR 2
#define MODE_ARG 1
#define FILE_ARG 2
#define NUMBER_THREADS 2

int main(int argc, char *argv[]) {
	if (argc != EXACT_ARGS)
		return COMMAND_LINE_ERROR;

	std::string mode = argv[MODE_ARG] ;
	if (mode == POOL) {
		unsigned int num_threads = std::stoi(argv[NUMBER_THREADS]);
		Heap h;
		Pool p(num_threads, h);
		for (std::string line; getline(std::cin, line);) {
			h.push(Script(line)); 
		}


	} else if (mode == INTERPRETER){
		std::ifstream file(argv[FILE_ARG]);
		std::stringstream script;
		script << file.rdbuf();
		Interpreter interpreter(script.str());
		interpreter.execute();
	}

	return 0;

}
