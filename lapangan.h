// Africa Nurhanrafif 103012400150
#ifndef LAPANGAN_H
#define LAPANGAN_H

#include <cstddef>

// ===== CHILD: Lapangan =====
struct Lapangan {
    char kodeLapangan[20];
    char namaLapangan[100];
    char jenisOlahraga[50];
    double hargaPerJam;
};

struct NodeLapangan {
    Lapangan info;
    NodeLapangan* next;
};

struct ListLapangan {
    NodeLapangan* first;
};

void buatListLapangan(ListLapangan &L);
NodeLapangan* cariLapangan(ListLapangan L, const char kodeLapangan[]);

bool tambahLapangan(ListLapangan &L, Lapangan data);

bool ubahLapangan(ListLapangan &L, const char kodeLapangan[], Lapangan dataBaru);

bool hapusLapangan(ListLapangan &L, const char kodeLapangan[]);

void tampilLapangan(ListLapangan L);

#endif
