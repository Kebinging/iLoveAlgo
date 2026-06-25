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
    {"T3", "Finish Sorting Assignment",   4, 3, 1, 5, "Assignment"},
    {"T4", "Prepare for Midterm Exam",    5, 5, 2, 4, "Exam"},
    {"T5", "Read Chapter on Trees",       2, 2, 4, 2, "Lecture"},
    {"T6", "Solve Recursion Problems",     3, 4, 3, 3, "Tutorial"},
    {"T7", "Python Group Project",        4, 3, 1, 5, "Assignment"},
    {"T8", "Review Sorting Algorithms",   2, 5, 2, 4, "Lecture"},
    {"T9", "Complete Graph Assignment",   3, 4, 3, 3, "Assignment"},
    {"T10","Prepare for Final Exam",      5, 5, 1, 5, "Exam"}
};

int totalTasks = 10; // however many you have

#endif