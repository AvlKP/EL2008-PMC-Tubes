// Membaca file data dengan asumsi bentuk data akan selalu sama seperti yang diberikan
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "files.h"

#define BUFLEN 256

char* MONTHS[12] = {"Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"};

Tanggal* bacaTanggal(char *sTanggal)
{
  int hari, bulan, tahun;
  char sBulan[10];

  if (sscanf(sTanggal, "%d %s %d", &hari, sBulan, &tahun) != 3) {
    sscanf(sTanggal, "%d-%s-%d", &hari, sBulan, &tahun);
  }
  
  for (int i = 0; i < 12; i ++) {
    if (!strncmp(MONTHS[i], sBulan, 3)) {
      bulan = i+1;
      break;
    }
  }

 return buatTanggal(hari, bulan, tahun);
}

Pasien* bacaDataPasien(char *path)
{
  FILE* fp = fopen(path, "r");
  if (fp == NULL)
  {
    printf("File data pasien gagal dibuka.\n");
    exit(EXIT_FAILURE);
  }

  char buf[BUFLEN];
  int row = 0;

  Pasien* daftarPasien = NULL;
  Pasien* tempPasien = NULL;
  while (fgets(buf, BUFLEN, fp))
  {
    if (row > 0)
    {
      int ID, umur, BPJS;
      char nama[25], alamat[25], kota[25], tempatLahir[25], tempTanggal[20];
      Tanggal* tanggalLahir;

      sscanf(buf, "%*d, %[^,], %[^,], %[^,], %[^,], %[^,], %d, %d, %*s %d",
             nama, alamat, kota, tempatLahir, tempTanggal, &umur, &BPJS, &ID);

      tanggalLahir = bacaTanggal(tempTanggal);

      if (daftarPasien == NULL) {
        daftarPasien = buatPasien(ID, nama, alamat, kota, tempatLahir, tanggalLahir, umur, BPJS);
        tempPasien = daftarPasien;
      } else {
        tempPasien->next = buatPasien(ID, nama, alamat, kota, tempatLahir, tanggalLahir, umur, BPJS);
        tempPasien = tempPasien->next;
      }
    }
    row++;
  }

  fclose(fp);
  return daftarPasien;
}

Riwayat* bacaRiwayat(char *path) {
  FILE* fp = fopen(path, "r");
  if (fp == NULL)
  {
    printf("File riwayat gagal dibuka.\n");
    exit(EXIT_FAILURE);
  }

  char buf[BUFLEN];
  int row = 0;

  Riwayat* daftarRiwayat = NULL;
  Riwayat* tempRiwayat = NULL;
  while (fgets(buf, BUFLEN, fp))
  {
    if (row > 0)
    {
      int ID, biaya;
      Tanggal* tanggal;
      Tanggal* kontrol;
      Diagnosis diagnosis;
      Tindakan tindakan;

      char tempTanggal[20], tempKontrol[20], tempDiagnosis[20], tempTindakan[20];

      sscanf(buf, "%*d, %[^,], %*s %d, %[^,], %[^,], %[^,], %d",
      tempTanggal, &ID, tempDiagnosis, tempTindakan, tempKontrol, &biaya);
      
      tanggal = bacaTanggal(tempTanggal);
      kontrol = bacaTanggal(tempKontrol);
      diagnosis = str2Diagnosis(tempDiagnosis);
      tindakan = str2Tindakan(tempTindakan);

      if (daftarRiwayat == NULL) {
        daftarRiwayat = buatRiwayat(ID, tanggal, diagnosis, tindakan, kontrol, biaya);
        tempRiwayat = daftarRiwayat;
      } else {
        tempRiwayat->next = buatRiwayat(ID, tanggal, diagnosis, tindakan, kontrol, biaya);
        tempRiwayat = tempRiwayat->next;
      }
    }
    row++;
  }

  fclose(fp);
  return daftarRiwayat;
}

void bacaBiaya(char *path, int* biaya){
  FILE* fp = fopen(path, "r");

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