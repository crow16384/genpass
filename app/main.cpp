#include <iostream>
#include <boost/program_options.hpp>

#include "password.hpp"
#include "parser.hpp"
#include "generator.hpp"
#include "config.hpp"

namespace po = boost::program_options;

struct Parser;

void print_version() {
    std::cout << "Readable password generator by " << project_author 
              << "\n" << project_name << " version: " 
              << project_version << std::endl;
}

void print_help() {
    std::cout << "genpass [options] format\n\n"
                 "options:\n"
                 "  -n [ --number ]  number of passwords (default =3)\n\n"
                 "'format' is required\n"
                 "where:\n"
                 "  W - uppercase word\n"
                 "  w - lowercase word\n"
                 "  d - digit\n"
                 "  s - special symbol\n\n"
                 "This is a template for generation with type and number of characters\n"
                 "For example:\n"
                 "  genpass W4s2w3d5\n\n"
                 "will produce 3 (default, see --number) passwords\n"
                 "like: 'Cyvi!:wof90943'" << std::endl;
}

int main(int argc, char *argv[])
{
    std::string password_format; // Password format

    po::options_description generic("Password generator");

    generic.add_options()("version,v", "print version")
                         ("help,h",    "produce help message")
                         ("number,n",  po::value<unsigned int>()->default_value(3), "number of passwords")
                         ("format", po::value(&password_format), "password format")
                         ;

    // Positional arguments don't need a parameter flag
    po::positional_options_description positional;
    positional.add("format", 1);

    po::variables_map vm;

    try
    {
        po::store(
            po::command_line_parser(argc, argv)
                .positional(positional)
                .options(generic)
                .run(),
            vm
        );
        po::notify(vm);
    }
    catch (po::error &e)
    {
        std::cerr << "ERROR: " << e.what() << "\n";
        std::cerr << generic << "\n";
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

    if (!vm.count ("format")) {
        std::cerr << generic << "\n";
        return 1;
    }

    unsigned int number(vm["number"].as<unsigned int>());

    Generator g;
    PasswordTemplate pwd;
    pwd.parts = Parser::parse(password_format);

    for (auto i = 0; i < number; i++)
    {
        std::cout << g.generate(pwd.parts) << "\n";
    }
    std::cout << std::endl; // Flush

    return 0;
}