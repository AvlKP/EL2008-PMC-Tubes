#pragma once
#include <gtk/gtk.h>
#include "types.h"

void print_pendapatan_bln_to_buffer(PendapatanBulanan *pendapatan, GtkTextBuffer *buffer);
void print_pendapatan_thn_to_buffer(PendapatanTahunan *pendapatan, GtkTextBuffer *buffer);
