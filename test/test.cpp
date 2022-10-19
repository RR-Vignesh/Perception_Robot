#include "../app/camera.cpp"
#include "../app/detector.cpp"
#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>

using namespace cv;

TEST(getImage, should_pass) {
  Camera C;
  EXPECT_EQ(C.getImage().channels(), 3);
}
TEST(ImageHeightCheck, should_pass) {
  Detector D;
  cv::Mat image = D.getImage();
  EXPECT_EQ(D.preProcessing(image).size().height, 640);
}

TEST(ImageWidthCheck, should_pass) {
  Detector D;
  cv::Mat image = D.getImage();
  EXPECT_EQ(D.preProcessing(image).size().width, 640);
}