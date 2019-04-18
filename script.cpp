#include <string>
#include "script.h"

using namespace std;

Script::Script(string s1, int p, string s2, string s3, 
	string s4) : script_name(s1), priority(p), input(s2), outputFile(s3), code(s4) { 
} 
