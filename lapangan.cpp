#include <iostream>
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

void tambahLapangan(ListLapangan &L, Lapangan data) {
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
