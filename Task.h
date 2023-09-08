#ifndef TASK_H
#define TASK_H
#include <string>
#include <vector>
#pragma once

struct Task
{
    std::string description_;
    bool done;
};

void SaveTasksToFile(const std::vector<Task> &tasks, const std::string filename);
std::vector<Task> loadTasksFromFile(const std::string &filename); 
#endif