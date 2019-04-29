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

	string mode = argv[MODE_ARG] ;
	if (mode == POOL) {
		unsigned int num_threads = stoi(argv[NUMBER_THREADS]);
		string script_name, priority, input, outputFile, code;
		condition_variable cv;
		mutex m;
		Heap h(m, cv);
		Pool p(num_threads, h, m, cv);

		for (string line; getline(cin, line);) {
			istringstream lineStream(line);
			getline(lineStream.ignore(1,'('), script_name, ',');
			getline(lineStream, priority, ',');
			getline(lineStream.ignore(1,' '), input, ',');
			getline(lineStream.ignore(1,' '), outputFile, ',');
			getline(lineStream.ignore(1,','), code, ')');
			h.add(Script(script_name, stoi(priority), input, outputFile, code)); 
		}

	} else if (mode == INTERPRETER){
		ifstream file;

		file.open(argv[FILE_ARG]);
		stringstream script;
		script << file.rdbuf();

		Interpreter interpreter(script.str());
		interpreter.execute();
	}

	return 0;

}
