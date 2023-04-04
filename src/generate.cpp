//
// Created by guanyx on 23-4-3.
//

#include <iostream>
#include <fstream>
#include <random>

// 生成一个4x4随机矩阵
void generate_matrix(int matrix[4][4]) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 10);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            matrix[i][j] = dist(gen);
        }
    }
}

// 将矩阵写入文件
void write_to_file(const int matrix[4][4], const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                file << matrix[i][j] << " ";
            }
            file << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

int main() {
    for (int k = 0; k < 1000; ++k) {
        int matrix[4][4];
        generate_matrix(matrix);
        std::string filename = "../Matrix/A4x4_" + std::to_string(k);
        write_to_file(matrix, filename);
    }
    return 0;
}
