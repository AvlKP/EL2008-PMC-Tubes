#include "buff_printer.h"

void print_pasien_to_buffer(Pasien *pasien, GtkTextBuffer *buffer)
{
  gtk_text_buffer_set_text(buffer, "", -1);

  GtkTextIter iter;
  gtk_text_buffer_get_start_iter(buffer, &iter);

  char line[LINEMAX];
  snprintf(line, sizeof(line), "%-3s | %-10s | %-24s | %-24s | %-20s | %-20s | %-17s | %-4s | %-10s\n",
           "No.", "ID Pasien", "Nama", "Alamat", "Kota", "Tempat Lahir", "Tanggal Lahir", "Umur", "No BPJS");
  gtk_text_buffer_insert(buffer, &iter, line, -1);

  int i = 1;
  char tanggalLahir[STRLEN];
  Pasien *current = pasien;
  while (current != NULL)
  {
    cetak_tanggal(tanggalLahir, current->hariLahir, current->bulanLahir, current->tahunLahir);
    snprintf(line, sizeof(line), "%-3d | KX %7d | %-24s | %-24s | %-20s | %-20s | %-17s | %-4d | %10d\n",
             i, current->ID, current->nama, current->alamat, current->kota, current->tempatLahir, tanggalLahir, current->umur, current->BPJS);
    gtk_text_buffer_insert(buffer, &iter, line, -1);
    i++;
    current = current->next;
  }
}

void print_riwayat_to_buffer(Riwayat *riwayat, GtkTextBuffer *buffer)
{
  gtk_text_buffer_set_text(buffer, "", -1);

  GtkTextIter iter;
  gtk_text_buffer_get_start_iter(buffer, &iter);

  char line[LINEMAX];
  snprintf(line, sizeof(line), "%-3s | %-17s | %-10s | %-16s | %-16s | %-17s | %-8s\n",
           "No.", "Tanggal", "ID", "Diagnosis", "Tindakan", "Kontrol", "Biaya");
  gtk_text_buffer_insert(buffer, &iter, line, -1);

  int i = 1;
  char tanggalPeriksa[STRLEN], tanggalKontrol[STRLEN], diagnosis[STRLEN], tindakan[STRLEN];
  Riwayat *current = riwayat;
  while (current != NULL)
  {
    cetak_tanggal(tanggalPeriksa, current->hariPeriksa, current->bulanPeriksa, current->tahunPeriksa);
    cetak_tanggal(tanggalKontrol, current->hariKontrol, current->bulanKontrol, current->tahunKontrol);
    snprintf(line, sizeof(line), "%-3d | %-17s | KX %-7d | %-16s | %-16s | %-17s | %-8d\n",
             i, tanggalPeriksa, current->ID, current->diagnosis, current->tindakan, tanggalKontrol, current->biaya);
    gtk_text_buffer_insert(buffer, &iter, line, -1);
    i++;
    current = current->next;
  }
}

void print_pendapatan_bln_to_buffer(PendapatanBulanan *pendapatan, GtkTextBuffer *buffer)
{
  gtk_text_buffer_set_text(buffer, "", -1);

  GtkTextIter iter;
  gtk_text_buffer_get_start_iter(buffer, &iter);

  char line[LINEMAX];
  snprintf(line, sizeof(line), "%-14s | %-15s\n", "Bulan", "Pendapatan");
  gtk_text_buffer_insert(buffer, &iter, line, -1);

  PendapatanBulanan *current = pendapatan;
  char temp[STRLEN];
  while (current != NULL)
  {
    cetak_tanggal(temp, 0, current->bulan, current->tahun);
    snprintf(line, sizeof(line), "%-14s | %-15d\n", temp, current->pendapatan);
    gtk_text_buffer_insert(buffer, &iter, line, -1);
    current = current->next;
  }
}

void print_pendapatan_thn_to_buffer(PendapatanTahunan *pendapatan, GtkTextBuffer *buffer)
{
  gtk_text_buffer_set_text(buffer, "", -1);

  GtkTextIter iter;
  gtk_text_buffer_get_start_iter(buffer, &iter);

  char line[LINEMAX];
  snprintf(line, sizeof(line), "%-5s | %-15s\n", "Tahun", "Pendapatan");
  gtk_text_buffer_insert(buffer, &iter, line, -1);

  PendapatanTahunan *current = pendapatan;
  while (current != NULL)
  {
    snprintf(line, sizeof(line), "%-5d | %-15d\n", current->tahun, current->pendapatan);
    gtk_text_buffer_insert(buffer, &iter, line, -1);
    current = current->next;
  }
}

void print_stat_bln_to_buffer(StatBulanan *stat, GtkTextBuffer *buffer)
{
  gtk_text_buffer_set_text(buffer, "", -1);

  GtkTextIter iter;
  gtk_text_buffer_get_start_iter(buffer, &iter);

  char line[LINEMAX];
  snprintf(line, sizeof(line), "%-14s | %-13s | %-128s\n", "Bulan", "Jumlah Pasien", "Penyakit");
  gtk_text_buffer_insert(buffer, &iter, line, -1);

  StatBulanan *current = stat;
  char penyakit[LINEMAX], bulan[STRLEN];
  while (current != NULL)
  {
    cetak_stat_penyakit(penyakit, current->stat_penyakit);
    cetak_tanggal(bulan, 0, current->bulan, current->tahun);
    snprintf(line, sizeof(line), "%-14s | %-13d | %-128s\n", bulan, current->jumlah_pasien, penyakit);
    gtk_text_buffer_insert(buffer, &iter, line, -1);
    current = current->next;
  }
}

void print_stat_thn_to_buffer(StatTahunan *stat, GtkTextBuffer *buffer)
{
  gtk_text_buffer_set_text(buffer, "", -1);

  GtkTextIter iter;
  gtk_text_buffer_get_start_iter(buffer, &iter);

  char line[LINEMAX];
  snprintf(line, sizeof(line), "%-5s | %-13s | %-128s\n", "Tahun", "Jumlah Pasien", "Penyakit");
  gtk_text_buffer_insert(buffer, &iter, line, -1);

  StatTahunan *current = stat;
  char penyakit[LINEMAX];
  while (current != NULL)
  {
    cetak_stat_penyakit(penyakit, current->stat_penyakit);
    snprintf(line, sizeof(line), "%-5d | %-13d | %-128s\n", current->tahun, current->jumlah_pasien, penyakit);
    gtk_text_buffer_insert(buffer, &iter, line, -1);
    current = current->next;
  }
}

void print_kontrol_to_buffer(Pasien *pasien, Riwayat *riwayat, GtkTextBuffer *buffer)
{
  gtk_text_buffer_set_text(buffer, "", -1);

  GtkTextIter iter;
  gtk_text_buffer_get_start_iter(buffer, &iter);

  char line[LINEMAX];
  snprintf(line, sizeof(line), "%-3s | %-10s | %-24s | %-4s | %-16s | %-16s | %-17s\n", "No.", "ID", "Nama", "Umur", "Diagnosis", "Tindakan", "Kontrol");
  gtk_text_buffer_insert(buffer, &iter, line, -1);

  int i = 1;
  char tanggal_kontrol[STRLEN];
  Pasien *current_pasien = pasien;
  Riwayat *current_riwayat = NULL;
  while (current_pasien != NULL)
  {
    current_riwayat = cari_kontrol_akhir(riwayat, current_pasien->ID);
    if (current_riwayat != NULL)
    {
      cetak_tanggal(tanggal_kontrol, current_riwayat->hariKontrol, current_riwayat->bulanKontrol, current_riwayat->tahunKontrol);
      snprintf(line, sizeof(line), "%-3d | %-10d | %-24s | %-4d | %-16s | %-16s | %-17s\n",
               i, current_pasien->ID, current_pasien->nama, current_pasien->umur,
               current_riwayat->diagnosis, current_riwayat->tindakan, tanggal_kontrol);
      gtk_text_buffer_insert(buffer, &iter, line, -1);
      i++;
    }
    current_pasien = current_pasien->next;
  }
}