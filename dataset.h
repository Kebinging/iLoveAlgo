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
// The data set consists of 3 scenarios which have the same task ids, names,
// study time, difficulty. importance and type but different number of tasks and
// deadline

//  scenario A has the total time availability of 15 hrs and required study time
//  of 21 hours (ratio = 21/15 = 1.4)
Task tasksA[] = {{"T1", "Revise Dynamic Programming", 3, 5, 2, 4, "Lecture"},
                 {"T2", "Complete Graph Tutorial", 2, 4, 3, 3, "Tutorial"},
                 {"T3", "Finish Sorting Assignment", 4, 3, 5, 5, "Assignment"},
                 {"T4", "Prepare for Midterm Exam", 5, 5, 6, 4, "Exam"},
                 {"T5", "Read Chapter on Trees", 2, 2, 4, 2, "Lecture"},
                 {"T6", "Solve Recursion Problems", 3, 4, 3, 3, "Tutorial"},
                 {"T7", "Python Group Project", 4, 3, 5, 5, "Assignment"},
                 {"T8", "Review Sorting Algorithms", 2, 5, 4, 4, "Lecture"}};
int totalTasksA = 8;
int availableHrsA = 15;
// since the dealines are not very close, they are less urgent and are
// compatible with ranked based sorting

// scenario b has the total time availability of 10 hrs and required study time
// of 33 hours (ratio = 33/10 = 3.3)
Task tasksB[] = {{"T1", "Revise Dynamic Programming", 3, 5, 2, 4, "Lecture"},
                 {"T2", "Complete Graph Tutorial", 2, 4, 3, 3, "Tutorial"},
                 {"T3", "Finish Sorting Assignment", 4, 3, 1, 5, "Assignment"},
                 {"T4", "Prepare for Midterm Exam", 5, 5, 2, 4, "Exam"},
                 {"T5", "Read Chapter on Trees", 2, 2, 4, 2, "Lecture"},
                 {"T6", "Solve Recursion Problems", 3, 4, 3, 3, "Tutorial"},
                 {"T7", "Python Group Project", 4, 3, 1, 5, "Assignment"},
                 {"T8", "Review Sorting Algorithms", 2, 5, 2, 4, "Lecture"},
                 {"T9", "Complete Graph Assignment", 3, 4, 3, 3, "Assignment"},
                 {"T10", "Prepare for Final Exam", 5, 5, 1, 5, "Exam"}};
int totalTasksB = 10;
int availableHrsB = 10;
// since the total available time is very less and deadlines are moderately
// urgent, we have to use dynamic programming to optimize our task selection

// scenario c has the total time availability of 8 hrs and required study time
// of 21 hours (ratio = 21/8 = 2.6)
Task tasksC[] = {
    {"T1", "Revise Dynamic Programming", 3, 5, 2, 4, "Lecture"},
    {"T3", "Finish Sorting Assignment", 4, 3, 1, 5, "Assignment"},
    {"T4", "Prepare for Midterm Exam", 5, 5, 2, 4, "Exam"},
    {"T7", "Python Group Project", 4, 3, 1, 5, "Assignment"},
    {"T8", "Review Sorting Algorithms", 2, 5, 2, 4, "Lecture"},
    {"T10", "Prepare for Final Exam", 3, 5, 1, 5,
     "Exam"} // studyTime reduced to 3 for scenario fit
};
int totalTasksC = 6;
int availableHrsC = 8;
// since the available time is less and deadlines are extree=mely tight, we have
// to use greedy startegy

//  set the active scenario as scenario A before each run from the main file
Task *tasks = tasksA;
int totalTasks = 8;
int availableHours = 15;

#endif
