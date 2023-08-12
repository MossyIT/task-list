#pragma once
#include "task.h"

class Tasklist {
    public:
	Tasklist();

	void listLoadTasks();
	void listInsertTask();
	void listRemoveTask();
	void listSearchTask(char query[]);
	void listListTasks();
	void listSaveTasks(std::ofstream& output);
	void listTypeSearch(char query[]);

    private:
	Task taskList[30];
	int count;
	

};
