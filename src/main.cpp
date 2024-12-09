#include <iostream>

#include "BlockingQueue.h"
#include "ImageInverter.h"

int main() {
    BlockingQueue<int> blocking_queue;
    blocking_queue.push(12);
    int num = 0;
    blocking_queue.pop(num);
    std::cout << num << std::endl;
    return 0;
}
