#include <Utilities/include/logging.h>

#define CATCH_CONFIG_MAIN 
#include <catch.hpp>
#include <string.h> //used for errno
using namespace Toyscode;
using namespace Utilities;

TEST_CASE("log Utilities testing","[log]")
{
    Logging::Loglevel level = Logging::Loglevel::TRACE;
    
    SECTION("Test for api of LOG")
    {
        REQUIRE(Logging::get_log_level() == Logging::Loglevel::TRACE); 
        level = Logging::Loglevel::WARN;
        Logging::set_log_level(level);
        REQUIRE(Logging::get_log_level()== Logging::Loglevel::WARN);
    }

    SECTION("Test for LOG_TRACE ")
    {
        level = Logging::Loglevel::TRACE;
        Logging::set_log_level(level);
        LOG_TRACE << "Hello world" ;
    }
    
    SECTION("Test for LOG_DEBUG")
    {
        Logging::set_log_level(Logging::Loglevel::DEBUG);
        REQUIRE(Logging::get_log_level() == Logging::Loglevel::DEBUG);
        LOG_DEBUG << "Hello world";
    }

    SECTION("Test for LOG_MSG")
    {
        REQUIRE(Logging::get_log_level() == Logging::Loglevel::DEBUG);
        LOG_MSG << "Log MSG " ;
        
    }

    SECTION("Test for LOG_WARN,LOG_ERR,LOG_FATAL")
    {
        REQUIRE(Logging::get_log_level() ==  Logging::Loglevel::DEBUG);
        LOG_WARN << "Log WARN";
        LOG_ERR << "Log ERR";
        // LOG_FATAL << "LOG FATAL" ;
        
    }

    SECTION("Test for LOG_SYSERR and LOG_SYSFATAL")
    {
        extern int errno  ;
        errno = 13;
        LOG_SYSFATAL << "system error " ; 
    }

} 
