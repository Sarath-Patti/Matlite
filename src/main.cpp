#include <iostream>
#include <string>

namespace matlite {

namespace {

constexpr auto kPrompt = ">> ";
constexpr auto kExitCommand = "exit";
constexpr auto kQuitCommand = "quit";

bool should_exit(const std::string& input)
{
    return input == kExitCommand || input == kQuitCommand;
}

void run_repl(std::istream& input, std::ostream& output)
{
    std::string line;

    while (true) {
        output << kPrompt;

        if (!std::getline(input, line)) {
            output << '\n';
            break;
        }

        if (should_exit(line)) {
            break;
        }

        output << "You entered: " << line << '\n';
    }
}

} // namespace

} // namespace matlite

int main()
{
    matlite::run_repl(std::cin, std::cout);
    return 0;
}

