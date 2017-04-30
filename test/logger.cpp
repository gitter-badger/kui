#include <gtest/gtest.h>

#include <kui/logger.hpp>

TEST(Logger, Log) {
    KUI_LOG(trace, "THIS MESSAGE SHOULD NOT BE SEEN");
    KUI_LOG(debug, "THIS MESSAGE SHOULD BE SEEN");
    KUI_LOG(error, "THIS MESSAGE SHOULD BE SEEN");
}

TEST(Logger, Severity) {
    KUI_LOG_SEVERITY(warning);
    KUI_LOG(info, "THIS MESSAGE SHOULD NOT BE SEEN");
    KUI_LOG(warning, "THIS MESSAGE SHOULD BE SEEN");
    KUI_LOG_SEVERITY_RESET();
}