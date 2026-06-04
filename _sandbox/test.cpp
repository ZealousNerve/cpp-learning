#include <iostream>

int main()
{
    int x{};
    int y{};
    std::cout << "Enter a number: ";
    std::cin >> x;
    std::cout << x << std::endl;

    std::cin.clear();
    std::cin.ignore();

    std::cout << "enter the second number: ";
    std::cin >> y;
    std::cout << y;

    return 0;
}