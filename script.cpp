#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "script.h"



Script::Script(std::string &line) {
	std::string priority_string;
	std::istringstream lineStream(line);
	std::getline(lineStream.ignore(1,'('), this->script_name, ',');
	std::getline(lineStream, priority_string, ',');
	this->priority = std::stoi(priority_string);
	std::getline(lineStream.ignore(1,' '), this->input, ',');
	std::getline(lineStream.ignore(1,' '), this->outputFile, ',');
	std::getline(lineStream.ignore(1,','), this->code, ')');
	this->is_dummy = false;
}

Script::Script(bool dummy) {
	this->is_dummy = true;
}