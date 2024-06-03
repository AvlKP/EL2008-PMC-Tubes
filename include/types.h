#pragma once

typedef enum diagnosis_t {Dehidrasi, Keseleo, MasukAngin, Pusing} Diagnosis;
typedef enum tindakan_t {Pendaftaran, Pemeriksaan, Vaksinasi, CekGulaDarah, PasangInfus, Pengobatan} Tindakan;

extern char* MONTHS[12];

typedef struct tanggal_t {
  int hari;
  int bulan;
  int tahun;
} Tanggal;

typedef struct pasien_t {
  int ID;
  char nama[25];
  char alamat[25];
  char kota[25];
  char tempatLahir[25];
  Tanggal* tanggalLahir;
  int umur;
  int BPJS;
  struct pasien_t* next;
} Pasien;

typedef struct riwayat_t {
  int ID;
  Tanggal* tanggal;
  Diagnosis diagnosis;
  Tindakan tindakan;
  Tanggal* kontrol;
  int biaya;
  struct riwayat_t* next;
} Riwayat;

Tanggal* buatTanggal(int hari, int bulan, int tahun);
Pasien* buatPasien(int ID, char* nama, char* alamat, char* kota, char* tempatLahir, Tanggal* tanggalLahir, int umur, int BPJS);
Riwayat* buatRiwayat(int ID, Tanggal* tanggal, Diagnosis diagnosis, Tindakan tindakan, Tanggal* kontrol, int biaya);

void cetakTanggal(char* str, Tanggal* tanggal);
void cetakPasien(Pasien* pasien);
void cetakRiwayat(Riwayat* riwayat);

void hapusPasien(Pasien* pasien);
void hapusRiwayat(Riwayat* riwayat);

Diagnosis str2Diagnosis(char* str);
Tindakan str2Tindakan(char* str);