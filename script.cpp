#include <string>
#include "script.h"


Script::Script(std::string s1, int p, std::string s2, std::string s3, 
	std::string s4) : script_name(s1), priority(p), input(s2), outputFile(s3), code(s4) { 
} 
