#include <iostream>
#include <vector>
using namespace std;

struct village{
    vector<int> connections;
    int group = 0;
    bool visited = false;
};

void checkEveryConnections(int group, village v, village* villages){
    for(int i = 0; i < v.connections.size(); i++){
        v.visited = true;
        v.group = group;
        if (!villages[v.connections[i]].visited) checkEveryConnections(group, villages[v.connections[i]], villages);
    }
}

int main(){

    int N, M, K;

    cin >> N >> M >> K;

    village* villages = new village[N+1];

    for (int i = 0; i < M; i++){
        int a, b;
        cin >> a >> b;
        villages[a].connections.push_back(b);
    }

    for (int i = 1; i <= N; i++){
        if (!villages[i].visited) checkEveryConnections(i, villages[i], villages);
    }


    for (int i = 1; i <= N; i++){
        cout << "Village " << i << " belongs to group " << villages[i].group << endl;
    }

    return 0;
}