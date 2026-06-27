#include "sorting.cpp"
#include <iostream>
#include <vector>

void importData(Task localTask[]) {
  for (int i = 0; i < totalTasks; i++)
    localTask[i] = tasks[i];
}

std::vector<Task> greedyFishyAhh(int available_hours, Task tasks[]) {
  mergeSort(tasks, 0, totalTasks - 1, "ratio"); // Kevin's merge sort
  std::vector<Task> selectedTasks;

  for (int i = 0; i < totalTasks; i++) {
    if (available_hours <= 0)
      break;

    if (available_hours - tasks[i].studyTime < 0)
      continue;

    available_hours -= tasks[i].studyTime;
    selectedTasks.push_back(tasks[i]);
  }

  return selectedTasks;
}

std::vector<Task> NutSack01(int available_hours, Task tasks[]) {
  int n = totalTasks;
  int W = available_hours;

  // Build DP table: dp[i][w] = max importance using first i tasks with capacity
  int dp[n + 1][W + 1];
  for (int i = 0; i <= n; i++)
    for (int w = 0; w <= W; w++)
      dp[i][w] = 0;

  for (int i = 1; i <= n; i++) {         // iterate through tasks
    int weight = tasks[i - 1].studyTime; // weight of the current task
    int value = tasks[i - 1].importance;
    for (int w = 0; w <= W; w++) {
      // Option 1: skip this task
      dp[i][w] = dp[i - 1][w];
      // Option 2: take this task (only if it fits)
      if (weight <= w) {
        int withTask = dp[i - 1][w - weight] + value;
        if (withTask > dp[i][w])
          dp[i][w] = withTask;
      }
    }
  }

  // Backtrack to find which tasks were actually selected
  std::vector<Task> selectedTasks;
  int w = W;
  for (int i = n; i > 0; i--) {
    if (dp[i][w] !=
        dp[i - 1][w]) { // if the previous cell doesn't have the same value
      // it means that the current task is in the subset.
      selectedTasks.push_back(tasks[i - 1]);
      w -= tasks[i - 1].studyTime;
    }
  }

  return selectedTasks;
}

int main() {
  Task taskis[totalTasks];
  importData(taskis);
  int hours = 6; // testing
  std::vector<Task> greedyPlan = greedyFishyAhh(hours, taskis);
  importData(taskis);
  std::vector<Task> dpPlan = NutSack01(hours, taskis);

  // Greedy Rational Knapsack
  int greedyImportance = 0, greedyTime = 0;
  std::cout << "ID  | Task Name                  | StudyTime | Importance\n";
  for (size_t i = 0; i < greedyPlan.size(); i++) {
    std::cout << greedyPlan[i].id << " | " << greedyPlan[i].name << " | "
              << greedyPlan[i].studyTime << " | " << greedyPlan[i].importance
              << "\n";
    greedyImportance += greedyPlan[i].importance;
    greedyTime += greedyPlan[i].studyTime;
  }
  std::cout << "Total Time: " << greedyTime
            << "h | Total Importance: " << greedyImportance << "\n";

  // Dynamic programming 0/1 Knapsack
  int dpImportance = 0, dpTime = 0;
  std::cout << "\n0/1 KNAPSACK\n";
  std::cout << "ID  | Task Name                  | StudyTime | Importance\n";
  for (size_t i = 0; i < dpPlan.size(); i++) {
    std::cout << dpPlan[i].id << " | " << dpPlan[i].name << " | "
              << dpPlan[i].studyTime << " | " << dpPlan[i].importance << "\n";
    dpImportance += dpPlan[i].importance;
    dpTime += dpPlan[i].studyTime;
  }
  std::cout << "Total Time: " << dpTime
            << "\tTotal Importance: " << dpImportance << "\n";

  return 0;
}