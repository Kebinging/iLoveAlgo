//  identifies the best strategy by comparing the importance scores
#ifndef PERFORMANCE_MODULE_H
#define PERFORMANCE_MODULE_H

#include "dataset.h"
#include "aiml_module.h"
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//  Result container 
struct StrategyResult {
    string       strategyName;
    vector<Task> selectedTasks;
    int totalStudyTime;
    int totalImportance;
    double execMicros;   
    string comment;
};

//  Timer helpers
clock_t timerStart() { return clock(); }

double timerStop(clock_t start) {
    return (double)(clock() - start) / CLOCKS_PER_SEC * 1e6;
}

//  Build a result from a task vector + timing
StrategyResult makeResult(const string&       name, const vector<Task>& tasks, double micros, const string& comment) {
    int time = 0, imp = 0;
    for (const auto& t : tasks) { time += t.studyTime; imp += t.importance; }

    StrategyResult r;
    r.strategyName = name;
    r.selectedTasks = tasks;
    r.totalStudyTime  = time;
    r.totalImportance = imp;
    r.execMicros = micros;
    r.comment  = comment;
    return r;
}

// AI/ML prediction
StrategyResult makeAIMLResult(int prediction, double micros) {
    StrategyResult r;
    r.strategyName = "AI/ML Recommendation";
    r.totalStudyTime  = 0;
    r.totalImportance = 0;
    r.execMicros = micros;
    r.comment = "Recommends: " + strategyName(prediction);
    return r;
}

//  Print table
void printSep(int width = 108) { cout << string(width, '-') << "\n"; }

void printComparisonTable(const string& scenarioLabel, const vector<StrategyResult>& results, int aimlPrediction) {
    cout << "\n";
    printSep();
    cout << " Strategy comparison:  " << scenarioLabel
         << " | Available: " << availableHours << " hrs\n";
    printSep();

    cout << left << "| " << setw(24) << "Strategy" << "| " << setw(22) << "Selected Tasks" << "| " << setw(11) << "Time(hrs)"
         << "| " << setw(15) << "Importance" << "| " << setw(12) << "Exec Time" << "| Comment\n";
    printSep();

    for (const auto& r : results) {
        // Build task ID list
        string ids;
        for (size_t i = 0; i < r.selectedTasks.size(); i++) {
            ids += r.selectedTasks[i].id;
            if (i + 1 < r.selectedTasks.size()) ids += ",";
        }

        cout << "| " << setw(24) << r.strategyName << "| " << setw(22) << (ids.empty() ? "-" : ids)
             << "| " << setw(11) << (r.totalStudyTime  == 0 && ids.empty() ? "-" : to_string(r.totalStudyTime))
             << "| " << setw(15) << (r.totalImportance == 0 && ids.empty() ? "-" : to_string(r.totalImportance))
             << "| " << setw(12) << (to_string((int)r.execMicros) + " us")
             << "| " << r.comment << "\n";
    }

    printSep();

    // Best strategy by importance
    int    bestImp   = -1;
    string bestStrat = "-";
    for (const auto& r : results) {
        if (r.strategyName != "AI Recommendation" && r.totalImportance > bestImp) {
            bestImp   = r.totalImportance;
            bestStrat = r.strategyName;
        }
    }

    // Check if AI/ML prediction has the same or better resuts than the importace scores 
    string predicted = strategyName(aimlPrediction);
    int predictedImp = -1;
    for (const auto& r : results)
        if (r.strategyName == predicted) predictedImp = r.totalImportance;

    bool correct = (predicted == bestStrat) || (predictedImp == bestImp);

    cout << " AI/ML Recommended : " << predicted << "\n";
    cout << " Best by Importance: " << bestStrat << " (" << bestImp << " pts)\n";
    cout << " Prediction Correct: " << (correct ? "YES" : "NO") << "\n";
    printSep();
}


//  Calling this from the main allows the comparison table to be printed out 
void runComparison(const string& scenarioLabel, const vector<StrategyResult>& results, int aimlPrediction) {
    printComparisonTable(scenarioLabel, results, aimlPrediction);
}

#endif 