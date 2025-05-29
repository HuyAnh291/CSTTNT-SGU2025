#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;

bool readMatrixFromFile(const string &filename, vector<vector<int>> &costMatrix, int &n) {
    ifstream file(filename);
    if (!file) {
        cerr << "Khong the mo file " << filename << endl;
        return false;
    }

    file >> n;
    costMatrix.assign(n, vector<int>(n));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            file >> costMatrix[i][j];

    file.close();
    return true;
}

// Hàm tìm cách phân công công việc tối ưu theo chiến lược tham lam
int greedyAssignment(vector<vector<int>> &costMatrix, int n) {
    vector<bool> jobAssigned(n, false); 
    int totalCost = 0;

    for (int i = 0; i < n; i++) {
        int minCost = numeric_limits<int>::max();
        int jobIndex = -1;

        // Tìm công việc có chi phí nhỏ nhất chưa được giao
        for (int j = 0; j < n; j++) {
            if (!jobAssigned[j] && costMatrix[i][j] < minCost) {
                minCost = costMatrix[i][j];
                jobIndex = j;
            }
        }

        if (jobIndex != -1) {
            jobAssigned[jobIndex] = true; 
            totalCost += minCost;
            cout << "Nguoi tho " << i + 1 << " -> Cong viec " << jobIndex + 1 << " (Chi phi: " << minCost << ")" << endl;
        }
    }

    return totalCost;
}

int main() {
    vector<vector<int>> costMatrix;
    int n;

    if (!readMatrixFromFile("assignment.txt", costMatrix, n)) {
        return 1;
    }

    int totalCost = greedyAssignment(costMatrix, n);
    cout << "Tong chi phi phan cong: " << totalCost << endl;

    return 0;
}
