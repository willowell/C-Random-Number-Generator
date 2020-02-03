#include <cctype>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

char my_toupper(char ch) {
    return static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
}

bool yes_or_no_prompt(const std::string& prompt) {
    std::string buffer;
    char answer = 'a';
    do {
        std::cout << prompt << " [y/n]" << std::endl;
        std::cin >> buffer;
        
        if (buffer.length() != 1) {
            std::cout << "Please enter only one character!" << std::endl;
            continue;
        }
        
        answer = my_toupper(buffer.at(0));
        
        if (answer != 'Y' && answer != 'N') {
            std::cout << "Please enter only 'y' or 'n'!" << std::endl;
        }
    } while (answer != 'Y' && answer != 'N');
    
    return (answer == 'Y');
}

int main() {

    // Random number generator with a distribution
    std::random_device rand_dev;
    std::mt19937 gen(rand_dev());
    std::uniform_int_distribution<> dist(1, 100);

    // Zero-initialize an array of 256 elements.
    // By making the array now and limiting the user to (0, 256),
    // we can avoid making a variable-length array or a dynamic array.
    int nums[256] = {0};

    while (true) {
        // Populate the array with some random numbers.
        for (auto& i : nums) {
            i = dist(gen);
        }

        std::string buffer;
        std::cout << "How many numbers would you like to see? ";
        std::cin >> buffer;

        std::istringstream iss(buffer);

        int how_many = 0;

        // Read the value from what the user input.
        if (iss >> how_many) {

            // Make sure the index is valid before using it.
            if (how_many < 256 && how_many > 0) {
                // Looks like the number is safe to use!

                std::cout << "Here are your numbers!\n";

                int row_limit = std::sqrt(how_many);
                for (int y = 1; y <= how_many; ++y) {
                    std::cout << std::setw(3) << nums[y - 1] << ' ';
                    if (y % row_limit == 0) {
                        std::cout << std::endl;
                    }
                }
                std::cout << std::endl;
                
                if (yes_or_no_prompt("Again?")) {
                    continue;
                } else {
                    break;
                }
                
            } else {
                std::cout << "Number too low or high!" << std::endl;
                continue;
            }
        } else {
            std::cout << "Invalid input!" << std::endl;
            continue;
        }
    }
    std::cout << "Goodbye!" << std::endl;
    return 0;
}
