#include <classes.hpp>
#include <string>
#include <iostream>
using namespace std; //for convenience 

int main()
{
    //declare vars
    string c;
    string task_text;
    string line;
    int timefromNow;
    int task_no;

    //instantiate
    TaskManager tm;

    cout << "Welcome to your To Do List!" << endl;
    cout << "1. Create a New Task" << endl << "2. View Your Current Tasks" << endl << "3. Check if Tasks are Overdue";
    cin >> c;

    if (c == "1")
    {
        cout << "Lets Create a Task!" << endl;
        cout << "Enter the task description: " << endl;
        cin >> ws >> task_text;
        cout << "Enter the time from now that the task is due in hours: " << endl;
        cin >> timefromNow;

        // handle task no
        task_no = tm.no_tasks + 1;

        tm.createTask(task_text, timefromNow, task_no, false, false);
    } else if (c == "2")
    {
        for (Task& obj : tm.tasksV)
        {
            line = tm.gettaskTXT(obj.task_no);
            cout << obj.task_no << line << endl;
        }
    } else if (c == "3")
    {
        tm.update();
    } else
    {
        cout << "Invalid choice: " << c << endl;
        cout << "Closing To Do List, restart software." << endl;
    }
    
    return 0;
}