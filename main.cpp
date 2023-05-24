#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
using namespace std;


class EightPuzzle{
  
private:
    string start;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> frontier;
    map<string, bool> visted;
    map<string, string> parent;
    vector<string> path;
    map<string, int> depth;
    
    // Get Manhatten Distance between two points
    int getDist(int x, int y, int x2, int y2){
        return abs(x - x2) + abs(y - y2);
    }

    // Get the cost to the goal node
    int getCost(string node){
        int cost = 0;
        for(int i = 0 ; i < 9 ; i++){
            int x = i / 3;
            int y = i % 3;
            int val = node[i] - '0';
            int x2 = val / 3;
            int y2 = val % 3;
            cost += getDist(x, y, x2, y2);
        }
        return cost;
    }
    
    // Generating all child nodes of current node
    vector<pair<int, string>> generateChildNodes(string node){
        vector<pair<int, string>> children;
        int pos = 0;
        for(int i = 0 ; i < 9 ; i++){
            if(node[i] == '0'){
                pos = i;
                break;
            }
        }
        // Move empty square down
        if(pos + 3 < 9){
            string newnode = node;
            swap(newnode[pos], newnode[pos+3]);
            int cost = getCost(newnode);
            children.push_back({cost,newnode});
        }
        // Move empty square up
        if(pos - 3 >= 0){
            string newnode = node;
            swap(newnode[pos], newnode[pos-3]);
            int cost = getCost(newnode);
            children.push_back({cost,newnode});
        }
        // Move empty square right
        if(pos % 3 != 2){
            string newnode = node;
            swap(newnode[pos], newnode[pos+1]);
            int cost = getCost(newnode);
            children.push_back({cost,newnode});
        }
        // Move empty square left
        if(pos % 3 != 0){
            string newnode = node;
            swap(newnode[pos], newnode[pos-1]);
            int cost = getCost(newnode);
            children.push_back({cost,newnode});
        }
        return children;
    }
    
    void printNode(string node){
        for(int i = 0 ; i < 9 ; i++){
            if(i % 3 == 0 && i != 0) cout << "\n";
            if(node[i] == '0') cout << '_';
            else cout << node[i];
            cout << ' ';
        }
    }
    
    // Printing the path from the start state to goal state
    void getPath(){
        string current = "012345678";
        while(current != start){
            path.push_back(current);
            if(parent[parent[current]] == current){
                cout << "INVALID";
                exit(0);
            }
            current = parent[current];
        }
        path.push_back(start);
        reverse(path.begin(), path.end());
        for(string node : path){
            printNode(node);
            cout << "\n-------------------\n";
        }
    }
    
    void solve(){
        while(!frontier.empty()){
            pair<int, string> current = frontier.top();
            frontier.pop();
            string node = current.second;
            
            vector<pair<int, string>> children = generateChildNodes(node);
            for(pair<int, string> child : children){
                if(!visted[child.second]){
                    parent[child.second] = node;
                    depth[child.second] = depth[node] + 1;
                    int cost = depth[child.second] + child.first;
                    frontier.push({cost,child.second});
                    visted[child.second] = true;
                }
                if(child.first == 0){
                    return;
                }
            }
        }
    }
    
    
public:
    
    EightPuzzle(string root){
        start = root;
        frontier.push({0,root});
        visted[root] = true;
        depth[root] = 0;
        solve();
        getPath();
    }
    
};


int main(){
    
    EightPuzzle("143826570");

}
