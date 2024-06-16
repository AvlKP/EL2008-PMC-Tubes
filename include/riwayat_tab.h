#pragma once
#include <gtk/gtk.h>
#include "types.h"

typedef struct {
  GtkWidget *entry_tglp_hari;
  GtkWidget *entry_tglp_bulan;
  GtkWidget *entry_tglp_tahun;
  GtkWidget *entry_id;
  GtkWidget *entry_diagnosis;
  GtkWidget *entry_tindakan;
  GtkWidget *entry_tglk_hari;
  GtkWidget *entry_tglk_bulan;
  GtkWidget *entry_tglk_tahun;
  GtkWidget *entry_biaya;
} RiwayatForm;

void open_add_riwayat(GtkButton *button, gpointer user_data);
void open_edit_riwayat(GtkButton *button, gpointer user_data);
void open_delete_riwayat(GtkButton *button, gpointer user_data);
void open_search_riwayat(GtkButton *button, gpointer user_data);