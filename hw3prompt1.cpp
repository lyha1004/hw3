#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<climits>
#include<tuple>
#include<queue>
#include<algorithm>
using namespace std;

int mDist(const vector<int>& d, const vector<bool>& S){
	int min = INT_MAX;
	int index = 0;
	for (int v = 1; v < d.size(); v++){
		if(S[v] == false & d[v] <= min){
			min = d[v];
			index = v;
		}	
		if (min == 0){
			break;
		}
	}
	return index;
}

void sssp(vector<vector<int>>& G, int s, ofstream &output){
	vector<int> d(G.size(), INT_MAX);
	vector<bool> S(G.size(), false);
	
	d[s] = 0;
	priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> Q;
	Q.push(make_pair(0,s));

	while(!Q.empty()){
		int u = Q.top().second;
		Q.pop();

		if(S[u]){
			continue;
		}

		S[u] = true;
		
		for(int v = 0; v < G.size();v++){
			int distance = d[u] + G[u][v];
			if( !S[v] && G[u][v] && d[u] != INT_MAX && distance < d[v]){
				d[v] = distance;
				Q.push(make_pair(d[v],v));
			}
		}
	}
    for (int i = 2; i < G.size(); i++) {
        if (d[i] != INT_MAX) {
            output << "1," << s << ","<< i << "," << d[i] << endl;
        }
    }
}

// mst struct and functions
struct edge_struct {
    int source_vertex;
    int dest_vertex;
    int weight;
};

bool compare_edges (const edge_struct &a, const edge_struct &b)
{
    return a.weight < b.weight;
}

int find_parent(int x, vector<int>& parent)
{
    if (parent[x] != x)
    {
        parent[x] = find_parent(parent[x], parent);
    }
    return parent[x];
}

void kruskal(vector<edge_struct> &edges, int n)
{
    vector <int> parent(n+1);
    vector<edge_struct> mst;
    
    for (int x = 1; x <= n; x++)
    {
        parent[x] = x;
    }
    sort (edges.begin(), edges.end(), compare_edges);
    for (edge_struct e : edges)
    {
        int i = e.source_vertex;
        int j = e.dest_vertex;
        int v = e.weight;
        int parent_i = find_parent(i, parent);
        int parent_j = find_parent(j, parent);
        if (parent_i != parent_j)
        {
            mst.push_back(e);
            parent[parent_i] = parent_j;
        }
    }
    for (edge_struct e : mst)
    {
        output << "1," << e.source_vertex << "," << e.dest_vertex << "," << e.weight << endl;
    }
}


int main(int argc, char* argv[]){
    string inPutFileName = argv[1];
		string outPutFileName = argv[2];
		string alg = argv[3];
	
    ifstream file(inPutFileName);

    string line;
    int i;
    int j;
    int v;
    int numVert = 0;
    vector<tuple<int,int,int>> storage;

    getline(file,line);
    while(getline(file,line)){
        stringstream ss(line);
        string num;
        getline(ss, num, ',');
        i = stoi(num);
				
        getline(ss, num, ',');
        j = stoi(num);
				
        getline(ss, num, ',');
        v = stoi(num);

        storage.push_back(make_tuple(i,j,v));
      
        numVert = max(numVert, max(i,j));
    }
    file.close();
	if(j == numVert){
    vector<vector<int>> adjMat(numVert + 1, vector<int>(numVert + 1, 0));
    for (auto store : storage) {
        i = get<0>(store);
        j = get<1>(store);
				v = get<2>(store);
        adjMat[i][j] = v;
				adjMat[j][i] = v;
		}
	
	
		/*for (int i = 1; i <= numVert; i++) {
      for (int j = 1; j <= numVert; j++) {
          cout << adjMat[i][j] << " ";
      }
      cout << endl;
    }*/
		
	
    ofstream file2(outPutFileName);
		file2 << "G,i,j,v" << endl;
		if (alg == "sssp"){
			sssp(adjMat, 1, file2);
		}
		else if (alg == "mst"){
			vector <edge_struct> edges;

			for (int x = 0; x < numVert; x++)
			{
			    int i = get<0>(storage);
			    int j = get<1>(storage);
			    int v = get<2> (storage);
			    edges.push_back({i,j,v});
			}
			kruskal(edges, numVert);
		}
    		file2.close();
		storage.clear();
		numVert = 0;

    }
    
    return 0;
}
