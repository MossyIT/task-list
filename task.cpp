#include "task.h"

Task::Task(){
	day = 0;
	duration = 0;
	index = 0;
	task_name = nullptr;
	crew_name = nullptr;
	task_category = nullptr;
}

char * Task::getString(std::ifstream& input){
	int count = 0;
	char * temp = nullptr;
	char * word = nullptr;
	
	//std::cout << "got to while loop" << std::endl;	
	while (input.good() && input.peek() != '\n' && input.peek() != ';'){
		temp = new char[count + 2];
		//std::cout << "1" << std::endl;
		if (word){
			strcpy(temp, word);
		}
		//std::cout << "2" << std::endl;
		temp[count] = input.get();
		temp[count + 1] = '\0';
		count++;
		//std::cout << "3" << std::endl;
		word = new char[count + 1];
		strcpy(word, temp);	
		delete[] temp;
		//std::cout << "4" << std::endl;
	}
	input.get();

	char * returnPoint = new char[count + 1];	
	strcpy(returnPoint, word);
	delete[] word;
	//std::cout << "5" << std::endl;	
	return returnPoint;
}
