#ifndef LAPANGAN_H
#define LAPANGAN_H

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
void tambahLapangan(ListLapangan &L, Lapangan data);
void tampilLapangan(ListLapangan L);

#endif
