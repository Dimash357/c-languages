#include <iostream>
#include <string>
#include <vector>

std::string MultiplyStrings(const std::string& first_number, const std::string& second_number) {
    if ((first_number == "0") || (second_number == "0")) {
        return "0";
    }

    const size_t length_first = first_number.size();
    const size_t length_second = second_number.size();
    std::vector<int> result(length_first + length_second, 0);

    for (int i = static_cast<int>(length_first) - 1; i >= 0; --i) {
        const int digit_first = first_number[i] - '0';
        for (int j = static_cast<int>(length_second) - 1; j >= 0; --j) {
            const int digit_second = second_number[j] - '0';
            const int product = digit_first * digit_second + result[i + j + 1];
            result[i + j + 1] = product % 10;
            result[i + j] += product / 10;
        }
    }

    std::string product_string;
    for (size_t index = 0; index < result.size(); ++index) {
        if ((index == 0) && (result[index] == 0)) {
            continue;
        }
        product_string.push_back(static_cast<char>(result[index] + '0'));
    }

    return product_string.empty() ? "0" : product_string;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string first_number;
    std::string second_number;
    std::cin >> first_number >> second_number;

    std::cout << MultiplyStrings(first_number, second_number) << '\n';

    return 0;
}
