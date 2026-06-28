#include "greedy_dp_lib.cpp"
#include "aiml_module.h"
#include "performance_module.h"


//  Run all modules for a scenario
void runScenario(const string& label) {
    cout << "\n\n";
    cout << "Scenario: " << label << "\n";
    cout << "Tasks: " << totalTasks << "  |  Available: " << availableHours << " hrs\n";
   
    // Print task list
    cout << "\n     Task List \n";
    cout << left << setw(5)  << "ID" << setw(34) << "Task Name" << setw(8)  << "Time" << setw(12) << "Importance"
         << setw(10) << "Deadline" << setw(12) << "Difficulty" << "Type\n";
    cout << string(88, '-') << "\n";
    for (int i = 0; i < totalTasks; i++) {
        cout << setw(5)  << tasks[i].id << setw(34) << tasks[i].name << setw(8)  << (to_string(tasks[i].studyTime) + "h")
             << setw(12) << tasks[i].importance << setw(10) << (to_string(tasks[i].deadline)  + "d")
             << setw(12) << tasks[i].difficulty << tasks[i].type << "\n";
    }

    vector<StrategyResult> results;
    clock_t t0;
    double  elapsed;

    //  Module 2: Sorting by importance
    Task sortArr[totalTasks];
    importData(sortArr);

    t0 = timerStart();
    mergeSort(sortArr, 0, totalTasks - 1, "importance");
    elapsed = timerStop(t0);

    cout << "\n    Module 2: Sorting by Importance\n";
    printRankedTasks(sortArr, totalTasks);

    // Pick tasks that fit within available hours
    vector<Task> sortSelected;
    int sortTime = 0;
    for (int i = 0; i < totalTasks; i++) {
        if (sortTime + sortArr[i].studyTime <= availableHours) {
            sortSelected.push_back(sortArr[i]);
            sortTime += sortArr[i].studyTime;
        }
    }
    results.push_back(makeResult("Sorting-based Ranking", sortSelected, elapsed,
                                 "Ranked by importance"));

    //  Module 3: Greedy method
    Task greedyArr[totalTasks];
    importData(greedyArr);

    t0 = timerStart();
    vector<Task> greedyPlan = greedyScheduler(availableHours, greedyArr);
    elapsed = timerStop(t0);

    cout << "\n    Module 3: Greedy Output \n";
    cout << left << setw(6) << "ID" << setw(34) << "Task Name" << setw(12) << "Study Time" << "Importance\n";
    cout << string(60, '-') << "\n";
    for (size_t i = 0; i < greedyPlan.size(); i++) {
        cout << setw(6)  << greedyPlan[i].id << setw(34) << greedyPlan[i].name << setw(12) << greedyPlan[i].studyTime
             << greedyPlan[i].importance << "\n";
    }
    results.push_back(makeResult("Greedy Strategy", greedyPlan, elapsed, "Highest importance/time ratio first"));

    //  Module 4: Dynamic Programming using Knapsack algorithm
    Task dpArr[totalTasks];
    importData(dpArr);

    t0 = timerStart();
    vector<Task> dpPlan = knapsack01DP(availableHours, dpArr);
    elapsed = timerStop(t0);

    cout << "\n    Module 4: DP Output \n";
    cout << left << setw(6) << "ID" << setw(34) << "Task Name" << setw(12) << "Study Time" << "Importance\n";
    cout << string(60, '-') << "\n";
    for (size_t i = 0; i < dpPlan.size(); i++) {
        cout << setw(6)  << dpPlan[i].id << setw(34) << dpPlan[i].name << setw(12) << dpPlan[i].studyTime
             << dpPlan[i].importance << "\n";
    }
    results.push_back(makeResult("Dynamic Programming", dpPlan, elapsed,
                                 "Optimal subset by using 0/1 Knapsack"));

    //  Module 5: AI/ML Recommendation
    t0 = timerStart();
    int prediction = runAIML(label);
    elapsed = timerStop(t0);
    results.push_back(makeAIMLResult(prediction, elapsed));

    //  Module 6: Performance Comparison Table
    runComparison(label, results, prediction);
}

//  Running all 3 scenarios 
int main() {
    cout << "    StudySmart AI \n";
    cout << "--------------------------------\n";

    // Prints the training data at the start
    printTrainingData();

    // Scenario A: Low Pressure 
    tasks        = tasksA;
    totalTasks   = totalTasksA;
    availableHours = availableHrsA;
    runScenario("Scenario A (Low Pressure)");

    // Scenario B: High Pressure 
    tasks        = tasksB;
    totalTasks   = totalTasksB;
    availableHours = availableHrsB;
    runScenario("Scenario B (High Pressure)");

    // Scenario C: Deadline Focused 
    tasks        = tasksC;
    totalTasks   = totalTasksC;
    availableHours = availableHrsC;
    runScenario("Scenario C (Deadline Focused)");

    cout << "\n\nProgram complete.\n";
    return 0;
}
