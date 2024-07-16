#pragma once

#include<vector>
#include<stack>
#include<unordered_map>
#include<queue>

using namespace std;

template <typename T>



class Graph{
  unordered_map<T,vector<pair<T, int>>> adjList;

  struct Compare{
    bool operator()(pair<T,int> a, pair<T,int> b){
      return a.second > b.second;
    }
  };

public:
  Graph(){}

  bool addNode(T nodeVal){
    if(adjList.find(nodeVal) != adjList.end()) return false;

    adjList[nodeVal] = {};
    return true;
  }

  bool addEdge(T fromNode, T toNode){
    if(adjList.find(fromNode) == adjList.end()) return false;

    adjList[fromNode].push_back({toNode, 1});
    return true;
  }

  bool addEdge(T fromNode, T toNode, int weight){
    if(adjList.find(fromNode) == adjList.end()) return false;

    adjList[fromNode].push_back({toNode, weight});
    return true;
  }


  vector<T> dfs(T searchFrom, T search){
    vector<T> searchPath;
    stack<T> toBeVisited;
    unordered_map<T,bool> isVisitedNode;

    toBeVisited.push(searchFrom);
    isVisitedNode[searchFrom] = true;

    while(!toBeVisited.empty()){
      T topNode = toBeVisited.top();
      
      bool isUnvisitedFound = false;
      for(auto& node: adjList[topNode]){
        T nodeVal = node.first;
        if(isVisitedNode[nodeVal]) continue;

        if(nodeVal == search){
          searchPath.push_back(nodeVal);

          while(!toBeVisited.empty()){
            searchPath.push_back(toBeVisited.top());
            toBeVisited.pop();
          }
          return searchPath;

        }

        isVisitedNode[nodeVal] = true;
        toBeVisited.push(nodeVal);
        isUnvisitedFound = true;
        break;
      }

      if(!isUnvisitedFound) toBeVisited.pop();
    }

    return searchPath;
  }

  vector<T> findMinDistancePath(T fromNode, T toNode){
    priority_queue<pair<T,int>, vector<pair<T,int>>, Compare> closestNodes;
    unordered_map<T,int> minDistances;
    unordered_map<T,T> prevNode;

    minDistances[fromNode] = 0;
    closestNodes.push({fromNode,0});
    prevNode[fromNode] = fromNode;

    for(auto& node: this->adjList){
      minDistances[node.first] = INT_MAX;
    }

    while(!closestNodes.empty()){
      auto topNode = closestNodes.top(); 
      closestNodes.pop();
      
      for(auto& neighbour: this->adjList[topNode.first]){
        int newDistance = topNode.second + neighbour.second;
        if(newDistance < minDistances[neighbour.first]){
          minDistances[neighbour.first] = newDistance;
          closestNodes.push({neighbour.first, newDistance});
          prevNode[neighbour.first] = topNode.first;
        }
      }
    }

    if(minDistances[toNode] == INT_MAX) return {};

    auto pathWalk = toNode;
    vector<T> path;
    while(pathWalk != prevNode[pathWalk]){
      path.push_back(pathWalk);

      pathWalk = prevNode[pathWalk];
    }
    path.push_back(pathWalk);

    return path;

  }

  void print(){
    for(auto& node:adjList){
      cout << "Node " << node.first << " is Connected to :- [ " ;
      for(auto& neighbour: node.second){
        cout << neighbour.first << " - " << neighbour.second << " ";
      }

      cout << "]" <<endl;
    } 
  }
};
