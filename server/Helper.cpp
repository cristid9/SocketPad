#include "Helper.h"
#include <fstream>

static json Helper::load_config()
{
    std::ifstream in_file(config_path);
    std::stringstream str_stream;

    str_stream << in_file.rdbuf();
    std::string config = str_stream.str();

    return json::parse(config);
}
