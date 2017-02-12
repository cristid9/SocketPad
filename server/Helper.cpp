#include "Helper.h"
#include <fstream>

const std::string Helper::config_path = "/home/cristi/computer_networks/colaborative_notepad/server/configs/config.json";

json Helper::load_config()
{
    std::ifstream in_file(Helper::config_path);
    std::stringstream str_stream;

    str_stream << in_file.rdbuf();
    std::string config = str_stream.str();

    return json::parse(config);
}
