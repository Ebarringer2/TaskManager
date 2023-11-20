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