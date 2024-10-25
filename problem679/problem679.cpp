#include <bits/stdc++.h>
using namespace std;

// Define the Automaton class
struct Automaton {
    struct Node {
        int children[4];
        int fail;
        vector<int> output; // list of keyword indices
        Node() : fail(0) { 
            for(int i=0;i<4;i++) children[i]=-1; 
        }
    };
    
    vector<Node> trie;
    Automaton() {
        trie.emplace_back(); // root node
    }
    
    // Map letters to indices: A=0, E=1, F=2, R=3
    int charToIndex(char c){
        if(c == 'A') return 0;
        if(c == 'E') return 1;
        if(c == 'F') return 2;
        if(c == 'R') return 3;
        return -1;
    }
    
    // Insert a keyword into the trie and assign its index
    void insert(const string &word, int index){
        int node = 0;
        for(char c : word){
            int ci = charToIndex(c);
            if(trie[node].children[ci] == -1){
                trie[node].children[ci] = trie.size();
                trie.emplace_back();
            }
            node = trie[node].children[ci];
        }
        trie[node].output.push_back(index);
    }
    
    // Build failure links
    void build(){
        queue<int> q;
        // Initialize fail links for depth 1 nodes to root
        for(int i=0;i<4;i++){
            if(trie[0].children[i] != -1){
                trie[trie[0].children[i]].fail = 0;
                q.push(trie[0].children[i]);
            }
            else{
                trie[0].children[i] = 0; // missing transitions go to root
            }
        }
        
        // BFS
        while(!q.empty()){
            int current = q.front(); q.pop();
            for(int i=0;i<4;i++){
                int child = trie[current].children[i];
                if(child != -1){
                    // Set fail link for child
                    int fail = trie[current].fail;
                    while(trie[fail].children[i] == -1 && fail != 0){
                        fail = trie[fail].fail;
                    }
                    if(trie[fail].children[i] != -1){
                        fail = trie[fail].children[i];
                    }
                    trie[child].fail = fail;
                    
                    // Merge output
                    for(auto &k : trie[fail].output){
                        trie[child].output.push_back(k);
                    }
                    
                    q.push(child);
                }
                else{
                    // Set missing transitions
                    trie[current].children[i] = trie[trie[current].fail].children[i];
                }
            }
        }
    }
    
    // Transition function
    int transition(int state, char c){
        int ci = charToIndex(c);
        return trie[state].children[ci];
    }
};

int main(){
    // Assign indices to keywords
    // FREE=0, FARE=1, AREA=2, REEF=3
    vector<string> keywords = {"FREE", "FARE", "AREA", "REEF"};
    
    // Build the automaton
    Automaton ac;
    for(int i=0;i<keywords.size();i++) ac.insert(keywords[i], i);
    ac.build();
    
    int n = 30; // Change this to 9 or 15 to verify with given examples
    
    // DP[pos][state][used_mask]
    // Since n=30, use two layers
    // Number of states in automaton
    int num_states = ac.trie.size();
    // Initialize current and next DP tables
    vector<vector<unsigned long long>> current(num_states, vector<unsigned long long>(16, 0));
    vector<vector<unsigned long long>> next_dp(num_states, vector<unsigned long long>(16, 0));
    
    // Start at position 0, state 0, used_mask 0
    current[0][0] = 1;
    
    // Letters in S
    vector<char> letters = {'A', 'E', 'F', 'R'};
    
    for(int pos=0; pos<n; pos++){
        // Reset next_dp
        for(int s=0; s<num_states; s++) {
            fill(next_dp[s].begin(), next_dp[s].end(), 0ULL);
        }
        
        for(int state=0; state<num_states; state++){
            for(int mask=0; mask<16; mask++){
                if(current[state][mask] == 0) continue;
                unsigned long long cnt = current[state][mask];
                for(char c : letters){
                    int next_state = ac.transition(state, c);
                    int new_mask = mask;
                    bool invalid = false;
                    for(auto &k : ac.trie[next_state].output){
                        if(mask & (1 << k)){
                            // Keyword already used, invalid
                            invalid = true;
                            break;
                        }
                        new_mask |= (1 << k);
                    }
                    if(invalid) continue;
                    next_dp[next_state][new_mask] += cnt;
                }
            }
        }
        
        // Swap current and next_dp
        current.swap(next_dp);
    }
    
    // Sum all current[state][15]
    unsigned long long result = 0;
    for(int state=0; state<num_states; state++) {
        result += current[state][15];
    }
    
    cout << result << endl;
    
    return 0;
}

