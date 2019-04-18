#ifndef POOL_H
#define POOL_H

//Clase utilizada para el pool de threads
class Pool {
	int size_pool;
	Heap &queue;
	vector<thread> threads;
	bool run;
	mutex &m;
	condition_variable &cond_var;

	public:

	//Constructor que recibe el tamano del pool
	//Una referencia a la cola de prioridad
	//Y referencias a un objeto mutex y una CV para el manejo de threading.
	Pool(int size, Heap &heap, mutex &m, condition_variable &cond_var);
 	
 	//"Lanza" el pool
	void execute();

	//Destructor del Pool.
	~Pool();

};

#endif
