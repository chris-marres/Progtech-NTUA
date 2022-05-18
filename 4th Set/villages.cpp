#include <iostream>  
#include <vector>  
using namespace std;  
    
struct village{  
    vector<int> connections;  
    bool visited = false;  
};  
    
void checkEveryConnections(village &v, village* villages){  
    v.visited = true;  
    for(int i = 0; i < v.connections.size(); i++){  
        if (!villages[v.connections[i]].visited) checkEveryConnections(villages[v.connections[i]], villages);  
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
        villages[b].connections.push_back(a);  
    }  
    
    int groups = 0;  
    for (int i = 1; i <= N; i++){  
        if (!villages[i].visited){  
            checkEveryConnections(villages[i], villages);  
            groups++;  
        }  
    }  
    
    int diff = groups - K;  
    if (diff > 1) cout << diff << endl;  
    else cout << 1 << endl;  
    
    return 0;  
}  