#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include "main.h"



int main(){
    
    char choice = '\0';
    


    Tasklist list;
    //std::cout << "Made it to the first func call" << std::endl;
    list.listLoadTasks();

    std::cout << "\nWelcome to the ISS task list!\n";
    std::cout << "(valid inputs are \'a\', \'b\', \'c\', \'d\', \'e\' and \'q\')\n";
    
    while (choice != 'q'){
        std::cout << "(a) Create new task\n";
        std::cout << "(b) List all task information\n";
        std::cout << "(c) Remove task by index\n";
        std::cout << "(d) Search for task by name\n";
        std::cout << "(e) Save task list to memory\n";
	std::cout << "(f) Search for task by type\n";
        std::cout << "(q) Quit the program\n\n";
        std::cin >> choice;

        while (!std::cin || (choice != 'a' && choice != 'b' && choice != 'c' && choice != 'd' && choice != 'e' && choice != 'f' && choice != 'q')){
            std::cout << "Whoops! Invalid input. Please try again: ";
            std::cin >> choice;
        }
        if (choice == 'a'){
            // scrap the newline character
            std::cin.get();
		
	    list.listInsertTask();

        } else if (choice == 'b'){
            // scrap the newline character
            std::cin.get();

	    list.listListTasks();
        } else if (choice == 'c'){
            // scrap the newline character
            std::cin.get();

	    list.listRemoveTask();

        } else if (choice == 'd'){
            // scrap newline left by std::cin >>
	    char query[51];
            std::cin.get();
            std::cout << "Enter part or all of the name of the task you are searching for. Be wary of capitals: ";
            std::cin.getline(query, 50, '\n');
            list.listSearchTask(query);
	    





            std::cout << std::endl << std::endl;
        } else if (choice == 'e'){
	    std::ofstream output;
	    output.open("tasks.txt");
	
            std::cout << "Saving all tasks...\n";
	    list.listSaveTasks(output);

       	    output.close();

	    std::cout << "Saved!\n\n";
	} else if (choice == 'f'){
		char query[51];
		std::cin.get();
		std::cout << "Enter the type of task you would like to search for (no spaces, case sensitive): ";
		std::cin.getline(query, 50, '\n');
		list.listTypeSearch(query);
	}
    }

    return 0;
}
