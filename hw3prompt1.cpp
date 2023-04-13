#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int main(){

    ifstream file("input1.csv");
    char line;
    if(file.is_open()){
       while(file){
        line = file.get();
        cout << line;
       }
    }

    

    return 0;
}