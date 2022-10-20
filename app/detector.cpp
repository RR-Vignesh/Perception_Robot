/******************************************************************************
 * MIT License
 *
 * Copyright (c) 2021 Dhanush Babu Allam, Guru Nandhan A D P, Vignesh RR
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 *all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 ******************************************************************************/
/**
 * @file detector.cpp
 * @author Dhanush Babu Allam, Guru Nandhan A D P, Vignesh RR
 * @This module preprocesses the image, detects objects and only filters humans
 * @version 0.1
 * @date 2022-10-19
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "../include/detector.hpp"

#include <iostream>

#include "opencv2/opencv.hpp"
/**
 * @brief this resizes the image
 *
 * @param image
 * @return cv::Mat
 */
cv::Mat Detector::preProcessing(cv::Mat image) {
  cv::Mat resize_down;
  return resize_down;
}
/**
 * @brief detects objects
 *
 * @param img
 * @return cv::Mat
 */
cv::Mat Detector::objectDetections(cv::Mat img) { return img; }
/**
 * @brief filters humans
 *
 * @param detectedImage
 * @return int
 */
int Detector::filterHuman(cv::Mat detectedImage) {
  int numberOfObjects = 0;
  return numberOfObjects;
}
/**
 * @brief draws bounding box
 *
 * @param img
 * @return vector<int>
 */
vector<int> Detector::boundingBox(cv::Mat img) {
  vector<int> coordinates = {2, 2, 2, 2};
  return coordinates;
}
