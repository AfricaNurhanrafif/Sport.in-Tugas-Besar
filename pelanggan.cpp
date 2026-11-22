// Africa Nurhanrafif 103012400150
#include <iostream>
#include <cstring>
#include "pelanggan.h"
#include "reservasi.h"   // butuh NodeRelasi lengkap untuk hapusPelanggan
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

bool tambahPelanggan(ListPelanggan &L, Pelanggan data) {
    if (cariPelanggan(L, data.idPelanggan) != NULL) return false; // id harus unik

    NodePelanggan* p = new NodePelanggan;
    p->info = data;
    p->firstRelasi = NULL;   // belum punya reservasi
    p->next = NULL;

    if (L.first == NULL) {
        L.first = p;
    } else {
        NodePelanggan* q = L.first;
        while (q->next != NULL) q = q->next;
        q->next = p;
    }
    return true;
}

bool ubahPelanggan(ListPelanggan &L, int idPelanggan, Pelanggan dataBaru) {
    NodePelanggan* p = cariPelanggan(L, idPelanggan);
    if (p == NULL) return false;

    // id tidak diubah, hanya data lainnya
    strcpy(p->info.nama, dataBaru.nama);
    strcpy(p->info.nomorTelepon, dataBaru.nomorTelepon);
    strcpy(p->info.email, dataBaru.email);
    return true;
}

bool hapusPelanggan(ListPelanggan &L, int idPelanggan) {
    NodePelanggan* prev = NULL;
    NodePelanggan* p = L.first;
    while (p != NULL) {
        if (p->info.idPelanggan == idPelanggan) {
            // hapus seluruh reservasi milik pelanggan ini (lapangan TIDAK ikut dihapus)
            NodeRelasi* r = p->firstRelasi;
            while (r != NULL) {
                NodeRelasi* hapus = r;
                r = r->next;
                delete hapus;
            }
            if (prev == NULL) L.first = p->next;
            else prev->next = p->next;
            delete p;
            return true;
        }
        prev = p;
        p = p->next;
    }
    return false;
}

void tampilPelanggan(ListPelanggan L) {
    NodePelanggan* p = L.first;
    while (p != NULL) {
        cout << p->info.idPelanggan << " | " << p->info.nama
             << " | " << p->info.nomorTelepon << " | " << p->info.email << '\n';
        p = p->next;
    }
}
