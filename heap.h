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
	std::priority_queue<Script, std::vector<Script>, 
								ComparePriority> protected_queue;
	std::mutex m;
	std::condition_variable cond_var;
	bool blocked;

	public:
	//Constructor
	Heap();

	//Encola en la queue.
	void push(Script s);

	void unblock();

	//Devuelve true en caso de encontrarse vacia la queue.
	//False en caso contrario.
	bool empty();

	//Desencola de la queue.
	Script pop();

	//~Heap();
};

#endif
