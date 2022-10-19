#ifndef INCLUDE_CAMERA_HPP_
#define INCLUDE_CAMERA_HPP_

#include <opencv2/opencv.hpp>
using namespace cv;
class Camera {
public:
  Mat image;
  Mat getImage();
  void calibrateCamera();
};

#endif