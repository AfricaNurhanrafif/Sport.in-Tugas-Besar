#ifndef RESERVASI_H
#define RESERVASI_H

#include <cstddef>
#include "pelanggan.h"
#include "lapangan.h"

// Nilai status reservasi (pakai konstanta ini, jangan ketik string manual)
#define RESERVASI_MENUNGGU   "Menunggu"
#define RESERVASI_DIBAYAR    "Dibayar"
#define RESERVASI_DIBATALKAN "Dibatalkan"

// ===== RELASI: Reservasi =====
struct Reservasi {
    int idReservasi;            // unik
    char tanggalReservasi[11];  // format tetap "YYYY-MM-DD" (bisa dibandingkan dgn strcmp)
    int jamMulai;               // 0 - 23
    int durasiJam;              // lama pemakaian (jam)
    char statusReservasi[20];
};

// Node relasi: menghubungkan parent (Pelanggan) ke child (Lapangan)
struct NodeRelasi {
    Reservasi info;
    NodeLapangan* lapangan;     // pointer ke child
    NodeRelasi* next;
};

// ----- Primitif -----
// false jika id reservasi sudah dipakai ATAU jadwal bentrok di lapangan tsb.
// Status awal diisi RESERVASI_MENUNGGU.
bool tambahReservasi(ListPelanggan LP, NodePelanggan* pelanggan,
                     NodeLapangan* lapangan, Reservasi data);

// Mencari reservasi di semua pelanggan; 'pemilik' diisi parent-nya
NodeRelasi* cariReservasi(ListPelanggan LP, int idReservasi, NodePelanggan* &pemilik);

bool ubahStatusReservasi(ListPelanggan LP, int idReservasi, const char statusBaru[]);
bool hapusReservasi(ListPelanggan LP, int idReservasi);

void tampilReservasiPelanggan(NodePelanggan* pelanggan);
void tampilSemuaReservasi(ListPelanggan LP);

// ----- Perhitungan & pengecekan -----
double hitungTotalReservasi(NodeRelasi* r);          // hargaPerJam x durasiJam
bool lapanganDipakai(ListPelanggan LP, const char kodeLapangan[]);
bool jadwalBentrok(ListPelanggan LP, const char kodeLapangan[],
                   const char tanggal[], int jamMulai, int durasiJam);

// ----- Fungsional bonus -----
int hitungReservasiLapangan(ListPelanggan LP, const char kodeLapangan[]);
NodeLapangan* lapanganReservasiTerbanyak(ListPelanggan LP, ListLapangan LL);
void tampilJadwalTersedia(ListPelanggan LP, NodeLapangan* lapangan,
                          const char tanggal[], int jamBuka, int jamTutup);
void tampilRiwayatPelanggan(NodePelanggan* pelanggan,
                            const char tanggalAwal[], const char tanggalAkhir[]);

#endif
