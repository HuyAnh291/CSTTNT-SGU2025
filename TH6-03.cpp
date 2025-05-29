#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <cmath>
#include <algorithm>

using namespace std;

const int N = 3;

// Trạng thái của bảng TACI
struct State {
    vector<vector<int>> board;
    int g; 
    int h; 
    int x, y; 
    string path; 

    bool operator>(const State &other) const {
        return (g + h) > (other.g + other.h);
    }
};

// Khởi tạo bảng start và goal
vector<vector<int>> start = {
    {2, 8, 3},
    {1, 6, 4},
    {7, 0, 5}
};

vector<vector<int>> goal = {
    {1, 2, 3},
    {8, 0, 4},
    {7, 6, 5}
};

// Tính hàm heuristic (tổng khoảng cách Manhattan)
int calculate_h(const vector<vector<int>> &board) {
    int h = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int val = board[i][j];
            if (val != 0) {
                int goalX = val / N;
                int goalY = val % N;
                h += abs(i - goalX) + abs(j - goalY);
            }
        }
    }
    return h;
}

// Kiểm tra xem bảng hiện tại có phải đích không
bool is_goal(const vector<vector<int>> &board) {
    return board == goal;
}

// Tìm vị trí ô trống (số 0)
pair<int, int> find_0(const vector<vector<int>> &board) {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (board[i][j] == 0) return {i, j};
    return {-1, -1};
}

// Giải bài toán bằng thuật toán A*
void solve_taci(const vector<vector<int>> &startBoard) {
    priority_queue<State, vector<State>, greater<State>> open;
    map<vector<vector<int>>, int> visited;

    auto [x0, y0] = find_0(startBoard);

    State start = {startBoard, 0, calculate_h(startBoard), x0, y0, ""};
    open.push(start);
    visited[startBoard] = 0;

    int dx[] = {-1, 1, 0, 0}; 
    int dy[] = {0, 0, -1, 1};
    char moveChar[] = {'U', 'D', 'L', 'R'};

    while (!open.empty()) {
        State current = open.top();
        open.pop();

        if (is_goal(current.board)) {
            cout << "Da tim thay duong di voi so buoc: " << current.g << endl;
            cout << "Chuoi buoc di (U: len, D: xuong, L: trai, R: phai): " << current.path << endl;
            return;
        }

        for (int dir = 0; dir < 4; ++dir) {
            int nx = current.x + dx[dir];
            int ny = current.y + dy[dir];

            if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
                vector<vector<int>> nextBoard = current.board;
                swap(nextBoard[current.x][current.y], nextBoard[nx][ny]);

                int nextG = current.g + 1;
                if (!visited.count(nextBoard) || visited[nextBoard] > nextG) {
                    visited[nextBoard] = nextG;
                    int nextH = calculate_h(nextBoard);
                    State next = {nextBoard, nextG, nextH, nx, ny, current.path + moveChar[dir]};
                    open.push(next);
                }
            }
        }
    }

    cout << "Khong tim duoc duong di den dich." << endl;
}


int main() {
    solve_taci(start); 
    return 0;
}
