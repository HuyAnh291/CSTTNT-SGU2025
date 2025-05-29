#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Hàm đọc danh sách công việc từ file
bool readJobsFromFile(const string &filename, vector<int> &jobs) {
    ifstream file(filename);
    if (!file) {
        cerr << "Khong the mo file " << filename << endl;
        return false;
    }

    int n;
    file >> n; 
    jobs.resize(n);
    
    for (int i = 0; i < n; i++) {
        file >> jobs[i];
    }

    file.close();
    return true;
}

// Thuật toán tham lam để phân công việc vào 3 máy
int greedyJobScheduling(const vector<int> &jobs, int numMachines = 3) {
    vector<int> sortedJobs = jobs;
    sort(sortedJobs.rbegin(), sortedJobs.rend());

    priority_queue<int, vector<int>, greater<int>> machines;
    
    for (int i = 0; i < numMachines; i++) {
        machines.push(0);
    }

    // Gán từng công việc vào máy có tổng thời gian nhỏ nhất
    for (int job : sortedJobs) {
        int minLoad = machines.top();
        machines.pop();
        machines.push(minLoad + job);
    }

    // Máy có tổng thời gian lớn nhất sẽ là thời gian hoàn thành tất cả công việc
    int maxTime = 0;
    while (!machines.empty()) {
        maxTime = max(maxTime, machines.top());
        machines.pop();
    }

    return maxTime;
}

int main() {
    vector<int> jobs;
    
    if (!readJobsFromFile("schedulea.txt", jobs)) {
        return 1; 
    }

    int minCompletionTime = greedyJobScheduling(jobs, 3);
    cout << "Thoi gian hoan thanh tat ca cong viec: " << minCompletionTime << endl;

    return 0;
}
