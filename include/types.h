#pragma once
#include <time.h>

typedef enum diagnosis_t {Dehidrasi, Keseleo, MasukAngin, Pusing} Diagnosis;
typedef enum tindakan_t {Pendaftaran, Pemeriksaan, Vaksinasi, CekGulaDarah, PasangInfus, Pengobatan} Tindakan;

typedef struct pasien_t {
  int ID;
  char nama[25];
  char alamat[25];
  char kota[25];
  char tempatLahir[25];
  struct tm tanggalLahir;
  int umur;
  int BPJS;
  struct pasien_t* next;
} Pasien;

typedef struct riwayat_t {
  int ID;
  struct tm tanggal;
  Diagnosis diagosis;
  Tindakan tindakan;
  struct tm kontrol;
  int biaya;
  struct riwayat_t* next;
} Riwayat;