#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

// Hàm đọc đồ thị từ file
void readGraph(const string& filename, vector<vector<int>>& graph, int& numVertices) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Khong the mo file " << filename << endl;
        exit(1);
    }

    file >> numVertices;
    graph.resize(numVertices, vector<int>(numVertices, 0));

    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            file >> graph[i][j];
        }
    }

    file.close();
}

// Hàm tính bậc bão hòa của một đỉnh
int saturationDegree(const vector<vector<int>>& graph, const vector<int>& colors, int vertex) {
    set<int> uniqueColors;
    for (int i = 0; i < graph.size(); ++i) {
        if (graph[vertex][i] == 1 && colors[i] != -1) {
            uniqueColors.insert(colors[i]);
        }
    }
    return uniqueColors.size();
}

// Thuật toán DSATUR để tô màu đồ thị
int dsatur(const vector<vector<int>>& graph, int numVertices) {
    vector<int> colors(numVertices, -1);
    vector<int> degree(numVertices, 0);

    // Tính bậc của mỗi đỉnh
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            if (graph[i][j] == 1) {
                degree[i]++;
            }
        }
    }

    // Chọn đỉnh có bậc lớn nhất để tô màu đầu tiên
    int maxDegreeVertex = max_element(degree.begin(), degree.end()) - degree.begin();
    colors[maxDegreeVertex] = 0;

    // Tô màu các đỉnh còn lại
    for (int i = 1; i < numVertices; ++i) {
        int maxSaturationVertex = -1;
        int maxSaturation = -1;
        int maxDegree = -1;

        // Tìm đỉnh có bậc bão hòa lớn nhất
        for (int j = 0; j < numVertices; ++j) {
            if (colors[j] == -1) {
                int saturation = saturationDegree(graph, colors, j);
                if (saturation > maxSaturation || (saturation == maxSaturation && degree[j] > maxDegree)) {
                    maxSaturation = saturation;
                    maxSaturationVertex = j;
                    maxDegree = degree[j];
                }
            }
        }

        // Tô màu cho đỉnh có bậc bão hòa lớn nhất
        set<int> usedColors;
        for (int j = 0; j < numVertices; ++j) {
            if (graph[maxSaturationVertex][j] == 1 && colors[j] != -1) {
                usedColors.insert(colors[j]);
            }
        }

        int color = 0;
        while (usedColors.find(color) != usedColors.end()) {
            color++;
        }
        colors[maxSaturationVertex] = color;
    }

    set<int> uniqueColors(colors.begin(), colors.end());
    cout << "So mau toi thieu can de to do thi: " << uniqueColors.size() << endl;
    return uniqueColors.size();
}

int main() {
    vector<vector<int>> graph;
    int numVertices;

    readGraph("color4.txt", graph, numVertices);
    dsatur(graph, numVertices);

    return 0;
}
