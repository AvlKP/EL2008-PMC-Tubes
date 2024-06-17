#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "types.h"

// BASE

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
  if (bulan == 0)
  {
    sprintf(str, "%d", tahun);
  }
  else if (hari == 0)
  {
    sprintf(str, "%s %d", MONTHS[bulan - 1], tahun);
  }
  else
  {
    sprintf(str, "%d %s %d", hari, MONTHS[bulan - 1], tahun);
  }
}

void cetak_pasien(Pasien *pasien)
{
  int i = 1;
  char tanggalLahir[20];

  Pasien *current = pasien;
  while (current != NULL)
  {
    cetak_tanggal(tanggalLahir, current->hariLahir, current->bulanLahir, current->tahunLahir);
    printf("%d. %s | %s | %s | %s | %s | %d | %d | %d\n",
           i, current->nama, current->alamat, current->kota, current->tempatLahir, tanggalLahir, current->umur, current->BPJS, current->ID);
    i++;
    current = current->next;
  }
}

void cetak_riwayat(Riwayat *riwayat)
{
  int i = 1;
  char tanggalPeriksa[20], tanggalKontrol[20];

  Riwayat *current = riwayat;
  while (current != NULL)
  {
    cetak_tanggal(tanggalPeriksa, current->hariPeriksa, current->bulanPeriksa, current->tahunPeriksa);
    cetak_tanggal(tanggalKontrol, current->hariKontrol, current->bulanKontrol, current->tahunKontrol);
    printf("%d. %s | %d | %s | %s | %s | %d\n", i, tanggalPeriksa, current->ID, current->diagnosis, current->tindakan, tanggalKontrol, current->biaya);
    i++;
    current = current->next;
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

// NO 3

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

// NO 4

void tambah_pendapatan(Pendapatan **head, Riwayat *riwayat, int tahunan)
{
  Pendapatan *current = *head;
  while (current != NULL)
  {
    if (current->tahun == riwayat->tahunPeriksa && (tahunan == 1 || current->bulan == riwayat->bulanPeriksa))
    {
      current->pendapatan += riwayat->biaya;
      return;
    }
    current = current->next;
  }

  Pendapatan *newNode = malloc(sizeof(Pendapatan));
  if (tahunan == 1)
    newNode->bulan = 0;
  else
    newNode->bulan = riwayat->bulanPeriksa;
  newNode->tahun = riwayat->tahunPeriksa;
  newNode->pendapatan = riwayat->biaya;
  newNode->next = *head;
  *head = newNode;
}

double pendapatan_rata2_thn(Pendapatan *head)
{
  int total_tahun = 0;
  int total_pendapatan = 0;

  Pendapatan *current = head;
  while (current != NULL)
  {
    total_pendapatan += current->pendapatan;
    total_tahun++;
    current = current->next;
  }
  if (total_tahun == 0)
    return 0;
  return (double)(total_pendapatan / total_tahun);
}

void generate_pendapatan(Pendapatan **pend_bln, Pendapatan **pend_thn, Riwayat *riwayat)
{
  Riwayat *current = riwayat;
  while (current != NULL)
  {
    tambah_pendapatan(pend_bln, current, 0);
    tambah_pendapatan(pend_thn, current, 1);
    current = current->next;
  }
}

// NO 5

StatPenyakit *buat_stat_penyakit(char *nama, int jumlah)
{
  StatPenyakit *newNode = malloc(sizeof(StatPenyakit));
  strcpy(newNode->nama, nama);
  newNode->jumlah = jumlah;
  newNode->next = NULL;
  return newNode;
}

void sort_stat_penyakit(StatPenyakit **head)
{
  int swapped;
  StatPenyakit **h;
  StatPenyakit *p1, *p2, *temp;
  StatPenyakit *lptr = NULL;

  if (*head == NULL)
    return;

  do
  {
    swapped = 0;
    h = head;

    while ((*h)->next != lptr)
    {
      p1 = *h;
      p2 = p1->next;

      if (p1->jumlah < p2->jumlah)
      {
        temp = p2->next;
        p2->next = p1;
        p1->next = temp;
        *h = p2;

        swapped = 1;
      }
      h = &(*h)->next;
    }
    lptr = *h;
  } while (swapped);
}

void tambah_stat_penyakit(StatPenyakit **head, char *diagnosis)
{
  StatPenyakit *current = *head;

  while (current != NULL)
  {
    if (strcmp(current->nama, diagnosis) == 0)
    {
      current->jumlah++;
      return;
    }
    current = current->next;
  }

  StatPenyakit *newNode = buat_stat_penyakit(diagnosis, 1);
  newNode->next = *head;
  *head = newNode;
}

void tambah_stat(Stat **head, Riwayat *riwayat, int tahunan)
{
  Stat *current = *head;
  while (current != NULL)
  {
    if (current->tahun == riwayat->tahunPeriksa && (tahunan == 1 || current->bulan == riwayat->bulanPeriksa))
    {
      current->jumlah_pasien++;
      tambah_stat_penyakit(&(current->stat_penyakit), riwayat->diagnosis);
      return;
    }
    current = current->next;
  }

  Stat *newNode = malloc(sizeof(Stat));
  if (tahunan == 1)
    newNode->bulan = 0;
  else
    newNode->bulan = riwayat->bulanPeriksa;
  newNode->tahun = riwayat->tahunPeriksa;
  newNode->jumlah_pasien = 1;
  newNode->stat_penyakit = NULL;
  tambah_stat_penyakit(&(newNode->stat_penyakit), riwayat->diagnosis);
  newNode->next = *head;
  *head = newNode;
}

void generate_stat(Stat **stat_bln, Stat **stat_thn, Riwayat *riwayat)
{
  Riwayat *current = riwayat;
  while (current != NULL)
  {
    tambah_stat(stat_bln, current, 0);
    tambah_stat(stat_thn, current, 1);
    current = current->next;
  }
}

void cetak_stat_penyakit(char *str, StatPenyakit *stat)
{
  char temp[STRLEN];
  str[0] = '\0';

  StatPenyakit *current = stat;
  while (current != NULL)
  {
    snprintf(temp, sizeof(temp), "%s (%d), ", current->nama, current->jumlah);
    strcat(str, temp);
    current = current->next;
  }
  str[strlen(str) - 2] = '\0';
}

// NO 6

int banding_tanggal(int hari1, int bulan1, int tahun1, int hari2, int bulan2, int tahun2)
{
  // return 1 jika tanggal 1 lebih baru
  if (tahun1 > tahun2)
    return 1;
  if (tahun1 < tahun2)
    return 0;
  if (bulan1 > bulan2)
    return 1;
  if (bulan1 < bulan2)
    return 0;
  if (hari1 > hari2)
    return 1;
  return 0;
}

Riwayat *cari_kontrol_akhir(Riwayat *head, int ID)
{
  Riwayat *riwayat = NULL;

  Riwayat *current = head;
  while (current != NULL)
  {
    if (current->ID == ID)
    {
      if (riwayat == NULL ||
          banding_tanggal(current->hariKontrol, current->bulanKontrol, current->tahunKontrol,
                          riwayat->hariKontrol, riwayat->bulanKontrol, riwayat->tahunKontrol))
      {
        riwayat = current;
      }
    }
    current = current->next;
  }

  return riwayat;
}

// Utilities

void sort_pasien_id(Pasien **head)
{
  int swapped;
  Pasien **h;
  Pasien *p1, *p2, *temp;
  Pasien *lptr = NULL;

  if (*head == NULL)
    return;

  do
  {
    swapped = 0;
    h = head;

    while ((*h)->next != lptr)
    {
      p1 = *h;
      p2 = p1->next;

      if (p1->ID > p2->ID)
      {
        temp = p2->next;
        p2->next = p1;
        p1->next = temp;
        *h = p2;

        swapped = 1;
      }
      h = &(*h)->next;
    }
    lptr = *h;
  } while (swapped);
}

void sort_riwayat_tanggal(Riwayat **head)
{
  int swapped;
  Riwayat **h;
  Riwayat *p1, *p2, *temp;
  Riwayat *lptr = NULL;

  if (*head == NULL)
    return;

  do
  {
    swapped = 0;
    h = head;

    while ((*h)->next != lptr)
    {
      p1 = *h;
      p2 = p1->next;

      if (banding_tanggal(p1->hariPeriksa, p1->bulanPeriksa, p1->tahunPeriksa,
                          p2->hariPeriksa, p2->bulanPeriksa, p2->tahunPeriksa))
      {
        temp = p2->next;
        p2->next = p1;
        p1->next = temp;
        *h = p2;

        swapped = 1;
      }
      h = &(*h)->next;
    }
    lptr = *h;
  } while (swapped);
}

void sort_pendapatan(Pendapatan **head)
{
  int swapped;
  Pendapatan **h;
  Pendapatan *p1, *p2, *temp;
  Pendapatan *lptr = NULL;

  if (*head == NULL)
    return;

  do
  {
    swapped = 0;
    h = head;

    while ((*h)->next != lptr)
    {
      p1 = *h;
      p2 = p1->next;

      if (banding_tanggal(0, p1->bulan, p1->tahun,
                          0, p2->bulan, p2->tahun))
      {
        temp = p2->next;
        p2->next = p1;
        p1->next = temp;
        *h = p2;

        swapped = 1;
      }
      h = &(*h)->next;
    }
    lptr = *h;
  } while (swapped);
}

void sort_stat(Stat **head)
{
  int swapped;
  Stat **h;
  Stat *p1, *p2, *temp;
  Stat *lptr = NULL;

  if (*head == NULL)
    return;

  do
  {
    swapped = 0;
    h = head;

    while ((*h)->next != lptr)
    {
      p1 = *h;
      p2 = p1->next;

      if (banding_tanggal(0, p1->bulan, p1->tahun,
                          0, p2->bulan, p2->tahun))
      {
        temp = p2->next;
        p2->next = p1;
        p1->next = temp;
        *h = p2;

        swapped = 1;
      }
      h = &(*h)->next;
    }
    lptr = *h;
  } while (swapped);
}