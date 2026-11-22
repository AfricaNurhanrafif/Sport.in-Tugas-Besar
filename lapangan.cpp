// Africa Nurhanrafif 103012400150 
#include <cstring>
#include "lapangan.h"
using namespace std;

void buatListLapangan(ListLapangan &L) {
    L.first = NULL;
}

NodeLapangan* cariLapangan(ListLapangan L, const char kodeLapangan[]) {
    NodeLapangan* p = L.first;
    while (p != NULL) {
        if (strcmp(p->info.kodeLapangan, kodeLapangan) == 0) return p;
        p = p->next;
    }
    return NULL;
}

bool tambahLapangan(ListLapangan &L, Lapangan data) {
    if (cariLapangan(L, data.kodeLapangan) != NULL) return false; // kode harus unik

    NodeLapangan* p = new NodeLapangan;
    p->info = data;
    p->next = NULL;

    if (L.first == NULL) {
        L.first = p;
    } else {
        NodeLapangan* q = L.first;
        while (q->next != NULL) q = q->next;
        q->next = p;
    }
    return true;
}

bool ubahLapangan(ListLapangan &L, const char kodeLapangan[], Lapangan dataBaru) {
    NodeLapangan* p = cariLapangan(L, kodeLapangan);
    if (p == NULL) return false;

    // kode tidak diubah, hanya data lainnya
    strcpy(p->info.namaLapangan, dataBaru.namaLapangan);
    strcpy(p->info.jenisOlahraga, dataBaru.jenisOlahraga);
    p->info.hargaPerJam = dataBaru.hargaPerJam;
    return true;
}

bool hapusLapangan(ListLapangan &L, const char kodeLapangan[]) {
    NodeLapangan* prev = NULL;
    NodeLapangan* p = L.first;
    while (p != NULL) {
        if (strcmp(p->info.kodeLapangan, kodeLapangan) == 0) {
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

void tampilLapangan(ListLapangan L) {
    NodeLapangan* p = L.first;
    while (p != NULL) {
        cout << p->info.kodeLapangan << " | " << p->info.namaLapangan
             << " | " << p->info.jenisOlahraga << " | Rp"
             << p->info.hargaPerJam << "/jam\n";
        p = p->next;
    }
}
