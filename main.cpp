#include <iostream>
#include <boost/program_options.hpp>

#include "password.hpp"
#include "parser.hpp"
#include "generator.hpp"

namespace po = boost::program_options;

struct Parser;

int main(int argc, char *argv[])
{

    po::options_description desc("\nReadable password generator.\n"
                                 "'*' - required parameter(s)!\n\n"
                                 "Invocation : <program> --number <number> <format>\nAgruments:");

    desc.add_options()
        ("help", "  Produce help message")
        ("number", po::value<uint>()->default_value(3), "  Number of passwords")
        ("format", po::value<std::string>()->required(), "* Password format");

    // Positional arguments don't need a parameter flag
    po::positional_options_description pos_desc;
    pos_desc.add("format", -1);

    po::variables_map vm;

    try
    {
        po::store(po::command_line_parser(argc, argv)
                    .options(desc)
                    .positional(pos_desc)
                    .run(), vm);
        po::notify(vm);
    }
    catch (po::error &e)
    {
        std::cerr << "ERROR: " << e.what() << "\n";
        std::cerr << desc << "\n";
        return 1;
    }

    uint number(vm["number"].as<uint>());
    std::string format(vm["format"].as<std::string>());

    Generator g;
    Password pwd;
    pwd.parts = Parser::parse(format);

    for (uint i = 0; i < number; i++) {
        std::cout << g.generate(pwd.parts) << std::endl;
    }

    return 0;
}