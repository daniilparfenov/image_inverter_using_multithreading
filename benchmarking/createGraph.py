import os
import subprocess
import time
from PIL import Image

import matplotlib.pyplot as plt

executables = {
    "SingleThread": "benchmarking/benchmark_single_thread",
    "MultiThread": "benchmarking/benchmark_multi_thread",
}

all_outputs = [
    "benchmarking_outputs/singlethread.txt",
    "benchmarking_outputs/multithread.txt",
]

def generate_image(width, height, output_dir):
    image = Image.new("RGB", (width, height))
    pixels = image.load()
    
    for x in range(width):
        for y in range(height):
            pixels[x, y] = (200, 200, 200)
    
    filename = f"{width}x{height}.png"
    filepath = os.path.join(output_dir, filename)
    
    image.save(filepath)
    print(f"Сохранено: {filepath}")


def compile_code():
    print("[COMPILATION] >> Компиляция исходных файлов...")
    try:
        subprocess.run(["cmake", "--build", "."], cwd="build", check=True)
        print("[COMPILATION] >> Компиляция завершена успешно.")
    except subprocess.CalledProcessError as e:
        print(f"Ошибка при компиляции: {e}")
        exit(1)
    except FileNotFoundError as e:
        print(f"Ошибка: {e}. Проверьте путь до build!")
        exit(1)


def parse_output(file_path):
    if not os.path.exists(file_path):
        print(f"Файл {file_path} не найден!")
        exit(1)

    results = []
    with open(file_path, "r") as file:
        for line in file:
            results.append(float(line.strip()))
        return results


def save_results_from_benchmarking():
    time_start = time.time()
    for algo, executable in executables.items():
        subprocess.run([executable], cwd="build", check=True)
    print(f"Benchmarking took {time.time() - time_start:.2f} seconds")


def generate_graph(sizes):
    plt.figure(figsize=(10, 6))
    
    for algo, output in zip(executables.keys(), all_outputs):
        results = parse_output(output)
        plt.plot(sizes, results, label=algo, marker="o") 

    plt.xlabel("Photo size (N x N)")
    plt.ylabel("Seconds")
    plt.title("Invert photo performance")
    plt.legend()
    plt.grid(True)
    plt.savefig("benchmarking_outputs/performance.png")
    print("График сохранён в performance.png")


if "__main__" == __name__:
    if not os.path.exists("benchmarking_outputs"):
        os.mkdir("benchmarking_outputs")
    
    sizes = [x for x in range(5000, 10001, 500)]
    
    if not os.path.exists("generated_images"):
        os.mkdir("generated_images")
        for size in sizes:
            generate_image(size, size, "generated_images")
        
    compile_code()

    save_results_from_benchmarking()

    generate_graph(sizes)
    