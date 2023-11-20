// this file is created to avoid compilation errors raised when trying to include the classes heading file
// it is just classes.hpp and main.cpp combined into one complete file

#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <vector>

auto currentT = std::chrono::system_clock::now();

struct DueDate
{
    std::chrono::system_clock::time_point timePoint;
    int task_no;
    DueDate(std::chrono::system_clock::time_point tp, int task) : timePoint(tp), task_no(task) {}

    bool isPast() const
    {
        return std::chrono::system_clock::now() > timePoint;
    }
};

class Task
{
    public:
        std::string task_txt;
        int timefromNow; // in hours
        int task_no;
        bool isCompleted;
        bool isPast;
    Task(std::string task_txt, int timefromNow, int task_no, bool isCompleted, bool isPast)
    {
        this->task_txt = task_txt;
        this->timefromNow = timefromNow;
        this->task_no = task_no;
        this->isCompleted = isCompleted;
        this->isPast = isPast;
    }
};

class TaskManager
{
    public:
        int no_tasks;
        bool running = true;
        std::vector<Task> tasksV;
        std::vector<DueDate> ddV;
    void createTask(std::string task_txt, int timefromNow, int task_no, bool isCompleted, bool isPast)
    {
        Task t(task_txt, timefromNow, task_no, isCompleted, isPast);
        this->tasksV.emplace_back(t);
        this->no_tasks += 1;

        // due date management
        auto dt = currentT + std::chrono::hours(t.timefromNow);
        DueDate dd(dt, t.task_no);
        this->ddV.emplace_back(dd);

        std::ofstream t_file("tasks.txt");
        t_file << this->no_tasks << std::endl << t.task_txt;
    }
    std::string gettaskTXT(int t_no) //intake task number as arg
    {
        char target = t_no;
        std::string filename = "tasks.txt";
        std::ifstream inputFile(filename);
        std::string line;

        while (std::getline(inputFile, line))
        {
            size_t found = line.find(target);
            if (found != std::string::npos)
            {
                if (std::getline(inputFile, line))
                {
                    return line;
                } else {
                    std::cout << "no task found with number: " << t_no;
                }
                break;
            }
        }
        inputFile.close();
        return "";
    }
    void update()
    {
        // checking if tasks are overdue
        for (DueDate& obj : this->ddV)
        {
            bool p = obj.isPast();
            int n = obj.task_no;

            for (Task& obj : this->tasksV)
            {
                if (n == obj.task_no)
                    obj.isPast = p;
                for (Task& o : this->tasksV)
                {
                    if (o.isPast)
                        std::cout << "The following task is late: " << this->gettaskTXT(o.task_no);
                }
            }
        }
    }
};

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

    while (tm.running)
    {
        cout << "Welcome to your To Do List!" << endl;
        cout << "1. Create a New Task" << endl << "2. View Your Current Tasks" << endl << "3. Check if Tasks are Overdue" << endl << "4. Exit the To Do List";
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
        } else if (c == "4")
        {
            tm.running = false;
        } else
        {
            cout << "Invalid choice: " << c << endl;
            cout << "Closing To Do List, restart software." << endl;
        }
    }
    return 0;
}