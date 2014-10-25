#include <string>
#include <vector>
#include <queue>
#include <ctime>
#include <iostream>
#include <unordered_map>

using namespace std;

bool valid_MUI(string str);

void analyze(string str);

void generate_theorums(unordered_map<string, string> &theorums, queue<pair<string, string>> &bfs_queue);

int main() {
    
    // driver loop
    while (true) {
        
        string resp;
        cout << "\nEnter a MUI string: ";
        cin >> resp;
        
        // clear line
        while (cin.get() != '\n');
        
        // check for quit
        if (resp == "q" || resp == "Q" || resp == "Quit"
            || resp == "quit" || resp == "QUIT") {
            cout << "Goodbye!\n";
            exit(0);
        }
        
        if (!valid_MUI(resp)) {
            cout << "Not a valid MUI string!\n";
            continue;
        }
        
        analyze(resp);
        
    }
    
}


bool valid_MUI(string str)
{
    for (char c : str) {
        if ((c != 'M') && (c != 'I') && (c != 'U'))
            return false;
    }
    return true;
}

void analyze(string str)
{
    // statically linked map of theorums
    static unordered_map<string, string> theorums {pair<string, string>{"MI","MI"}};
    static queue<pair<string, string>> bfs_queue;
    if (bfs_queue.empty()) {
        bfs_queue.push(pair<string, string>{"MI","MI"});
        
        auto start = clock();
        
        // three seconds of initial calculation
        while (((clock() - start) / (double)CLOCKS_PER_SEC) < 3 ) {
            generate_theorums(theorums, bfs_queue);
        }
    }
    
    // check to see if we already have it
    if (theorums.count(str) > 0) {
        cout << str << " is a theorum!\n";
        cout << "Here one possible derivation:\n";
        cout << theorums.find(str)->second << "\n";
    }
    
    // didn't find it
    else {
        auto start = clock();
        
        // ten seconds of calculation
        while (((clock() - start) / (double)CLOCKS_PER_SEC) < 3 ) {
            generate_theorums(theorums, bfs_queue);
        }
        
        // check again
        if (theorums.count(str) > 0) {
            cout << str << " is a theorum!\n";
            cout << "Here one possible derivation:\n";
            cout << theorums.find(str)->second << "\n";
        }
        
        else {
            cout << "Could not assert theorum in given time!\n";
            cout << "Enter same MUI string to calculate for longer\n";
        }
    }
    
}


void generate_theorums(unordered_map<string, string> &theorums, queue<pair<string, string>> &bfs_queue)
{
    // take front elt
    auto base_pair = bfs_queue.front();
    string str = base_pair.first;
    string derivation = base_pair.second;
    bfs_queue.pop();
    
    // Rule 1: add U to any string ending in I
    {
        if (str[str.length() - 1] == 'I') {
            bfs_queue.push(pair<string, string>{str + 'U', derivation + " -I-> " + str + 'U'});
            theorums.insert(pair<string, string>{str + 'U', derivation + " -I-> " + str + 'U'});
        }
    }
    
    // Rule 2: double string after M
    {
        bfs_queue.push(pair<string, string>{str + str.substr(1), derivation + " -II-> " + str + str.substr(1)});
        theorums.insert(pair<string, string>{str + str.substr(1), derivation + " -II-> " + str + str.substr(1)});
    }
    
    // Rule 3: replace any III with U
    {
        vector<size_t> iii_indices;
        size_t pos = str.find("III", 0);
        
        // populate indixes
        while (pos != string::npos) {
            iii_indices.push_back(pos);
            pos = str.find("III", pos + 1);
        }
        
        for (size_t i : iii_indices) {
            string copy {str};
            copy.erase(i, 3);
            copy.insert(i, "U");
            
            bfs_queue.push(pair<string, string>{copy, derivation + " -III-> " + copy});
            theorums.insert(pair<string, string>{copy, derivation + " -III-> " + copy});
        }
    }
    
    // Rule 4: remove any UU
    {
        vector<size_t> uu_indices;
        size_t pos = str.find("UU", 0);
        
        // populate indixes
        while (pos != string::npos) {
            uu_indices.push_back(pos);
            pos = str.find("UU", pos + 1);
        }
        
        for (size_t i : uu_indices) {
            string copy {str};
            copy.erase(i, 2);
            
            bfs_queue.push(pair<string, string>{copy, derivation + " -III-> " + copy});
            theorums.insert(pair<string, string>{copy, derivation + " -III-> " + copy});
        }
    }
}

