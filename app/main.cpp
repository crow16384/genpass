#include <boost/program_options.hpp>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "config.hpp"
#include "generator.hpp"
#include "parser.hpp"
#include "password.hpp"

namespace po = boost::program_options;

namespace memories {

std::string memory_path() {
    const char* home = std::getenv("HOME");
    if (!home || !*home) return {};
    return std::string(home) + "/.genpass_memory";
}

std::string read_last_format() {
    std::string path = memory_path();
    if (path.empty()) return {};
    std::ifstream f(path);
    std::string format;
    if (std::getline(f, format)) return format;
    return {};
}

void save_format(const std::string& format) {
    std::string path = memory_path();
    if (path.empty()) return;
    std::ofstream f(path);
    if (f) f << format << '\n';
}

}  // namespace memories

static void print_version() {
    std::cout << "Readable password generator by " << project_author << '\n'
              << project_name << " version: " << project_version << '\n';
}

static void print_help() {
    std::cout << "genpass [options] [format]\n\n"
                 "options:\n"
                 "  -n [ --number ]  number of passwords (default = 3)\n"
                 "  -l [ --last ]    use last remembered format (serena memory)\n\n"
                 "format (optional if --last is used):\n"
                 "  W - uppercase word   w - lowercase word\n"
                 "  d - digit            s - special symbol\n\n"
                 "Example: genpass W4s2w3d5  → 3 passwords like 'Cyvi!:wof90943'\n"
                 "The last used format is remembered for --last.\n";
}

int main(int argc, char* argv[]) {
    std::string password_format;

    po::options_description generic("Password generator");
    generic.add_options()
        ("version,v", "print version")
        ("help,h", "produce help message")
        ("number,n", po::value<unsigned>()->default_value(3), "number of passwords")
        ("last,l", "use last remembered format")
        ("format", po::value(&password_format), "password format");

    po::positional_options_description positional;
    positional.add("format", 1);

    po::variables_map vm;
    try {
        po::store(
            po::command_line_parser(argc, argv).positional(positional).options(generic).run(),
            vm);
        po::notify(vm);
    } catch (const po::error& e) {
        std::cerr << "ERROR: " << e.what() << "\n" << generic << "\n";
        return 1;
    }

    if (vm.count("version")) {
        print_version();
        return 0;
    }
    if (vm.count("help")) {
        print_help();
        return 0;
    }

    if (password_format.empty() && vm.count("last"))
        password_format = memories::read_last_format();

    if (password_format.empty()) {
        std::cerr << "No format given. Use --last to recall last format or provide format.\n"
                  << generic << "\n";
        return 1;
    }

    const unsigned number = vm["number"].as<unsigned>();
    const PasswordTemplate tpl = Parser::parse(password_format);

    PasswordGenerator g;
    for (unsigned i = 0; i < number; ++i)
        std::cout << g.generate(tpl) << '\n';

    memories::save_format(password_format);
    std::cout.flush();
    return 0;
}