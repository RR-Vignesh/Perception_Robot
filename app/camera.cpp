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
 * @file camera.cpp
 * @author Dhanush Babu Allam, Guru Nandhan A D P, Vignesh RR
 * @This module calibrates camera and gets input
 * @version 0.1
 * @date 2022-10-19
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "../include/camera.hpp"

#include <iostream>

#include "opencv2/opencv.hpp"

/**
 * @this function gets image from camera
 *
 * @return cv::Mat
 */
cv::Mat Camera::getImage() {
  std::cout << "Get Image\n";

  cv::VideoCapture cap("../data/video.MOV");
  //VideoCapture cap(0);

  while (1) {

    cv::Mat frame;
    // Capture frame-by-frame
    cap >> frame;

    // If the frame is empty, break immediately
    if (frame.empty())
      break;

    // Display the resulting frame
    imshow("Frame", frame);

    // Press  ESC on keyboard to exit
    char c = (char)cv::waitKey(25);
    if (c == 27)
      break;
  }

  // When everything done, release the video capture object
  cap.release();

  // Closes all the frames
  cv::destroyAllWindows();

  return image;
}
/**
 * @this function calibrates the camera
 *
 */
void calibrateCamera() {}
