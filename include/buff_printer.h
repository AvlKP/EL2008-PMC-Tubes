#pragma once
#include <gtk/gtk.h>
#include "types.h"

void print_pasien_to_buffer(Pasien **pasien, GtkTextBuffer *buffer);
void print_riwayat_to_buffer(Riwayat **riwayat, GtkTextBuffer *buffer);
void print_pendapatan_bln_to_buffer(PendapatanBulanan **pendapatan, GtkTextBuffer *buffer);
void print_pendapatan_thn_to_buffer(PendapatanTahunan **pendapatan, GtkTextBuffer *buffer);
void print_stat_bln_to_buffer(StatBulanan **stat_thn, GtkTextBuffer *buffer);
void print_stat_thn_to_buffer(StatTahunan **stat_thn, GtkTextBuffer *buffer);
void print_kontrol_to_buffer(Pasien *pasien, Riwayat *riwayat, GtkTextBuffer *buffer);
