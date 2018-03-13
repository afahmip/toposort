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
    int adjlist[20][20];
    int node_amount, nodes_visited;
    bool visit[20];
    map<int,int>topolist;
    vector<pair<int,int> >toposort;

    // DFS dictionary
    stack<int>node;
    int now, next;
    int time = 0;

    cin >> node_amount;
    for(int i=0; i<node_amount; i++) {
        // How many neighbors
        cin >> adjlist[i][0];
        topolist[adjlist[i][0]] = 0;
        // Input neighbors
        for(int j=1; j<=adjlist[i][0]; j++) {
            cin >> adjlist[i][j];
        }
    }  

    // DFS starts
    nodes_visited = 0;
    memset(visit, 0, sizeof visit);
    node.push(0);
    while(nodes_visited != node_amount) {
        now = node.top();
        visit[now] = true;
        nodes_visited++;
        node.pop();

        time++;
        topolist[now] = time;
        
        // If there are any neighbors around its node
        if(adjlist[now][0] > 0) {
            for(int i=1; i<=adjlist[now][0]; i++) {
                next = adjlist[now][i];
                time++;
                topolist[next] = time;

                if(!visit[next]) {
                    visit[next] = true;
                    node.push(next);
                } else {
                    time++;
                    topolist[next] = time;
                }
            }
        }

        // If finished visiting all connected nodes,
        // and there still any nodes unvisited, find the index
        for(int i=0; i<node_amount; i++) {
            if(!visit[i]) {
                node.push(i);
                break;
            }
        }
    }

    for(int i=0; i<node_amount; i++) {
        toposort.push_back(make_pair(topolist[i], i));
    }
    sort(toposort.rbegin(), toposort.rend());
    
    // Print result
    cout << "RESULT: ";
    for(int i=0; i<node_amount; i++) {
        cout << toposort[i].second << " ";
    }
    cout << endl;
}