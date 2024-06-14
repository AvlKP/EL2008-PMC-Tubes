#pragma once
#include <gtk/gtk.h>
#include "types.h"

#define PASIEN_TYPE_BOX pasien_box_get_type()
G_DECLARE_FINAL_TYPE(PasienBox, pasien_box, PASIEN, BOX, GtkBox)

void
pasien_box_set_data(PasienBox *pb, Pasien *pasien);

Pasien *
pasien_box_get_data(PasienBox *pb);

GtkWidget *
pasien_box_new();