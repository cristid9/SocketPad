#include "CNServer.h"
#include "Helper.h"
#include <glog/logging.h>

using json = nlohmann::json;
using namespace google;

int main(int argc, char** argv)
{

    auto json_config = Helper::load_config();

    FilesManager::load_values(json_config["storage_path"]);

    InitGoogleLogging(argv[0]);

    // you could rely on the env var on the future
    // ...just sayin'
    FLAGS_logtostderr = 1;

    LOG(INFO) << "Server started";

    CNServer serv;

    serv.start_server();

    return 0;
}