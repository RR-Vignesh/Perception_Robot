#include "../app/camera.cpp"
#include "../app/detector.cpp"
#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>

using namespace cv;

TEST(getImage, should_pass) {
  Camera C;
  EXPECT_EQ(C.getImage().channels(), 3);
}