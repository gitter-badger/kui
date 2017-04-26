#include <gtest/gtest.h>

#include <kui/logger.hpp>

TEST(Logger, Log) {
  KUI_LOG("Test: " << 3);
}