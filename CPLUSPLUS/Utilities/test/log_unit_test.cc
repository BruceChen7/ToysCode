#include "logging.h"

#define CATCH_CONFIG_MAIN 
#include "../../catch.hpp"

using namespace Toyscode;
using namespace Utilities;

TEST_CASE("log Utilities testing","[log]")
{
	Logging::Loglevel level = Logging::Loglevel::TRACE;
	
	SECTION("Test for api of LOG")
	{
		Logging log("log.c",1);
		REQUIRE(log.get_log_level() == Logging::Loglevel::TRACE);

		level = Logging::Loglevel::WARN;
		log.set_log_level(level);
		REQUIRE(log.get_log_level()== Logging::Loglevel::WARN);
	}

	SECTION("Test for LOG_TRACE ")
	{
		LOG_TRACE << "Hello world" ;
	}

} 
