#include <gtk/gtk.h>
#include "gui.h"
#include "types.h"
#include "pasien_tab.h"
#include "riwayat_tab.h"

void activate(GtkApplication *app, gpointer user_data)
{
  Pasien **pasien_ref = g_object_get_data(G_OBJECT(app), "pasien_ref");
  Riwayat **riwayat_ref = g_object_get_data(G_OBJECT(app), "riwayat_ref");

  GtkWidget *win, *pasien_add_win;
  GtkWidget *nb;
  GtkBuilder *builder;

  builder = gtk_builder_new_from_resource("/com/github/AvlKP/KlinikX/klinikx.ui");
  win = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
  gtk_window_set_application(GTK_WINDOW(win), GTK_APPLICATION(app));
  nb = GTK_WIDGET(gtk_builder_get_object(builder, "notebook"));

  // Pasien Tab

  GtkWidget *tv_pasien;
  GtkWidget *btn_pasien[4];
  GtkTextBuffer *tb_pasien;

  tv_pasien = GTK_WIDGET(gtk_builder_get_object(builder, "tv_pasien"));
  tb_pasien = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tv_pasien));
  btn_pasien[0] = GTK_WIDGET(gtk_builder_get_object(builder, "btn_buat_pasien"));
  btn_pasien[1] = GTK_WIDGET(gtk_builder_get_object(builder, "btn_ubah_pasien"));
  btn_pasien[2] = GTK_WIDGET(gtk_builder_get_object(builder, "btn_hapus_pasien"));
  btn_pasien[3] = GTK_WIDGET(gtk_builder_get_object(builder, "btn_cari_pasien"));
  print_pasien_to_buffer(*pasien_ref, tb_pasien);

  for (int i = 0; i < 4; i++) {
    g_object_set_data(G_OBJECT(btn_pasien[i]), "pasien_ref", pasien_ref);
    g_object_set_data(G_OBJECT(btn_pasien[i]), "buffer", tb_pasien);
    g_object_set_data(G_OBJECT(btn_pasien[i]), "main_window", win);
  }
  g_object_set_data(G_OBJECT(btn_pasien[3]), "riwayat_ref", riwayat_ref);
  
  g_signal_connect(btn_pasien[0], "clicked", G_CALLBACK(open_add_pasien), NULL);
  g_signal_connect(btn_pasien[1], "clicked", G_CALLBACK(open_edit_pasien), NULL);
  g_signal_connect(btn_pasien[2], "clicked", G_CALLBACK(open_delete_pasien), NULL);
  g_signal_connect(btn_pasien[3], "clicked", G_CALLBACK(open_search_pasien), NULL);

  // Riwayat Tab

  GtkWidget *tv_riwayat;
  GtkWidget *btn_riwayat[4];
  GtkTextBuffer *tb_riwayat;

  tv_riwayat = GTK_WIDGET(gtk_builder_get_object(builder, "tv_riwayat"));
  tb_riwayat = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tv_riwayat));
  btn_riwayat[0] = GTK_WIDGET(gtk_builder_get_object(builder, "btn_buat_riwayat"));
  btn_riwayat[1] = GTK_WIDGET(gtk_builder_get_object(builder, "btn_ubah_riwayat"));
  btn_riwayat[2] = GTK_WIDGET(gtk_builder_get_object(builder, "btn_hapus_riwayat"));
  btn_riwayat[3] = GTK_WIDGET(gtk_builder_get_object(builder, "btn_cari_riwayat"));
  print_riwayat_to_buffer(*riwayat_ref, tb_riwayat);
  
  for (int i = 0; i < 4; i++) {
    g_object_set_data(G_OBJECT(btn_riwayat[i]), "riwayat_ref", riwayat_ref);
    g_object_set_data(G_OBJECT(btn_riwayat[i]), "buffer", tb_riwayat);
    g_object_set_data(G_OBJECT(btn_riwayat[i]), "main_window", win);
  }
  
  g_signal_connect(btn_riwayat[0], "clicked", G_CALLBACK(open_add_riwayat), NULL);
  g_signal_connect(btn_riwayat[1], "clicked", G_CALLBACK(open_edit_riwayat), NULL);
  g_signal_connect(btn_riwayat[2], "clicked", G_CALLBACK(open_delete_riwayat), NULL);
  g_signal_connect(btn_riwayat[3], "clicked", G_CALLBACK(open_search_riwayat), NULL);

  g_object_unref(builder);
  gtk_window_present(GTK_WINDOW(win));
}