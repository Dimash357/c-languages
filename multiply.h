#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

std::string MultiplyBigNumbers(const std::string& num1, const std::string& num2) {
    if (num1 == "0" || num2 == "0") {
        return "0";
    }

    const size_t len1 = num1.size();
    const size_t len2 = num2.size();
    std::vector<int> result(len1 + len2, 0);

    for (int i = static_cast<int>(len1) - 1; i >= 0; --i) {
        const int digit1 = num1[i] - '0';

        for (int j = static_cast<int>(len2) - 1; j >= 0; --j) {
            const int digit2 = num2[j] - '0';
            const int product = digit1 * digit2;

            const int sum = product + result[i + j + 1];
            result[i + j + 1] = sum % 10;
            result[i + j] += sum / 10;
        }
    }

    std::string output;
    for (const int num : result) {
        if (output.empty() && num == 0) {
            continue;
        }
        output.push_back(static_cast<char>(num + '0'));
    }

    return output.empty() ? "0" : output;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string a;
    std::string b;
    std::cin >> a >> b;
    std::cout << MultiplyBigNumbers(a, b) << '\n';
    return 0;
}
