//  Reads the values from global tasks[], totalTasks, availableHours set by main.cpp and makes prediction using two models
//i.e, descision tree and k's nearest neighbours (descision tree is primary prediction) and labels scenarios 
// as 0, 1 and 2 indicating the recommended usage of sorting, greedy and dynamic programming strategy respectively

#ifndef AIML_MODULE_H
#define AIML_MODULE_H

#include "dataset.h"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//  Scenario Feature Container
struct ScenarioFeatures {
    int    numTasks;
    int    totalRequired;
    int    availableTime;
    double timePressureRatio;   // totalRequired / availableTime
    double avgImportance;
    int    urgentTasks;         // tasks with deadline less than or equal to 2
    double importanceVariation; // max importance - min importance
};

//  Feature Extraction

ScenarioFeatures extractFeatures() {
    ScenarioFeatures f;
    // sets the variables according to the values optained from main.cpp
    f.numTasks = totalTasks;
    f.availableTime = availableHours;

    // finding the tasks with minimum and maximum importance, and also the number of urgent tasks 
    int totalTime = 0, totalImp = 0;
    int minImp = 100, maxImp = 0, urgentCount = 0;

    for (int i = 0; i < totalTasks; i++) {
        totalTime += tasks[i].studyTime;
        totalImp  += tasks[i].importance;
        if (tasks[i].importance < minImp) minImp = tasks[i].importance;
        if (tasks[i].importance > maxImp) maxImp = tasks[i].importance;
        if (tasks[i].deadline <= 2)       urgentCount++;
    }

    // calculating the other features based on the above results 
    f.totalRequired       = totalTime;
    f.timePressureRatio   = (double)totalTime / availableHours;
    f.avgImportance       = (double)totalImp  / totalTasks;
    f.urgentTasks         = urgentCount;
    f.importanceVariation = (double)(maxImp - minImp);

    return f;
}

//  Training Dataset using 15 created scenarios covering 3 different scenario types 
//  labelled 0 if low time ratio and low urgency, 1 if moderate time ratio and high urgency, 2 if high ratio and moderate urgency
struct TrainingExample {
    double timePressureRatio;
    double avgImportance;
    int    urgentTasks;
    double importanceVariation;
    int    label;
};

//15 training scenarios consisting of different time availability and urgency levels 
const vector<TrainingExample> TRAINING_DATA = {
    {1.2, 3.8, 0, 2.0, 0}, {1.4, 4.0, 1, 2.0, 0}, {1.3, 3.5, 0, 3.0, 0}, {1.5, 4.2, 1, 2.5, 0},
    {2.2, 4.3, 6, 2.0, 1}, {2.0, 4.0, 4, 2.0, 1}, {2.3, 4.5, 5, 1.5, 1}, {1.8, 3.8, 4, 2.0, 1},
    {2.3, 4.0, 5, 2.5, 1}, {3.3, 4.0, 4, 3.0, 2}, {2.8, 4.5, 3, 3.0, 2}, {3.5, 4.2, 3, 3.5, 2},
    {2.5, 5.0, 2, 4.0, 2}, {3.0, 4.0, 4, 2.5, 2}, {4.0, 4.3, 3, 3.0, 2},
};

// algorithm suggestion based on the label number 
string strategyName(int label) {
    if (label == 0) return "Sorting-based Ranking";
    if (label == 1) return "Greedy Strategy";
    return "Dynamic Programming";
}

//  Decision Tree to judge whcih algorithm to apply 
int decisionTree(const ScenarioFeatures& f) {
    if (f.timePressureRatio <= 1.5) {
        return 0; // Sorting
    } else if (f.timePressureRatio >= 2.5) {
        return 2; // DP (high pressure)
    } else {
        // Moderate pressure (1.5 < ratio < 2.5)
        if (f.urgentTasks >= 4) {
            return 1; // Greedy
        } else if (f.urgentTasks <= 1) {
            return 0; // Sorting
        } else {
            return 1; // Greedy
        }
    }
}

//  k-NN Classifier with k value of 3
//using euclidean distance formula to caluclate the similarity of training data and given data 
double euclideanDist(const TrainingExample& a, const ScenarioFeatures& f) {
    //setting the maximum expected values for each feature 
    const double maxRatio  = 4.0;
    const double maxImp = 5.0;
    const double maxUrgent = 6.0;
    const double maxVar = 4.0;

    //calculating the 4 dimensions to apply to the formula 
    double dr = (a.timePressureRatio - f.timePressureRatio) / maxRatio;
    double di = (a.avgImportance - f.avgImportance) / maxImp;
    double du = ((double)a.urgentTasks - f.urgentTasks) / maxUrgent;
    double dv = (a.importanceVariation - f.importanceVariation) / maxVar;

    return sqrt(dr*dr + di*di + du*du + dv*dv);
}


int kNNPredict(const ScenarioFeatures& f, int k = 3) {
    vector<pair<double, int>> dist;
    for (const auto& ex : TRAINING_DATA)
        dist.push_back({euclideanDist(ex, f), ex.label});

    sort(dist.begin(), dist.end());

    int votes[3] = {0, 0, 0};
    for (int i = 0; i < k && i < (int)dist.size(); i++)
        votes[dist[i].second]++;

    int best = 0;
    for (int i = 1; i < 3; i++)
        if (votes[i] > votes[best]) best = i;

    return best;
}

//  Print Training Table 
void printTrainingData() {
    cout << "\n    AI/ML Training Dataset \n";
    cout << left << setw(6)  << "No." << setw(20) << "TimePressureRatio" << setw(18) << "AvgImportance" << setw(14)
         << "UrgentTasks" << setw(22) << "ImportanceVariation" << "Label\n";
    cout << string(88, '-') << "\n";
    for (int i = 0; i < (int)TRAINING_DATA.size(); i++) {
        const auto& ex = TRAINING_DATA[i];
        cout << setw(6)  << i + 1 << setw(20) << fixed << setprecision(1) << ex.timePressureRatio << setw(18) << ex.avgImportance
             << setw(14) << ex.urgentTasks << setw(22) << ex.importanceVariation << strategyName(ex.label) << "\n";
    }
}

//  printing the scenario features 
void printFeatures(const ScenarioFeatures& f) {
    cout << "\n    Extracted Scenario Features \n";
    cout << left
         << setw(32) << "Number of tasks" << f.numTasks << "\n"
         << setw(32) << "Total required study time"<< f.totalRequired << " hrs\n"
         << setw(32) << "Available study time" << f.availableTime << " hrs\n"
         << setw(32) << "Time pressure ratio"
         << fixed << setprecision(2) << f.timePressureRatio << "\n"
         << setw(32) << "Average importance" << f.avgImportance << "\n"
         << setw(32) << "Urgent tasks (deadline<=2)" << f.urgentTasks << "\n"
         << setw(32) << "Importance variation" << f.importanceVariation << "\n";
}

// Returns predicted strategy label (0/1/2)
int runAIML(const string& scenarioLabel) {
    cout << "\n   Module 5 : AI/ML study strategy recommendation \n";
    cout << " Scenario: " << scenarioLabel << "\n";

    ScenarioFeatures f = extractFeatures();
    printFeatures(f);

    int dtPred  = decisionTree(f);
    int knnPred = kNNPredict(f, 3);

    cout << "\n    Model Predictions \n";
    cout << "Decision Tree : " << strategyName(dtPred)  << "\n";
    cout << "k-NN (k=3): " << strategyName(knnPred) << "\n";

    if (dtPred == knnPred)
        cout << "\nBoth models have same suggestion.\n";
    else
        cout << "\nModels disagree so Decision Tree used as primary suggestion.\n";

    cout << "\nRecommended strategy: " << strategyName(dtPred) << "\n";
    return dtPred;
}

#endif
