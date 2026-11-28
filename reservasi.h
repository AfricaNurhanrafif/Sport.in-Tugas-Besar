// Africa Nurhanrafif 103012400150
#ifndef RESERVASI_H
#define RESERVASI_H

#include <cstddef>
#include "pelanggan.h"
#include "lapangan.h"

#define RESERVASI_MENUNGGU   "Menunggu"
#define RESERVASI_DIBAYAR    "Dibayar"
#define RESERVASI_DIBATALKAN "Dibatalkan"

struct Reservasi {
    int idReservasi;
    char tanggalReservasi[11];
    int jamMulai;
    int durasiJam;
    char statusReservasi[20];
};

struct NodeRelasi {
    Reservasi info;
    NodeLapangan* lapangan;
    NodeRelasi* next;
};


bool tambahReservasi(ListPelanggan LP, NodePelanggan* pelanggan,
                     NodeLapangan* lapangan, Reservasi data);

NodeRelasi* cariReservasi(ListPelanggan LP, int idReservasi, NodePelanggan* &pemilik);

bool ubahStatusReservasi(ListPelanggan LP, int idReservasi, const char statusBaru[]);
bool hapusReservasi(ListPelanggan LP, int idReservasi);

void tampilReservasiPelanggan(NodePelanggan* pelanggan);
void tampilSemuaReservasi(ListPelanggan LP);

double hitungTotalReservasi(NodeRelasi* r);
bool lapanganDipakai(ListPelanggan LP, const char kodeLapangan[]);
bool jadwalBentrok(ListPelanggan LP, const char kodeLapangan[],
                   const char tanggal[], int jamMulai, int durasiJam);

int hitungReservasiLapangan(ListPelanggan LP, const char kodeLapangan[]);
NodeLapangan* lapanganReservasiTerbanyak(ListPelanggan LP, ListLapangan LL);
void tampilJadwalTersedia(ListPelanggan LP, NodeLapangan* lapangan,
                          const char tanggal[], int jamBuka, int jamTutup);
void tampilRiwayatPelanggan(NodePelanggan* pelanggan,
                            const char tanggalAwal[], const char tanggalAkhir[]);

#endif
