#ifndef INCLUDE_CAMERA_HPP_
#define INCLUDE_CAMERA_HPP_

#include <opencv2/opencv.hpp>

class Camera {
public:
  cv::Mat image;
  void getImage();
};

#endif