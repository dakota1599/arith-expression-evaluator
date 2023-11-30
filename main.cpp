#include "include/scanner.hpp"
#include "include/parser.hpp"

int main(int argc, char **argv)
{
    std::string input;

    if (argc <= 1)
    {
        std::cout << "> ";

        getline(std::cin, input);
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            input += argv[i];
        }
    }

    Scanner s(input);

    s.scan();

    Parser p(s.get_tokens());

    std::cout << p.parse() << std::endl;
}