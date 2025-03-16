#include<bits/stdc++.h>
using namespace std;

class Node {
    public:
        string name;
        bool is_file;
        unordered_map<string, Node *> childrens;
        int children_count;
        Node() {
            name = "";
            is_file = false;
            children_count = 0;
        }
};

class Trie {
    private:
        Node *root;
    public:
        Trie() {
            root = new Node();
        }
        
        vector<string> getPathComponents(string &path) {
            vector<string> components;
            string temp = "";
            for(char c: path) {
                if(c != '/') temp += c;
                else {
                    components.push_back(temp);
                    temp = "";
                }
            }
            components.push_back(temp);
            return components;
        }
        
        void addPath(string &path) {
            vector<string> components = getPathComponents(path);
            Node *temp = root;
            string path_till_now = "";
            for(int i = 0; i < components.size(); i ++) {
                string component = components[i];
                if(!temp -> childrens.count(component)) {
                    temp -> childrens[component] = new Node();
                    temp -> children_count ++;
                }
                
                temp = temp -> childrens[component];
                
                if(i > 0) path_till_now += "/";
                path_till_now += component;
                
                temp -> name = path_till_now;
                if(i == components.size() - 1)
                    temp -> is_file = true;
            }
        }
    
        int compressSelectionUtils(Node *node, unordered_set<string> &paths, unordered_set<string> &compressed_paths) {
            if(paths.count(node -> name)) {
                compressed_paths.insert(node -> name);
                return 1;
            }
            
            if(node -> is_file) return 0;
            
            int children_selected = 0;
            for(auto item: node -> childrens) {
                string name = item.first;
                Node *child = item.second;
                int count = compressSelectionUtils(child, paths, compressed_paths);
                
                if(count == 1) children_selected ++;
            }
            
            if(children_selected == node -> children_count) {
                for(auto item: node -> childrens) {
                    string child_name = item.first;
                    compressed_paths.erase(node -> name + "/" + child_name);   
                }
                compressed_paths.insert(node -> name);
                return 1;
            }
            
            return 0;
        }
    
        vector<string> compressSelection(vector<string> &selected_paths) {
            unordered_set<string> paths(selected_paths.begin(), selected_paths.end());
            unordered_set<string> compressed_paths_set;
            
            int count = compressSelectionUtils(root, paths, compressed_paths_set);
            vector<string> compressed_paths(compressed_paths_set.begin(), compressed_paths_set.end());
            return compressed_paths;
        }
};


int main(){

    vector<string> all_files = {"a/b.txt", "b/c.txt", "b/d.txt", "c/e.txt", "c/f/a.txt", "c/f/b.txt", "c/g.txt", "d/a/b.txt"};
    vector<string> selected_files = {"b/c.txt", "b/d.txt", "c/e.txt", "c/f/a.txt", "c/f/b.txt", "d/a/b.txt"};

    Trie files_tree;
    for(string &file_path: all_files) {
        files_tree.addPath(file_path);
    }
    
    vector<string> compressed_selection = files_tree.compressSelection(selected_files);
    for(string &path: compressed_selection) {
        cout << path << "\n";
    }
    
    return 0;
}
