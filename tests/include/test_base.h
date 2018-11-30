#pragma once

#include "gtest/gtest.h"


class TestBase : public ::testing::Test
{
protected:
  std::string GetFilePath(std::string filename) const {
    // Path into examples from bin
    std::string path = "../tests/examples/" + filename;
    return path;
  }

}; // class TestBase