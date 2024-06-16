#include <gtk/gtk.h>
#include "files.h"
#include "types.h"
#include "gui.h"

void cetakPendBln(PendapatanBulanan *pend) {
  printf("%-14s | %-15s\n", "Bulan", "Pendapatan");
  
  PendapatanBulanan *curr = pend;
  char temp[STRLEN];
  while (curr != NULL)
  {
    cetak_tanggal(temp, 0, curr->bulan, curr->tahun);
    printf("%-14s | %-15d\n", temp, curr->pendapatan);
    curr = curr->next;
  }
}

void cetakPendThn(PendapatanTahunan *pend) {
  printf("%-5s | %-15s\n", "Tahun", "Pendapatan");
  
  PendapatanTahunan *curr = pend;
  while (curr != NULL)
  {
    printf("%-5d | %-15d\n", curr->tahun, curr->pendapatan);
    curr = curr->next;
  }
}

int main(int argc, char **argv)
{
  Pasien *pasien = baca_data_pasien("../data/Data Pasien.csv");
  Riwayat *riwayat = baca_riwayat("../data/Riwayat.csv");
  int biaya[6];
  baca_biaya("../data/Biaya.csv", biaya);

  // Pasien *search_test = search_pasien_by_id(pasien, 1230123);
  // cetak_pasien(search_test);
  // cetak_riwayat(riwayat);

  // PendapatanBulanan *pend_bln = NULL;
  // PendapatanTahunan *pend_thn = NULL;

  // Riwayat *curr = riwayat;
  // while (curr != NULL) {
  //   tambah_pendapatan_bln(&pend_bln, curr->bulanPeriksa, curr->tahunPeriksa, curr->biaya);
  //   tambah_pendapatan_thn(&pend_thn, curr->tahunPeriksa, curr->biaya);
  //   curr = curr->next;
  // }
  // cetakPendBln(pend_bln);
  // cetakPendThn(pend_thn);

  GtkApplication *app;
  int status;

  app = gtk_application_new("com.github.AvlKP.KlinikX", G_APPLICATION_DEFAULT_FLAGS);
  g_object_set_data(G_OBJECT(app), "pasien_ref", &pasien);
  g_object_set_data(G_OBJECT(app), "riwayat_ref", &riwayat);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
  // return 0;
}