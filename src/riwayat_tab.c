#include "riwayat_tab.h"

#define LINEMAX 256

void print_riwayat_to_buffer(Riwayat *riwayat, GtkTextBuffer *buffer)
{
  gtk_text_buffer_set_text(buffer, "", -1);

  GtkTextIter iter;
  gtk_text_buffer_get_start_iter(buffer, &iter);

  char line[LINEMAX];
  snprintf(line, sizeof(line), "%-3s | %-17s | %-10s | %-11s | %-16s | %-17s | %-8s\n",
           "No.", "Tanggal", "ID", "Diagnosis", "Tindakan", "Kontrol", "Biaya");
  gtk_text_buffer_insert(buffer, &iter, line, -1);

  Riwayat *curr = riwayat;
  int counter = 0;
  while (curr != NULL)
  {
    counter++;
    curr = curr->next;
  }

  int i = 1;
  char tanggalPeriksa[20], tanggalKontrol[20], diagnosis[20], tindakan[20];
  curr = riwayat;
  while (curr != NULL)
  {
    cetak_tanggal(tanggalPeriksa, curr->hariPeriksa, curr->bulanPeriksa, curr->tahunPeriksa);
    cetak_tanggal(tanggalKontrol, curr->hariKontrol, curr->bulanKontrol, curr->tahunKontrol);
    snprintf(line, sizeof(line), "%-3d | %-17s | KX %-7d | %-11s | %-16s | %-17s | %-8d\n",
             i, tanggalPeriksa, curr->ID, curr->diagnosis, curr->tindakan, tanggalKontrol, curr->biaya);
    gtk_text_buffer_insert(buffer, &iter, line, -1);
    i++;
    curr = curr->next;
  }
}

void create_riwayat_form(Riwayat *old, GtkWidget **win_ref, GtkWidget **btn_submit_ref)
{
  GtkWidget *entry_id, *entry_diagnosis, *entry_tindakan, *entry_biaya;
  GtkWidget *entry_tglp_hari, *entry_tglp_bulan, *entry_tglp_tahun;
  GtkWidget *entry_tglk_hari, *entry_tglk_bulan, *entry_tglk_tahun;
  GtkBuilder *builder;

  builder = gtk_builder_new_from_resource("/com/github/AvlKP/KlinikX/riwayat_form.ui");
  *win_ref = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
  entry_id = GTK_WIDGET(gtk_builder_get_object(builder, "entry_id"));
  entry_diagnosis = GTK_WIDGET(gtk_builder_get_object(builder, "entry_diagnosis"));
  entry_tindakan = GTK_WIDGET(gtk_builder_get_object(builder, "entry_tindakan"));
  entry_biaya = GTK_WIDGET(gtk_builder_get_object(builder, "entry_biaya"));
  entry_tglp_hari = GTK_WIDGET(gtk_builder_get_object(builder, "entry_tglp_hari"));
  entry_tglp_bulan = GTK_WIDGET(gtk_builder_get_object(builder, "entry_tglp_bulan"));
  entry_tglp_tahun = GTK_WIDGET(gtk_builder_get_object(builder, "entry_tglp_tahun"));
  entry_tglk_hari = GTK_WIDGET(gtk_builder_get_object(builder, "entry_tglk_hari"));
  entry_tglk_bulan = GTK_WIDGET(gtk_builder_get_object(builder, "entry_tglk_bulan"));
  entry_tglk_tahun = GTK_WIDGET(gtk_builder_get_object(builder, "entry_tglk_tahun"));
  *btn_submit_ref = GTK_WIDGET(gtk_builder_get_object(builder, "btn_submit"));
  g_object_unref(builder);

  if (old != NULL)
  {
    char temp[LINEMAX];
    sprintf(temp, "%d", old->hariPeriksa);
    gtk_editable_set_text(GTK_EDITABLE(entry_tglp_hari), temp);
    sprintf(temp, "%d", old->bulanPeriksa);
    gtk_editable_set_text(GTK_EDITABLE(entry_tglp_bulan), temp);
    sprintf(temp, "%d", old->tahunPeriksa);
    gtk_editable_set_text(GTK_EDITABLE(entry_tglp_tahun), temp);
    sprintf(temp, "%d", old->ID);
    gtk_editable_set_text(GTK_EDITABLE(entry_id), temp);
    sprintf(temp, old->diagnosis);
    gtk_editable_set_text(GTK_EDITABLE(entry_diagnosis), temp);
    sprintf(temp, old->tindakan);
    gtk_editable_set_text(GTK_EDITABLE(entry_tindakan), temp);
    sprintf(temp, "%d", old->hariKontrol);
    gtk_editable_set_text(GTK_EDITABLE(entry_tglk_hari), temp);
    sprintf(temp, "%d", old->bulanKontrol);
    gtk_editable_set_text(GTK_EDITABLE(entry_tglk_bulan), temp);
    sprintf(temp, "%d", old->tahunKontrol);
    gtk_editable_set_text(GTK_EDITABLE(entry_tglk_tahun), temp);
    sprintf(temp, "%d", old->biaya);
    gtk_editable_set_text(GTK_EDITABLE(entry_biaya), temp);
  }

  RiwayatForm *form_data = g_malloc(sizeof(RiwayatForm));
  form_data->entry_tglp_hari = entry_tglp_hari;
  form_data->entry_tglp_bulan = entry_tglp_bulan;
  form_data->entry_tglp_tahun = entry_tglp_tahun;
  form_data->entry_id = entry_id;
  form_data->entry_diagnosis = entry_diagnosis;
  form_data->entry_tindakan = entry_tindakan;
  form_data->entry_tglk_hari = entry_tglk_hari;
  form_data->entry_tglk_bulan = entry_tglk_bulan;
  form_data->entry_tglk_tahun = entry_tglk_tahun;
  form_data->entry_biaya = entry_biaya;

  g_object_set_data(G_OBJECT(*(btn_submit_ref)), "form_data", form_data);
}

void create_riwayat_entry(GtkWidget **win_ref, GtkWidget **btn_submit_ref)
{
  GtkWidget *entry_id;
  GtkWidget *btn_submit;
  GtkWidget *entry_tglp_hari, *entry_tglp_bulan, *entry_tglp_tahun;
  GtkBuilder *builder;

  builder = gtk_builder_new_from_resource("/com/github/AvlKP/KlinikX/riwayat_entry.ui");
  *win_ref = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
  entry_id = GTK_WIDGET(gtk_builder_get_object(builder, "entry_id"));
  entry_tglp_hari = GTK_WIDGET(gtk_builder_get_object(builder, "entry_tglp_hari"));
  entry_tglp_bulan = GTK_WIDGET(gtk_builder_get_object(builder, "entry_tglp_bulan"));
  entry_tglp_tahun = GTK_WIDGET(gtk_builder_get_object(builder, "entry_tglp_tahun"));
  *btn_submit_ref = GTK_WIDGET(gtk_builder_get_object(builder, "btn_submit"));
  g_object_unref(builder);

  g_object_set_data(G_OBJECT(*btn_submit_ref), "entry_pid", entry_id);
  g_object_set_data(G_OBJECT(*btn_submit_ref), "entry_tglp_hari", entry_tglp_hari);
  g_object_set_data(G_OBJECT(*btn_submit_ref), "entry_tglp_bulan", entry_tglp_bulan);
  g_object_set_data(G_OBJECT(*btn_submit_ref), "entry_tglp_tahun", entry_tglp_tahun);
}

void on_add_riwayat(GtkButton *button, gpointer user_data)
{
  RiwayatForm *form_data = g_object_get_data(G_OBJECT(button), "form_data");
  Riwayat **riwayat_ref = g_object_get_data(G_OBJECT(button), "riwayat_ref");
  GtkTextBuffer *tb = GTK_TEXT_BUFFER(g_object_get_data(G_OBJECT(button), "buffer"));

  int tglp_hari = atoi(gtk_editable_get_text(GTK_EDITABLE(form_data->entry_tglp_hari)));
  int tglp_bulan = atoi(gtk_editable_get_text(GTK_EDITABLE(form_data->entry_tglp_bulan)));
  int tglp_tahun = atoi(gtk_editable_get_text(GTK_EDITABLE(form_data->entry_tglp_tahun)));
  int id = atoi(gtk_editable_get_text(GTK_EDITABLE(form_data->entry_id)));
  int tglk_hari = atoi(gtk_editable_get_text(GTK_EDITABLE(form_data->entry_tglk_hari)));
  int tglk_bulan = atoi(gtk_editable_get_text(GTK_EDITABLE(form_data->entry_tglk_bulan)));
  int tglk_tahun = atoi(gtk_editable_get_text(GTK_EDITABLE(form_data->entry_tglk_tahun)));
  int biaya = atoi(gtk_editable_get_text(GTK_EDITABLE(form_data->entry_biaya)));
  char *diagnosis = gtk_editable_get_text(GTK_EDITABLE(form_data->entry_diagnosis));
  char *tindakan = gtk_editable_get_text(GTK_EDITABLE(form_data->entry_tindakan));

  add_riwayat(riwayat_ref, id, tglp_hari, tglp_bulan, tglp_tahun, diagnosis, tindakan, tglk_hari, tglk_bulan, tglk_tahun, biaya);
  print_riwayat_to_buffer(*(riwayat_ref), tb);

  g_free(form_data);
  gtk_window_close(GTK_WINDOW(user_data));
}

void on_edit_riwayat(GtkButton *button, gpointer user_data)
{
  RiwayatForm *form_data = g_object_get_data(G_OBJECT(button), "form_data");
  Riwayat **riwayat_ref = g_object_get_data(G_OBJECT(button), "riwayat_ref");
  Riwayat *riwayat = g_object_get_data(G_OBJECT(button), "riwayat");
  GtkTextBuffer *tb = GTK_TEXT_BUFFER(g_object_get_data(G_OBJECT(button), "buffer"));

  int tglp_hari = atoi(gtk_editable_get_text(GTK_EDITABLE(form_data->entry_tglp_hari)));
  int tglp_bulan = atoi(gtk_editable_get_text(GTK_EDITABLE(form_data->entry_tglp_bulan)));
  int tglp_tahun = atoi(gtk_editable_get_text(GTK_EDITABLE(form_data->entry_tglp_tahun)));
  int id = atoi(gtk_editable_get_text(GTK_EDITABLE(form_data->entry_id)));
  int tglk_hari = atoi(gtk_editable_get_text(GTK_EDITABLE(form_data->entry_tglk_hari)));
  int tglk_bulan = atoi(gtk_editable_get_text(GTK_EDITABLE(form_data->entry_tglk_bulan)));
  int tglk_tahun = atoi(gtk_editable_get_text(GTK_EDITABLE(form_data->entry_tglk_tahun)));
  int biaya = atoi(gtk_editable_get_text(GTK_EDITABLE(form_data->entry_biaya)));
  char *diagnosis = gtk_editable_get_text(GTK_EDITABLE(form_data->entry_diagnosis));
  char *tindakan = gtk_editable_get_text(GTK_EDITABLE(form_data->entry_tindakan));

  edit_riwayat(riwayat, id, tglp_hari, tglp_bulan, tglp_tahun, diagnosis, tindakan, tglk_hari, tglk_bulan, tglk_tahun, biaya);
  print_riwayat_to_buffer(*(riwayat_ref), tb);

  g_free(form_data);
  gtk_window_close(GTK_WINDOW(user_data));
}

void on_edit_riwayat_entry(GtkButton *button, gpointer user_data)
{
  GtkWidget *main_win = g_object_get_data(G_OBJECT(button), "main_window");
  GtkWidget *entry_pid = g_object_get_data(G_OBJECT(button), "entry_pid");
  GtkWidget *entry_tglp_hari = g_object_get_data(G_OBJECT(button), "entry_tglp_hari");
  GtkWidget *entry_tglp_bulan = g_object_get_data(G_OBJECT(button), "entry_tglp_bulan");
  GtkWidget *entry_tglp_tahun = g_object_get_data(G_OBJECT(button), "entry_tglp_tahun");
  Riwayat **riwayat_ref = g_object_get_data(G_OBJECT(button), "riwayat_ref");
  GtkTextBuffer *tb = GTK_TEXT_BUFFER(g_object_get_data(G_OBJECT(button), "buffer"));

  int id = atoi(gtk_editable_get_text(GTK_EDITABLE(entry_pid)));
  int tglp_hari = atoi(gtk_editable_get_text(GTK_EDITABLE(entry_tglp_hari)));
  int tglp_bulan = atoi(gtk_editable_get_text(GTK_EDITABLE(entry_tglp_bulan)));
  int tglp_tahun = atoi(gtk_editable_get_text(GTK_EDITABLE(entry_tglp_tahun)));

  gtk_window_close(GTK_WINDOW(user_data));

  GtkWidget *win;
  GtkWidget *btn_submit;
  Riwayat *riwayat = search_riwayat_by_id_and_tanggal(*riwayat_ref, id, tglp_hari, tglp_bulan, tglp_tahun);

  create_riwayat_form(riwayat, &win, &btn_submit);

  gtk_window_set_transient_for(GTK_WINDOW(win), GTK_WINDOW(main_win));
  gtk_window_set_title(GTK_WINDOW(win), "Ubah Riwayat");
  g_signal_connect(btn_submit, "clicked", G_CALLBACK(on_edit_riwayat), (gpointer)win);

  g_object_set_data(G_OBJECT(btn_submit), "riwayat_ref", riwayat_ref);
  g_object_set_data(G_OBJECT(btn_submit), "buffer", tb);
  g_object_set_data(G_OBJECT(btn_submit), "riwayat", riwayat);

  gtk_window_present(GTK_WINDOW(win));
}

void on_delete_riwayat(GtkButton *button, gpointer user_data)
{
  GtkWidget *entry_pid = g_object_get_data(G_OBJECT(button), "entry_pid");
  GtkWidget *entry_tglp_hari = g_object_get_data(G_OBJECT(button), "entry_tglp_hari");
  GtkWidget *entry_tglp_bulan = g_object_get_data(G_OBJECT(button), "entry_tglp_bulan");
  GtkWidget *entry_tglp_tahun = g_object_get_data(G_OBJECT(button), "entry_tglp_tahun");
  Riwayat **riwayat_ref = g_object_get_data(G_OBJECT(button), "riwayat_ref");
  GtkTextBuffer *tb = GTK_TEXT_BUFFER(g_object_get_data(G_OBJECT(button), "buffer"));

  int id = atoi(gtk_editable_get_text(GTK_EDITABLE(entry_pid)));
  int tglp_hari = atoi(gtk_editable_get_text(GTK_EDITABLE(entry_tglp_hari)));
  int tglp_bulan = atoi(gtk_editable_get_text(GTK_EDITABLE(entry_tglp_bulan)));
  int tglp_tahun = atoi(gtk_editable_get_text(GTK_EDITABLE(entry_tglp_tahun)));

  delete_riwayat(riwayat_ref, id, tglp_hari, tglp_bulan, tglp_tahun);
  print_riwayat_to_buffer(*(riwayat_ref), tb);
  gtk_window_close(GTK_WINDOW(user_data));
}

void on_search_riwayat_entry(GtkButton *button, gpointer user_data) {
  GtkWidget *main_win = g_object_get_data(G_OBJECT(button), "main_window");
  Riwayat **riwayat_ref = g_object_get_data(G_OBJECT(button), "riwayat_ref");
  GtkWidget *entry_pid = g_object_get_data(G_OBJECT(button), "entry_pid");
  GtkWidget *entry_tglp_hari = g_object_get_data(G_OBJECT(button), "entry_tglp_hari");
  GtkWidget *entry_tglp_bulan = g_object_get_data(G_OBJECT(button), "entry_tglp_bulan");
  GtkWidget *entry_tglp_tahun = g_object_get_data(G_OBJECT(button), "entry_tglp_tahun");

  int id = atoi(gtk_editable_get_text(GTK_EDITABLE(entry_pid)));
  int tglp_hari = atoi(gtk_editable_get_text(GTK_EDITABLE(entry_tglp_hari)));
  int tglp_bulan = atoi(gtk_editable_get_text(GTK_EDITABLE(entry_tglp_bulan)));
  int tglp_tahun = atoi(gtk_editable_get_text(GTK_EDITABLE(entry_tglp_tahun)));

  gtk_window_close(GTK_WINDOW(user_data));

  Riwayat *riwayat = search_riwayat_by_id(*riwayat_ref, id);
  GtkWidget *win;
  GtkWidget *label_tglp, *label_id, *label_diagnosis, *label_tindakan, *label_tglk, *label_biaya;
  GtkBuilder *builder;

  builder = gtk_builder_new_from_resource("/com/github/AvlKP/KlinikX/riwayat_search.ui");
  win = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
  label_tglp = GTK_WIDGET(gtk_builder_get_object(builder, "label_tglp"));
  label_id = GTK_WIDGET(gtk_builder_get_object(builder, "label_id"));
  label_diagnosis = GTK_WIDGET(gtk_builder_get_object(builder, "label_diagnosis"));
  label_tindakan = GTK_WIDGET(gtk_builder_get_object(builder, "label_tindakan"));
  label_tglk = GTK_WIDGET(gtk_builder_get_object(builder, "label_tglk"));
  label_biaya = GTK_WIDGET(gtk_builder_get_object(builder, "label_biaya"));
  g_object_unref(builder);

  char temp[LINEMAX];
  cetak_tanggal(temp, riwayat->hariPeriksa, riwayat->bulanPeriksa, riwayat->tahunPeriksa);
  gtk_label_set_text(GTK_LABEL(label_tglp), temp);
  sprintf(temp, "%d", riwayat->ID);
  gtk_label_set_text(GTK_LABEL(label_id), temp);
  gtk_label_set_text(GTK_LABEL(label_diagnosis), riwayat->diagnosis);
  gtk_label_set_text(GTK_LABEL(label_tindakan), riwayat->tindakan);
  cetak_tanggal(temp, riwayat->hariKontrol, riwayat->bulanKontrol, riwayat->tahunKontrol);
  gtk_label_set_text(GTK_LABEL(label_tglk), temp);
  sprintf(temp, "%d", riwayat->biaya);
  gtk_label_set_text(GTK_LABEL(label_biaya), temp);

  gtk_window_set_transient_for(GTK_WINDOW(win), GTK_WINDOW(main_win));
  
  gtk_window_present(GTK_WINDOW(win));
}

void open_add_riwayat(GtkButton *button, gpointer user_data)
{
  GtkWidget *main_win = g_object_get_data(G_OBJECT(button), "main_window");
  Riwayat **riwayat_ref = g_object_get_data(G_OBJECT(button), "riwayat_ref");
  GtkTextBuffer *tb = g_object_get_data(G_OBJECT(button), "buffer");
  GtkWidget *win;
  GtkWidget *btn_submit;

  create_riwayat_form(NULL, &win, &btn_submit);

  gtk_window_set_transient_for(GTK_WINDOW(win), GTK_WINDOW(main_win));
  gtk_window_set_title(GTK_WINDOW(win), "Tambah Riwayat");
  g_signal_connect(btn_submit, "clicked", G_CALLBACK(on_add_riwayat), (gpointer)win);

  g_object_set_data(G_OBJECT(btn_submit), "riwayat_ref", riwayat_ref);
  g_object_set_data(G_OBJECT(btn_submit), "buffer", tb);

  gtk_window_present(GTK_WINDOW(win));
}

void open_edit_riwayat(GtkButton *button, gpointer user_data)
{
  GtkWidget *main_win = g_object_get_data(G_OBJECT(button), "main_window");
  Riwayat **riwayat_ref = g_object_get_data(G_OBJECT(button), "riwayat_ref");
  GtkTextBuffer *tb = g_object_get_data(G_OBJECT(button), "buffer");

  GtkWidget *win;
  GtkWidget *btn_submit;
  create_riwayat_entry(&win, &btn_submit);

  gtk_window_set_transient_for(GTK_WINDOW(win), GTK_WINDOW(main_win));
  gtk_window_set_title(GTK_WINDOW(win), "Ubah Riwayat");
  g_signal_connect(btn_submit, "clicked", G_CALLBACK(on_edit_riwayat_entry), (gpointer)win);

  g_object_set_data(G_OBJECT(btn_submit), "main_window", main_win);
  g_object_set_data(G_OBJECT(btn_submit), "riwayat_ref", riwayat_ref);
  g_object_set_data(G_OBJECT(btn_submit), "buffer", tb);

  gtk_window_present(GTK_WINDOW(win));
}

void open_delete_riwayat(GtkButton *button, gpointer user_data)
{
  GtkWidget *main_win = g_object_get_data(G_OBJECT(button), "main_window");
  Riwayat **riwayat_ref = g_object_get_data(G_OBJECT(button), "riwayat_ref");
  GtkTextBuffer *tb = g_object_get_data(G_OBJECT(button), "buffer");

  GtkWidget *win;
  GtkWidget *btn_submit;
  create_riwayat_entry(&win, &btn_submit);

  gtk_window_set_transient_for(GTK_WINDOW(win), GTK_WINDOW(main_win));
  gtk_window_set_title(GTK_WINDOW(win), "Hapus Riwayat");
  g_signal_connect(btn_submit, "clicked", G_CALLBACK(on_delete_riwayat), (gpointer)win);

  g_object_set_data(G_OBJECT(btn_submit), "riwayat_ref", riwayat_ref);
  g_object_set_data(G_OBJECT(btn_submit), "buffer", tb);

  gtk_window_present(GTK_WINDOW(win));
}

void open_search_riwayat(GtkButton *button, gpointer user_data)
{
  GtkWidget *main_win = g_object_get_data(G_OBJECT(button), "main_window");
  Riwayat **riwayat_ref = g_object_get_data(G_OBJECT(button), "riwayat_ref");

  GtkWidget *win;
  GtkWidget *btn_submit;
  create_riwayat_entry(&win, &btn_submit);

  gtk_window_set_transient_for(GTK_WINDOW(win), GTK_WINDOW(main_win));
  gtk_window_set_title(GTK_WINDOW(win), "Cari Riwayat Pemeriksaan");
  g_signal_connect(btn_submit, "clicked", G_CALLBACK(on_search_riwayat_entry), (gpointer)win);

  g_object_set_data(G_OBJECT(btn_submit), "riwayat_ref", riwayat_ref);

  gtk_window_present(GTK_WINDOW(win));
}