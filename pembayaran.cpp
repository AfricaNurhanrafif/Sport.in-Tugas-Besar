#include <iostream>
#include <cstring>
#include "pembayaran.h"
using namespace std;

void buatBSTPembayaran(NodePembayaran* &root) {
    root = NULL;
}

NodePembayaran* cariPembayaran(NodePembayaran* root, int idPembayaran) {
    if (root == NULL || root->info.idPembayaran == idPembayaran) return root;
    if (idPembayaran < root->info.idPembayaran)
        return cariPembayaran(root->left, idPembayaran);
    return cariPembayaran(root->right, idPembayaran);
}

void insertPembayaran(NodePembayaran* &root, Pembayaran data) {
    if (root == NULL) {
        root = new NodePembayaran;
        root->info = data;
        root->left = NULL;
        root->right = NULL;
    } else if (data.idPembayaran < root->info.idPembayaran) {
        insertPembayaran(root->left, data);
    } else if (data.idPembayaran > root->info.idPembayaran) {
        insertPembayaran(root->right, data);
    }
    // ID duplikat tidak dimasukkan.
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

double hitungPendapatanBerhasil(NodePembayaran* root) {
    if (root == NULL) return 0;
    double total = 0;
    if (strcmp(root->info.statusPembayaran, "Berhasil") == 0)
        total = root->info.totalPembayaran;
    return total + hitungPendapatanBerhasil(root->left)
                 + hitungPendapatanBerhasil(root->right);
}
