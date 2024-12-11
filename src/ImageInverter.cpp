#include "ImageInverter.h"

#include <iostream>
#include <mutex>
#include <opencv2/opencv.hpp>
#include <thread>

ImageInverter::ImageInverter(int blockSize, int consumerNumber) {
    this->consumerNumber = consumerNumber;
    this->blockToProcessSize = blockSize;
}

// Функция-производитель. Делит изображение на строки и отправляет их в очередь задач
void ImageInverter::divideImage() {
    for (int row = 0; row < image.rows; row += blockToProcessSize) {
        int rowsToProcess = std::min(blockToProcessSize, image.rows - row);
        std::lock_guard<std::mutex> lock(imageMutex);
        cv::Mat imageBlock = image(cv::Range(row, row + rowsToProcess), cv::Range::all());
        taskQueue.push(Task{imageBlock, row});
    }
    taskQueue.finish();
}

// Функция-потребитель. Извлекает строку изображения из очереди и инвертирует в ней каждый пиксель
void ImageInverter::invertImagePart() {
    while (true) {
        Task task;
        if (!taskQueue.pop(task)) break;

        // Инверсия каждого пикселя в imagePart
        for (int i = 0; i < task.imagePart.rows; ++i) {
            for (int j = 0; j < task.imagePart.cols; ++j) {
                cv::Vec3b& pixel = task.imagePart.at<cv::Vec3b>(i, j);
                pixel = cv::Vec3b(255 - pixel[0], 255 - pixel[1], 255 - pixel[2]);
            }
        }

        // Копирование инвертированной строки в результирующее изображение
        {
            std::lock_guard<std::mutex> lock(imageMutex);
            task.imagePart.copyTo(image(
                cv::Range(task.rowOffset, task.rowOffset + task.imagePart.rows), cv::Range::all()));
        }
    }
}

// Запускает инвертирование изображения и записывает результат в resultImage
void ImageInverter::invert(const cv::Mat& imageToProcess, cv::Mat& resultImage) {
    imageToProcess.copyTo(this->image);

    // Поток-производитель, делит изображение на строки для обработки
    std::thread producerThread(&ImageInverter::divideImage, this);

    // Запуск потоков-потребителей
    std::vector<std::thread> consumerThreads;
    for (int i = 0; i < consumerNumber; ++i) {
        consumerThreads.emplace_back(&ImageInverter::invertImagePart, this);
    }

    producerThread.join();
    for (auto& thread : consumerThreads) {
        thread.join();
    }

    // Запись результата
    this->image.copyTo(resultImage);
}
