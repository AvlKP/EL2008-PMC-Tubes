#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "types.h"

Pasien *buat_pasien(int ID, char *nama, char *alamat, char *kota, char *tempatLahir, int hariLahir, int bulanLahir, int tahunLahir, int umur, int BPJS)
{
  Pasien *pasien = malloc(sizeof(Pasien));
  pasien->next = NULL;
  pasien->ID = ID;
  pasien->umur = umur;
  pasien->BPJS = BPJS;
  pasien->hariLahir = hariLahir;
  pasien->bulanLahir = bulanLahir;
  pasien->tahunLahir = tahunLahir;
  strncpy(pasien->nama, nama, sizeof(pasien->nama) - 1);
  strncpy(pasien->alamat, alamat, sizeof(pasien->alamat) - 1);
  strncpy(pasien->kota, kota, sizeof(pasien->kota) - 1);
  strncpy(pasien->tempatLahir, tempatLahir, sizeof(pasien->tempatLahir) - 1);

  return pasien;
}

Riwayat *buat_riwayat(int ID, int hariPeriksa, int bulanPeriksa, int tahunPeriksa, char *diagnosis, char *tindakan, int hariKontrol, int bulanKontrol, int tahunKontrol, int biaya)
{
  Riwayat *riwayat = malloc(sizeof(Riwayat));
  riwayat->next = NULL;
  riwayat->ID = ID;
  riwayat->hariPeriksa = hariPeriksa;
  riwayat->bulanPeriksa = bulanPeriksa;
  riwayat->tahunPeriksa = tahunPeriksa;
  riwayat->hariKontrol = hariKontrol;
  riwayat->bulanKontrol = bulanKontrol;
  riwayat->tahunKontrol = tahunKontrol;
  riwayat->biaya = biaya;
  strncpy(riwayat->diagnosis, diagnosis, sizeof(riwayat->diagnosis) - 1);
  strncpy(riwayat->tindakan, tindakan, sizeof(riwayat->tindakan) - 1);

  return riwayat;
}

void cetak_tanggal(char *str, int hari, int bulan, int tahun)
{
  sprintf(str, "%d %s %d", hari, MONTHS[bulan - 1], tahun);
}

void cetak_pasien(Pasien *pasien)
{
  int i = 1;
  char tanggalLahir[20];

  Pasien *curr = pasien;
  while (curr != NULL)
  {
    cetak_tanggal(tanggalLahir, curr->hariLahir, curr->bulanLahir, curr->tahunLahir);
    printf("%d. %s | %s | %s | %s | %s | %d | %d | %d\n",
           i, curr->nama, curr->alamat, curr->kota, curr->tempatLahir, tanggalLahir, curr->umur, curr->BPJS, curr->ID);
    i++;
    curr = curr->next;
  }
}

void cetak_riwayat(Riwayat *riwayat)
{
  int i = 1;
  char tanggalPeriksa[20], tanggalKontrol[20];

  Riwayat *curr = riwayat;
  while (curr != NULL)
  {
    cetak_tanggal(tanggalPeriksa, curr->hariPeriksa, curr->bulanPeriksa, curr->tahunPeriksa);
    cetak_tanggal(tanggalKontrol, curr->hariKontrol, curr->bulanKontrol, curr->tahunKontrol);
    printf("%d. %s | %d | %s | %s | %s | %d\n", i, tanggalPeriksa, curr->ID, curr->diagnosis, curr->tindakan, tanggalKontrol, curr->biaya);
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
    free(temp);
  }
}

// NO 1

void add_pasien(Pasien **head, int ID, char *nama, char *alamat, char *kota, char *tempatLahir, int hariLahir, int bulanLahir, int tahunLahir, int umur, int BPJS)
{
  Pasien *new_pasien = buat_pasien(ID, nama, alamat, kota, tempatLahir, hariLahir, bulanLahir, tahunLahir, umur, BPJS);
  new_pasien->next = *head;
  *head = new_pasien;
}

void edit_pasien(Pasien *head, int ID, char *nama, char *alamat, char *kota, char *tempatLahir, int hariLahir, int bulanLahir, int tahunLahir, int umur, int BPJS)
{
  strncpy(head->nama, nama, sizeof(head->nama) - 1);
  strncpy(head->alamat, alamat, sizeof(head->alamat) - 1);
  strncpy(head->kota, kota, sizeof(head->kota) - 1);
  strncpy(head->tempatLahir, tempatLahir, sizeof(head->tempatLahir) - 1);
  head->ID = ID;
  head->hariLahir = hariLahir;
  head->bulanLahir = bulanLahir;
  head->tahunLahir = tahunLahir;
  head->umur = umur;
  head->BPJS = BPJS;
}

void delete_pasien(Pasien **head, int ID)
{
  Pasien *current = *head;
  Pasien *previous = NULL;

  while (current != NULL && current->ID != ID)
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

  free(current);
}

Pasien *search_pasien_by_id(Pasien *head, int ID)
{
  Pasien *current = head;
  while (current != NULL)
  {
    if (current->ID == ID)
    {
      return current;
    }
    current = current->next;
  }
  return NULL;
}

// NO 2

void add_riwayat(Riwayat **head, int ID, int hariPeriksa, int bulanPeriksa, int tahunPeriksa, char *diagnosis, char *tindakan, int hariKontrol, int bulanKontrol, int tahunKontrol, int biaya)
{
  Riwayat *new_riwayat = buat_riwayat(ID, hariPeriksa, bulanPeriksa, tahunPeriksa, diagnosis, tindakan, hariKontrol, bulanKontrol, tahunKontrol, biaya);
  new_riwayat->next = *head;
  *head = new_riwayat;
}

Riwayat *search_riwayat_by_id_and_tanggal(Riwayat *head, int ID, int hariPeriksa, int bulanPeriksa, int tahunPeriksa)
{
  Riwayat *current = head;
  while (current != NULL)
  {
    if (current->ID == ID &&
        current->hariPeriksa == hariPeriksa &&
        current->bulanPeriksa == bulanPeriksa &&
        current->tahunPeriksa == tahunPeriksa)
    {
      return current;
    }
    current = current->next;
  }
  return NULL;
}

Riwayat *search_riwayat_by_id(Riwayat *head, int ID)
{
  Riwayat *result_head = NULL;
  Riwayat *result_tail = NULL;
  Riwayat *current = head;

  while (current != NULL)
  {
    if (current->ID == ID)
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

void edit_riwayat(Riwayat *head, int ID, int hariPeriksa, int bulanPeriksa, int tahunPeriksa, char *diagnosis, char *tindakan, int hariKontrol, int bulanKontrol, int tahunKontrol, int biaya)
{
  head->ID = ID;
  head->hariPeriksa = hariPeriksa;
  head->bulanPeriksa = bulanPeriksa;
  head->tahunPeriksa = tahunPeriksa;
  head->hariKontrol = hariKontrol;
  head->bulanKontrol = bulanKontrol;
  head->tahunKontrol = tahunKontrol;
  head->biaya = biaya;
  strncpy(head->diagnosis, diagnosis, sizeof(head->diagnosis) - 1);
  strncpy(head->tindakan, tindakan, sizeof(head->tindakan) - 1);
}

void delete_riwayat(Riwayat **head, int ID, int hariPeriksa, int bulanPeriksa, int tahunPeriksa)
{
  Riwayat *current = *head;
  Riwayat *previous = NULL;

  while (current != NULL)
  {
    if (current->ID == ID &&
        current->hariPeriksa == hariPeriksa &&
        current->bulanPeriksa == bulanPeriksa &&
        current->tahunPeriksa == tahunPeriksa)
    {
      if (previous == NULL)
      {
        *head = current->next;
      }
      else
      {
        previous->next = current->next;
      }
      free(current);
      return;
    }
    previous = current;
    current = current->next;
  }
}