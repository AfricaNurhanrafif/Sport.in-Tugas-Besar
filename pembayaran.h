#ifndef PEMBAYARAN_H
#define PEMBAYARAN_H

struct Pembayaran {
    int idPembayaran; // key BST: harus unik
    int idReservasi;
    char tanggalPembayaran[20];
    char metodePembayaran[30];
    double totalPembayaran;
    char statusPembayaran[20];
};

struct NodePembayaran {
    Pembayaran info;
    NodePembayaran* left;
    NodePembayaran* right;
};

void buatBSTPembayaran(NodePembayaran* &root);
NodePembayaran* cariPembayaran(NodePembayaran* root, int idPembayaran);
void insertPembayaran(NodePembayaran* &root, Pembayaran data);
void tampilPembayaranInOrder(NodePembayaran* root);
double hitungPendapatanBerhasil(NodePembayaran* root);

#endif
