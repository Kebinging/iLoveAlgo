#ifndef DATASET_H
#define DATASET_H

#include <string>
using namespace std;

class Task {
public:
    string id;
    string name;
    int studyTime;
    int importance;
    int deadline;
    int difficulty;
    string type;
};

// Your actual dataset
Task tasks[] = {
    {"T1", "Revise Dynamic Programming", 3, 5, 2, 4, "Lecture"},
    {"T2", "Complete Graph Tutorial",    2, 4, 3, 3, "Tutorial"},
    // ... rest of your tasks
};

int totalTasks = 10; // however many you have

#endif