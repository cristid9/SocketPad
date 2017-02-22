#include "CNServer.h"
#include "Helper.h"
#include <glog/logging.h>

using json = nlohmann::json;
using namespace google;

int main(int argc, char** argv)
{

    json json_config = Helper::load_config();

    FilesManager::load_values(json_config["storage_path"]);

    InitGoogleLogging(argv[0]);

    FLAGS_logtostderr = 1;

    LOG(INFO) << "Server started";

    CNServer serv;

    serv.start_server();

    return 0;
}