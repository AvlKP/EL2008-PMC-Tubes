#include "pasienTab.h"

struct _PasienBox {
  GtkBox parent;
  GtkButton *btn_buat;
  GtkButton *btn_ubah;
  GtkButton *btn_hapus;
  GtkCheckButton *btn_search_by;
  GtkSearchEntry *search;
  GtkColumnView *table;
  Pasien *pasien;
};

G_DEFINE_FINAL_TYPE(PasienBox, pasien_box, GTK_TYPE_BOX)

static void
pasien_box_init(PasienBox *pb) {
  gtk_widget_init_template(GTK_WIDGET(pb));
}

static void
pasien_box_dispose(GObject *gobject) {
  gtk_widget_dispose_template(GTK_WIDGET(gobject), PASIEN_TYPE_BOX);
  G_OBJECT_CLASS(pasien_box_parent_class)->dispose(gobject);
}

static void
pasien_box_class_init(PasienBoxClass *pbc) {
  G_OBJECT_CLASS(pbc)->dispose = pasien_box_dispose;
  gtk_widget_class_set_template_from_resource(GTK_WIDGET_CLASS(pbc), "/com/github/AvlKP/KlinikX/pasien.ui");
  gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(pbc), PasienBox, btn_buat);
  gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(pbc), PasienBox, btn_ubah);
  gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(pbc), PasienBox, btn_hapus);
  gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(pbc), PasienBox, btn_search_by);
  gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(pbc), PasienBox, search);
  gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(pbc), PasienBox, table);
}

static GListStore *
create_list_store(Pasien *head) {
}

void
pasien_box_set_data(PasienBox *pb, Pasien *pasien) {
  pb->pasien = pasien;
}

Pasien *
pasien_box_get_data(PasienBox *pb) {
  return pb->pasien;
}

GtkWidget *
pasien_box_new() {
  return GTK_WIDGET(g_object_new(PASIEN_TYPE_BOX, NULL));
}