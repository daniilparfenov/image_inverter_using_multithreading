#ifndef INCLUDE_IMAGE_INVERTER_H
#define INCLUDE_IMAGE_INVERTER_H

#include <mutex>
#include <opencv2/opencv.hpp>

#include "BlockingQueue.h"

// Структура задачи для потребителей
struct Task {
    cv::Mat imagePart;
    int rowOffset;
};

class ImageInverter {
   private:
    BlockingQueue<Task> taskQueue;
    cv::Mat image;
    std::mutex imageMutex;
    int blockToProcessSize;  // Кол-во строк, которое будет обрабатывать 1 поток
    int consumerNumber;      // Кол-во потоков - потребителей

    void divideImage();      // Producer
    void invertImagePart();  // Consumer

   public:
    ImageInverter(int blockSize, int consumerNumber);
    void invert(const cv::Mat& imageToProcess, cv::Mat& resultImage);
};

#endif
