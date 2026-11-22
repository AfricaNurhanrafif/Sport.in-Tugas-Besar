// Africa Nurhanrafif 103012400150
#ifndef PEMBAYARAN_H
#define PEMBAYARAN_H

#include <cstddef>
#include "reservasi.h"

// Nilai status pembayaran
#define BAYAR_BERHASIL "Berhasil"
#define BAYAR_GAGAL    "Gagal"

// ===== BST: Pembayaran (key = idPembayaran) =====
struct Pembayaran {
    int idPembayaran;           // key BST: unik & acak
    int idReservasi;
    char tanggalPembayaran[11]; // "YYYY-MM-DD"
    char metodePembayaran[30];
    double totalPembayaran;
    char statusPembayaran[20];
};

struct NodePembayaran {
    Pembayaran info;
    NodePembayaran* left;
    NodePembayaran* right;
};

// ----- Primitif BST -----
void buatBSTPembayaran(NodePembayaran* &root);
NodePembayaran* cariPembayaran(NodePembayaran* root, int idPembayaran);

// false jika idPembayaran sudah ada (caller bisa generate ulang)
bool insertPembayaran(NodePembayaran* &root, Pembayaran data);

void tampilPembayaranInOrder(NodePembayaran* root);

// Membuat id acak yang BELUM ada di BST
int generateIdPembayaran(NodePembayaran* root);

// Mencari pembayaran lewat idReservasi (traversal, karena key BST = idPembayaran)
NodePembayaran* cariPembayaranByReservasi(NodePembayaran* root, int idReservasi);

// ----- Fungsional khusus -----
// Memilih reservasi, membuat pembayaran ke BST, lalu mengubah
// statusReservasi -> RESERVASI_DIBAYAR dan statusPembayaran -> BAYAR_BERHASIL.
// false jika reservasi tidak ada / sudah dibayar / dibatalkan.
bool prosesPembayaran(ListPelanggan LP, NodePembayaran* &root, int idReservasi,
                      const char metode[], const char tanggalBayar[]);

double hitungPengeluaranPelanggan(NodePelanggan* pelanggan, NodePembayaran* root);
NodePelanggan* pelangganPengeluaranTertinggi(ListPelanggan LP, NodePembayaran* root);
double hitungPendapatanBerhasil(NodePembayaran* root);

#endif
