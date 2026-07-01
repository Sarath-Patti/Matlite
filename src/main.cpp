#include "evaluator/Evaluator.h"
#include "lexer/Lexer.h"
#include "parser/Parser.h"

#include <exception>
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

void evaluate_line(const std::string& line, std::ostream& output)
{
    lexer::Lexer lexer(line);
    parser::Parser parser(lexer.tokenize());
    auto expression = parser.parse();

    if (expression == nullptr) {
        output << "Error: could not parse expression.\n";
        return;
    }

    evaluator::Evaluator evaluator;
    output << evaluator.evaluate(*expression) << '\n';
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

        try {
            evaluate_line(line, output);
        } catch (const std::exception& error) {
            output << "Error: " << error.what() << '\n';
        }
    }
}

} // namespace

} // namespace matlite

int main()
{
    matlite::run_repl(std::cin, std::cout);
    return 0;
}
