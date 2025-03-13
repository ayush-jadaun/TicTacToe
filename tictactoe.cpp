#include<bits/stdc++.h>
using namespace std;

const char X = 'X', O = 'O', E = ' ';

void print(vector<vector<char>>& b) {
    cout << "\n";
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << b[i][j];
            if (j < 2) cout << " | ";
        }
        cout << "\n";
        if (i < 2) cout << "--|---|--\n";
    }
    cout << "\n";
}

bool win(vector<vector<char>>& b, char p) {
    for (int i = 0; i < 3; ++i) 
        if ((b[i][0] == p && b[i][1] == p && b[i][2] == p) || 
            (b[0][i] == p && b[1][i] == p && b[2][i] == p))
            return true;
    return (b[0][0] == p && b[1][1] == p && b[2][2] == p) || 
           (b[0][2] == p && b[1][1] == p && b[2][0] == p);
}

bool full(vector<vector<char>>& b) {
    for (auto& r : b)
        for (char c : r)
            if (c == E) return false;
    return true;
}

pair<int, int> mm(vector<vector<char>>& b, char p, int d) {
    if (win(b, X)) return {10 - d, -1};
    if (win(b, O)) return {-10 + d, -1};
    if (full(b)) return {0, -1};

    int bs = (p == X) ? numeric_limits<int>::min() : numeric_limits<int>::max();
    int bm = -1;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (b[i][j] == E) {
                b[i][j] = p;
                int sc = mm(b, (p == X) ? O : X, d + 1).first;
                b[i][j] = E;
                if ((p == X && sc > bs) || (p == O && sc < bs)) {
                    bs = sc;
                    bm = i * 3 + j;
                }
            }
        }
    }
    return {bs, bm};
}

void pMove(vector<vector<char>>& b, char p) {
    int m;
    while (true) {
        cout << "Player " << p << ", your move (1-9): ";
        cin >> m;
        --m;
        int r = m / 3, c = m % 3;
        if (m >= 0 && m < 9 && b[r][c] == E) {
            b[r][c] = p;
            break;
        }
        cout << "Invalid! Try again.\n";
    }
}

void aiMove(vector<vector<char>>& b, char ai, char hm) {
    cout << "AI is thinking...\n";
    int bm = mm(b, ai, 0).second;
    int r = bm / 3, c = bm % 3;
    b[r][c] = ai;
}

int main() {
    int mode;
    cout << "Tic-Tac-Toe! Mode:\n1. Single (vs AI)\n2. Multi\nChoose: ";
    cin >> mode;

    vector<vector<char>> b(3, vector<char>(3, E));
    char cur = X;

    if (mode == 1) {
        char hm, ai;
        cout << "Your symbol (X/O): ";
        cin >> hm;
        ai = (hm == X) ? O : X;

        while (true) {
            print(b);
            if (cur == hm) pMove(b, hm);
            else aiMove(b, ai, hm);

            if (win(b, cur)) {
                print(b);
                cout << "Player " << cur << " wins!\n";
                break;
            }
            if (full(b)) {
                print(b);
                cout << "Draw!\n";
                break;
            }
            cur = (cur == X) ? O : X;
        }
    } else {
        while (true) {
            print(b);
            pMove(b, cur);

            if (win(b, cur)) {
                print(b);
                cout << "Player " << cur << " wins!\n";
                break;
            }
            if (full(b)) {
                print(b);
                cout << "Draw!\n";
                break;
            }
            cur = (cur == X) ? O : X;
        }
    }
    return 0;
}
