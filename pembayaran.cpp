#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "pembayaran.h"
using namespace std;

// Menyalin string ke array tetap tanpa melewati batas
static void salin(char tujuan[], const char sumber[], int ukuran) {
    strncpy(tujuan, sumber, ukuran - 1);
    tujuan[ukuran - 1] = '\0';
}

void buatBSTPembayaran(NodePembayaran* &root) {
    root = NULL;
}

NodePembayaran* cariPembayaran(NodePembayaran* root, int idPembayaran) {
    if (root == NULL || root->info.idPembayaran == idPembayaran) return root;
    if (idPembayaran < root->info.idPembayaran)
        return cariPembayaran(root->left, idPembayaran);
    return cariPembayaran(root->right, idPembayaran);
}

bool insertPembayaran(NodePembayaran* &root, Pembayaran data) {
    if (root == NULL) {
        root = new NodePembayaran;
        root->info = data;
        root->left = NULL;
        root->right = NULL;
        return true;
    }
    if (data.idPembayaran < root->info.idPembayaran)
        return insertPembayaran(root->left, data);
    if (data.idPembayaran > root->info.idPembayaran)
        return insertPembayaran(root->right, data);
    return false;   // ID duplikat tidak dimasukkan
}

void tampilPembayaranInOrder(NodePembayaran* root) {
    if (root != NULL) {
        tampilPembayaranInOrder(root->left);
        cout << "ID Pembayaran: " << root->info.idPembayaran
             << " | ID Reservasi: " << root->info.idReservasi
             << " | Tanggal: " << root->info.tanggalPembayaran
             << " | Metode: " << root->info.metodePembayaran
             << " | Total: Rp" << root->info.totalPembayaran
             << " | Status: " << root->info.statusPembayaran << '\n';
        tampilPembayaranInOrder(root->right);
    }
}

// ID acak 6 digit (100000 - 999999) yang belum ada di BST.
// rand() digabung dua kali supaya aman di compiler dengan RAND_MAX kecil (32767).
int generateIdPembayaran(NodePembayaran* root) {
    static bool sudahSeed = false;
    if (!sudahSeed) {
        srand((unsigned) time(NULL));
        sudahSeed = true;
    }
    int id;
    do {
        id = 100000 + ((rand() % 1000) * 1000 + (rand() % 1000)) % 900000;
    } while (cariPembayaran(root, id) != NULL);
    return id;
}

NodePembayaran* cariPembayaranByReservasi(NodePembayaran* root, int idReservasi) {
    if (root == NULL) return NULL;
    if (root->info.idReservasi == idReservasi) return root;
    NodePembayaran* hasil = cariPembayaranByReservasi(root->left, idReservasi);
    if (hasil != NULL) return hasil;
    return cariPembayaranByReservasi(root->right, idReservasi);
}

bool prosesPembayaran(ListPelanggan LP, NodePembayaran* &root, int idReservasi,
                      const char metode[], const char tanggalBayar[]) {
    NodePelanggan* pemilik;
    NodeRelasi* r = cariReservasi(LP, idReservasi, pemilik);
    if (r == NULL) return false;

    // hanya reservasi berstatus "Menunggu" yang boleh dibayar
    if (strcmp(r->info.statusReservasi, RESERVASI_MENUNGGU) != 0) return false;
    if (cariPembayaranByReservasi(root, idReservasi) != NULL) return false;

    Pembayaran b;
    b.idPembayaran = generateIdPembayaran(root);
    b.idReservasi = idReservasi;
    salin(b.tanggalPembayaran, tanggalBayar, sizeof(b.tanggalPembayaran));
    salin(b.metodePembayaran, metode, sizeof(b.metodePembayaran));
    b.totalPembayaran = hitungTotalReservasi(r);
    salin(b.statusPembayaran, BAYAR_BERHASIL, sizeof(b.statusPembayaran));

    if (!insertPembayaran(root, b)) return false;

    // transaksi berhasil -> perbarui status reservasi
    strcpy(r->info.statusReservasi, RESERVASI_DIBAYAR);
    return true;
}

double hitungPengeluaranPelanggan(NodePelanggan* pelanggan, NodePembayaran* root) {
    if (pelanggan == NULL) return 0;
    double total = 0;
    NodeRelasi* r = pelanggan->firstRelasi;
    while (r != NULL) {
        NodePembayaran* b = cariPembayaranByReservasi(root, r->info.idReservasi);
        if (b != NULL && strcmp(b->info.statusPembayaran, BAYAR_BERHASIL) == 0)
            total += b->info.totalPembayaran;
        r = r->next;
    }
    return total;
}

// NULL jika belum ada pelanggan yang punya pembayaran berhasil
NodePelanggan* pelangganPengeluaranTertinggi(ListPelanggan LP, NodePembayaran* root) {
    NodePelanggan* terbaik = NULL;
    double maks = 0;
    NodePelanggan* p = LP.first;
    while (p != NULL) {
        double total = hitungPengeluaranPelanggan(p, root);
        if (total > maks) {
            maks = total;
            terbaik = p;
        }
        p = p->next;
    }
    return terbaik;
}

double hitungPendapatanBerhasil(NodePembayaran* root) {
    if (root == NULL) return 0;
    double total = 0;
    if (strcmp(root->info.statusPembayaran, BAYAR_BERHASIL) == 0)
        total = root->info.totalPembayaran;
    return total + hitungPendapatanBerhasil(root->left)
                 + hitungPendapatanBerhasil(root->right);
}
