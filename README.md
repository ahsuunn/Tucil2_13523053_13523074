# 🌳 QuadTree Image Compression

## a. Deskripsi Singkat  
Program ini melakukan kompresi gambar menggunakan algoritma **QuadTree** berbasis prinsip **divide and conquer**. Gambar akan dibagi secara rekursif menjadi blok-blok kecil berdasarkan tingkat keseragaman warna. Blok yang seragam akan direpresentasikan dengan satu warna rata-rata, sehingga menghasilkan gambar terkompresi dengan ukuran file yang lebih kecil namun tetap mempertahankan struktur visual.

---

## b. Requirement & Instalasi

**Dependensi:**
- **Compiler:** C++17 (g++, clang++, dsb.)
- **Library:**
  - [`FreeImage`](https://freeimage.sourceforge.io/) – untuk membaca dan menyimpan file gambar.
  - [`ImageMagick`](https://imagemagick.org/) – (opsional) digunakan untuk menggabungkan frame menjadi GIF.

**Instalasi di macOS menggunakan Homebrew:**

```
brew install freeimage  
brew install imagemagick  
```

**Instalasi di Windows menggunakan WSL:**

Jika kamu menggunakan **Windows**, disarankan untuk menjalankan program melalui **WSL (Windows Subsystem for Linux)** agar kompatibel dengan perintah Linux seperti `g++` dan `apt`.

Berikut langkah-langkah instalasi dependency di WSL (misalnya Ubuntu):

```
sudo apt update  
sudo apt install libfreeimage-dev  
sudo apt install imagemagick  
```

Untuk memastikan ImageMagick sudah terinstall, jalankan:

```
magick --version
```   

---

## c. Cara Kompilasi

Pastikan semua file `.cpp` ada di folder `src/`, dan kamu berada di folder root project.

```
g++ -std=c++17 -Iinclude src/*.cpp -lfreeimage -o bin/main 
``` 

> Output executable akan berada di folder `bin/`.
Untuk pengguna Windows pastikan membuka root folder dari terminal **WSL**

---

## d. Cara Menjalankan & Menggunakan Program

Dari folder root, jalankan program:

```
./bin/main 
``` 

Ikuti instruksi dari program melalui terminal:

1. Masukkan path absolut ke gambar yang akan dikompresi.  
2. Pilih metode perhitungan error (1: Variance, 2: MAD, 3: Max Pixel Diff, 4: Entropy).  
3. Masukkan nilai threshold dan ukuran blok minimum.  
4. Masukkan path output hasil kompresi.  
5. (Opsional) Masukkan path output untuk GIF.  

Jika pengguna memilih membuat GIF, maka frame akan otomatis disimpan dan digabung menggunakan perintah:

```
magick -delay 50 -loop 0 frame*.bmp [path_output].gif  
```

---

## e. Author

- **Author 1:** Sakti Bimasena/13523053 
- **Author 2:** Ahsan Malik Al Farisi/13523074   
