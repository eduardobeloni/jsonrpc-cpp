#include <iostream>
#include <fstream>
#include <sstream>

#include <jsoncpp/json.h>

int main(int argc, char *argv[])
{
    Json::Value euroSquad;
    Json::Value players;
    Json::Reader reader;
    bool parsingSuccessful;
    std::ifstream fin;
    std::ostringstream oss;
    std::string str;

    if (argc != 2)
    {
        std::cerr << "Invalid parameters. Usage\n";
        std::cerr << argv[0] << " <squad>\n";
        return 1;
    }

    fin.open(argv[1]);
    if (!fin.is_open())
    {
        std::cerr << "Unable to open " << argv[1] << "\n";
        return 2;
    }

    oss << fin.rdbuf();
    str = oss.str();
    std::cout << str << "\n";

    parsingSuccessful = reader.parse(str, euroSquad);
    if (!parsingSuccessful)
    {
        // report to the user the failure and their locations in the document.
        std::cout  << "Failed to parse configuration\n"
                   << reader.getFormattedErrorMessages();
        return 1;
    }

    std::cout << "This is the Euro 2012 opening match squad\n";
    players = euroSquad["goal-keeper"];
    std::cout << "goal keeper: " << players.asString() << "\n";

    players = euroSquad["defenders"];
    for (int i = 0; i < players.size(); i++)
        std::cout << "defender " << i << ": " << players[i];

    players = euroSquad["midfielders"];
    for (int i = 0; i < players.size(); i++)
        std::cout << "midfielder " << i << ": " << players[i];

    players = euroSquad["strikers"];
    for (int i = 0; i < players.size(); i++)
        std::cout << "striker " << i << ": " << players[i];

    return 0;
}
