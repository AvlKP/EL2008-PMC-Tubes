#include <gtk/gtk.h>
#include "files.h"
#include "types.h"
#include "gui.h"

int main(int argc, char **argv)
{
  Pasien *pasien = baca_data_pasien("../data/Data Pasien.csv");
  Riwayat *riwayat = baca_riwayat("../data/Riwayat.csv");
  int biaya[6];
  baca_biaya("../data/Biaya.csv", biaya);

  // Pasien *search_test = search_pasien_by_id(pasien, 1230123);
  // cetak_pasien(search_test);
  // cetak_riwayat(riwayat);

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