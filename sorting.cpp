#include "dataset.h"
#include <iostream>
using namespace std;

// Merge Sort helper
void merge(Task arr[], int left, int mid, int right, string criterion) {
  int index1 = left;
  int index2 = mid + 1;
  Task temp[right - left + 1];
  int indexTemp = 0;

  while (index1 <= mid && index2 <= right) {
    if (criterion == "importance") {
      if (arr[index1].importance > arr[index2].importance) {
        temp[indexTemp++] = arr[index1++];
      } else {
        temp[indexTemp++] = arr[index2++];
      }
    } else if (criterion == "deadline") {
      if (arr[index1].deadline < arr[index2].deadline) {
        temp[indexTemp++] = arr[index1++];
      } else {
        temp[indexTemp++] = arr[index2++];
      }
    } else if (criterion == "studyTime") {
      if (arr[index1].studyTime < arr[index2].studyTime) {
        temp[indexTemp++] = arr[index1++];
      } else {
        temp[indexTemp++] = arr[index2++];
      }
    } else if (criterion == "difficulty") {
      if (arr[index1].difficulty < arr[index2].difficulty) {
        temp[indexTemp++] = arr[index1++];
      } else {
        temp[indexTemp++] = arr[index2++];
      }
    } else if (criterion == "ratio") {
      // Sort by importance-to-studyTime ratio (descending)
      double r1 = (double)arr[index1].importance / arr[index1].studyTime;
      double r2 = (double)arr[index2].importance / arr[index2].studyTime;
      if (r1 > r2) {
        temp[indexTemp++] = arr[index1++];
      } else {
        temp[indexTemp++] = arr[index2++];
      }
    } else {
      // Default to importance if criterion is unrecognized
      if (arr[index1].importance > arr[index2].importance) {
        temp[indexTemp++] = arr[index1++];
      } else {
        temp[indexTemp++] = arr[index2++];
      }
    }
  }

  // Copy any remaining elements from either half
  while (index1 <= mid) {
    temp[indexTemp++] = arr[index1++];
  }
  while (index2 <= right) {
    temp[indexTemp++] = arr[index2++];
  }

  // Copy the merged elements back to the original array
  for (int i = 0; i < indexTemp; i++) {
    arr[left + i] = temp[i];
  }
}

void mergeSort(Task arr[], int left, int right, string criterion) {
  if (left < right) {
    int mid = (left + right) / 2;
    mergeSort(arr, left, mid, criterion);
    mergeSort(arr, mid + 1, right, criterion);
    merge(arr, left, mid, right, criterion);
  }
}

void printRankedTasks(Task arr[], int n) {
  cout << "Rank | Task Name | Deadline | Importance | Study Time\n";
  for (int i = 0; i < n; i++) {
    cout << i + 1 << " | " << arr[i].name << " | " << arr[i].deadline << " | "
         << arr[i].importance << " | " << arr[i].studyTime << "\n";
  }
}