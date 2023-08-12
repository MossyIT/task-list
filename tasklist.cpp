#include "tasklist.h"



Tasklist::Tasklist(){
	count = 0;


}

void Tasklist::listLoadTasks(){
	std::ifstream input;


	input.open("tasks.txt");

	while (!input.eof()){
		Task temp;
		char tempstring[51];
		
		input.getline(tempstring, 50, ';');
		temp.day = atoi(tempstring);
		
		//input.getline(temp.task_name, 50, ';');
		// std::cout << "made it to getString call" << std::endl;
		temp.task_name = temp.getString(input);
		//std::cout << "I got task_name: ";
		
		//for (int i = 0; i < strlen(temp.task_name); i++){
		//	std::cout << temp.task_name[i];
		//}
		
		input.getline(tempstring, 50, ';');
		temp.duration = atoi(tempstring);

		//input.getline(temp.crew_name, 50, ';');
		temp.crew_name = temp.getString(input);

		//input.getline(temp.task_category, 50, '\n');
		temp.task_category = temp.getString(input);


		temp.index = count + 1;
		
		taskList[count] = temp;

		count++;
	}
	input.close();
	return;
}


void Tasklist::listListTasks(){
	for (int i = 0; i < count; i++){
		Task temp = taskList[i];
		std::cout << temp.index << ") ";
		std::cout << temp.day << ";";
		for (int j = 0; j < strlen(temp.task_name); j++){
			std::cout << temp.task_name[j];
		}
		std::cout << ";";
		std::cout << temp.duration << ";";
		for (int j = 0; j < strlen(temp.crew_name); j++){
			std::cout << temp.crew_name[j];
		}
		std::cout << ";";
		for (int j = 0; j < strlen(temp.task_category); j++){
			std::cout << temp.task_category[j];
		}
		std::cout << "\n\n";
	}

	return;
}

void Tasklist::listInsertTask(){
        int temp;
	Task newTask;
	
	std::cout << "New task name: ";
        // working here
        std::cin.getline(newTask.task_name, 50);

        std::cout << "Duration to complete \'";
        for (int i = 0; i < strlen(newTask.task_name); i++){
            std::cout << newTask.task_name[i];
        }
        std::cout << "\': ";
        std::cin >> newTask.duration;

        while (!std::cin || (newTask.duration < 0 || newTask.duration > 24)){
            std::cin.clear();
            std::cin.ignore(100, '\n');
            std::cout << "Whoops! Invalid input. Please try again: ";
            std::cin >> newTask.duration;
    	}


    	std::cout << "Day of the month: ";
    	std::cin >> newTask.day;

        while (!std::cin || (newTask.day < 1 || newTask.day > 30)){
            std::cin.clear();
            std::cin.ignore(100, '\n');
            std::cout << "Whoops! Invalid input. Please try again: ";
            std::cin >> newTask.day;
        }

       // scrap newline
       std::cin.get();

        std::cout << "Crew member to perform: ";
        std::cin.getline(newTask.crew_name, 50);

        std::cout << "Category of task (0- Operations; 1- Maintenace; 2- Inventory;";
	std::cout << " 3- Communications); 4- Others: ";
        std::cin >> temp;
        while (!std::cin || (temp < 0 || temp > 4)){
            std::cin.clear();
            std::cin.ignore(100, '\n');
            std::cout << "Whoops! Invalid input. Please try again: ";
            std::cin >> temp;
        }
        switch (temp){
            case 0:
                strcpy(newTask.task_category, "Operations");
                break;
            case 1:
                strcpy(newTask.task_category, "Maintenance");
                 break;
            case 2:
                strcpy(newTask.task_category, "Inventory");
                break;
            case 3:
                strcpy(newTask.task_category, "Communications");
                break;
            case 4:
                strcpy(newTask.task_category, "Others");
                break;
        }


        std::cout << "\n\n";




	
	bool insertion = false; 
        if (count == 0){
            newTask.index = 1;
            taskList[0] = newTask;
	    count++;
            return;
       
        }
        for (int i = 0; i < count; i++){
            Task temp1 = taskList[i];
            Task temp2;
  
  
            // look for spot
            if (i < count - 1 || count == 1){
                if (count != 1){
                    temp2 = taskList[i + 1];
                }
  
                // if it should be the first element
                if (newTask.crew_name[0] < temp1.crew_name[0]){
                    for (int j = count; j > i; j--){
                        Task shiftTemp;
                        taskList[j] = taskList[j - 1];
                        shiftTemp = taskList[j];
                        shiftTemp.index++;
                        taskList[j] = shiftTemp;
                    }
                    newTask.index = 1;
                    taskList[0] = newTask;
		    count++;
                    return;
                }


            //}
            // if it should be any element in the middle
            if (newTask.crew_name[0] >= temp1.crew_name[0] && newTask.crew_name[0] < temp2.crew_name[0]){
                insertion = true;
            }

        // if it should be the last element
            } else if (i == count - 1){
		newTask.index = count + 1;
                taskList[count] = newTask;
		count++;
                return;
            }
        // found a spot
        if (insertion){
            for (int j = count; j > i; j--){
                Task shiftTemp;
                taskList[j] = taskList[j - 1];
                shiftTemp = taskList[j];
                shiftTemp.index++;
                taskList[j] = shiftTemp;


            }
            newTask.index = i + 1;
            taskList[i] = newTask;
            i = count;

        }
    }
    count++;
    return;
}

void Tasklist::listRemoveTask(){
	int choice;
	std::cout << "Which task would you like removed? (1-" << count << "): ";
        std::cin >> choice;
        while (!std::cin || (choice > count || choice < 1)){
             std::cin.clear();
             std::cin.ignore(50, '\n');
             std::cout << "Whoops! Invalid input. Please try again: ";
             std::cin >> choice;
        }

	choice--;
	count--;
	for (int i = choice; i < count; i++){
		taskList[i] = taskList[i + 1];
	}
	for (int i = 0; i < count; i++){
		Task shiftTemp;
		shiftTemp = taskList[i];
		shiftTemp.index = i + 1;
		taskList[i] = shiftTemp;
	}

	return;
}

void Tasklist::listSearchTask(char query[]){
    bool search_failure = true;
    Task search;
    //strcpy(search_failure.task_name, "fail");
    for (int i = 0; i < count; i++){
        Task temp = taskList[i];
        if (strstr(temp.task_name, query)){
            //return temp;
            search_failure = false;
            std::cout << "I found it!\n\n";
	    search = temp;
            i = count;
        } else {
            search_failure = true;
        }
    }
    //return search_failure;
    if (!search_failure){

        std::cout << "There is a task \'";
        for (int i = 0; i < strlen(search.task_name); i++){
                std::cout << search.task_name[i];
        }
        std::cout << "\' that matches your search query.\n\n";
        std::cout << "Here is a description of the aforementioned task:\n";
        std::cout << "Task index: " << search.index << std::endl;
        std::cout << "Day to be performed: " << search.day << std::endl;
        std::cout << "Hours to complete: " << search.duration << std::endl;
        std::cout << "Crew member to perform: ";
        for (int i = 0; i < strlen(search.crew_name); i++){
                std::cout << search.crew_name[i];
        }
        std::cout << "\nCategory of task: ";
        for (int i = 0; i < strlen(search.task_category); i++){
                std::cout << search.task_category[i];
        }
    } else {
        std::cout << "There is no task that matches your search.";
    }
    return;

}


void Tasklist::listSaveTasks(std::ofstream& output){
    for (int i = 0; i < count; i++){
	Task temp = taskList[i];
        output << temp.day << ";";
        for (int j = 0; j < strlen(temp.task_name); j++){
            output << temp.task_name[j];
        }
        output << ";";
        output << temp.duration << ";";
        for (int j = 0; j < strlen(temp.crew_name); j++){
            output << temp.crew_name[j];
        }
        output << ";";
        for (int j = 0; j < strlen(temp.task_category); j++){
            output << temp.task_category[j];
        }
	if (i != count - 1){
	    output << "\n";
	}
    }
    
        // one line
    return;
}

void Tasklist::listTypeSearch(char query[]){
	Task newList[30];
	int counter = 0;
	for (int i = 0; i < count; i++){
		Task temp = taskList[i];
		if (strstr(temp.task_category, query)){
			newList[counter] = taskList[i];
			counter++;
		}
	}
	std::cout << "Here is the list of current tasks of this type: \n";
	for (int i = 0; i < counter; i++){
		Task temp = newList[i];
		std::cout << temp.task_name << "\n";
	}
	std::cout << "\n";
	return;
}










