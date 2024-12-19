#ifndef INCLUDE_SINGLETHREADINVERTER_H_
#define INCLUDE_SINGLETHREADINVERTER_H_

#include <opencv2/opencv.hpp>

void naive_invertImage(const cv::Mat& imageToProcess, cv::Mat& resultImage);

#endif  // INCLUDE_SINGLETHREADINVERTER_H_
