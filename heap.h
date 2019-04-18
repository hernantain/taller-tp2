#ifndef HEAP_H
#define HEAP_H

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

using namespace std;

//Clase utilizada sobrecargando el operador '()' para 
//luego pasarle al heap y que ordene segun prioridad de la clase 'Script'
class ComparePriority {

public:
	bool operator()(const Script& s1, const Script& s2);
};

//Clase Heap para la cola de prioridad de los archivos a ejecutar
//Contiene una priority queue (STL de c++) y referencias
//a objjetos mutex y condition variable para el manejo de threading.
class Heap {
	priority_queue<Script, vector<Script>, ComparePriority> queue;
	mutex &m;
	condition_variable &cond_var;

	public:

	//Constructor
	Heap(mutex &m, condition_variable &cond_var);

	//Encola en la queue.
	void add(Script s);

	//Devuelve true en caso de encontrarse vacia la queue.
	//False en caso contrario.
	bool empty();

	//Desencola de la queue.
	Script get_first();
};

#endif
