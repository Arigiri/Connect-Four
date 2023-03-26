#include <bits/stdc++.h>
using namespace std;
typedef vector<vector<int>> state;


const int width = 7, height = 6;


state read() // read data from map
{
    state mat;
    freopen("map.txt", "r", stdin);
    for(int i = 0; i < height; i++) {
        vector <int> v;
        for (int j = 0 ; j < width; j++) {
            int x;
            cin >> x;
            v.push_back(x);
        }
        mat.push_back(v);
    }
    return mat;
}
void MakeDecision(pair<int, int> result)
{
    ///make any decision here
    //pair<int, int> result = {0, 1}; 

    freopen("decision.txt", "w", stdout);
    cout << result.second << ' ' << result.first; // in ra 2 số lần lượt là tọa độ x và tọa độ y của bảng
}

//in ra bàn cờ
void printState(state mat) {
    cout << "-----------------------------\n";
    for (int i = 0; i < height; i++) {
        cout << "| ";
        for (int j = 0; j < width; j++) {
            cout << mat[i][j] << " | ";
        }
        cout << "\n";
        cout << "-----------------------------\n";
    }
}

//kiểm tra hàng
bool checkRow(state mat, int x, int y) {
    int val = mat[x][y];
    int count = 1;
    for (int i = 1; i <= 3 && y + i < width; i++) {
        if (mat[x][y + i] == val) {
            count++;
        } else {
            break;
        }
        
    }
    for (int i = 1; i <= 3 && y - i >= 0; i++) {
        if (mat[x][y - i] == val) {
            count++;
        } else {
            break;
        }
    }
    return count >= 4;
}

//Kiểm tra cột
bool checkCol(state mat, int x, int y) {
    int val = mat[x][y];
    int count = 1;
    for (int i = 1; i <= 3 && x + i < height; i++) {
        if (mat[x + i][y] == val) {
            count++;
        } else {
            break;
        }
    }
    for (int i = 1; i <= 3 && x - i >= 0; i++) {
        if (mat[x - i][y] == val) {
            count++;
        } else {
            break;
        } 
    }
    return count >= 4;
}


//Kiểm tra đường chéo
bool checkCross(state mat, int x, int y) {
    int count1 = 0;
    int count2 = 0;
    for (int i = 1; i <= 3 && y + i < width && x + i < height ; i++)
    {
        if (mat[x][y] == mat[x + i][y + i])
        {
            count1++;
        }
        else
        {
            break;
        }
    }
    for (int i = 1; i <= 3 && y - i >= 0 && x - i >= 0; i++)
    {
        if (mat[x][y] == mat[x - i][y - i])
        {
            count1++;
        }
        else
        {
            break;
        }
    }
    for (int i = 1; i <= 3 && y + i < width && x - i >= 0; i++)
    {
        if (mat[x][y] == mat[x - i][y + i])
        {
            count2++;
        }
        else
        {
            break;
        }
    }
    for (int i = 1; i <= 3 && y - i >= 0 && x + i < height; i++)
    {
        if (mat[x][y] == mat[x + i][y - i])
        {
            count2++;
        }
        else
        {
            break;
        }
    }
    return (count1 == 3 || count2 == 3);
}

//Kiểm tra game kết thúc chưa
bool checkEnd(state mat) {
    int count = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (mat[i][j] != 0) {
                if (checkCol(mat, i, j)) return true;
                if (checkCross(mat, i, j)) return true;
                if (checkRow(mat, i, j)) return true;
                count++;
            }
        }
    }
    if (count == 42) return true;
    return false;
}

//Kiểm tra người thắng
int whoWin(state mat) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (mat[i][j] != 0) {
                if (checkCol(mat, i, j)) return mat[i][j];
                if (checkCross(mat, i, j)) return mat[i][j];
                if (checkRow(mat, i, j)) return mat[i][j];
            }
        }
    }
    return 0;
}

//Lấy ra vị trí dưới cùng của cột chưa được đánh
int getLast(state mat, int col) {
    for (int i = height - 1; i >= 0; i--) {
        if (mat[i][col] == 0) return i;
    }
    return -1;
}

//Trả về nước đi hiện tại
int moveNow(state mat) {
    int count = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (mat[i][j] != 0) count++;
        }
    }
    return (count % 2 == 0 ? 1 : -1);
}

//Đếm số lượng quân cờ đã đánh
int countChess(state mat) {
    int count = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (mat[i][j] != 0) count++;
        }
    }
    return count;
}

//Tạo ra tất cả trạng thái tiếp theo
vector<state> allMove(state mat) {
    vector<state> all;
    srand(time(NULL));
    int res = rand() % (6 - 0 + 1) + 0;
    int countMove = res;
    for (int i = countMove; i < width; i++) {
        int rowLast = getLast(mat, i);
        if (rowLast != -1) {
           mat[rowLast][i] = moveNow(mat);
           all.push_back(mat);
           mat[rowLast][i] = 0;
        }
    }
    for (int i = 0; i < countMove; i++) {
        int rowLast = getLast(mat, i);
        if (rowLast != -1) {
           mat[rowLast][i] = moveNow(mat);
           all.push_back(mat);
           mat[rowLast][i] = 0;
        }
    }
    return all;
}

//Tính điểm trạng thái cờ
int pointMove(state mat, int depth, int alpha, int beta, bool maxMin) {
    if (depth == 0) return 0;
    if (checkEnd(mat)) return whoWin(mat) * -1 * depth;
    vector<state> all = allMove(mat);
   
    int bestScore = -10;
    for (state nextState : all) {
        int score = pointMove(nextState, depth - 1, alpha, beta, !maxMin);
        if (maxMin) {
            if (bestScore < score || bestScore == -10) {
                bestScore = score;
            }
            if (bestScore >= beta) return score;
            alpha = max(bestScore, alpha);
        } else {
            if (bestScore > score || bestScore == -10) {
                bestScore = score;
            }
            if (bestScore <= alpha) return score;
            beta = min(bestScore, beta);
        }
    }
    return bestScore;
}


state bestMove(state mat) {
    int alpha = -100;
    int beta = 100;
    bool maxMin = false;
    vector<state> all = allMove(mat);
    int depth;
    int countMoved = countChess(mat);
    if (countMoved <= 7) depth = 6;
    else if (countMoved > 7 && countMoved <= 16) depth = 7;
    else if (countMoved > 16) depth = 8;
    int bestScore = -10;
    int score;
    state bestState;
    for (int i = 0; i < all.size(); i++) {
        score = pointMove(all[i], depth, alpha, beta, maxMin);
        if (score > bestScore || bestScore == -10) {
            bestScore = score;
            bestState = all[i];
        }
    } 
    return bestState;
}

pair<int, int> point(state mat, state nextMat) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (mat[i][j] != nextMat[i][j]) {
                return make_pair(i,j);
            }
        }
    }
}

void play(state mat) {
    while (!checkEnd(mat)) {
        printState(mat);
        int x, y;
        cin >> x >> y;
        mat[x][y] = 1;
        printState(mat);
        if (checkEnd(mat)) break;
        state preMat = mat;
        mat = bestMove(mat);
        printState(mat);
        pair<int, int> result = point(preMat, mat);
        cout << result.first << " " << result.second << "\n";
    }
}

int main()
{
    state mat;//(height, vector<int> (width, 0));
    //mat[0][0] = 0; mat[0][1] = 0; mat[0][2] = 0; mat[0][3] = 0; mat[0][4] = 0; mat[0][5] = 0; mat[0][6] = 0;
    //mat[1][0] = 0; mat[1][1] = 0; mat[1][2] = 0; mat[1][3] = 0; mat[1][4] = 0; mat[1][5] = 0; mat[1][6] = 0;
    //mat[2][0] = 0; mat[2][1] = 0; mat[2][2] = 0; mat[2][3] = 0; mat[2][4] = 0; mat[2][5] = 0; mat[2][6] = 0;
    //mat[3][0] = 0; mat[3][1] = 0; mat[3][2] = 0; mat[3][3] = 0; mat[3][4] = 0; mat[3][5] = 0; mat[3][6] = 0;
    //mat[4][0] = 0; mat[4][1] = 0; mat[4][2] = 0; mat[4][3] = 0; mat[4][4] = 0; mat[4][5] = 0; mat[4][6] = 0;
    //mat[5][0] = 0; mat[5][1] = 0; mat[5][2] = 0; mat[5][3] = 0; mat[5][4] = 0; mat[5][5] = 0; mat[5][6] = 0;
    mat = read();
    pair<int, int> result = point(mat, bestMove(mat));
    MakeDecision(result);
    //play(mat);
}