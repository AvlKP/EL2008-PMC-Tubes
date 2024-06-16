#include "pendapatan_tab.h"

void print_pendapatan_bln_to_buffer(PendapatanBulanan *pendapatan, GtkTextBuffer *buffer)
{
  gtk_text_buffer_set_text(buffer, "", -1);

  GtkTextIter iter;
  gtk_text_buffer_get_start_iter(buffer, &iter);

  char line[LINEMAX];
  snprintf(line, sizeof(line), "%-14s | %-15s\n", "Bulan", "Pendapatan");
  gtk_text_buffer_insert(buffer, &iter, line, -1);

  PendapatanBulanan *curr = pendapatan;
  char temp[STRLEN];
  while (curr != NULL)
  {
    cetak_tanggal(temp, 0, curr->bulan, curr->tahun);
    snprintf(line, sizeof(line), "%-14s | %-15d\n", temp, curr->pendapatan);
    gtk_text_buffer_insert(buffer, &iter, line, -1);
    curr = curr->next;
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

  PendapatanTahunan *curr = pendapatan;
  while (curr != NULL)
  {
    snprintf(line, sizeof(line), "%-5d | %-15d\n", curr->tahun, curr->pendapatan);
    gtk_text_buffer_insert(buffer, &iter, line, -1);
    curr = curr->next;
  }
}
