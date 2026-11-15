#include <iostream>
#include "reservasi.h"
using namespace std;

void buatListReservasi(ListReservasi &L) {
    L.first = NULL;
}

NodeReservasi* cariReservasi(ListReservasi L, int idReservasi) {
    NodeReservasi* p = L.first;
    while (p != NULL) {
        if (p->info.idReservasi == idReservasi) return p;
        p = p->next;
    }
    return NULL;
}

void tambahReservasi(ListReservasi &L, Reservasi data) {
    NodeReservasi* p = new NodeReservasi;
    p->info = data;
    p->next = NULL;

    if (L.first == NULL) {
        L.first = p;
    } else {
        NodeReservasi* q = L.first;
        while (q->next != NULL) q = q->next;
        q->next = p;
    }
}

void tampilReservasi(ListReservasi L) {
    NodeReservasi* p = L.first;
    while (p != NULL) {
        cout << "ID: " << p->info.idReservasi
             << " | Pelanggan: " << p->info.idPelanggan
             << " | Lapangan: " << p->info.kodeLapangan
             << " | Tanggal: " << p->info.tanggalReservasi
             << " | Mulai: " << p->info.jamMulai
             << " | Durasi: " << p->info.durasiJam
             << " jam | Status: " << p->info.statusReservasi << '\n';
        p = p->next;
    }
}
