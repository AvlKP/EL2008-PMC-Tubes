#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "types.h"

Tindakan str2Tindakan(char* str) {
  if (!strcmp(str, "Dehidrasi")) {
    return Dehidrasi;
  } else if (!strcmp(str, "Keseleo")) {
    return Keseleo;
  } else if (!strcmp(str, "Pusing")) {
    return Pusing;
  } else {
    return MasukAngin;
  }
}

Diagnosis str2Diagnosis(char* str) {
  if (!strcmp(str, "Pendaftaran")) {
    return Pendaftaran;
  } else if (!strcmp(str, "Pemeriksaan")) {
    return Pemeriksaan;
  } else if (!strcmp(str, "Vaksinasi")) {
    return Vaksinasi;
  } else if (!strcmp(str, "Pasang Infus")) {
    return PasangInfus;
  } else if (!strcmp(str, "Pengobatan")) {
    return Pengobatan;
  } else {
    return CekGulaDarah;
  }
}

void diagnosis2Str(char* str, Diagnosis diagnosis) {
  switch (diagnosis) {
    case Dehidrasi:
      strcpy(str, "Dehidrasi");
      break;
    case Keseleo:
      strcpy(str, "Keseleo");
      break;
    case MasukAngin:
      strcpy(str, "Masuk Angin");
      break;
    case Pusing:
      strcpy(str, "Pusing");
      break;
  }
}

void tindakan2Str(char* str, Tindakan tindakan) {
  switch (tindakan) {
    case Pendaftaran:
      strcpy(str, "Pendaftaran");
      break;
    case Pemeriksaan:
      strcpy(str, "Pemeriksaan");
      break;
    case Vaksinasi:
      strcpy(str, "Vaksinasi");
      break;
    case CekGulaDarah:
      strcpy(str, "Cek Gula Darah");
      break;
    case PasangInfus:
      strcpy(str, "Pasang Infus");
      break;
    case Pengobatan:
      strcpy(str, "Pengobatan");
      break;
  }
}

Tanggal* buatTanggal(int hari, int bulan, int tahun) {
  Tanggal* tanggal = malloc(sizeof(Tanggal));
  tanggal->hari = hari;
  tanggal->bulan = bulan;
  tanggal->tahun = tahun;

  return tanggal;
}

Pasien* buatPasien(int ID, char* nama, char* alamat, char* kota, char* tempatLahir, Tanggal* tanggalLahir, int umur, int BPJS) {
  Pasien* pasien = malloc(sizeof(Pasien));
  pasien->next = NULL;
  pasien->ID = ID;
  pasien->umur = umur;
  pasien->BPJS = BPJS;
  pasien->tanggalLahir = tanggalLahir;
  strcpy(pasien->nama, nama);
  strcpy(pasien->alamat, alamat);
  strcpy(pasien->kota, kota);
  strcpy(pasien->tempatLahir, tempatLahir);

  return pasien;
}

Riwayat* buatRiwayat(int ID, Tanggal* tanggal, Diagnosis diagnosis, Tindakan tindakan, Tanggal* kontrol, int biaya) {
  Riwayat* riwayat = malloc(sizeof(Riwayat));
  riwayat->next = NULL;
  riwayat->ID = ID;
  riwayat->tanggal = tanggal;
  riwayat->diagnosis = diagnosis;
  riwayat->tindakan = tindakan;
  riwayat->kontrol = kontrol;
  riwayat->biaya = biaya;

  return riwayat;
}

void cetakTanggal(char* str, Tanggal* tanggal) {
  sprintf(str, "%d %s %d", tanggal->hari, MONTHS[tanggal->bulan - 1], tanggal->tahun);
}

void cetakPasien(Pasien* pasien) {
  int i = 1;
  char tanggalLahir[20];
  cetakTanggal(tanggalLahir, pasien->tanggalLahir);

  Pasien* curr = pasien;
  while (curr != NULL) {
    printf("%d. %s | %s | %s | %s | %s | %d | %d | %d\n",
    i, curr->nama, curr->alamat, curr->kota, curr->tempatLahir, tanggalLahir, curr->umur, curr->BPJS, curr->ID);
    i++;
    curr = curr->next;
  }
}

void cetakRiwayat(Riwayat* riwayat) {
  int i = 1;
  char tanggal[20], kontrol[20];
  cetakTanggal(tanggal, riwayat->tanggal);
  cetakTanggal(kontrol, riwayat->kontrol);

  char diagnosis[20];
  diagnosis2Str(diagnosis, riwayat->diagnosis);
  char tindakan[20];
  tindakan2Str(tindakan, riwayat->tindakan);

  Riwayat* curr = riwayat;
  while (curr != NULL) {
    printf("%d. %s | %d | %s | %s | %s | %d\n", i, tanggal, riwayat->ID, diagnosis, tindakan, kontrol, riwayat->biaya);
    i++;
    curr = curr->next;
  }
}

void hapusPasien(Pasien* pasien) {
  Pasien* temp;

  while (pasien != NULL) {
    temp = pasien;
    pasien = pasien->next;
    free(temp->tanggalLahir);
    free(temp);
  }
}

void hapusRiwayat(Riwayat* riwayat) {
  Riwayat* temp;

  while (riwayat != NULL) {
    temp = riwayat;
    riwayat = riwayat->next;
    free(temp->tanggal);
    free(temp->kontrol);
    free(temp);
  }
}