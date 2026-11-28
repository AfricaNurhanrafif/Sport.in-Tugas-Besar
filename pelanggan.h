// Africa Nurhanrafif 103012400150
#ifndef PELANGGAN_H
#define PELANGGAN_H

#include <cstddef>

struct NodeRelasi;

struct Pelanggan {
    int idPelanggan;
    char nama[100];
    char nomorTelepon[25];
    char email[100];
};

struct NodePelanggan {
    Pelanggan info;
    NodeRelasi* firstRelasi;
    NodePelanggan* next;
};

struct ListPelanggan {
    NodePelanggan* first;
};

void buatListPelanggan(ListPelanggan &L);
NodePelanggan* cariPelanggan(ListPelanggan L, int idPelanggan);

bool tambahPelanggan(ListPelanggan &L, Pelanggan data);

bool ubahPelanggan(ListPelanggan &L, int idPelanggan, Pelanggan dataBaru);

bool hapusPelanggan(ListPelanggan &L, int idPelanggan);

void tampilPelanggan(ListPelanggan L);

#endif
