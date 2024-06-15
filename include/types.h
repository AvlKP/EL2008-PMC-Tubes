#pragma once
#include <gtk/gtk.h>

typedef enum diagnosis_t
{
  Dehidrasi,
  Keseleo,
  MasukAngin,
  Pusing
} Diagnosis;
typedef enum tindakan_t
{
  Pendaftaran,
  Pemeriksaan,
  Vaksinasi,
  CekGulaDarah,
  PasangInfus,
  Pengobatan
} Tindakan;

extern char *MONTHS[12];

typedef struct tanggal_t
{
  int hari;
  int bulan;
  int tahun;
} Tanggal;

typedef struct pasien_t
{
  int ID;
  char nama[25];
  char alamat[25];
  char kota[25];
  char tempatLahir[25];
  Tanggal *tanggalLahir;
  int umur;
  int BPJS;
  struct pasien_t *next;
} Pasien;

typedef struct riwayat_t
{
  int ID;
  Tanggal *tanggal;
  Diagnosis diagnosis;
  Tindakan tindakan;
  Tanggal *kontrol;
  int biaya;
  struct riwayat_t *next;
} Riwayat;

typedef struct pasien_search_t {
  Pasien *pasien;
  struct pasien_search_t *next;
} PasienSearch;

typedef struct riwayat_search_t {
  Riwayat *riwayat;
  struct riwayat_search_t *next;
} RiwayatSearch;

Tanggal *buat_tanggal(int hari, int bulan, int tahun);
Pasien *buat_pasien(int ID, char *nama, char *alamat, char *kota, char *tempatLahir, Tanggal *tanggalLahir, int umur, int BPJS);
Riwayat *buat_riwayat(int ID, Tanggal *tanggal, Diagnosis diagnosis, Tindakan tindakan, Tanggal *kontrol, int biaya);

void cetak_tanggal(char *str, Tanggal *tanggal);
void cetak_pasien(Pasien *pasien);
void cetak_riwayat(Riwayat *riwayat);

void hapus_pasien(Pasien *pasien);
void hapus_riwayat(Riwayat *riwayat);

Diagnosis str_ke_diagnosis(char *str);
Tindakan str_ke_tindakan(char *str);

void add_pasien(Pasien **head, int id, char *nama, char *alamat, char *kota, char *tempatLahir, Tanggal *tanggalLahir, int umur, int BPJS);
void edit_pasien(Pasien *head, int id, char *nama, char *alamat, char *kota, char *tempatLahir, Tanggal *tanggalLahir, int umur, int BPJS);
void delete_pasien(Pasien **head, int id);
Pasien *search_pasien_by_id(Pasien *head, int id);