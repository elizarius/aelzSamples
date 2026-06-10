#include <string>
#include <iostream>
#include <map>


int main(int argc, char* argv[])
{
    std::string print_usage = "Usage:   ./a.out --classX|-X  anyMessage \nExample: ./a.out --classA BLABLABLA";
    if (argc < 2) {
        std::cerr << print_usage << std::endl;
        return 1;
    }

    std::map<std::string, std::string> arg_pairs;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if ((arg.substr(0, 2) == "--" || arg.substr(0, 1) == "-") && i + 1 < argc) {
            std::string key = arg;
            std::string value = argv[i + 1];
            if ((value.substr(0, 1) != "-") || (value.substr(0, 2) != "--")) {
                arg_pairs[key] = value;
                ++i;
            }
        }
    }

    std::cout << "Captured " << arg_pairs.size() << " argument pair(s):" << std::endl;
    for (const auto& pair : arg_pairs) {
        std::cout << "  " << pair.first << " => " << pair.second << std::endl;
    }

    return 0;
}

