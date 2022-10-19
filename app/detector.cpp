#include "../include/detector.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
/**
 * @brief
 *
 */
using namespace cv;
Mat Detector::preProcessing(Mat image) {
  Mat resize_down;
  return resize_down;
}
Mat Detector::objectDetections(Mat img) {
  return img;
}
int Detector::filterHuman(Mat detectedImage) { 
  int numberOfObjects=0;
  return numberOfObjects;
  }
  vector<int> Detector::boundingBox(Mat img){
    vector<int> coordinates = {2,2,2,2};
    return coordinates;

}
