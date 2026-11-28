// Africa Nurhanrafif 103012400150
#ifndef PEMBAYARAN_H
#define PEMBAYARAN_H

#include <cstddef>
#include "reservasi.h"

#define BAYAR_BERHASIL "Berhasil"
#define BAYAR_GAGAL    "Gagal"

struct Pembayaran {
    int idPembayaran;
    int idReservasi;
    char tanggalPembayaran[11];
    char metodePembayaran[30];
    double totalPembayaran;
    char statusPembayaran[20];
};

struct NodePembayaran {
    Pembayaran info;
    NodePembayaran* left; //pake typedef address aja yg bintang bintang gini
    NodePembayaran* right;
};

void buatBSTPembayaran(NodePembayaran* &root);
NodePembayaran* cariPembayaran(NodePembayaran* root, int idPembayaran);

bool insertPembayaran(NodePembayaran* &root, Pembayaran data);

void tampilPembayaranInOrder(NodePembayaran* root);

int generateIdPembayaran(NodePembayaran* root);

NodePembayaran* cariPembayaranByReservasi(NodePembayaran* root, int idReservasi);

bool prosesPembayaran(ListPelanggan LP, NodePembayaran* &root, int idReservasi,
                      const char metode[], const char tanggalBayar[]);

double hitungPengeluaranPelanggan(NodePelanggan* pelanggan, NodePembayaran* root);
NodePelanggan* pelangganPengeluaranTertinggi(ListPelanggan LP, NodePembayaran* root);
double hitungPendapatanBerhasil(NodePembayaran* root);

#endif
