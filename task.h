#pragma once
#include <iostream>
#include <cstring>
#include <fstream>

class Task {
	public:
		Task();
		char * getString(std::ifstream& input);
    		int day;
    		char * task_name;
    		int duration;
    		char * crew_name;
    		char * task_category;
    		int index;
};
