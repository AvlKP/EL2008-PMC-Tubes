#pragma once
#include <gtk/gtk.h>
#include "types.h"

void print_pasien_to_buffer(Pasien **pasien, GtkTextBuffer *buffer);
void print_riwayat_to_buffer(Riwayat **riwayat, GtkTextBuffer *buffer);
void print_pendapatan_to_buffer(Pendapatan **pendapatan, GtkTextBuffer *buffer);
void print_stat_to_buffer(Stat **stat_thn, GtkTextBuffer *buffer);
void print_kontrol_to_buffer(Pasien *pasien, Riwayat *riwayat, GtkTextBuffer *buffer);
