#include <bits/stdc++.h>
using namespace std;

const int width = 7, height = 6;
int mat[10][10]; // save game map

void read()
{
    freopen("map.txt", "r", stdin);
    for(int i = 0; i < height; i++)  
        for(int j = 0; j < width; j++)
            cin >> mat[i][j];
}
void MakeDecision()
{
    ///make any decision here
    pair<int, int> result = {2, 2}; 

    freopen("decision.txt", "w", stdout);
    cout << result.first << ' ' << result.second; // in ra 2 số lần lượt là tọa độ x và tọa độ y của bảng
}
int main()
{
    read();
    MakeDecision();
    
}