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

	//Constructor de la clase.
	Script(std::string s1, int p, std::string s2, std::string s3,
												 std::string s4);

};

#endif
