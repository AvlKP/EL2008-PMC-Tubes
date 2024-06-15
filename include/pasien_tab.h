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
void show_add_win(GtkButton *button, gpointer user_data);
void show_edit_win(GtkButton *button, gpointer user_data);
void show_delete_win(GtkButton *button, gpointer user_data);
void show_search_win(GtkButton *button, gpointer user_data);