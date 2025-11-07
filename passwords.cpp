#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

struct TrieNode {  // NOLINT
    std::unordered_map<char, TrieNode*> children;
    int count = 0;
};

void insert(TrieNode* root, const std::string& word) {
    TrieNode* node = root;
    for (char c : word) {
        if (node->children.find(c) == node->children.end()) {
            node->children[c] = new TrieNode();
        }
        node = node->children[c];
        node->count++;
    }
}

int countSubstrings(TrieNode* root, const std::string& word) {
    int total = 0;
    for (size_t i = 0; i < word.size(); ++i) {
        TrieNode* node = root;
        for (size_t j = i; j < word.size(); ++j) {
            char c = word[j];
            if (node->children.find(c) == node->children.end()) {
                break;
            }
            node = node->children[c];
            total += node->count;
        }
    }
    return total;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N;
    std::cin >> N;
    std::vector<std::string> passwords(N);
    
    for (int i = 0; i < N; ++i) {
        std::cin >> passwords[i];
    }

    TrieNode* trie = new TrieNode();
    for (const std::string& pwd : passwords) {
        insert(trie, pwd);
    }
    
    long long result = 0;

    for (const std::string& pwd : passwords) {
        result += countSubstrings(trie, pwd);
    }
    
    std::cout << result << '\n';
    
    return 0;
}