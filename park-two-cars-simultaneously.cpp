#include<bits/stdc++.h>
using namespace std;

bool is_valid(int x, int y, int n, int m) {
    return (x >= 0 && x < n && y >= 0 && y < m);
}

// generic bfs function. if flag is true then it tries to find b, otherwise it checks if discoverable graph from a is nonlinear
bool bfs_generic(pair<int, int> a, pair<int, int> b, vector<string> &matrix, bool flag) {
    int n = matrix.size();
    int m = matrix[0].size();

    vector<vector<bool>> vis(n, vector<bool>(m, false));
    vector<pair<int, int>> dir = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    queue<pair<int, int> > q; 
    q.push(a);
    vis[a.first][a.second] = true;


    while(!q.empty()) {
        pair<int, int> vertex = q.front();
        q.pop();
        
        int cnt = 0;
        for(auto it : dir) {
            int x = vertex.first + it.first, y = vertex.second + it.second;

            // if flag is true we're trying to find b
            if(flag) {
                if(make_pair(x, y) == b) return true; 
            }

            if(is_valid(x, y, n, m) && matrix[x][y] != '#') {
                cnt++; // valid neighbor for vertex
                if(!vis[x][y]) {
                    vis[x][y] = true;
                    q.push(make_pair(x, y));
                }
            }
        }
        // if flag is false we're trying to see if the graph is non-linear
        if(!flag && cnt > 2) {
            return true; // vertex v has more than 2 valid neighbors, we can use this vertex to reverse order of a, b
        }
    }
    return false;
}

pair<int, int> search(int n, int m, vector<string> &matrix, char c) {
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) if(matrix[i][j] == c) return make_pair(i, j);
    assert(false);
}

bool solve(int n, int m, vector<string> &matrix) {
    pair<int, int> a = search(n, m, matrix, 'a');
    pair<int, int> b = search(n, m, matrix, 'b');
    pair<int, int> A = search(n, m, matrix, 'A');
    pair<int, int> B = search(n, m, matrix, 'B');

    if(!(bfs_generic(a, A, matrix, true) && bfs_generic(b, B, matrix, true))) return false;

    matrix[B.first][B.second] = '#';
    bool is_connected_a_A = bfs_generic(a, A, matrix, true);
    matrix[B.first][B.second] = 'B';

    matrix[A.first][A.second] = '#';
    bool is_connected_b_B = bfs_generic(b, B, matrix, true);
    matrix[A.first][A.second] = 'B';

    if(is_connected_a_A &&  is_connected_b_B) return true;
    else return bfs_generic(a, {-1, -1}, matrix, false);

}

int main() {
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);
    
    int T;
    cin >> T;
    
    while(T--) {
        int n, m;
        cin >> n >> m;
        
        vector<string> matrix(n);
        for(int i = 0; i < n; i++) cin >> matrix[i];
        cout << (solve(n, m, matrix) ? "YES" : "NO") << endl;
    }
}
