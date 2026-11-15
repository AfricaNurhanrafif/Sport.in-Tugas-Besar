#ifndef PELANGGAN_H
#define PELANGGAN_H

struct Pelanggan {
    int idPelanggan;
    char nama[100];
    char nomorTelepon[25];
    char email[100];
};

struct NodePelanggan {
    Pelanggan info;
    NodePelanggan* next;
};

struct ListPelanggan {
    NodePelanggan* first;
};

void buatListPelanggan(ListPelanggan &L);
NodePelanggan* cariPelanggan(ListPelanggan L, int idPelanggan);
void tambahPelanggan(ListPelanggan &L, Pelanggan data);
void tampilPelanggan(ListPelanggan L);

#endif
