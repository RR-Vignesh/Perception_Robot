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
 * @version 0.2
 * @date 2022-10-19
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "../include/detector.hpp"

#include <fstream>
#include <iostream>
#include <vector>

#include "opencv2/opencv.hpp"

const float INPUT_WIDTH = 640.0;
const float INPUT_HEIGHT = 640.0;
const float SCORE_THRESHOLD = 0.5;
const float NMS_THRESHOLD = 0.45;
const float CONFIDENCE_THRESHOLD = 0.45;
const int FONT_FACE = cv::FONT_HERSHEY_COMPLEX;
const float FONT_SCALE = 0.7;
const int THICKNESS = 1;

// Colors.
cv::Scalar BLACK = cv::Scalar(0, 0, 0);
cv::Scalar BLUE = cv::Scalar(255, 178, 50);
cv::Scalar YELLOW = cv::Scalar(0, 255, 255);
cv::Scalar RED = cv::Scalar(0, 0, 255);

/**
 * @brief this function resizes the image
 *
 * @param image
 * @return std::vector<cv::Mat>
 */
std::vector<cv::Mat> Detector::preProcessing(cv::Mat &image,
                                             cv::dnn::Net &net) {
  cv::Mat blob;

  cv::dnn::blobFromImage(image, blob, 1. / 255.,
                         cv::Size(INPUT_WIDTH, INPUT_HEIGHT), cv::Scalar(),
                         true, false);

  net.setInput(blob);

  // Forward propagate.
  std::vector<cv::Mat> outputs;
  net.forward(outputs, net.getUnconnectedOutLayersNames());

  return outputs;
}
std::vector<std::string> classes_list;
std::vector<std::string> load_class_list() {
  std::ifstream ifs("../data/coco.names");
  std::string line;
  while (getline(ifs, line)) {
    classes_list.push_back(line);
  }
  return classes_list;
}
/**
 * @brief this function assigns label
 *
 * @param input_image, label, left top
 *
 */
void draw_label(cv::Mat &input_image, std::string label, int left, int top) {
  // Display the label at the top of the bounding box.
  int baseLine;
  cv::Size label_size =
      cv::getTextSize(label, FONT_FACE, FONT_SCALE, THICKNESS, &baseLine);
  top = cv::max(top, label_size.height);
  // Top left corner.
  cv::Point tlc = cv::Point(left, top);
  // Bottom right corner.
  cv::Point brc =
      cv::Point(left + label_size.width, top + label_size.height + baseLine);
  // Draw black rectangle.
  cv::rectangle(input_image, tlc, brc, cv::Scalar(0, 0, 0), cv::FILLED);
  // Put the label on the black rectangle.
  cv::putText(input_image, label, cv::Point(left, top + label_size.height),
              FONT_FACE, FONT_SCALE, cv::Scalar(255, 255, 0), THICKNESS);
}
/**
 * @brief this function detects the image
 *
 * @param image, detections, class_list
 * @return cv::Mat
 */
cv::Mat post_process(cv::Mat &image, std::vector<cv::Mat> &detections,
                     const std::vector<std::string> &class_list) {
  // Initialize vectors to hold respective outputs while unwrapping detections.
  std::vector<int> class_ids;
  std::vector<float> confidences;
  std::vector<cv::Rect> boxes;
  // Resizing factor.
  float x_factor = image.clone().cols / INPUT_WIDTH;
  float y_factor = image.clone().rows / INPUT_HEIGHT;
  float *data = reinterpret_cast<float *>(detections[0].data);
  const int dimensions = 85;
  // 25200 for default size 640.
  const int rows = 25200;
  // Iterate through 25200 detections.
  for (int i = 0; i < rows; ++i) {
    float confidence = data[4];

    // Discard bad detections and continue.
    if (confidence >= CONFIDENCE_THRESHOLD) {
      float *classes_scores = data + 5;
      cv::Mat scores(1, class_list.size(), CV_32FC1, classes_scores);
      cv::Point class_id;
      double max_class_score;

      minMaxLoc(scores, 0, &max_class_score, 0, &class_id);
      if (max_class_score > SCORE_THRESHOLD) {
        confidences.push_back(confidence);
        std::cout << class_id.x << std::endl;
        class_ids.push_back(class_id.x);
        // Center.
        float cx = data[0];
        float cy = data[1];
        // Box dimension.
        float w = data[2];
        float h = data[3];
        // Bounding box coordinates.
        int left = static_cast<int>((cx - 0.5 * w) * x_factor);
        int top = static_cast<int>((cy - 0.5 * h) * y_factor);
        int width = static_cast<int>(w * x_factor);
        int height = static_cast<int>(h * y_factor);
        // Store good detections in the boxes vector.
        boxes.push_back(cv::Rect(left, top, width, height));
      }
    }
    // Jump to the next row.
    data += 85;
  }

  std::vector<int> nms_result;
  cv::dnn::NMSBoxes(boxes, confidences, SCORE_THRESHOLD, NMS_THRESHOLD,
                    nms_result);
  for (int i = 0; i < nms_result.size(); i++) {
    int idx = nms_result[i];
    cv::Rect box = boxes[idx];

    int left = box.x;
    int top = box.y;
    int width = box.width;
    int height = box.height;

    // draw rectangle
    cv::rectangle(image, cv::Point(left, top),
                  cv::Point(left + width, top + height), BLUE, 3 * THICKNESS);
    std::string label = cv::format("%.2f", confidences[idx]);
    label = class_list[class_ids[idx]] + ":" + label;
    draw_label(image, label, left, top);
  }

  return image;
}

/**
 * @brief calls both pre-processing and post-processing functions
 *
 * @param imgage
 * @return cv::Mat
 */
cv::Mat Detector::objectDetections(cv::Mat &image) {
  std::vector<std::string> class_list = load_class_list();

  cv::dnn::Net net;
  net = cv::dnn::readNet("./../model/yolov5s.onnx");
  std::vector<cv::Mat> detections;
  detections = preProcessing(image, net);

  cv::Mat image1 = post_process(image, detections, class_list);
  std::vector<double> layersTimes;
  double freq = cv::getTickFrequency() / 1000;
  double t = net.getPerfProfile(layersTimes) / freq;
  std::string label = cv::format("Inference time : %.2f ms", t);
  cv::putText(image1, label, cv::Point(20, 40), FONT_FACE, FONT_SCALE, RED);

  cv::imshow("Output", image1);
  cv::waitKey(1);
  return image1;
}

/**
 * @brief filters humans
 *
 * @param detectedImage
 * @return int
 **/
int Detector::filterHuman(cv::Mat &detectedImage) {
  int numberOfObjects = 0;
  return numberOfObjects;
}

/**
 * @brief draws bounding box
 *
 * @param img
 * @return vector<int>
 */
std::vector<int> Detector::boundingBox(cv::Mat &image) {
  std::vector<int> coordinates = {2, 2, 2, 2};
  return coordinates;
}
