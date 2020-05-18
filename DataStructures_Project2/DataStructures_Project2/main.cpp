//
//  main.cpp
//  components.cpp
//
//  Created by Amr Hassanein on 9/17/18.
//  Copyright © 2018 Amr Hassanein. All rights reserved.
//

#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using std::cout;
using std::endl;
using std::cin;
using std::list;
using std::vector;

list<int>::iterator find_gt(list<int>::iterator start, list<int>::iterator stop, int x);
bool connComponent (list<int> first, list<int> second);
bool merge2(list<int> &big, list<int> &small);
void printGraph(vector <list <int> > adjList);


int main() {
    
    //declarations
    list<int>::iterator itr;
    std::ifstream inFile;
    std::string fileName, line;
    int index = 0, mList1, mList2;
    
    vector <list <int> > adjList;       //vector that will hold lists of numbers
    list<int> mtLst;    //empty list
    
    //get file name from user
    cout << "Please enter a file...";
    getline(cin, fileName);
    
    //open file and if not end the program
    inFile.open(fileName);
    if (!(inFile.is_open()))
    {
        cout << "Sorry dude, but that file is bogus" << endl;
        exit(0);
    }
    
    //get a line from the file and parse it so that each number can be accessed
    while(getline(inFile, line)){
        std::istringstream row(line);
        int num;
        adjList.push_back(mtLst);
        
        while(row >> num){
            itr = find_gt(adjList[index].begin(), adjList[index].end(), num);   //finds where the number should be inserted
            adjList[index].insert(itr, num);                                    // inserts the number into the correct position
        }
        index++;
    }
  
    printGraph(adjList);
    
    
    do {
        cout << endl << "Please enter two list ids to potentially merge together or -1 to quit: ";
        cin >> mList1;
        if(mList1 < 0){
            cout << "Goodbye";
        }
        cin >> mList2;
        
      
        if(adjList[mList1].size() > adjList[mList2].size()){
            if(merge2(adjList[mList1], adjList[mList2])){
                adjList[mList2].erase(adjList[mList2].begin(), adjList[mList2].end());
            }
            else{
                if(merge2(adjList[mList2], adjList[mList1])){
                    adjList[mList1].erase(adjList[mList1].begin(), adjList[mList1].end());
                }
            }
        }
        cout << "The lists are merged" << endl;
        cout << "the adjacency list for your graph" << endl;
        printGraph(adjList);
       
    }while (mList1 >= 0);
    
    
    
    return 0;
}

//FUNCTIONS

list<int>::iterator find_gt(list<int>::iterator start, list<int>::iterator stop, int x){
    
    list<int>::iterator ptr = start;
    
    for ( ; ptr != stop; ptr++){
        if (*ptr >= x)
            return ptr;
    }
    return ptr;
}

bool connComponent (list<int> first, list<int> second){
    list<int>::iterator firstPtr = first.begin();
    list<int>::iterator secondPtr = second.begin();
    
    for (; firstPtr != first.end(); firstPtr++){
        for(; secondPtr != second.end(); secondPtr++){
            if(*firstPtr == *secondPtr)
                return true;
        }
    }
    return false;
}

bool merge2(list<int> &big, list<int> &small){
    
    list<int>::iterator itrs = small.begin();
    list<int>::iterator itrAdd, itrFind;
    
    if(connComponent(big, small)){
    
        for(; itrs != small.end(); itrs++){
            itrFind = std::find(big.begin(), big.end(), *itrs);
            if (itrFind != big.end())
                continue;
            else{
                itrAdd = find_gt(big.begin(), big.end(), *itrs);
                big.insert(itrAdd, *itrs);
            }
        }
    }
        return true;
}


void printGraph(vector <list <int> > adjList){
    for (int i = 0; i < adjList.size(); i++){
        for (list<int>::iterator itr2 = adjList[i].begin(); itr2 != adjList[i].end(); itr2++){
            cout << *itr2 << " ";
        }
        cout << endl;
    }
}



