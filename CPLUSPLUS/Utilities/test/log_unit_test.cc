#include "logging.h"

#define CATCH_CONFIG_MAIN 
#include "../../catch.hpp"

using namespace Toyscode;
using namespace Utilities;

TEST_CASE("log Utilities testing","[log]")
{
	Logging::Loglevel level = Logging::Loglevel::LOG_DEBUG;

	Logging log("log.c",1);
	REQUIRE(log.get_log_level() == Logging::Loglevel::LOG_TRACE);

	level = Logging::Loglevel::LOG_WARN;
	log.set_log_level(level);
	REQUIRE(log.get_log_level()== Logging::Loglevel::LOG_WARN);


} 
