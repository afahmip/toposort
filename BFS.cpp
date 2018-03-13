#include <bits/stdc++.h>

using namespace std;

/*
Sample input (based on spec task's DAG):
5
1 2
2 0 3
0
2 0 2
2 1 3
*/

int main() {
    struct {
        int node;
        bool flag;
    } indegree[20];
    vector<int> adjlist[20];
    int node_amount, nodes_visited;
    vector<int> answer;

    // BFS dictionary
    queue<int> status;
    int now, next;
    int time = 0;

    // Input DAG
    cin >> node_amount;
    for(int i=0; i<node_amount; i++) {
        // How many neighbors
        int neighbor_amount; cin >> neighbor_amount;
        // Input neighbors
        for(int j=0; j<neighbor_amount; j++) {
            int x; cin >> x;
            adjlist[i].push_back(x);
        }
    }

    // Create indegree
    for(int i=0; i<node_amount; i++) {
        indegree[i].flag = false;
        indegree[i].node = 0;
        for(int j=0; j<adjlist[i].size(); j++) {
            indegree[i].node++;
        }
    }

    // Find node that has 0 indegree
    nodes_visited = 0;
    for(int i=0; i<node_amount; i++) {
        if(indegree[i].node == 0) {
            status.push(i);
            break;
        }
    }
    
    // BFS starts
    answer.push_back(status.front());
    while(nodes_visited != node_amount) {
        now = status.front();
        nodes_visited++;
        status.pop();
        indegree[now].flag = true;

        // DEBUG
        cout << "hehe " << now << " " << adjlist[now].size() << endl;
        
        // If there are any neighbors around its node
        for(int i=0; i<node_amount; i++) {
            // If there are any neighbors around its node
            if(adjlist[i].size() > 0) {
                // DEBUG
                cout << "this " << i << " " << adjlist[i].size() << endl;
                // Reduce node degree that connected with this degree by 1
                for(int j=0; j<adjlist[i].size(); j++) {
                    if(adjlist[i][j] == now && adjlist[i][j] != -1) {
                        // DEBUG
                        cout << "HEHE " << i << endl;
                        adjlist[i][j] = -1;
                        indegree[i].node--;
                    }
                }
            }
        }

        // DEBUG
        for(int i=0; i<node_amount; i++) {
            if(adjlist[i].size() > 0)
                for(int j=0; j<adjlist[i].size(); j++) {
                    cout << adjlist[i][j] << " ";
                }
            cout << endl;
        }

        // DEBUG
        for(int i=0; i<node_amount; i++) cout << indegree[i].node << " ";
        cout << endl;
        for(int i=0; i<node_amount; i++) cout << indegree[i].flag << " ";
        cout << endl;

        // If finished visiting all connected nodes,
        // and there still any nodes unvisited, find node that has 0 indegree
        for(int i=0; i<node_amount; i++) {
            if(indegree[i].node == 0 && indegree[i].flag == false) {
                status.push(i);
                answer.push_back(status.front());
                break;
            }
        }

        cout << endl;
    }

    // Print result
    cout << "RESULT: ";
    for(int i=0; i<answer.size(); i++) cout << answer[i] << " ";
    cout << endl;
}