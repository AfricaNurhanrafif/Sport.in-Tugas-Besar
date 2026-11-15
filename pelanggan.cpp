#include <iostream>
#include "pelanggan.h"
using namespace std;

void buatListPelanggan(ListPelanggan &L) {
    L.first = NULL;
}

NodePelanggan* cariPelanggan(ListPelanggan L, int idPelanggan) {
    NodePelanggan* p = L.first;
    while (p != NULL) {
        if (p->info.idPelanggan == idPelanggan) return p;
        p = p->next;
    }
    return NULL;
}

void tambahPelanggan(ListPelanggan &L, Pelanggan data) {
    NodePelanggan* p = new NodePelanggan;
    p->info = data;
    p->next = NULL;

    if (L.first == NULL) {
        L.first = p;
    } else {
        NodePelanggan* q = L.first;
        while (q->next != NULL) q = q->next;
        q->next = p;
    }
}

void tampilPelanggan(ListPelanggan L) {
    NodePelanggan* p = L.first;
    while (p != NULL) {
        cout << p->info.idPelanggan << " | " << p->info.nama
             << " | " << p->info.nomorTelepon << " | " << p->info.email << '\n';
        p = p->next;
    }
}
