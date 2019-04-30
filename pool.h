#ifndef POOL_H
#define POOL_H

#include <vector>

//Clase utilizada para el pool de threads
class Pool {
	int size_pool;
	Heap &queue;
	std::vector<std::thread> threads;
	bool run;
	//std::mutex &m;
	//std::condition_variable &cond_var;

	public:
	//Constructor que recibe el tamano del pool
	//Una referencia a la cola de prioridad
	//Y referencias a un objeto mutex y una CV para el manejo de threading.
	//Pool(int size, Heap &heap, std::mutex &m, std::condition_variable &cond_var);
	Pool(int size, Heap &heap);
 	
 	//"Lanza" el pool
	void execute();

	//Destructor del Pool.
	~Pool();
};
#endif
