//#include "gtest/gtest.h"
#include <sstream>
#include "frupal.h"
#include <gtest/gtest.h>
#include <string>

using namespace std;

class GrovnikTest : public ::testing::Test {
  protected:
  void SetUp() override {
    game_ = new Frupal(nullptr,10,10);
    ft_ = false;
    fs_ = false;
    fd_ = false;
  }

  void TearDown() override {
    delete game_;
  }

  bool testParseLine(string line, ifstream & mapFile, bool & terrain, bool & start, bool & diamonds) {
    return game_->parseLine(line, mapFile, terrain, start, diamonds);
    }

  Frupal * game_;
  string str_;
  bool ft_, fs_, fd_;
  ifstream file_;
};


TEST_F (GrovnikTest, ObsBRElement) {
    str_ = "bsinoculars: 10 6 25 2";
    EXPECT_DEATH(testParseLine(str_, file_, ft_, fs_, fd_), "");
}

TEST_F (GrovnikTest, ObsBRXLow) {
    str_ = "binoculars: -1 6 25 2";
    EXPECT_DEATH(testParseLine(str_, file_, ft_, fs_, fd_), "");
}

TEST_F (GrovnikTest, ObsBRXHigh) {
    str_ = "binoculars: 256 6 25 2";
    EXPECT_DEATH(testParseLine(str_, file_, ft_, fs_, fd_), "");
}

TEST_F (GrovnikTest, ObsBRYLow) {
    str_ = "binoculars: 10 -1 25 2";
    EXPECT_DEATH(testParseLine(str_, file_, ft_, fs_, fd_), "");
}

TEST_F (GrovnikTest, ObsBRYHigh) {
    str_ = "binoculars: 10 256 25 2";
    EXPECT_DEATH(testParseLine(str_, file_, ft_, fs_, fd_), "");
}

TEST_F (GrovnikTest, ObsBRYCostLow) {
    str_ = "binoculars: 10 11 -25 2";
    EXPECT_DEATH(testParseLine(str_, file_, ft_, fs_, fd_), "");
}

TEST_F (GrovnikTest, ObsBRYCostHigh) {
    str_ = "binoculars: 10 11 10000 2";
    EXPECT_DEATH(testParseLine(str_, file_, ft_, fs_, fd_), "");
}

TEST_F (GrovnikTest, ObsBRYCostZero) {
    str_ = "binoculars: 10 11 0 2";
    EXPECT_DEATH(testParseLine(str_, file_, ft_, fs_, fd_), "");
}

TEST_F (GrovnikTest, ObsBRRangeLow) {
    str_ = "binoculars: 10 11 25 -1";
    EXPECT_DEATH(testParseLine(str_, file_, ft_, fs_, fd_), "");
}

TEST_F (GrovnikTest, ObsBRRangeHigh) {
    str_ = "binoculars: 10 11 25 1000";
    EXPECT_DEATH(testParseLine(str_, file_, ft_, fs_, fd_), "");
}

TEST_F (GrovnikTest, ObsBRRangeZero) {
    str_ = "binoculars: 10 11 25 0";
    EXPECT_DEATH(testParseLine(str_, file_, ft_, fs_, fd_), "");
}

TEST_F (GrovnikTest, ObsBRExtraText) {
    str_ = "binoculars: 10 11 25 0  asdfadfasdf";
    EXPECT_DEATH(testParseLine(str_, file_, ft_, fs_, fd_), "");
}

TEST_F (GrovnikTest, ObsBRExtraWhiteSpace) {
    str_ = "binoculars: 10 11 25 2  	\r";
    EXPECT_TRUE(testParseLine(str_, file_, ft_, fs_, fd_));
}

TEST_F (GrovnikTest, ObsGoodRead) {
    str_ = "binoculars: 10 6 25 2";
    EXPECT_TRUE(testParseLine(str_, file_, ft_, fs_, fd_));
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

