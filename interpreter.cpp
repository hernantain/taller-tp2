#include <string>
#include <iostream>
#include <fstream>
#include <stack>
#include <streambuf>
#include <sstream>
#include <vector>

#include "interpreter.h"
#include "script.h"

#define MEMORY_SIZE 150
#define ZERO 0


Interpreter::Interpreter(std::string &commands) : memory(MEMORY_SIZE, ZERO),
												  script(commands) {
	this->mem_idx = ZERO;
	this->script_idx = ZERO;
}


Interpreter::Interpreter(Script &s) : memory(MEMORY_SIZE, ZERO), 
									  script(s.code) {
	this->mem_idx = ZERO;
	this->script_idx = ZERO;
	this->input_file.open(s.input);
	this->output_file.open(s.outputFile);
}

void Interpreter::decrement_pointer() {
	this->mem_idx--;
}

void Interpreter::increment_pointer() {
	this->mem_idx++;
}

void Interpreter::decrement_byte() {
	this->memory[this->mem_idx]--;
}

void Interpreter::increment_byte() {
	this->memory[this->mem_idx]++;
}

void Interpreter::print() {
	if (this->output_file.is_open()) {
		this->output_file << this->memory[this->mem_idx];
	} else {
		std::cout << this->memory[this->mem_idx];
	}
}

void Interpreter::read() {
	if (this->input_file.is_open()) {
		this->input_file >> std::noskipws >> this->memory[this->mem_idx];
	} else { 
		std::cin >> std::noskipws >> this->memory[this->mem_idx];
	}
}

void Interpreter::search_close_bracket() {
	int open_brackets = 1;
	do {
		this->script_idx++;
		if (this->script[this->script_idx] == '[') {
			open_brackets++;
		} else if (this->script[this->script_idx] == ']') {
			open_brackets--;
		}
	} while ( open_brackets != 0 );
}

void Interpreter::start_while() {
	if (this->memory[this->mem_idx] == ZERO) {
		this->search_close_bracket();
	} else {
		this->open_brackets.push(this->script_idx); 
	}
}

void Interpreter::end_while() {
	int idx = this->open_brackets.top();
	this->open_brackets.pop();
	this->script_idx = idx - 1;
}

void Interpreter::process(char c) {
	switch(c) {
		case '<':
			this->decrement_pointer();
			break;
		case '>':
			this->increment_pointer();
			break;
		case '+':
			this->increment_byte();
			break;
		case '-':
			this->decrement_byte();
			break;
		case '.':
			this->print();
			break;
		case ',':
			this->read();
			break;
		case '[':
			this->start_while();
			break;
		case ']':
			this->end_while();
			break;
	}
	this->script_idx++;
}

void Interpreter::execute() {
	char inst = 0;
	while(this->script_idx < this->script.size()) {
		inst = this->script[this->script_idx];
		this->process(inst);
	}
}

