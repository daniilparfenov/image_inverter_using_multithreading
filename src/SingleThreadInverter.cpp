#include "SingleThreadInverter.h"

void naive_invertImage(const cv::Mat& imageToProcess, cv::Mat& resultImage) {
    imageToProcess.copyTo(resultImage);

    for (int i = 0; i < resultImage.rows; ++i) {
        for (int j = 0; j < resultImage.cols; ++j) {
            cv::Vec3b& pixel = resultImage.at<cv::Vec3b>(i, j);
            pixel = cv::Vec3b(255 - pixel[0], 255 - pixel[1], 255 - pixel[2]);
        }
    }
}
