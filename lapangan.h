#ifndef LAPANGAN_H
#define LAPANGAN_H

#include <cstddef>

// ===== CHILD: Lapangan =====
struct Lapangan {
    char kodeLapangan[20];      // unik
    char namaLapangan[100];
    char jenisOlahraga[50];
    double hargaPerJam;
};

struct NodeLapangan {
    Lapangan info;
    NodeLapangan* next;
};

struct ListLapangan {
    NodeLapangan* first;
};

// ----- Primitif -----
void buatListLapangan(ListLapangan &L);
NodeLapangan* cariLapangan(ListLapangan L, const char kodeLapangan[]);

// Mengembalikan false jika kode sudah dipakai (kode harus unik)
bool tambahLapangan(ListLapangan &L, Lapangan data);

// Mengubah data selain kode lapangan. false jika kode tidak ditemukan
bool ubahLapangan(ListLapangan &L, const char kodeLapangan[], Lapangan dataBaru);

// PERHATIAN: panggil lapanganDipakai() (reservasi.h) dulu. Lapangan yang
// masih dipakai reservasi tidak boleh dihapus (pointer relasi jadi dangling).
bool hapusLapangan(ListLapangan &L, const char kodeLapangan[]);

void tampilLapangan(ListLapangan L);

#endif
