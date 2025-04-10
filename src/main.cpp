#include "header/Quadtree.h"
#include "header/ErrorMeasurement.h"
#include "header/ImageProcessor.h"
#include <iostream>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <sys/stat.h>
#include <algorithm>
#include <FreeImage.h>

namespace fs = std::filesystem;
using namespace std;

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


int main() {
    string inputPath, outputPath;
    int metodeError;
    double threshold;
    int minBlockSize;
    
    cout << "==== Program Kompresi Gambar dengan QuadTree ====\n";
    
    //Validasi input path
    while (true) {
        cout << "Masukkan path absolut gambar yang akan dikompresi: ";
        getline(cin, inputPath);
        
        ifstream checkFile(inputPath);
        if (!checkFile) {
            cout << "Error: File tidak ditemukan. Silakan coba lagi.\n";
            continue;
        }
        
        FREE_IMAGE_FORMAT format = FreeImage_GetFileType(inputPath.c_str(), 0);
        if (format == FIF_UNKNOWN) {
            format = FreeImage_GetFIFFromFilename(inputPath.c_str());
        }
        if (format == FIF_UNKNOWN || !FreeImage_FIFSupportsReading(format)) {
            cout << "Error: File bukan format gambar yang didukung. Silakan gunakan format seperti JPG, PNG, BMP.\n";
            continue;
        }
        
        break;
    }
    
    //Validasi pilihan metode
    while (true) {
        cout << "\nPilih metode perhitungan error:\n";
        cout << "1. Variance\n";
        cout << "2. MAD (Mean Absolute Deviation)\n";
        cout << "3. Max Pixel Difference\n";
        cout << "4. Entropy\n";
        cout << "Masukkan nomor metode: ";
        
        if (!(cin >> metodeError)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: Masukan harus berupa angka. Silakan coba lagi.\n";
            continue;
        }
        
        if (metodeError < 1 || metodeError > 4) {
            cout << "Error: Nomor metode harus antara 1-4. Silakan coba lagi.\n";
            continue;
        }
        
        break;
    }
    
    //Validasi nilai threshold
    while (true) {
        cout << "\nMasukkan nilai threshold (sesuai metode yang dipilih): ";
        
        if (!(cin >> threshold)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: Masukan harus berupa angka. Silakan coba lagi.\n";
            continue;
        }
        
        if (threshold < 0) {
            cout << "Error: Threshold harus bernilai positif. Silakan coba lagi.\n";
            continue;
        }
        break;
    }
    
    //Validasi ukuran blok
    while (true) {
        cout << "\nMasukkan ukuran blok minimum: ";
        
        if (!(cin >> minBlockSize)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: Masukan harus berupa angka. Silakan coba lagi.\n";
            continue;
        }
        
        if (minBlockSize <= 0) {
            cout << "Error: Ukuran blok minimum harus lebih besar dari 0. Silakan coba lagi.\n";
            continue;
        }
        
        break;
    }
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    

    //Validasi image output path
    while (true) {
        cout << "\nMasukkan path absolut untuk menyimpan gambar hasil kompresi: ";
        getline(cin, outputPath);
        
        size_t lastSlash = outputPath.find_last_of("/\\");
        if (lastSlash != string::npos) {
            string directory = outputPath.substr(0, lastSlash);
            struct stat info;
            if (stat(directory.c_str(), &info) != 0 || !(info.st_mode & S_IFDIR)) {
                cout << "Error: Direktori tujuan tidak ditemukan. Silakan coba lagi.\n";
                continue;
            }
        }
        
        string extension = outputPath.substr(outputPath.find_last_of(".") + 1);
        transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
        
        if (extension != "jpg" && extension != "jpeg" && extension != "png" ) {
            cout << "Error: Format file keluaran harus berupa JPG/JPEG/PNG. Silakan coba lagi.\n";
            continue;
        }
        
        ofstream testFile(outputPath);
        if (!testFile) {
            cout << "Error: Tidak dapat menulis ke file tujuan. Periksa izin akses atau gunakan path lain.\n";
            continue;
        }
        testFile.close();
        remove(outputPath.c_str()); 
        
        break;
    }
    
    //Validasi gif output path
    string isSaveGIF;
    while (true) {
        cout << "Apakah Anda ingin menyimpan hasil kompresi sebagai GIF? (y/n): ";
        getline(cin, isSaveGIF);
    
        if (isSaveGIF == "y" || isSaveGIF == "Y" || isSaveGIF == "n" || isSaveGIF == "N") {
            break;
        } else {
            cout << "Input tidak valid. Harap masukkan hanya 'y' atau 'n'.\n";
        }
    }

    string gifPath;
    if (isSaveGIF == "y" || isSaveGIF == "Y") {
        while (true) {
            cout << "\nMasukkan path absolut untuk menyimpan GIF hasil kompresi: ";
            getline(cin, gifPath);
    
            size_t lastSlash = gifPath.find_last_of("/\\");
            if (lastSlash != string::npos) {
                string directory = gifPath.substr(0, lastSlash);
                struct stat info;
                if (stat(directory.c_str(), &info) != 0 || !(info.st_mode & S_IFDIR)) {
                    cout << "Error: Direktori tujuan tidak ditemukan. Silakan coba lagi.\n";
                    continue;
                }
            }
    
            string extension = gifPath.substr(gifPath.find_last_of('.') + 1);
            transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
    
            if (extension != "gif") {
                cout << "Error: Format file harus berupa .gif. Silakan coba lagi.\n";
                continue;
            }
    
            ofstream testFile(gifPath);
            if (!testFile) {
                cout << "Error: Tidak dapat menulis ke file tujuan. Periksa izin akses atau gunakan path lain.\n";
                continue;
            }
            testFile.close();
            remove(gifPath.c_str()); 
    
            break;
        }
    }

    
    cout << "\n=== Input selesai. Memulai proses kompresi... ===\n";
    auto start = chrono::high_resolution_clock::now();
    
    int width, height;
    vector<vector<Pixel>> image;
    try {
        image = ImageProcessor::loadImage(inputPath, width, height);
    } catch (const exception& e) {
        cout << "Error saat memuat gambar: " << e.what() << endl;
        return 1;
    }

    if (width <= 0 || height <= 0) {
        cout << "Error: Dimensi gambar tidak valid.\n";
        return 1;
    }
    
    // Build root and compress
    QuadTreeNode* root = new QuadTreeNode(0, 0, width, height, true);
    
    try {
        switch (metodeError) {
            case 1:
            root->splitQuadTreeWithVariance(image, threshold, minBlockSize);
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
            delete root;
            return 1;
        }
        
        // Create compression result
        vector<vector<Pixel>> compressedImage(width, vector<Pixel>(height));
        QuadTreeNode::renderQuadTreeToMatrix(root, compressedImage);
        
        // Save to file
        if(!ImageProcessor::saveImage(outputPath, compressedImage, width, height)){
            std::cout << "Error saat menyimpan gambar hasil kompresi.\n";
            delete root;
            return 1;
        }
        std::cout << "Saved Image\n";
        
        //Render GIF
        if(isSaveGIF == "y" || isSaveGIF == "Y"){
            QuadTreeNode::generateGifFromQuadTree(root, width, height);
            std::system("magick -delay 50 -loop 0 frame*.bmp temp_output.gif");
            std::string moveCommand = "mv temp_output.gif \"" + gifPath + "\"";
            std::system(moveCommand.c_str());
        
            std::system("rm frame*.bmp"); // Clean up
            cout << "GIF berhasil disimpan di: " << gifPath << endl;
        }


        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;
        cout << "\nWaktu Eksekusi: " << duration.count() << " detik\n";
        
        calculateCompression(inputPath, outputPath);
        
        std::cout << "Banyak simpul: " << QuadTreeNode::countNodes(root) << std::endl;
        std::cout << "Kedalaman pohon: " << QuadTreeNode::treeDepth(root) << std::endl;
        
        delete root;
        return 0;
    }
    catch (const exception& e) {
        cout << "Error saat pemrosesan: " << e.what() << endl;
        delete root;
        return 1;
    }
}