#include <chrono>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

#include "ImageInverter.h"

int main() {
    std::vector<std::string> pathsToImages = {"input_images/cute_dog.jpg", "input_images/cat.jpg",
                                              "input_images/inverted_cute_dog.jpg"};
    const int blockSize = 100;
    const int consumerThreadNum = 4;
    ImageInverter imageInverter(blockSize, consumerThreadNum);
    cv::Mat inputImage;
    cv::Mat invertedImage;

    for (std::string& path : pathsToImages) {
        // Загрузка изображения
        inputImage = cv::imread(path);
        if (inputImage.empty()) {
            std::cerr << "Failed to load image!" << std::endl;
            return -1;
        }

        // Инвертирование цветов
        imageInverter.invert(inputImage, invertedImage);

        // Вывод исходного и инвертированного изображений
        cv::imshow("Input Image", inputImage);
        cv::imshow("Inverted Image", invertedImage);

        cv::waitKey(0);  // Ожидание нажатия любой клавиши клавиатуры
    }
    return 0;
}
