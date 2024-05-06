#include <parser.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>

using namespace std;

void Parser::error(const string &message)
{
    errors.push_back(to_string(nlines) + ": error: " + message);
}

void Parser::parse(istream &stream)
{
    for (string line; getline(stream, line); nlines++)
    {
        // Dev note: we strip comment and check for label first so that we can bail out early if there are no instructions

        if (line.find_first_of(';') != string::npos)
            line = line.substr(0, line.find_first_of(';'));

        if (line.find_first_of(':') != string::npos)
        {
            string label = line.substr(0, line.find_first_of(':'));
            statements.push_back(make_shared<Label>(boost::trim_copy(label)));
            line = line.substr(line.find_first_of(':') + 1);
        }

        boost::trim(line);
        if (line.empty())
            continue;
    }
}
