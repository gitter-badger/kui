#include <gtest/gtest.h>

#include <tui/screen.hpp>

using namespace tui;

TEST(Screen, GetScreen) {
  auto& s = Screen::get_screen();
}