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
    Task(std::string task_txt, int timefromNow, int task_no, bool isCompleted)
    {
        this->task_txt = task_txt;
        this->timefromNow = timefromNow;
        this->task_no = task_no;
        this->isCompleted = isCompleted;
    }
    void createdueDate()
    {
        auto dt = currentT + std::chrono::hours(this->timefromNow);
        DueDate dd(dt,  this->task_no)
    }
};

class TaskManager
{
    public:
        int no_tasks;
        std::vector<Task> tasksV;
    void createTask(std::string task_txt, int timefromNow, int task_no, bool isCompleted)
    {
        Task t(task_txt, timefromNow, task_no, isCompleted);
        this->tasksV.emplace_back(t);
        this->no_tasks += 1;

        std::ofstream t_file("tasks.txt");
        t_file << this->no_tasks << std::endl << t.task_txt;
    }
    std::string getT(int t_no) //intake task number as arg
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
};