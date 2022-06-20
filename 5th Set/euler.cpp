// Usefull link: http://repfiles.kallipos.gr/html_books/3403/main/node46.html
// Based on the above link, the problem simplifies to:
// (a) If all the edges of the grapgh have even ranks, then we have an euler cycle.
// (b) If all the edges of the graph have even ranks, except exactly two edges, then we have an euler path.

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main(){

    int N, M;
    cin >> N >> M;

    int* vertices = new int[N];

    int u, v;
    for (int i = 0; i < M; i++){
        cin >> u >> v;
        vertices[u]++;
        vertices[v]++;
    }

    int odd_count = 0;
    for (int i = 0; i < N; i++){
        if (vertices[i] % 2 == 1){
            odd_count++;
            if (odd_count == 1)
                u = i;
            if (odd_count == 2)
                v = i;
        }
    }

    if (odd_count == 0)
        cout << "CYCLE" << endl;
    else if (odd_count == 2)
        cout << "PATH " << u << " " << v << endl;
    else 
        cout << "IMPOSSIBLE" << endl;

    return 0;
}
