#ifndef SERVER_HELPER_H
#define SERVER_HELPER_H

#include <string>
#include "external_dependencies/json.hpp"
#include <sstream>

using json = nlohmann::json;


/**
 * @brief Helper that provides functionalities for not-server-related thing,
 *        like loading the config.
 */
class Helper
{
private:
    static const std::string config_path;
public:

    /**
     * @brief Loads the json config from the config file in to a a json object.
     *
     * @return A jason containing the loaded configuration.
     */
    static json load_config();
};


#endif //SERVER_HELPER_H
