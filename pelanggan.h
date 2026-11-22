// Africa Nurhanrafif 103012400150
#ifndef PELANGGAN_H
#define PELANGGAN_H

#include <cstddef>

struct NodeRelasi;              // didefinisikan di reservasi.h

// ===== PARENT: Pelanggan =====
struct Pelanggan {
    int idPelanggan;            // unik
    char nama[100];
    char nomorTelepon[25];
    char email[100];
};

struct NodePelanggan {
    Pelanggan info;
    NodeRelasi* firstRelasi;    // list reservasi milik pelanggan ini
    NodePelanggan* next;
};

struct ListPelanggan {
    NodePelanggan* first;
};

// ----- Primitif -----
void buatListPelanggan(ListPelanggan &L);
NodePelanggan* cariPelanggan(ListPelanggan L, int idPelanggan);

// Mengembalikan false jika id sudah dipakai. firstRelasi diisi NULL.
bool tambahPelanggan(ListPelanggan &L, Pelanggan data);

// Mengubah data selain id. false jika id tidak ditemukan
bool ubahPelanggan(ListPelanggan &L, int idPelanggan, Pelanggan dataBaru);

// Menghapus pelanggan beserta SELURUH list reservasinya
bool hapusPelanggan(ListPelanggan &L, int idPelanggan);

void tampilPelanggan(ListPelanggan L);

#endif
