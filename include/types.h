#pragma once
#include <gtk/gtk.h>

#define STRLEN 25
#define LINEMAX 256

extern char *MONTHS[12];

typedef struct pasien_t
{
  int ID;
  char nama[STRLEN];
  char alamat[STRLEN];
  char kota[STRLEN];
  char tempatLahir[STRLEN];
  int hariLahir;
  int bulanLahir;
  int tahunLahir;
  int umur;
  int BPJS;
  struct pasien_t *next;
} Pasien;

typedef struct riwayat_t
{
  int ID;
  int hariPeriksa;
  int bulanPeriksa;
  int tahunPeriksa;
  char diagnosis[STRLEN];
  char tindakan[STRLEN];
  int hariKontrol;
  int bulanKontrol;
  int tahunKontrol;
  int biaya;
  struct riwayat_t *next;
} Riwayat;

typedef struct pendapatan_bln_t {
  int tahun;
  int bulan;
  int pendapatan;
  struct pendapatan_bln_t *next;
} PendapatanBulanan;

typedef struct pendapatan_thn_t {
  int tahun;
  int pendapatan;
  struct pendapatan_thn_t *next;
} PendapatanTahunan;

typedef struct stat_penyakit_t {
  char nama[STRLEN];
  int jumlah;
  struct stat_penyakit_t *next;
} StatPenyakit;

typedef struct stat_bulanan_t
{
  int bulan;
  int tahun;
  int jumlah_pasien;
  StatPenyakit *stat_penyakit;
  struct stat_bulanan_t *next;
} StatBulanan;

typedef struct stat_tahunan_t
{
  int tahun;
  int jumlah_pasien;
  StatPenyakit *stat_penyakit;
  struct stat_tahunan_t *next;
} StatTahunan;

Pasien *buat_pasien(int ID, char *nama, char *alamat, char *kota, char *tempatLahir, int hariLahir, int bulanLahir, int tahunLahir, int umur, int BPJS);
Riwayat *buat_riwayat(int ID, int hariPeriksa, int bulanPeriksa, int tahunPeriksa, char *diagnosis, char *tindakan, int hariKontrol, int bulanKontrol, int tahunKontrol, int biaya);

void cetak_tanggal(char *str, int hari, int bulan, int tahun);
void cetak_pasien(Pasien *pasien);
void cetak_riwayat(Riwayat *riwayat);

void hapus_pasien(Pasien *pasien);
void hapus_riwayat(Riwayat *riwayat);

void add_pasien(Pasien **head, int ID, char *nama, char *alamat, char *kota, char *tempatLahir, int hariLahir, int bulanLahir, int tahunLahir, int umur, int BPJS);
void edit_pasien(Pasien *head, int ID, char *nama, char *alamat, char *kota, char *tempatLahir, int hariLahir, int bulanLahir, int tahunLahir, int umur, int BPJS);
void delete_pasien(Pasien **head, int ID);
Pasien *search_pasien_by_id(Pasien *head, int ID);

void add_riwayat(Riwayat **head, int ID, int hariPeriksa, int bulanPeriksa, int tahunPeriksa, char *diagnosis, char *tindakan, int hariKontrol, int bulanKontrol, int tahunKontrol, int biaya);
Riwayat *search_riwayat_by_id_and_tanggal(Riwayat *head, int ID, int hariPeriksa, int bulanPeriksa, int tahunPeriksa);
Riwayat *search_riwayat_by_id(Riwayat *head, int ID);
void edit_riwayat(Riwayat *head, int ID, int hariPeriksa, int bulanPeriksa, int tahunPeriksa, char *diagnosis, char *tindakan, int hariKontrol, int bulanKontrol, int tahunKontrol, int biaya);
void delete_riwayat(Riwayat **head, int ID, int hariPeriksa, int bulanPeriksa, int tahunPeriksa);

PendapatanBulanan *buat_pendapatan_bln(int bulan, int tahun, int pendapatan);
PendapatanTahunan *buat_pendapatan_thn(int tahun, int pendapatan);
void tambah_pendapatan_bln(PendapatanBulanan **head, Riwayat *riwayat);
void tambah_pendapatan_thn(PendapatanTahunan **head, Riwayat *riwayat);
double pendapatan_rata2_thn(PendapatanTahunan *head);
void generate_pendapatan(PendapatanBulanan **pend_bln, PendapatanTahunan **pend_thn, Riwayat *riwayat);

void cetak_stat_penyakit(char *str, StatPenyakit *stat);
void generate_stat(StatBulanan **stat_bln, StatTahunan **stat_thn, Riwayat *riwayat);
void sort_stat_penyakit(StatPenyakit **head);