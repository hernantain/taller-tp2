#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stack>
#include <streambuf>
#include <sstream>
#include <vector>
#include "script.h"

using namespace std;

//Clase utilizada para interpretar scripts de brainfuck
class Interpreter {
	private:
	vector<char> memory;
	stack <unsigned int> open_brackets;
	ofstream output_file;
	ifstream input_file;
	string script;
	unsigned int mem_idx, script_idx;

	//Inicializa un vector de memoria en 0s.
	void initiate_memory();

	//Mueve el puntero una posicion menos (izq)
	void decrement_pointer();

	//Mueve el puntero una posicion mas (der)
	void increment_pointer();

	//Incrementa el byte apuntado por el puntero
	void decrement_byte();

	//Decrementa el byte apuntado por el puntero
	void increment_byte();

	//Imprime por pantalla o al archivo pasado por parametro
	void print();

	//Lee de stdin o por el archivo pasado por parametro
	void read();

	//Busca el ']' correspondiente
	void search_close_bracket();

	//Comienza un while de brainfuck
	void start_while();

	//Vuelve al '[' corrrespondiente
	void end_while();

	//Lee una instruccion de brainfuck y redirecciona su ejecucion a la
	//funcion correspondiente. Luego aumenta el puntero del script.
	void process(char c);

	public:

	//Constructor del interprete en modo interprete
	Interpreter(string commands);

	//Constructor del interprete en modo thread-pool
	explicit Interpreter(Script s);

	//"Lanza" el interprete
	void execute();

	//Destructor
	~Interpreter();
};

#endif