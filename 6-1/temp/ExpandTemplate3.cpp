#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

const int MAXN = 1000005;
const int MAXM = 10005;
const int MAXK = 26;

struct BorNode {
    int next[MAXK];
    int suff;
    int id;
    bool is_end;
};

BorNode bor[MAXN];
int bor_size;

void init_trie() {
    bor_size = 1;
    for (auto & i : bor) {
        for (int & j : i.next) {
            j = 0;
        }
        i.suff = 0;
        i.id = 0;
        i.is_end = false;
    }
}

void insert_trie(const string& s, int id) {
    int u = 0;
    for (char i : s) {
        int c = i - 'a';
        if (bor[u].next[c] == 0) {
            bor[u].next[c] = bor_size++;
        }
        u = bor[u].next[c];
    }
    bor[u].is_end = true;
    bor[u].id = id;
}

void build_fail() {
    vector<int> q;
    for (int u : bor[0].next) {
        if (u != 0) {
            bor[u].suff = 0;
            q.push_back(u);
        }
    }
    while (!q.empty()) {
        int r = q.front();
        q.erase(q.begin());
        for (int i = 0; i < MAXK; i++) {
            int u = bor[r].next[i];
            if (u != 0) {
                q.push_back(u);
                int v = bor[r].suff;
                while (v != 0 && bor[v].next[i] == 0) {
                    v = bor[v].suff;
                }
                bor[u].suff = bor[v].next[i];
                bor[u].is_end |= bor[bor[u].suff].is_end;
            }
        }
    }
}

string expand_template(const string& template_str, unordered_map<string, string>& key_value_map) {
    init_trie();
    int id = 1;
    for (auto & it : key_value_map) {
        insert_trie(it.first, id++);
    }
    build_fail();

    string result;
    int u = 0;
    for (char i : template_str) {
        int c = i - 'a';
        while (u != 0 && bor[u].next[c] == 0) {
            u = bor[u].suff;
        }
        u = bor[u].next[c];
        if (bor[u].is_end) {
            result += key_value_map[bor[u].id];
            u = 0;
        } else {
            result += i;
        }
    }
    return result;
}

int main() {
    unordered_map<string, string> key_value_map = {
            {"name", "John"},
            {"age", "30"},
            {"city", "New York"}
    };
    string template_str = "My name is {{name}} and I am {{age}} years old. I live in {{city}}.";
    string result = expand_template(template_str, key_value_map);
    cout << result << endl;
    return 0;
}
