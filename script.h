#ifndef SCRIPT_H
#define SCRIPT_H

#include <string>

//Clase script para cuando es necesario leer de stdin varias ordenes
//Contiene el nombre del script, el archivo del cual debe leer de stdin
//El archivo al cual debe escribir, la prioridad del archivo y el codigo
//brainfuck correspondiente
class Script {
	public:
	std::string script_name;
	int priority;
	std::string input;
	std::string outputFile;
	std::string code;
	bool is_dummy;

	//Constructor de la clase.
	explicit Script(std::string &line);

	explicit Script(bool dummy);
};
#endif
