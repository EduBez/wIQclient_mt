#include "Log.h"

using namespace orga;

//  Logger
//

// Statics definition

boost::mutex  Logger::mutex_;
std::ofstream Logger::log_;
