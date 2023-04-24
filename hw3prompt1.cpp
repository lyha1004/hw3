#include<iostream>
#include<fstream>
#include<sstream>
#include<cstring>
#include<vector>
using namespace std;


int main(){
    
    ifstream file("input1.csv");

    string line;
    int i;
    int j;
    int v;
    int numVert = 0;
    vector<pair<int,int>> edges;

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

        edges.push_back({i,j});
        if(v != 1){
            edges.push_back({j,i});
        }
        numVert = max(numVert, max(i,j));
    }
    file.close();

    vector<vector<int>> adjMat(numVert + 1, vector<int>(numVert + 1, 0));
    for (auto edge : edges) {
        i = edge.first;
        j = edge.second;
        adjMat[i][j] = 1;
        if (edge.first != edge.second && v != 1) {
            adjMat[j][i] = v; 
        }
    }

    /*for (int i = 1; i <= numVert; i++) {
        for (int j = 1; j <= numVert; j++) {
            cout << adjMat[i][j] << " ";
        }
        cout << endl;
    }*/
    


    ofstream file2("output.csv");
    file2.close();

    return 0;
}