#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<std::string> passwords;
    std::unordered_map<std::string, long long> countMap;

    for (int i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;
        passwords.push_back(s);
        countMap[s]++;
    }

    long long total = 0;
    for (const std::string& p : passwords) {
        std::unordered_set<std::string> uniqueSubs;
        int len = static_cast<int>(p.length());
        for (int start = 0; start < len; ++start) {
            for (int l = 1; l <= len - start; ++l) {
                uniqueSubs.insert(p.substr(start, l));
            }
        }
        for (const std::string& sub : uniqueSubs) {
            auto it = countMap.find(sub);
            if (it != countMap.end()) {
                total += it->second;
            }
        }
    }

    total -= n;
    std::cout << total << "\n";

    return 0;
}
