#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "types.h"

Tindakan str_ke_tindakan(char *str)
{
  if (!strcmp(str, "Pendaftaran"))
  {
    return Pendaftaran;
  }
  else if (!strcmp(str, "Pemeriksaan"))
  {
    return Pemeriksaan;
  }
  else if (!strcmp(str, "Vaksinasi"))
  {
    return Vaksinasi;
  }
  else if (!strcmp(str, "Pemasangan infus"))
  {
    return PasangInfus;
  }
  else if (!strcmp(str, "Pengobatan"))
  {
    return Pengobatan;
  }
  else
  {
    return CekGulaDarah;
  }
}

Diagnosis str_ke_diagnosis(char *str)
{
  if (!strcmp(str, "Dehidrasi"))
  {
    return Dehidrasi;
  }
  else if (!strcmp(str, "Keseleo"))
  {
    return Keseleo;
  }
  else if (!strcmp(str, "Pusing"))
  {
    return Pusing;
  }
  else
  {
    return MasukAngin;
  }
}

void diagnosis_ke_str(char *str, Diagnosis diagnosis)
{
  switch (diagnosis)
  {
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

void tindakan_ke_str(char *str, Tindakan tindakan)
{
  switch (tindakan)
  {
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
    strcpy(str, "Cek gula darah");
    break;
  case PasangInfus:
    strcpy(str, "Pemasangan infus");
    break;
  case Pengobatan:
    strcpy(str, "Pengobatan");
    break;
  }
}

Tanggal *buat_tanggal(int hari, int bulan, int tahun)
{
  Tanggal *tanggal = malloc(sizeof(Tanggal));
  tanggal->hari = hari;
  tanggal->bulan = bulan;
  tanggal->tahun = tahun;

  return tanggal;
}

Pasien *buat_pasien(int ID, char *nama, char *alamat, char *kota, char *tempatLahir, Tanggal *tanggalLahir, int umur, int BPJS)
{
  Pasien *pasien = malloc(sizeof(Pasien));
  pasien->next = NULL;
  pasien->ID = ID;
  pasien->umur = umur;
  pasien->BPJS = BPJS;
  pasien->tanggalLahir = tanggalLahir;
  strncpy(pasien->nama, nama, sizeof(pasien->nama) - 1);
  strncpy(pasien->alamat, alamat, sizeof(pasien->alamat) - 1);
  strncpy(pasien->kota, kota, sizeof(pasien->kota) - 1);
  strncpy(pasien->tempatLahir, tempatLahir, sizeof(pasien->tempatLahir) - 1);

  return pasien;
}

Riwayat *buat_riwayat(int ID, Tanggal *tanggal, Diagnosis diagnosis, Tindakan tindakan, Tanggal *kontrol, int biaya)
{
  Riwayat *riwayat = malloc(sizeof(Riwayat));
  riwayat->next = NULL;
  riwayat->ID = ID;
  riwayat->tanggal = tanggal;
  riwayat->diagnosis = diagnosis;
  riwayat->tindakan = tindakan;
  riwayat->kontrol = kontrol;
  riwayat->biaya = biaya;

  return riwayat;
}

void cetak_tanggal(char *str, Tanggal *tanggal)
{
  sprintf(str, "%d %s %d", tanggal->hari, MONTHS[tanggal->bulan - 1], tanggal->tahun);
}

void cetak_pasien(Pasien *pasien)
{
  int i = 1;
  char tanggalLahir[20];

  Pasien *curr = pasien;
  while (curr != NULL)
  {
    cetak_tanggal(tanggalLahir, curr->tanggalLahir);
    printf("%d. %s | %s | %s | %s | %s | %d | %d | %d\n",
           i, curr->nama, curr->alamat, curr->kota, curr->tempatLahir, tanggalLahir, curr->umur, curr->BPJS, curr->ID);
    i++;
    curr = curr->next;
  }
}

void cetak_riwayat(Riwayat *riwayat)
{
  int i = 1;
  char tanggal[20], kontrol[20];
  char diagnosis[20];
  char tindakan[20];

  Riwayat *curr = riwayat;
  while (curr != NULL)
  {
    diagnosis_ke_str(diagnosis, curr->diagnosis);
    tindakan_ke_str(tindakan, curr->tindakan);
    cetak_tanggal(tanggal, curr->tanggal);
    cetak_tanggal(kontrol, curr->kontrol);
    printf("%d. %s | %d | %s | %s | %s | %d\n", i, tanggal, curr->ID, diagnosis, tindakan, kontrol, curr->biaya);
    i++;
    curr = curr->next;
  }
}

void hapus_pasien(Pasien *pasien)
{
  Pasien *temp;

  while (pasien != NULL)
  {
    temp = pasien;
    pasien = pasien->next;
    free(temp->tanggalLahir);
    free(temp);
  }
}

void hapus_riwayat(Riwayat *riwayat)
{
  Riwayat *temp;

  while (riwayat != NULL)
  {
    temp = riwayat;
    riwayat = riwayat->next;
    free(temp->tanggal);
    free(temp->kontrol);
    free(temp);
  }
}

// NO 1

void add_pasien(Pasien **head, int id, char *nama, char *alamat, char *kota, char *tempatLahir, Tanggal *tanggalLahir, int umur, int BPJS)
{
  Pasien *new_pasien = buat_pasien(id, nama, alamat, kota, tempatLahir, tanggalLahir, umur, BPJS);
  new_pasien->next = *head;
  *head = new_pasien;
}

void edit_pasien(Pasien *head, int id, char *nama, char *alamat, char *kota, char *tempatLahir, Tanggal *tanggalLahir, int umur, int BPJS)
{
  free(head->tanggalLahir);
  strncpy(head->nama, nama, sizeof(head->nama) - 1);
  strncpy(head->alamat, alamat, sizeof(head->alamat) - 1);
  strncpy(head->kota, kota, sizeof(head->kota) - 1);
  strncpy(head->tempatLahir, tempatLahir, sizeof(head->tempatLahir) - 1);
  head->ID = id;
  head->tanggalLahir = tanggalLahir;
  head->umur = umur;
  head->BPJS = BPJS;
}

void delete_pasien(Pasien **head, int id)
{
  Pasien *current = *head;
  Pasien *previous = NULL;

  while (current != NULL && current->ID != id)
  {
    previous = current;
    current = current->next;
  }

  if (current == NULL)
    return;

  if (previous == NULL)
  {
    *head = current->next;
  }
  else
  {
    previous->next = current->next;
  }

  free(current->tanggalLahir);
  free(current);
}

Pasien *search_pasien_by_id(Pasien *head, int id)
{
  Pasien *current = head;
  while (current != NULL)
  {
    if (current->ID == id)
    {
      return current;
    }
    current = current->next;
  }
  return NULL;
}

void add_riwayat(Riwayat **head, int id, Tanggal *tanggal, Diagnosis diagnosis, Tindakan tindakan, Tanggal *kontrol, int biaya)
{
  Riwayat *new_riwayat = buat_riwayat(id, tanggal, diagnosis, tindakan, kontrol, biaya);
  new_riwayat->next = *head;
  *head = new_riwayat;
}

Riwayat *search_riwayat_by_id_and_tanggal(Riwayat *head, int id, Tanggal *tanggal)
{
  Riwayat *current = head;
  while (current != NULL)
  {
    if (current->ID == id &&
        current->tanggal->hari == tanggal->hari &&
        current->tanggal->bulan == tanggal->bulan &&
        current->tanggal->tahun == tanggal->tahun)
    {
      return current;
    }
    current = current->next;
  }
  return NULL;
}

Riwayat *search_riwayat_by_id(Riwayat *head, int id)
{
  Riwayat *result_head = NULL;
  Riwayat *result_tail = NULL;
  Riwayat *current = head;

  while (current != NULL)
  {
    if (current->ID == id)
    {
      Riwayat *new_result = malloc(sizeof(Riwayat));
      *new_result = *current;
      new_result->next = NULL;

      if (result_head == NULL)
      {
        result_head = new_result;
        result_tail = new_result;
      }
      else
      {
        result_tail->next = new_result;
        result_tail = new_result;
      }
    }
    current = current->next;
  }
  return result_head;
}

void edit_riwayat(Riwayat *head, int id, Tanggal *tanggal, Diagnosis diagnosis, Tindakan tindakan, Tanggal *kontrol, int biaya)
{
  free(head->tanggal);
  free(head->kontrol);
  head->ID = id;
  head->tanggal = tanggal;
  head->diagnosis = diagnosis;
  head->tindakan = tindakan;
  head->kontrol = kontrol;
  head->biaya = biaya;
}

void delete_riwayat(Riwayat **head, int id, Tanggal *tanggal)
{
  Riwayat *current = *head;
  Riwayat *previous = NULL;

  while (current != NULL)
  {
    if (current->ID == id &&
        current->tanggal->hari == tanggal->hari &&
        current->tanggal->bulan == tanggal->bulan &&
        current->tanggal->tahun == tanggal->tahun)
    {
      if (previous == NULL)
      {
        *head = current->next;
      }
      else
      {
        previous->next = current->next;
      }
      free(current->tanggal);
      free(current->kontrol);
      free(current);
      return;
    }
    previous = current;
    current = current->next;
  }
}