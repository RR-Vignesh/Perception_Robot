#ifndef INCLUDE_DETECTOR_HPP_
#define INCLUDE_DETECTOR_HPP_

#include <opencv2/opencv.hpp>
#include "camera.hpp"
#include <string>
#include <vector>

using namespace std;
using namespace cv;

class Detector: public Camera {
private:
  cv::Mat resizedImage;
  vector<int> boundingCoordinates;
  string classToBeDetected;
public:
  Mat preProcessing(Mat img);
  Mat objectDetections(Mat img);
  int filterHuman(Mat img);
  vector<int> boundingBox(Mat img);

};

#endif