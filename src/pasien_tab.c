#include "pasien_tab.h"
#include "riwayat_tab.h"
#include "buff_printer.h"

void create_pasien_form(Pasien *old, GtkWidget **win_ref, GtkWidget **btn_submit_ref)
{
  GtkWidget *entry_id, *entry_nama, *entry_alamat, *entry_kota, *entry_templ, *entry_umur, *entry_bpjs;
  GtkWidget *entry_tgll_hari, *entry_tgll_bulan, *entry_tgll_tahun;
  GtkBuilder *builder;

  builder = gtk_builder_new_from_resource("/com/github/AvlKP/KlinikX/pasien_form.ui");
  *win_ref = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
  entry_id = GTK_WIDGET(gtk_builder_get_object(builder, "entry_id"));
  entry_nama = GTK_WIDGET(gtk_builder_get_object(builder, "entry_nama"));
  entry_alamat = GTK_WIDGET(gtk_builder_get_object(builder, "entry_alamat"));
  entry_kota = GTK_WIDGET(gtk_builder_get_object(builder, "entry_kota"));
  entry_templ = GTK_WIDGET(gtk_builder_get_object(builder, "entry_templ"));
  entry_umur = GTK_WIDGET(gtk_builder_get_object(builder, "entry_umur"));
  entry_bpjs = GTK_WIDGET(gtk_builder_get_object(builder, "entry_bpjs"));
  entry_tgll_hari = GTK_WIDGET(gtk_builder_get_object(builder, "entry_tgll_hari"));
  entry_tgll_bulan = GTK_WIDGET(gtk_builder_get_object(builder, "entry_tgll_bulan"));
  entry_tgll_tahun = GTK_WIDGET(gtk_builder_get_object(builder, "entry_tgll_tahun"));
  *btn_submit_ref = GTK_WIDGET(gtk_builder_get_object(builder, "btn_submit"));
  g_object_unref(builder);

  if (old != NULL)
  {
    char temp[LINEMAX];
    gtk_editable_set_text(GTK_EDITABLE(entry_nama), old->nama);
    gtk_editable_set_text(GTK_EDITABLE(entry_alamat), old->alamat);
    gtk_editable_set_text(GTK_EDITABLE(entry_kota), old->kota);
    gtk_editable_set_text(GTK_EDITABLE(entry_templ), old->tempatLahir);
    sprintf(temp, "%d", old->umur);
    gtk_editable_set_text(GTK_EDITABLE(entry_umur), temp);
    sprintf(temp, "%d", old->BPJS);
    gtk_editable_set_text(GTK_EDITABLE(entry_bpjs), temp);
    sprintf(temp, "%d", old->hariLahir);
    gtk_editable_set_text(GTK_EDITABLE(entry_tgll_hari), temp);
    sprintf(temp, "%d", old->bulanLahir);
    gtk_editable_set_text(GTK_EDITABLE(entry_tgll_bulan), temp);
    sprintf(temp, "%d", old->tahunLahir);
    gtk_editable_set_text(GTK_EDITABLE(entry_tgll_tahun), temp);
    sprintf(temp, "%d", old->ID);
    gtk_editable_set_text(GTK_EDITABLE(entry_id), temp);
  }

  PasienForm *form_data = g_malloc(sizeof(PasienForm));
  form_data->entry_id = entry_id;
  form_data->entry_nama = entry_nama;
  form_data->entry_alamat = entry_alamat;
  form_data->entry_kota = entry_kota;
  form_data->entry_templ = entry_templ;
  form_data->entry_tgll_hari = entry_tgll_hari;
  form_data->entry_tgll_bulan = entry_tgll_bulan;
  form_data->entry_tgll_tahun = entry_tgll_tahun;
  form_data->entry_umur = entry_umur;
  form_data->entry_bpjs = entry_bpjs;

  g_object_set_data(G_OBJECT(*(btn_submit_ref)), "form_data", form_data);
}

void create_pasien_entry(GtkWidget **win_ref, GtkWidget **btn_submit_ref)
{
  GtkWidget *entry_id;
  GtkWidget *btn_submit;
  GtkBuilder *builder;

  builder = gtk_builder_new_from_resource("/com/github/AvlKP/KlinikX/pasien_entry.ui");
  *win_ref = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
  entry_id = GTK_WIDGET(gtk_builder_get_object(builder, "entry_id"));
  *btn_submit_ref = GTK_WIDGET(gtk_builder_get_object(builder, "btn_submit"));
  g_object_unref(builder);

  g_object_set_data(G_OBJECT(*btn_submit_ref), "entry_pid", entry_id);
}

void on_add_pasien(GtkButton *button, gpointer user_data)
{
  PasienForm *form_data = g_object_get_data(G_OBJECT(button), "form_data");
  Pasien **pasien_ref = g_object_get_data(G_OBJECT(button), "pasien_ref");
  GtkTextBuffer *tb = GTK_TEXT_BUFFER(g_object_get_data(G_OBJECT(button), "buffer"));

  int id = atoi(gtk_editable_get_text(GTK_EDITABLE(form_data->entry_id)));
  char *nama = gtk_editable_get_text(GTK_EDITABLE(form_data->entry_nama));
  char *alamat = gtk_editable_get_text(GTK_EDITABLE(form_data->entry_alamat));
  char *kota = gtk_editable_get_text(GTK_EDITABLE(form_data->entry_kota));
  char *templ = gtk_editable_get_text(GTK_EDITABLE(form_data->entry_templ));
  int tgll_hari = atoi(gtk_editable_get_text(GTK_EDITABLE(form_data->entry_tgll_hari)));
  int tgll_bulan = atoi(gtk_editable_get_text(GTK_EDITABLE(form_data->entry_tgll_bulan)));
  int tgll_tahun = atoi(gtk_editable_get_text(GTK_EDITABLE(form_data->entry_tgll_tahun)));
  int umur = atoi(gtk_editable_get_text(GTK_EDITABLE(form_data->entry_umur)));
  int bpjs = atoi(gtk_editable_get_text(GTK_EDITABLE(form_data->entry_bpjs)));

  add_pasien(pasien_ref, id, nama, alamat, kota, templ, tgll_hari, tgll_bulan, tgll_tahun, umur, bpjs);
  print_pasien_to_buffer(pasien_ref, tb);

  g_free(form_data);
  gtk_window_close(GTK_WINDOW(user_data));
}

void on_edit_pasien(GtkButton *button, gpointer user_data) {
  PasienForm *form_data = g_object_get_data(G_OBJECT(button), "form_data");
  Pasien **pasien_ref = g_object_get_data(G_OBJECT(button), "pasien_ref");
  Pasien *pasien = g_object_get_data(G_OBJECT(button), "pasien");
  GtkTextBuffer *tb = GTK_TEXT_BUFFER(g_object_get_data(G_OBJECT(button), "buffer"));

  int id = atoi(gtk_editable_get_text(GTK_EDITABLE(form_data->entry_id)));
  char *nama = gtk_editable_get_text(GTK_EDITABLE(form_data->entry_nama));
  char *alamat = gtk_editable_get_text(GTK_EDITABLE(form_data->entry_alamat));
  char *kota = gtk_editable_get_text(GTK_EDITABLE(form_data->entry_kota));
  char *templ = gtk_editable_get_text(GTK_EDITABLE(form_data->entry_templ));
  int tgll_hari = atoi(gtk_editable_get_text(GTK_EDITABLE(form_data->entry_tgll_hari)));
  int tgll_bulan = atoi(gtk_editable_get_text(GTK_EDITABLE(form_data->entry_tgll_bulan)));
  int tgll_tahun = atoi(gtk_editable_get_text(GTK_EDITABLE(form_data->entry_tgll_tahun)));
  int umur = atoi(gtk_editable_get_text(GTK_EDITABLE(form_data->entry_umur)));
  int bpjs = atoi(gtk_editable_get_text(GTK_EDITABLE(form_data->entry_bpjs)));

  edit_pasien(pasien, id, nama, alamat, kota, templ, tgll_hari, tgll_bulan, tgll_tahun, umur, bpjs);
  print_pasien_to_buffer(pasien_ref, tb);
  g_free(form_data);
  gtk_window_close(GTK_WINDOW(user_data));
}

void on_edit_pasien_entry(GtkButton *button, gpointer user_data) {
  GtkWidget *main_win = g_object_get_data(G_OBJECT(button), "main_window");
  GtkWidget *entry_pid = g_object_get_data(G_OBJECT(button), "entry_pid");
  Pasien **pasien_ref = g_object_get_data(G_OBJECT(button), "pasien_ref");
  GtkTextBuffer *tb = GTK_TEXT_BUFFER(g_object_get_data(G_OBJECT(button), "buffer"));
  int id = atoi(gtk_editable_get_text(GTK_EDITABLE(entry_pid)));

  gtk_window_close(GTK_WINDOW(user_data));

  Pasien *pasien = search_pasien_by_id(*pasien_ref, id);
  if (pasien == NULL) return;

  GtkWidget *win;
  GtkWidget *btn_submit;

  create_pasien_form(pasien, &win, &btn_submit);

  gtk_window_set_transient_for(GTK_WINDOW(win), GTK_WINDOW(main_win));
  gtk_window_set_title(GTK_WINDOW(win), "Ubah Pasien");
  g_signal_connect(btn_submit, "clicked", G_CALLBACK(on_edit_pasien), (gpointer)win);
  
  g_object_set_data(G_OBJECT(btn_submit), "pasien_ref", pasien_ref);
  g_object_set_data(G_OBJECT(btn_submit), "buffer", tb);
  g_object_set_data(G_OBJECT(btn_submit), "pasien", pasien);

  gtk_window_present(GTK_WINDOW(win));
}

void on_delete_pasien(GtkButton *button, gpointer user_data)
{
  GtkWidget *entry_pid = g_object_get_data(G_OBJECT(button), "entry_pid");
  Pasien **pasien_ref = g_object_get_data(G_OBJECT(button), "pasien_ref");
  GtkTextBuffer *tb = GTK_TEXT_BUFFER(g_object_get_data(G_OBJECT(button), "buffer"));
  int id = atoi(gtk_editable_get_text(GTK_EDITABLE(entry_pid)));

  delete_pasien(pasien_ref, id);
  print_pasien_to_buffer(pasien_ref, tb);
  gtk_window_close(GTK_WINDOW(user_data));
}

void on_search_pasien_riwayat(GtkButton *button, gpointer user_data) {
  Riwayat **riwayat_ref = g_object_get_data(G_OBJECT(button), "riwayat_ref");
  Pasien *pasien = g_object_get_data(G_OBJECT(button), "pasien");
  
  GtkWidget *parent_win = GTK_WIDGET(user_data);
  GtkWidget *win;
  GtkWidget *tv;
  GtkTextBuffer *tb;
  GtkBuilder *builder;
  
  builder = gtk_builder_new_from_resource("/com/github/AvlKP/KlinikX/pasien_search.ui");
  win = GTK_WIDGET(gtk_builder_get_object(builder, "win_riwayat"));
  tv = GTK_WIDGET(gtk_builder_get_object(builder, "tv_riwayat"));
  g_object_unref(builder);

  tb = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tv));

  Riwayat *riwayat = search_riwayat_by_id(*riwayat_ref, pasien->ID);
  print_riwayat_to_buffer(&riwayat, tb);

  gtk_window_set_transient_for(GTK_WINDOW(win), GTK_WINDOW(parent_win));
  
  gtk_window_present(GTK_WINDOW(win));
}

void on_search_pasien_entry(GtkButton *button, gpointer user_data) {
  GtkWidget *main_win = g_object_get_data(G_OBJECT(button), "main_window");
  GtkWidget *entry_pid = g_object_get_data(G_OBJECT(button), "entry_pid");
  Pasien **pasien_ref = g_object_get_data(G_OBJECT(button), "pasien_ref");
  Riwayat **riwayat_ref = g_object_get_data(G_OBJECT(button), "riwayat_ref");
  int id = atoi(gtk_editable_get_text(GTK_EDITABLE(entry_pid)));

  gtk_window_close(GTK_WINDOW(user_data));

  Pasien *pasien = search_pasien_by_id(*pasien_ref, id);
  if (pasien == NULL) return;

  GtkWidget *win;
  GtkWidget *label_id, *label_nama, *label_alamat, *label_kota, *label_templ, *label_tgll, *label_umur, *label_bpjs;
  GtkWidget *btn_info;
  GtkBuilder *builder;

  builder = gtk_builder_new_from_resource("/com/github/AvlKP/KlinikX/pasien_search.ui");
  win = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
  label_id = GTK_WIDGET(gtk_builder_get_object(builder, "label_id"));
  label_nama = GTK_WIDGET(gtk_builder_get_object(builder, "label_nama"));
  label_alamat = GTK_WIDGET(gtk_builder_get_object(builder, "label_alamat"));
  label_kota = GTK_WIDGET(gtk_builder_get_object(builder, "label_kota"));
  label_templ = GTK_WIDGET(gtk_builder_get_object(builder, "label_templ"));
  label_tgll = GTK_WIDGET(gtk_builder_get_object(builder, "label_tgll"));
  label_umur = GTK_WIDGET(gtk_builder_get_object(builder, "label_umur"));
  label_bpjs = GTK_WIDGET(gtk_builder_get_object(builder, "label_bpjs"));
  btn_info = GTK_WIDGET(gtk_builder_get_object(builder, "btn_info"));
  g_object_unref(builder);

  char temp[LINEMAX];
  gtk_label_set_text(GTK_LABEL(label_nama), pasien->nama);
  gtk_label_set_text(GTK_LABEL(label_alamat), pasien->alamat);
  gtk_label_set_text(GTK_LABEL(label_kota), pasien->kota);
  gtk_label_set_text(GTK_LABEL(label_templ), pasien->tempatLahir);
  sprintf(temp, "%d", pasien->umur);
  gtk_label_set_text(GTK_LABEL(label_umur), temp);
  sprintf(temp, "%d", pasien->BPJS);
  gtk_label_set_text(GTK_LABEL(label_bpjs), temp);
  cetak_tanggal(temp, pasien->hariLahir, pasien->bulanLahir, pasien->tahunLahir);
  gtk_label_set_text(GTK_LABEL(label_tgll), temp);
  sprintf(temp, "%d", pasien->ID);
  gtk_label_set_text(GTK_LABEL(label_id), temp);

  gtk_window_set_transient_for(GTK_WINDOW(win), GTK_WINDOW(main_win));
  g_signal_connect(btn_info, "clicked", G_CALLBACK(on_search_pasien_riwayat), (gpointer)win);
  
  g_object_set_data(G_OBJECT(btn_info), "pasien", pasien);
  g_object_set_data(G_OBJECT(btn_info), "riwayat_ref", riwayat_ref);
  gtk_window_present(GTK_WINDOW(win));
}

void open_add_pasien(GtkButton *button, gpointer user_data)
{
  GtkWidget *main_win = g_object_get_data(G_OBJECT(button), "main_window");
  Pasien **pasien_ref = g_object_get_data(G_OBJECT(button), "pasien_ref");
  GtkTextBuffer *tb = g_object_get_data(G_OBJECT(button), "buffer");
  GtkWidget *win;
  GtkWidget *btn_submit;

  create_pasien_form(NULL, &win, &btn_submit);

  gtk_window_set_transient_for(GTK_WINDOW(win), GTK_WINDOW(main_win));
  gtk_window_set_title(GTK_WINDOW(win), "Tambah Pasien");
  g_signal_connect(btn_submit, "clicked", G_CALLBACK(on_add_pasien), (gpointer)win);

  g_object_set_data(G_OBJECT(btn_submit), "pasien_ref", pasien_ref);
  g_object_set_data(G_OBJECT(btn_submit), "buffer", tb);

  gtk_window_present(GTK_WINDOW(win));
}

void open_edit_pasien(GtkButton *button, gpointer user_data)
{
  GtkWidget *main_win = g_object_get_data(G_OBJECT(button), "main_window");
  Pasien **pasien_ref = g_object_get_data(G_OBJECT(button), "pasien_ref");
  GtkTextBuffer *tb = g_object_get_data(G_OBJECT(button), "buffer");

  GtkWidget *win;
  GtkWidget *btn_submit;
  create_pasien_entry(&win, &btn_submit);

  gtk_window_set_transient_for(GTK_WINDOW(win), GTK_WINDOW(main_win));
  gtk_window_set_title(GTK_WINDOW(win), "Ubah Pasien");
  g_signal_connect(btn_submit, "clicked", G_CALLBACK(on_edit_pasien_entry), (gpointer)win);

  g_object_set_data(G_OBJECT(btn_submit), "main_window", main_win);
  g_object_set_data(G_OBJECT(btn_submit), "pasien_ref", pasien_ref);
  g_object_set_data(G_OBJECT(btn_submit), "buffer", tb);

  gtk_window_present(GTK_WINDOW(win));
}

void open_delete_pasien(GtkButton *button, gpointer user_data)
{
  GtkWidget *main_win = g_object_get_data(G_OBJECT(button), "main_window");
  Pasien **pasien_ref = g_object_get_data(G_OBJECT(button), "pasien_ref");
  GtkTextBuffer *tb = g_object_get_data(G_OBJECT(button), "buffer");

  GtkWidget *win;
  GtkWidget *btn_submit;
  create_pasien_entry(&win, &btn_submit);

  gtk_window_set_transient_for(GTK_WINDOW(win), GTK_WINDOW(main_win));
  gtk_window_set_title(GTK_WINDOW(win), "Hapus Pasien");
  g_signal_connect(btn_submit, "clicked", G_CALLBACK(on_delete_pasien), (gpointer)win);

  g_object_set_data(G_OBJECT(btn_submit), "pasien_ref", pasien_ref);
  g_object_set_data(G_OBJECT(btn_submit), "buffer", tb);

  gtk_window_present(GTK_WINDOW(win));
}

void open_search_pasien(GtkButton *button, gpointer user_data)
{
  GtkWidget *main_win = g_object_get_data(G_OBJECT(button), "main_window");
  Pasien **pasien_ref = g_object_get_data(G_OBJECT(button), "pasien_ref");
  Riwayat **riwayat_ref = g_object_get_data(G_OBJECT(button), "riwayat_ref");

  GtkWidget *win;
  GtkWidget *btn_submit;
  create_pasien_entry(&win, &btn_submit);

  gtk_window_set_transient_for(GTK_WINDOW(win), GTK_WINDOW(main_win));
  gtk_window_set_title(GTK_WINDOW(win), "Cari Pasien");
  g_signal_connect(btn_submit, "clicked", G_CALLBACK(on_search_pasien_entry), (gpointer)win);

  g_object_set_data(G_OBJECT(btn_submit), "pasien_ref", pasien_ref);
  g_object_set_data(G_OBJECT(btn_submit), "riwayat_ref", riwayat_ref);

  gtk_window_present(GTK_WINDOW(win));
}