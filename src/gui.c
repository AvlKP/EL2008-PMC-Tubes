#include <gtk/gtk.h>
#include "gui.h"
#include "types.h"
#include "pasien_tab.h"

void activate(GtkApplication *app, gpointer user_data)
{
  Pasien **pasien_ref = g_object_get_data(G_OBJECT(app), "pasien_ref");
  Riwayat **riwayat_ref = g_object_get_data(G_OBJECT(app), "riwayat_ref");

  GtkWidget *win, *pasien_add_win;
  GtkWidget *nb;
  GtkWidget *tv_pasien;
  GtkWidget *btn_pasien[4];
  GtkTextBuffer *tb_pasien;
  GtkNotebookPage *nbpage;
  GtkBuilder *builder;

  builder = gtk_builder_new_from_resource("/com/github/AvlKP/KlinikX/klinikx.ui");
  win = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
  gtk_window_set_application(GTK_WINDOW(win), GTK_APPLICATION(app));
  nb = GTK_WIDGET(gtk_builder_get_object(builder, "notebook"));

  tv_pasien = GTK_WIDGET(gtk_builder_get_object(builder, "tv_pasien"));
  tb_pasien = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tv_pasien));
  btn_pasien[0] = GTK_WIDGET(gtk_builder_get_object(builder, "btn_buat_pasien"));
  btn_pasien[1] = GTK_WIDGET(gtk_builder_get_object(builder, "btn_ubah_pasien"));
  btn_pasien[2] = GTK_WIDGET(gtk_builder_get_object(builder, "btn_hapus_pasien"));
  btn_pasien[3] = GTK_WIDGET(gtk_builder_get_object(builder, "btn_cari_pasien"));
  print_pasien_to_buffer(*pasien_ref, tb_pasien);

  g_object_unref(builder);

  for (int i = 0; i < 4; i++) {
    g_object_set_data(G_OBJECT(btn_pasien[i]), "pasien_ref", pasien_ref);
    g_object_set_data(G_OBJECT(btn_pasien[i]), "buffer", tb_pasien);
    g_object_set_data(G_OBJECT(btn_pasien[i]), "main_window", win);
  }
  
  g_signal_connect(btn_pasien[0], "clicked", G_CALLBACK(show_add_win), NULL);
  g_signal_connect(btn_pasien[1], "clicked", G_CALLBACK(show_edit_win), NULL);
  g_signal_connect(btn_pasien[2], "clicked", G_CALLBACK(show_delete_win), NULL);
  g_signal_connect(btn_pasien[3], "clicked", G_CALLBACK(show_search_win), NULL);

  gtk_window_present(GTK_WINDOW(win));
}