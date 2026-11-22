#include <iostream>
#include <cstring>
#include "reservasi.h"
using namespace std;

NodeRelasi* cariReservasi(ListPelanggan LP, int idReservasi, NodePelanggan* &pemilik) {
    NodePelanggan* pl = LP.first;
    while (pl != NULL) {
        NodeRelasi* r = pl->firstRelasi;
        while (r != NULL) {
            if (r->info.idReservasi == idReservasi) {
                pemilik = pl;
                return r;
            }
            r = r->next;
        }
        pl = pl->next;
    }
    pemilik = NULL;
    return NULL;
}

bool tambahReservasi(ListPelanggan LP, NodePelanggan* pelanggan,
                     NodeLapangan* lapangan, Reservasi data) {
    if (pelanggan == NULL || lapangan == NULL) return false;

    // validasi jadwal: jam 0-23, durasi minimal 1 jam, tidak lewat tengah malam
    if (data.jamMulai < 0 || data.jamMulai > 23) return false;
    if (data.durasiJam < 1 || data.jamMulai + data.durasiJam > 24) return false;

    NodePelanggan* pemilik;
    if (cariReservasi(LP, data.idReservasi, pemilik) != NULL) return false; // id unik
    if (jadwalBentrok(LP, lapangan->info.kodeLapangan, data.tanggalReservasi,
                      data.jamMulai, data.durasiJam)) return false;

    NodeRelasi* r = new NodeRelasi;
    r->info = data;
    strcpy(r->info.statusReservasi, RESERVASI_MENUNGGU);
    r->lapangan = lapangan;
    r->next = NULL;

    if (pelanggan->firstRelasi == NULL) {
        pelanggan->firstRelasi = r;
    } else {
        NodeRelasi* q = pelanggan->firstRelasi;
        while (q->next != NULL) q = q->next;
        q->next = r;
    }
    return true;
}

bool ubahStatusReservasi(ListPelanggan LP, int idReservasi, const char statusBaru[]) {
    NodePelanggan* pemilik;
    NodeRelasi* r = cariReservasi(LP, idReservasi, pemilik);
    if (r == NULL) return false;
    strcpy(r->info.statusReservasi, statusBaru);
    return true;
}

bool hapusReservasi(ListPelanggan LP, int idReservasi) {
    NodePelanggan* pl = LP.first;
    while (pl != NULL) {
        NodeRelasi* prev = NULL;
        NodeRelasi* r = pl->firstRelasi;
        while (r != NULL) {
            if (r->info.idReservasi == idReservasi) {
                if (prev == NULL) pl->firstRelasi = r->next;
                else prev->next = r->next;
                delete r;
                return true;
            }
            prev = r;
            r = r->next;
        }
        pl = pl->next;
    }
    return false;
}

void tampilReservasiPelanggan(NodePelanggan* pelanggan) {
    if (pelanggan == NULL) return;
    NodeRelasi* r = pelanggan->firstRelasi;
    if (r == NULL) {
        cout << "  (belum ada reservasi)\n";
        return;
    }
    while (r != NULL) {
        cout << "  ID: " << r->info.idReservasi
             << " | Lapangan: " << r->lapangan->info.namaLapangan
             << " (" << r->lapangan->info.kodeLapangan << ")"
             << " | Tanggal: " << r->info.tanggalReservasi
             << " | Mulai: " << r->info.jamMulai << ":00"
             << " | Durasi: " << r->info.durasiJam << " jam"
             << " | Status: " << r->info.statusReservasi << '\n';
        r = r->next;
    }
}

void tampilSemuaReservasi(ListPelanggan LP) {
    NodePelanggan* pl = LP.first;
    while (pl != NULL) {
        cout << pl->info.idPelanggan << " - " << pl->info.nama << '\n';
        tampilReservasiPelanggan(pl);
        pl = pl->next;
    }
}

double hitungTotalReservasi(NodeRelasi* r) {
    if (r == NULL || r->lapangan == NULL) return 0;
    return r->lapangan->info.hargaPerJam * r->info.durasiJam;
}

bool lapanganDipakai(ListPelanggan LP, const char kodeLapangan[]) {
    NodePelanggan* pl = LP.first;
    while (pl != NULL) {
        NodeRelasi* r = pl->firstRelasi;
        while (r != NULL) {
            if (strcmp(r->lapangan->info.kodeLapangan, kodeLapangan) == 0) return true;
            r = r->next;
        }
        pl = pl->next;
    }
    return false;
}

// Bentrok jika rentang [mulai, selesai) saling tumpang tindih pada
// lapangan dan tanggal yang sama. Reservasi yang dibatalkan diabaikan.
bool jadwalBentrok(ListPelanggan LP, const char kodeLapangan[],
                   const char tanggal[], int jamMulai, int durasiJam) {
    int selesaiBaru = jamMulai + durasiJam;
    NodePelanggan* pl = LP.first;
    while (pl != NULL) {
        NodeRelasi* r = pl->firstRelasi;
        while (r != NULL) {
            if (strcmp(r->lapangan->info.kodeLapangan, kodeLapangan) == 0 &&
                strcmp(r->info.tanggalReservasi, tanggal) == 0 &&
                strcmp(r->info.statusReservasi, RESERVASI_DIBATALKAN) != 0) {
                int mulaiAda = r->info.jamMulai;
                int selesaiAda = r->info.jamMulai + r->info.durasiJam;
                if (jamMulai < selesaiAda && mulaiAda < selesaiBaru) return true;
            }
            r = r->next;
        }
        pl = pl->next;
    }
    return false;
}

// Reservasi yang dibatalkan tidak dihitung
int hitungReservasiLapangan(ListPelanggan LP, const char kodeLapangan[]) {
    int jumlah = 0;
    NodePelanggan* pl = LP.first;
    while (pl != NULL) {
        NodeRelasi* r = pl->firstRelasi;
        while (r != NULL) {
            if (strcmp(r->lapangan->info.kodeLapangan, kodeLapangan) == 0 &&
                strcmp(r->info.statusReservasi, RESERVASI_DIBATALKAN) != 0) {
                jumlah++;
            }
            r = r->next;
        }
        pl = pl->next;
    }
    return jumlah;
}

// NULL jika belum ada lapangan yang direservasi. Jika seri, yang pertama di list.
NodeLapangan* lapanganReservasiTerbanyak(ListPelanggan LP, ListLapangan LL) {
    NodeLapangan* terbaik = NULL;
    int maks = 0;
    NodeLapangan* p = LL.first;
    while (p != NULL) {
        int jumlah = hitungReservasiLapangan(LP, p->info.kodeLapangan);
        if (jumlah > maks) {
            maks = jumlah;
            terbaik = p;
        }
        p = p->next;
    }
    return terbaik;
}

void tampilJadwalTersedia(ListPelanggan LP, NodeLapangan* lapangan,
                          const char tanggal[], int jamBuka, int jamTutup) {
    if (lapangan == NULL) return;
    cout << "Jadwal tersedia " << lapangan->info.namaLapangan
         << " pada " << tanggal << ":\n";

    bool ada = false;
    int mulai = -1;   // awal rentang jam kosong yang sedang dibaca
    for (int jam = jamBuka; jam <= jamTutup; jam++) {
        bool kosong = (jam < jamTutup) &&
                      !jadwalBentrok(LP, lapangan->info.kodeLapangan, tanggal, jam, 1);
        if (kosong && mulai == -1) {
            mulai = jam;
        } else if (!kosong && mulai != -1) {
            cout << "  " << mulai << ":00 - " << jam << ":00\n";
            ada = true;
            mulai = -1;
        }
    }
    if (!ada) cout << "  (tidak ada jadwal kosong)\n";
}

// Tanggal berformat YYYY-MM-DD, jadi bisa dibandingkan dengan strcmp
void tampilRiwayatPelanggan(NodePelanggan* pelanggan,
                            const char tanggalAwal[], const char tanggalAkhir[]) {
    if (pelanggan == NULL) return;
    bool ada = false;
    NodeRelasi* r = pelanggan->firstRelasi;
    while (r != NULL) {
        if (strcmp(r->info.tanggalReservasi, tanggalAwal) >= 0 &&
            strcmp(r->info.tanggalReservasi, tanggalAkhir) <= 0) {
            cout << "  ID: " << r->info.idReservasi
                 << " | Lapangan: " << r->lapangan->info.namaLapangan
                 << " | Tanggal: " << r->info.tanggalReservasi
                 << " | Mulai: " << r->info.jamMulai << ":00"
                 << " | Durasi: " << r->info.durasiJam << " jam"
                 << " | Status: " << r->info.statusReservasi << '\n';
            ada = true;
        }
        r = r->next;
    }
    if (!ada) cout << "  (tidak ada reservasi pada periode ini)\n";
}
