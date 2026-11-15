#ifndef RESERVASI_H
#define RESERVASI_H

struct Reservasi {
    int idReservasi;
    int idPelanggan;
    char kodeLapangan[20];
    char tanggalReservasi[20];
    char jamMulai[10];
    int durasiJam;
    char statusReservasi[20];
};

struct NodeReservasi {
    Reservasi info;
    NodeReservasi* next;
};

struct ListReservasi {
    NodeReservasi* first;
};

void buatListReservasi(ListReservasi &L);
NodeReservasi* cariReservasi(ListReservasi L, int idReservasi);
void tambahReservasi(ListReservasi &L, Reservasi data);
void tampilReservasi(ListReservasi L);

#endif
