#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

vector<string> V; //words from wordlist05.txt
unordered_map<string, bool> visited;
unordered_map<string, int> dist;
unordered_map<string, string> pred;
unordered_map<string, vector<string>> nbrs;

//Implement breadth-first search
void search(string s) {
    queue<string> to_visit;
    to_visit.push(s);
    visited[s] = true;
    dist[s] = 0;

    while (!to_visit.empty()) {
        string curnode = to_visit.front();
        to_visit.pop();
        for (string n : nbrs[curnode])
            if (!visited[n]) {
                pred[n] = curnode;
                dist[n] = 1 + dist[curnode];
                visited[n] = true;
                to_visit.push(n);
            }
    }
}

void wordLadder(string s, string t, int &steps, vector<string> &p)
{
    //Read words from wordlist05.txt and build adjacency list
    ifstream inFile("wordlist05.txt");
    unordered_set<string> wordSet;
    string input;
    while (inFile >> input) {
        V.push_back(input);
    }

    for(string r : V){
        wordSet.insert(r);
    }

    for(string word : V){
        for (int i = 0; i < word.size(); i++) {
            string w = word;
            for (char c = 'a'; c <= 'z'; c++) {
                if (c != word[i]) {
                    w[i] = c;
                    if(wordSet.find(w) != wordSet.end()){
                        nbrs[word].push_back(w);
                    }
                }
            }
        }
    }

    search(s);

    if(visited[t]){
        steps = dist[t];
        string cur = t;
        while(cur != s){
            p.push_back(cur);
            cur = pred[cur];
        }
    }
}