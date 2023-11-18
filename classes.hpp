#include <iostream>
#include <fstream>
#include <chrono>
#include <string>

auto currentT = std::chrono::system_clock::now();

struct DueDate
{
    std::chrono::system_clock::time_point timePoint;
    DueDate(std::chrono::system_clock::time_point tp) : timePoint(tp) {}

    bool isPast() const
    {
        return std::chrono::system_clock::now() > timePoint;
    }
};

class Task
{
    public:
        std::string task_txt;
        int timefromNow;
        bool isCompleted;
    Task(std::string task_txt, int timefromNow, bool isCompleted)
    {
        this->task_txt = task_txt;
        this->timefromNow = timefromNow;
        this->isCompleted = isCompleted;
    }
};

class TaskManager
{
    public:
        int no_tasks;
    void createTask(std::string task_txt, int timefromNow, bool isCompleted)
    {
        Task t(task_txt, timefromNow, isCompleted);
        this->no_tasks += 1;

        std::ofstream t_file("tasks.txt");
        t_file << this->no_tasks << std::endl << t.task_txt;
    }
    std::string getT(int t_no)
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