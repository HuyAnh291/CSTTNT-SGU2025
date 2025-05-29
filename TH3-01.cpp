#include <iostream>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;

const int INF = INT_MAX; 
int n;
vector<vector<int>> cost;
vector<bool> daDi;

void docFile(const string &tenFile, int &n, vector<vector<int>> &cost) {
    ifstream input(tenFile);
    if (!input) {
        cout << "Khong the mo file " << tenFile << endl;
        exit(1);
    }

    input >> n;
    cost.assign(n, vector<int>(n)); 

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            input >> cost[i][j];
            if (cost[i][j] == 0 && i != j) {
                cost[i][j] = INF;
            }
        }
    }

    input.close();
}

int greedyTSP(int batDau) {
    int tongChiPhi = 0;
    int hienTai = batDau;
    daDi.assign(n, false);
    
    daDi[hienTai] = true;

    for (int i = 1; i < n; i++) {
        int thanhPhoGanNhat = -1;
        int chiPhiMin = INF;
        
        for (int j = 0; j < n; j++) {
            if (!daDi[j] && cost[hienTai][j] < chiPhiMin) {
                chiPhiMin = cost[hienTai][j];
                thanhPhoGanNhat = j;
            }
        }

        if (thanhPhoGanNhat == -1) {
            cout << "Khong co duong di giua cac thanh pho" << endl;
            return -1; 
        }

        daDi[thanhPhoGanNhat] = true;
        tongChiPhi += chiPhiMin;
        hienTai = thanhPhoGanNhat;
    }

    if (cost[hienTai][batDau] == INF) {
        cout << "Khong the quay lai thanh pho bat dau" << endl;
        return -1; 
    }

    tongChiPhi += cost[hienTai][batDau]; 
    return tongChiPhi;
}

int main() {
    docFile("GTS1a.txt", n, cost); 

    int batDau;
    cout << "Nhap thanh pho bat dau (1-" << n << "): ";
    cin >> batDau;
    
    while (batDau < 1 || batDau > n) {
        cout << "Thanh pho khong hop le. Vui long nhap lai (1-" << n << "): ";
        cin >> batDau;
    }

    batDau -= 1; // vì chỉ số mảng bắt đầu từ 0

    // Kiểm tra các cặp không có đường đi
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (cost[i][j] == INF && i != j) {
                cout << "Khong co duong di giua thanh pho " << i + 1 << " va " << j + 1 << endl;  
            }
        }
    }

    int chiPhiMin = greedyTSP(batDau); 
    if (chiPhiMin != -1) {
        cout << "Chi phi nho nhat: " << chiPhiMin << endl; 
    }

    return 0;
}
