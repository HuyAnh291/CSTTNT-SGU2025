#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

struct Point {
    double x, y;
    int cluster;
};

double distance(Point a, Point b) {
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

void kmeans(vector<Point>& points, int k, int maxIterations = 100) {
    int n = points.size();
    vector<Point> centroids(k);

    srand(time(NULL));
    for (int i = 0; i < k; ++i) {
        int idx = rand() % n;
        centroids[i] = points[idx];
    }

    for (int iter = 0; iter < maxIterations; ++iter) {
        bool changed = false;

        for (int i = 0; i < n; ++i) {
            double minDist = numeric_limits<double>::max();
            int newCluster = 0;
            for (int j = 0; j < k; ++j) {
                double dist = distance(points[i], centroids[j]);
                if (dist < minDist) {
                    minDist = dist;
                    newCluster = j;
                }
            }
            if (points[i].cluster != newCluster) {
                changed = true;
                points[i].cluster = newCluster;
            }
        }

        vector<double> sumX(k, 0), sumY(k, 0);
        vector<int> count(k, 0);

        for (int i = 0; i < n; ++i) {
            int c = points[i].cluster;
            sumX[c] += points[i].x;
            sumY[c] += points[i].y;
            count[c]++;
        }

        for (int j = 0; j < k; ++j) {
            if (count[j] != 0) {
                centroids[j].x = sumX[j] / count[j];
                centroids[j].y = sumY[j] / count[j];
            }
        }

        if (!changed) break;
    }

    cout << "\n=== Ket qua phan cum ===\n";
    for (int i = 0; i < k; ++i) {
        cout << "Cum " << i + 1 << ": ";
        for (int j = 0; j < n; ++j) {
            if (points[j].cluster == i)
                cout << "(" << points[j].x << "," << points[j].y << ") ";
        }
        cout << "\n";
    }
}

int main() {
    ifstream inFile("input.txt");
    if (!inFile) {
        cerr << "Khong mo duoc file input.txt\n";
        return 1;
    }

    int numPoints, k;
    inFile >> numPoints;

    vector<Point> points(numPoints);
    for (int i = 0; i < numPoints; ++i) {
        inFile >> points[i].x >> points[i].y;
        points[i].cluster = -1;
    }

    inFile >> k;
    inFile.close();

    kmeans(points, k);
    return 0;
}
