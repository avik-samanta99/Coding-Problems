#include<bits/stdc++.h>
using namespace std;


vector<int> dir_x = {0, -1, 0, 1};
vector<int> dir_y = {-1, 0, 1, 0};


class cityTour {
private:
    int rows, cols;
    vector<int> parent, rank;
    vector<int> max_column, min_column;

public:
    cityTour(int m, int n) {
        rows = m;
        cols = n;
        parent.resize(m*n + 1, -1);
        rank.resize(m*n + 1, 0);
        max_column.resize(m*n + 1, INT_MIN);
        min_column.resize(m*n + 1, INT_MAX);
    }
    
    int findParentUtils(int node) {
        if(parent[node] == node) return node;
        parent[node] = findParentUtils(parent[node]);
        return parent[node];
    }
    
    int findParent(int x, int y) {
        int node = cols * x + y;
        if(parent[node] == -1) return -1;
        return findParentUtils(node);
    }
    
    pair<int, int> mergeNodes(int x1, int y1, int x2, int y2) {
        int node_parent = findParent(x1, y1);
        int neigh_parent = findParent(x2, y2);
        if(neigh_parent == -1 or node_parent == neigh_parent) 
            return {min_column[node_parent], max_column[node_parent]};
        
        if(rank[node_parent] > rank[neigh_parent]) {
            parent[neigh_parent] = node_parent;
            min_column[node_parent] = min(min_column[node_parent], min_column[neigh_parent]);
            max_column[node_parent] = max(max_column[node_parent], max_column[neigh_parent]);
            return {min_column[node_parent], max_column[node_parent]};
        }
        else if(rank[node_parent] < rank[neigh_parent]) {
            parent[node_parent] = neigh_parent;
            min_column[neigh_parent] = min(min_column[node_parent], min_column[neigh_parent]);
            max_column[neigh_parent] = max(max_column[node_parent], max_column[neigh_parent]);
            return {min_column[neigh_parent], max_column[neigh_parent]};
        }
        else {
            parent[neigh_parent] = node_parent;
            rank[node_parent] ++;
            min_column[node_parent] = min(min_column[node_parent], min_column[neigh_parent]);
            max_column[node_parent] = max(max_column[node_parent], max_column[neigh_parent]);
            return {min_column[node_parent], max_column[node_parent]};
        }
    }
    
    bool addLand(int x, int y) {
        int node = cols * x + y;
        rank[node] = 1;
        parent[node] = node;
        min_column[node] = max_column[node] = y;
        
        bool path_created = false;
        for(int i = 0; i < 4; i ++) {
            int n_x = x + dir_x[i], n_y = y + dir_y[i];
            if(min(n_x, n_y) >= 0 and n_x < rows and n_y < cols) {
                pair<int, int> columns = mergeNodes(x, y, n_x, n_y);
                if(columns.first == 0 and columns.second == cols-1) 
                    path_created = true;
            }
        }
        
        return path_created;
    }
};


int main() {
    
    cityTour country(8, 5);
	
    country.addLand(5, 4) ? cout << "Created\n" : cout << "No connection\n";
	country.addLand(6, 4) ? cout << "Created\n" : cout << "No connection\n";
	country.addLand(0, 2) ? cout << "Created\n" : cout << "No connection\n";
	country.addLand(1, 0) ? cout << "Created\n" : cout << "No connection\n";
	country.addLand(3, 4) ? cout << "Created\n" : cout << "No connection\n";
	country.addLand(1, 2) ? cout << "Created\n" : cout << "No connection\n";
	country.addLand(2, 2) ? cout << "Created\n" : cout << "No connection\n";
	// country.addLand(2, 4) ? cout << "Created\n" : cout << "No connection\n";
	country.addLand(1, 1) ? cout << "Created\n" : cout << "No connection\n";
	country.addLand(2, 3) ? cout << "Created\n" : cout << "No connection\n";
    country.addLand(3, 3) ? cout << "Created\n" : cout << "No connection\n";
	
	return 0;
}
