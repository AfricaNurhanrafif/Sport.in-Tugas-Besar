# Sport.in — Template Tugas Besar Struktur Data

Template awal C++ untuk topik **Lapangan Olahraga (Sport.in)**.

## Struktur data yang disiapkan
- **Pelanggan (Parent):** singly linked list
- **Lapangan (Child):** singly linked list
- **Reservasi (Relasi):** singly linked list yang menyimpan ID pelanggan dan kode lapangan
- **Pembayaran:** Binary Search Tree (BST) dengan `idPembayaran` sebagai key

## Cara membuka
1. Ekstrak ZIP.
2. Buka `Sport.in.cbp` menggunakan Code::Blocks.
3. Pastikan compiler C++ tersedia.
4. Klik **Build and Run**.

## Status template
Template ini merupakan kerangka awal yang dapat dikompilasi. Struktur data, deklarasi fungsi, menu utama, dan placeholder fitur sudah disiapkan. Isi fungsi CRUD, validasi jadwal, proses pembayaran, dan laporan masih perlu dikembangkan sesuai aturan tugas dosen.

## File
- `main.cpp`: titik masuk program
- `interface.h/.cpp`: menu utama
- `pelanggan.h/.cpp`: data dan operasi pelanggan
- `lapangan.h/.cpp`: data dan operasi lapangan
- `reservasi.h/.cpp`: data dan operasi reservasi
- `pembayaran.h/.cpp`: node BST pembayaran
