#include "header/Quadtree.h"
#include "header/ErrorMeasurement.h"
#include "header/ImageProcessor.h"
#include <iostream>
#include <chrono>
#include <filesystem>
namespace fs = std::filesystem;

using namespace std;

// Fungsi bantu: mengisi blok dengan warna solid
void fillBlock(vector<vector<Pixel>>& result, int startX, int startY, int width, int height, const Pixel& color) {
    for (int y = startY; y < startY + height; ++y) {
        for (int x = startX; x < startX + width; ++x) {
            if (x < result.size() && y < result[0].size()) {
                result[x][y] = color;
            } 
        }
    }
}

// Render dari QuadTree ke matrix hasil
void renderQuadTreeToMatrix(QuadTreeNode* node, vector<vector<Pixel>>& result) {
    if (node->isLeaf) {
        fillBlock(result, node->startX, node->startY, node->width, node->height, node->color);
    } else {
        for (int i = 0; i < 4; i++) {
            if (node->children[i]) {
                renderQuadTreeToMatrix(node->children[i], result);
            }
        }
    }
}

// Menghitung dan mencetak persentase kompresi
void calculateCompression(const std::string& inputPath, const std::string& outputPath) {
    if (fs::exists(inputPath) && fs::exists(outputPath)) {
        auto inputSize = fs::file_size(inputPath);
        auto outputSize = fs::file_size(outputPath);

        float compressionRatio = 1.0f - (float)outputSize / (float)inputSize;
        float compressionPercent = compressionRatio * 100.0f;

        std::cout << "\n========== Hasil Kompresi ==========\n";
        std::cout << "Ukuran Gambar Sebelum : " << inputSize << " bytes\n";
        std::cout << "Ukuran Gambar Setelah : " << outputSize << " bytes\n";
        std::cout << "Persentase Kompresi   : " << compressionPercent << " %\n";
    } else {
        std::cerr << "Error: File tidak ditemukan.\n";
    }
}


int countNodes(QuadTreeNode* node) {
    if (node == nullptr) return 0;
    int count = 1;
    for (int i = 0; i < 4; ++i) {
        count += countNodes(node->children[i]);
    }
    return count;
}

int treeDepth(QuadTreeNode* node) {
    if (node == nullptr || node->isLeaf) return 1;
    int maxDepth = 0;
    for (int i = 0; i < 4; ++i) {
        maxDepth = std::max(maxDepth, treeDepth(node->children[i]));
    }
    return 1 + maxDepth;
}

int main() {
    string inputPath, outputPath;
    int metodeError;
    double threshold;
    int minBlockSize;

    cout << "==== Program Kompresi Gambar dengan QuadTree ====\n";

    cout << "Masukkan path absolut gambar yang akan dikompresi: ";
    getline(cin, inputPath);

    cout << "\nPilih metode perhitungan error:\n";
    cout << "1. Variance\n";
    cout << "2. MAD (Mean Absolute Deviation)\n";
    cout << "3. Max Pixel Difference\n";
    cout << "4. Entropy\n";
    cout << "Masukkan nomor metode: ";
    cin >> metodeError;

    cout << "\nMasukkan nilai threshold (sesuai metode yang dipilih): ";
    cin >> threshold;

    cout << "\nMasukkan ukuran blok minimum (misal: 1): ";
    cin >> minBlockSize;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\nMasukkan path absolut untuk menyimpan gambar hasil kompresi: ";
    getline(cin, outputPath);

    cout << "\n=== Input selesai. Memulai proses kompresi... ===\n";
    auto start = chrono::high_resolution_clock::now();

    int width, height;
    vector<vector<Pixel>> image = ImageProcessor::loadImage(inputPath, width, height);

    // Bangun root dan kompres
    QuadTreeNode* root = new QuadTreeNode(0, 0, width, height, true);

    switch (metodeError) {
        case 1:
            root->splitQuadTreeWithVariance(image, threshold, minBlockSize); // Variance
            break;
        case 2:
            root->splitQuadTreeWithMAD(image, threshold, minBlockSize);
            break;
        case 3:
            root->splitQuadTreeWithMaxDiff(image, threshold, minBlockSize);
            break;
        case 4:
            root->splitQuadTreeWithEntropy(image, threshold, minBlockSize);
            break;
        default:
            cout << "Metode error tidak valid.\n";
            return 1;
    }

    // Buat hasil kompresi
    vector<vector<Pixel>> compressedImage(width, vector<Pixel>(height));
    renderQuadTreeToMatrix(root, compressedImage);

    // Simpan ke file
    ImageProcessor::saveImage(outputPath, compressedImage, width, height);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "\nWaktu Eksekusi: " << duration.count() << " detik\n";

    calculateCompression(inputPath, outputPath);

    std::cout << "Banyak simpul: " << countNodes(root) << std::endl;
    std::cout << "Kedalaman pohon: " << treeDepth(root) << std::endl;  
    
    delete root;
    return 0;
}
