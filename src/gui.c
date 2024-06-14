#include <gtk/gtk.h>
#include "types.h"
#include "pasienTab.h"
#include "files.h"

void activate(GtkApplication *app, gpointer user_data)
{
  Pasien *pasien = bacaDataPasien("../data/Data Pasien.csv");
  Riwayat *riwayat = bacaRiwayat("../data/Riwayat.csv");
  int biaya[6];
  bacaBiaya("../data/Biaya.csv", biaya);

  // cetakPasien(pasien);
  // cetakRiwayat(riwayat);
  // printf("%d\n", biaya[CekGulaDarah]);

  // GUI

  GtkWidget *window;
  GtkWidget *label;
  GtkWidget *pbox;
  GtkWidget *notebook;
  GtkNotebookPage *nbpage;
  GtkBuilder *builder;

  builder = gtk_builder_new_from_resource("/com/github/AvlKP/KlinikX/klinikx.ui");
  window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
  gtk_window_set_application(GTK_WINDOW(window), GTK_APPLICATION(app));
  notebook = GTK_WIDGET(gtk_builder_get_object(builder, "notebook"));
  g_object_unref(builder);

  pbox = pasien_box_new();
  pasien_box_set_data(PASIEN_BOX(pbox), pasien);
  label = gtk_label_new("Pasien");
  gtk_notebook_append_page(GTK_NOTEBOOK(notebook), pbox, label);
  nbpage = gtk_notebook_get_page(GTK_NOTEBOOK(notebook), pbox);

  gtk_window_present(GTK_WINDOW(window));
}