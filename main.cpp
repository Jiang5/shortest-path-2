//"auto" was used, so please use "g++ -std=c++11 -g -o a main.cpp  to compile" 
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

class Edge{
    public:
        int s, d, w;
        Edge(int s, int d, int w){
            this->s = s;
            this->d = d;
            this->w = w;
        }
};        

class Node{
    public:
        int key, id = -1;
        int state; //MST state, 0 as default , 1 means it's in MST 
        vector<Edge*> adj; //ajacent list  
        Node(int key, int id){
            this->key = key;
            this->id = id;
            state = 0;
        }
};

class minHeap{
    public:
        vector<Node*> array;
        
        void swap(int pos, int j){
            Node* temp = array[pos];
            array[pos] = array[j];
            array[j] = temp;
        }
        
        void siftdown(int pos){
          if(pos < 0 || pos >= array.size()) {return;}
          if(left(pos) != -1 && right(pos) != -1){ // two children 
              int j = left(pos);
              if(array[j]->key > array[j+1]->key) j++; //pick up the smaller one
              if(array[pos]->key <= array[j]->key) return;
              swap(pos, j);
              siftdown(j);
          }
          if(left(pos) != -1 && right(pos) == -1){ // one child
              int j = left(pos);
              if(array[pos]->key <= array[j]->key) return;
              swap(pos, j);
              siftdown(j);
          }
          if(left(pos) == -1 && right(pos) == -1){ // no child
              return;
          }
        }
        
        int left(int parent){
            int i = parent * 2  + 1;
            return (i < array.size()) ? i : -1;
        }
        
        int right(int parent){
            int i = parent * 2 + 2;
            return (i < array.size()) ? i : -1;
        }
        
        int parent(int child){
            if(child != 0){
                int i = (child - 1) / 2;
                return i;
            }
            return -1;
        }  
        
        void buildheap(){ //decrease key
            for(int i = parent(array.size()-1) ; i >= 0; i --) siftdown(i);
            return;
        }
          
        void addNode(Node* newNode){
            array.push_back(newNode);
            buildheap();
        }
        
        Node* getNode(){
            Node* temp = array[0];
            array[0] = array[array.size() - 1];
            array.pop_back();
            siftdown(0);
            return temp;
        }
        
        bool empty(){
            return array.size() == 0;
        }
        
        unsigned int size(){
            return array.size();
        }
};

vector<Node*> list; //contains all nodes, list number is node id minus 1
void addEdge(int s, int d, int w){
            list[s-1]->adj.push_back(new Edge(s, d, w));
            list[d-1]->adj.push_back(new Edge(d, s, w));
}

int main(){
    
    int nodes, MSTNumber, edges, u, v, w, totalWeight = 0;
    int n = 1; //node id starts from 1
    minHeap heap;
    
    ifstream myfile("input.txt");
    if(!myfile.is_open()) cerr<<"Failed to open file\n";
    else{
        myfile>>nodes;
        myfile>>edges;
        MSTNumber = nodes;
        while(nodes != 0){
            list.push_back(new Node(1000001, n));//std::numeric_limits<int>::max()
            n++;
            nodes--;
            heap.addNode(list.back());
        }
        myfile.ignore(1000, '\n');
        
        while(!myfile.eof()){
            myfile>>u;
            myfile>>v;
            myfile>>w;
            addEdge(u, v, w);
            myfile.ignore(1000, '\n');
        }
        myfile.close();
    }

//Prim's Algorithm
    int MST[MSTNumber];
    for(int i = 0; i < MSTNumber; i++){
        MST[i] = 0;
    }
    list[0]->key = 0;
    list[0]->state = 1; // indicate it's in MST
    MST[0] = -1;
    while(!heap.empty()){
        Node* temp = heap.getNode();
        temp->state = 1;
        for(auto i : temp->adj){ // i is edge of the node
            
            if(list[i->d - 1]->state == 0 && list[i->d - 1]->key >= i->w){
                    list[i->d - 1]->key = i->w;
                    MST[i->d -1 ] = temp->id; // set u as v's previous node
                    heap.buildheap();
            }
        }
    }

    for(int i = 1; i < MSTNumber; i++){
        totalWeight += list[i]->key;
    }

//output in file    
    ofstream myfile1 ("output.txt");
    if (myfile1.is_open()){
        myfile1 << totalWeight<<endl;
        for(int i = 1; i < MSTNumber; i++){
            
            myfile1 << MST[i] << " " << i+1 << endl;
        }
        myfile1.close();
    }
    else cout << "Unable to open file";
    return 0;
}