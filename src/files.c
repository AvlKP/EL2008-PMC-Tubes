// Membaca file data dengan asumsi bentuk data akan selalu sama seperti yang diberikan
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "files.h"

#define BUFLEN 256

char *MONTHS[12] = {"Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"};

void *baca_tanggal(char *sTanggal, int offset, int *hari, int *bulan, int *tahun)
{
  char sBulan[10], temp[10];

  if (sscanf(sTanggal, "%d %s %d", hari, sBulan, tahun) != 3)
  {
    sscanf(sTanggal, "%d-%[^-]-%d", hari, sBulan, tahun);
    *tahun += offset;
  }

  for (int i = 0; i < 12; i++)
  {
    if (!strncmp(MONTHS[i], sBulan, 3))
    {
      *bulan = i + 1;
      break;
    }
  }
}

Pasien *baca_data_pasien(char *path)
{
  FILE *fp = fopen(path, "r");
  if (fp == NULL)
  {
    printf("File data pasien gagal dibuka.\n");
    exit(EXIT_FAILURE);
  }

  char buf[BUFLEN];
  int row = 0;

  Pasien *daftarPasien = NULL;
  Pasien *tempPasien = NULL;
  while (fgets(buf, BUFLEN, fp))
  {
    if (row > 0)
    {
      int ID, umur, BPJS;
      char nama[STRLEN], alamat[STRLEN], kota[STRLEN], tempatLahir[STRLEN], tanggalLahir[STRLEN];

      sscanf(buf, "%*d, %[^,], %[^,], %[^,], %[^,], %[^,], %d, %d, %*s %d",
             nama, alamat, kota, tempatLahir, tanggalLahir, &umur, &BPJS, &ID);

      int hariLahir, bulanLahir, tahunLahir;
      baca_tanggal(tanggalLahir, 1900, &hariLahir, &bulanLahir, &tahunLahir);

      if (daftarPasien == NULL)
      {
        daftarPasien = buat_pasien(ID, nama, alamat, kota, tempatLahir, hariLahir, bulanLahir, tahunLahir, umur, BPJS);
        tempPasien = daftarPasien;
      }
      else
      {
        tempPasien->next = buat_pasien(ID, nama, alamat, kota, tempatLahir, hariLahir, bulanLahir, tahunLahir, umur, BPJS);
        tempPasien = tempPasien->next;
      }
    }
    row++;
  }

  fclose(fp);
  return daftarPasien;
}

Riwayat *baca_riwayat(char *path)
{
  FILE *fp = fopen(path, "r");
  if (fp == NULL)
  {
    printf("File riwayat gagal dibuka.\n");
    exit(EXIT_FAILURE);
  }

  char buf[BUFLEN];
  int row = 0;

  Riwayat *daftarRiwayat = NULL;
  Riwayat *tempRiwayat = NULL;
  while (fgets(buf, BUFLEN, fp))
  {
    if (row > 0)
    {
      int ID, biaya;
      int hariPeriksa, bulanPeriksa, tahunPeriksa;
      int hariKontrol, bulanKontrol, tahunKontrol;

      char tanggalPeriksa[STRLEN], tanggalKontrol[STRLEN], diagnosis[STRLEN], tindakan[STRLEN];

      sscanf(buf, "%*d, %[^,], %*s %d, %[^,], %[^,], %[^,], %d",
             tanggalPeriksa, &ID, diagnosis, tindakan, tanggalKontrol, &biaya);

      baca_tanggal(tanggalPeriksa, 2000, &hariPeriksa, &bulanPeriksa, &tahunPeriksa);
      baca_tanggal(tanggalKontrol, 2000, &hariKontrol, &bulanKontrol, &tahunKontrol);

      if (daftarRiwayat == NULL)
      {
        daftarRiwayat = buat_riwayat(ID, hariPeriksa, bulanPeriksa, tahunPeriksa, diagnosis, tindakan, hariKontrol, bulanKontrol, tahunKontrol, biaya);
        tempRiwayat = daftarRiwayat;
      }
      else
      {
        tempRiwayat->next = buat_riwayat(ID, hariPeriksa, bulanPeriksa, tahunPeriksa, diagnosis, tindakan, hariKontrol, bulanKontrol, tahunKontrol, biaya);
        tempRiwayat = tempRiwayat->next;
      }
    }
    row++;
  }

  fclose(fp);
  return daftarRiwayat;
}

void baca_biaya(char *path, int *biaya)
{
  FILE *fp = fopen(path, "r");

  if (fp == NULL)
  {
    printf("File daftar biaya gagal dibuka.\n");
    exit(EXIT_FAILURE);
  }

  char buf[BUFLEN];
  int row = 0;

  while (fgets(buf, BUFLEN, fp))
  {
    if (row > 0)
    {
      sscanf(buf, "%*d, %*[^,], %d", &biaya[row - 1]);
    }
    row++;
  }

  fclose(fp);
}