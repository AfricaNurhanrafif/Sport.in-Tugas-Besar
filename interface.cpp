// Africa Nurhanrafif 103012400150
#include <iostream>
#include <limits>
#include "interface.h"
#include "pelanggan.h"
#include "lapangan.h"
#include "reservasi.h"
#include "pembayaran.h"

using namespace std;

void tampilkanMenu() {
    cout << "\n========== SPORT.IN ==========\n";
    cout << "1. Kelola data pelanggan\n";
    cout << "2. Kelola data lapangan\n";
    cout << "3. Kelola reservasi\n";
    cout << "4. Proses pembayaran\n";
    cout << "5. Laporan pelanggan dengan pengeluaran tertinggi\n";
    cout << "6. Laporan total pendapatan aplikasi\n";
    cout << "7. Bonus: lapangan dengan reservasi terbanyak\n";
    cout << "8. Bonus: jadwal lapangan tersedia\n";
    cout << "9. Bonus: riwayat reservasi pelanggan\n";
    cout << "0. Keluar\n";
    cout << "Pilihan: ";
}

void jalankanMenu() {
    int pilihan;
    do {
        tampilkanMenu();
        if (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pilihan = -1;
        }

        switch (pilihan) {
            case 1:
                cout << "Modul pelanggan: lengkapi operasi tambah/tampil/ubah/hapus.\n";
                break;
            case 2:
                cout << "Modul lapangan: lengkapi operasi tambah/tampil/ubah/hapus.\n";
                break;
            case 3:
                cout << "Modul reservasi: lengkapi pembuatan dan pengelolaan reservasi.\n";
                break;
            case 4:
                cout << "Modul pembayaran: pilih reservasi, catat pembayaran ke BST, lalu ubah status.\n";
                break;
            case 5:
                cout << "TODO: hitung total pengeluaran reservasi per pelanggan.\n";
                break;
            case 6:
                cout << "TODO: hitung total pendapatan dari pembayaran berhasil.\n";
                break;
            case 7:
                cout << "TODO: tampilkan lapangan dengan jumlah reservasi terbanyak.\n";
                break;
            case 8:
                cout << "TODO: tampilkan jadwal lapangan yang belum terisi.\n";
                break;
            case 9:
                cout << "TODO: tampilkan riwayat reservasi berdasarkan periode.\n";
                break;
            case 0:
                cout << "Program selesai.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);
}
