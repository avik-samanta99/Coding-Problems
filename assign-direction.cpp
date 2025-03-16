vector<vector<int>> dir = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
unordered_map<int,string> dirMapper = {{0, "Right"}, {1, "Left"}, {2, "Up"}, {3, "Down"}, {-1, "-"}};
vector<vector<bool>> visited;
vector<int> colors;
int n, m;

bool isPossible(int x, int y, vector<vector<int>> &grid) {
    if(x<0 || x>=n || y<0 || y>=m || visited[x][y] == true) return false;
    if(grid[x][y] == -1) return true;
    
    int cur_color = grid[x][y];
    int assignedDir = colors[cur_color];
    visited[x][y] = true;
    
    if(assignedDir != -1) {
        int nx = x + dir[assignedDir][0]; 
        int ny = y + dir[assignedDir][1];
        if(isPossible(nx, ny, grid)) return true;
    } 
    else {
        for(int i = 0; i < dir.size(); i ++) {
            colors[cur_color] = i;
            int nx = x + dir[i][0]; 
            int ny = y + dir[i][1];
            if(isPossible(nx, ny, grid)) return true;
        }
        colors[cur_color] = -1;
    }
    
    visited[x][y] = false;    
    return false;
}

vector<int> solve(vector<vector<int>> &grid) {
    n = grid.size();
    m = grid[0].size();
    colors.resize(8,-1);
    visited.resize(n, vector<bool> (m, false));
    
    if(isPossible(0, 0, grid)) return colors;
    return {};
}

int main() {
    int n, m; 
    cin >> n >> m;
    vector<vector<int>> grid(n,vector<int> (m));    
    for(auto &row: grid) {
        for(auto &col: row) {
            cin >> col;
        }
    }
    
    vector<int> res = solve(grid);
    if(res.size() == 0) cout << "Not Possible !!!";
    else for(int i = 0; i < res.size(); i ++) {
        if(res[i] != -1) cout << i << ": " << dirMapper[res[i]] << ", ";
    }
    
    return 0;
}
