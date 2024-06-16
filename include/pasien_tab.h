#pragma once
#include <gtk/gtk.h>
#include "types.h"

typedef struct {
  GtkWidget *entry_id;
  GtkWidget *entry_nama;
  GtkWidget *entry_alamat;
  GtkWidget *entry_kota;
  GtkWidget *entry_templ;
  GtkWidget *entry_tgll_hari;
  GtkWidget *entry_tgll_bulan;
  GtkWidget *entry_tgll_tahun;
  GtkWidget *entry_umur;
  GtkWidget *entry_bpjs;
} PasienForm;

void print_pasien_to_buffer(Pasien *pasien, GtkTextBuffer *buffer);
void open_add_pasien(GtkButton *button, gpointer user_data);
void open_edit_pasien(GtkButton *button, gpointer user_data);
void open_delete_pasien(GtkButton *button, gpointer user_data);
void open_search_pasien(GtkButton *button, gpointer user_data);