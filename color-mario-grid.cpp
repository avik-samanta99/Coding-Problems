#include <bits/stdc++.h>
using namespace std;

bool isPossible(vector<vector<char>> &board, int row, int col, char c){

    // check up
    if(row-1>=0 && board[row-1][col]==c){
        if(row-2>=0 && board[row-2][col]==c) return false;
    }
    
    // check down
    if(row+1<8 && board[row+1][col]==c){
        if(row+2<8 && board[row+2][col] ==c) return false;
    }
    
    //check left
    if(col-1>=0 && board[row][col-1]==c){
        if(col-2>=0 && board[row][col-2]==c) return false;
    }
    
    //check right
    if(col+1<16 && board[row][col+1]==c){
        if(col+2<16 && board[row][col+2] == c) return false;
    }
    
    if(row-1>=0 && board[row-1][col] == c && row+1<8 && board[row+1][col]==c) 
        return false;
    if(col-1>=0 && board[row][col-1] == c && col+1<16 && board[row][col+1]==c) 
        return false;
    
    return true;
}

bool backtrackPlacement(vector<vector<char>> &board, int numViruses, 
                        deque<int> &available, vector<char> &colours){
    
    if(numViruses==0) return true;
    if(available.size()==0) return false;
    
    int r = rand()%((int)available.size());
    auto it = next(available.begin(), r);
    int randPosition = *it;
    int row = randPosition / 16;
    int col = randPosition % 16;
    
    available.erase(it);
    
    // for(int i = 0; i < 3; i ++){
    //     board[row][col] = colours[i];
    //     if(isPossible(board, row, col, colours[i])){
    //         if(backtrackPlacement(board, numViruses-1, available, colours)) 
    //             return true;
    //     }
    //     board[row][col] = '.';
    // }
    
    int attempt = 5;
    while(attempt --) {
        int i = rand() % 3;
        board[row][col] = colours[i];
        if(isPossible(board, row, col, colours[i])){
            if(backtrackPlacement(board, numViruses-1, available, colours)) 
                return true;
        }
        board[row][col] = '.';
    }
    
    available.push_back(randPosition);
    return false;
}

vector<vector<char>> placeVirusUtils(int numViruses){
    deque<int> available;
    for(int i = 0; i < 128; i ++){
        available.push_back(i);
    }
    vector<vector<char>> board(8, vector<char>(16, '.'));
    vector<char> colours={'R','Y','B'};;
    backtrackPlacement(board, numViruses, available, colours);
    return board;
}

void placeVirus(int numVirus) {
    vector<vector<char>> board = placeVirusUtils(numVirus);
    for(int i = 0; i < 8; i ++) {
        for(int j = 0; j < 16; j ++) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

int main() {
    srand(time(0));
    placeVirus(128);
    return 0;
}
