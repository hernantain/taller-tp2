#ifndef SCRIPT_H
#define SCRIPT_H

#include <string>

using namespace std;

//Clase script para cuando es necesario leer de stdin varias ordenes
//Contiene el nombre del script, el archivo del cual debe leer de stdin
//El archivo al cual debe escribir, la prioridad del archivo y el codigo
//brainfuck correspondiente
class Script {
	public:
	string script_name;
	int priority;
	string input;
	string outputFile;
	string code;

	//Constructor de la clase.
	Script(string s1, int p, string s2, string s3, string s4);

};

#endif
