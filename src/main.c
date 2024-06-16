#include <gtk/gtk.h>
#include "files.h"
#include "types.h"
#include "gui.h"

// void cetakPendBln(PendapatanBulanan *pend) {
//   printf("%-14s | %-15s\n", "Bulan", "Pendapatan");

//   PendapatanBulanan *current = pend;
//   char temp[STRLEN];
//   while (current != NULL)
//   {
//     cetak_tanggal(temp, 0, current->bulan, current->tahun);
//     printf("%-14s | %-15d\n", temp, current->pendapatan);
//     current = current->next;
//   }
// }

// void cetakPendThn(PendapatanTahunan *pend) {
//   printf("%-5s | %-15s\n", "Tahun", "Pendapatan");

//   PendapatanTahunan *current = pend;
//   while (current != NULL)
//   {
//     printf("%-5d | %-15d\n", current->tahun, current->pendapatan);
//     current = current->next;
//   }
// }

void cetakBln(StatBulanan *stat)
{
  printf("%-14s | %-13s | %-128s\n", "Bulan", "Jumlah Pasien", "Penyakit");

  StatBulanan *current = stat;
  char penyakit[LINEMAX], bulan[STRLEN];
  while (current != NULL)
  {
    cetak_stat_penyakit(penyakit, stat->stat_penyakit);
    cetak_tanggal(bulan, 0, current->bulan, current->tahun);
    printf("%-14s | %-13d | %-128s", bulan, current->jumlah_pasien, penyakit);
    current = current->next;
  }
}

int main(int argc, char **argv)
{
  Pasien *pasien = baca_data_pasien("../data/Data Pasien.csv");
  Riwayat *riwayat = baca_riwayat("../data/Riwayat.csv");
  int biaya[6];
  baca_biaya("../data/Biaya.csv", biaya);

  // StatBulanan *stat_bln = NULL;
  // StatTahunan *stat_thn = NULL;

  // generate_stat(&stat_bln, &stat_thn, riwayat);
  // cetakBln(stat_bln);

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