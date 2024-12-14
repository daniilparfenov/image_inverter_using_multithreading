#include <chrono>
#include <fstream>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

#include "SingleThreadInverter.h"

#define BLOCK_SIZE 100
#define CONSUMER_THREAD_NUM 4
#define FILE_PATH_RESULT "../benchmarking_outputs/singlethread.txt"

int main() {
    std::vector<std::string> pathsToImages = {
        "../generated_images/5000x5000.png",  "../generated_images/5500x5500.png",
        "../generated_images/6000x6000.png",  "../generated_images/6500x6500.png",
        "../generated_images/7000x7000.png",  "../generated_images/7500x7500.png",
        "../generated_images/8000x8000.png",  "../generated_images/8500x8500.png",
        "../generated_images/9000x9000.png",  "../generated_images/9500x9500.png",
        "../generated_images/10000x10000.png"};

    cv::Mat inputImage;
    cv::Mat invertedImage;

    std::ofstream file(FILE_PATH_RESULT);

    // Затраченное время на обработку изображения
    std::chrono::time_point<std::chrono::system_clock> start, end;

    for (const std::string& path : pathsToImages) {
        start = std::chrono::system_clock::now();

        // Загрузка изображения
        inputImage = cv::imread(path);
        if (inputImage.empty()) {
            std::cerr << "Failed to load image!" << std::endl;
            return -1;
        }

        // Инвертирование цветов
        naive_invertImage(inputImage, invertedImage);

        end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsedSeconds = end - start;
        file << elapsedSeconds.count() << std::endl;
        std::cout << "Image " << path << " processed in " << elapsedSeconds.count()
                  << " seconds with single thread" << std::endl;
    }
    return 0;
}
