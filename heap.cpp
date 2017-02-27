#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

using namespace std;
class Node{
    public:
        int key, id = -1;
        int state; //MST state, 0 as default , 1 means it's in MST 
       
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
              if((j+1 < array.size()) && (array[j]->key > array[j+1]->key)) j++; //pick up the smaller one
              if(array[pos]->key < array[j]->key) return;
              swap(pos, j);
              siftdown(j);
          }
          if(left(pos) != -1 && right(pos) == -1){ // one child
              int j = left(pos);
              if(array[pos]->key < array[j]->key) return;
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
        
        void buildheap(){
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