#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tanggal_t {
    int hari;
    int bulan;
    int tahun;
} Tanggal;

typedef struct pasien_t {
    int ID;
    char nama[25];
    char alamat[25];
    char kota[25];
    char tempatLahir[25];
    Tanggal *tanggalLahir;
    int umur;
    int BPJS;
    struct pasien_t *next;
} Pasien;

// Function prototypes
void append_pasien_to_buffer(Pasien *head, GtkTextBuffer *buffer);
void on_add_button_clicked(GtkButton *button, gpointer user_data);
void on_edit_button_clicked(GtkButton *button, gpointer user_data);
void on_delete_button_clicked(GtkButton *button, gpointer user_data);
void add_pasien(Pasien **head, int id, const char *nama, const char *alamat, const char *kota, const char *tempatLahir, Tanggal *tanggalLahir, int umur, int BPJS);
void edit_pasien(Pasien *head, int id, const char *nama, const char *alamat, const char *kota, const char *tempatLahir, Tanggal *tanggalLahir, int umur, int BPJS);
void delete_pasien(Pasien **head, int id);
void show_add_pasien_dialog(GtkButton *button, gpointer user_data);
void show_edit_pasien_dialog(GtkButton *button, gpointer user_data);
void show_delete_pasien_dialog(GtkButton *button, gpointer user_data);
void on_form_submit(GtkButton *button, gpointer user_data);
void on_edit_form_submit(GtkButton *button, gpointer user_data);
void on_delete_confirm(GtkButton *button, gpointer user_data);

GtkTextBuffer *buffer;  // Global buffer
GtkWidget *window;  // Global main window

typedef struct {
    Pasien **head;
    GtkWidget *entry_id;
    GtkWidget *entry_nama;
    GtkWidget *entry_alamat;
    GtkWidget *entry_kota;
    GtkWidget *entry_tempat_lahir;
    GtkWidget *entry_tanggal_lahir;
    GtkWidget *entry_umur;
    GtkWidget *entry_bpjs;
} FormData;

typedef struct {
    Pasien **head;
    GtkWidget *entry_id;
} DeleteData;

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Create main window
    window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "Pasien List");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    // Create a vertical box container
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create TextView and add to the vbox
    GtkWidget *text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(text_view), FALSE);
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));

    // Create a scroll window to contain the TextView
    GtkWidget *scroll_window = gtk_scrolled_window_new();
    gtk_container_set_border_width(GTK_CONTAINER(scroll_window), 10);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(scroll_window), text_view);
    gtk_box_pack_start(GTK_BOX(vbox), scroll_window, TRUE, TRUE, 0);

    // Create Add, Edit, and Delete buttons and add to the vbox
    GtkWidget *add_button = gtk_button_new_with_label("Add Pasien");
    gtk_box_pack_start(GTK_BOX(vbox), add_button, FALSE, FALSE, 0);

    GtkWidget *edit_button = gtk_button_new_with_label("Edit Pasien");
    gtk_box_pack_start(GTK_BOX(vbox), edit_button, FALSE, FALSE, 0);

    GtkWidget *delete_button = gtk_button_new_with_label("Delete Pasien");
    gtk_box_pack_start(GTK_BOX(vbox), delete_button, FALSE, FALSE, 0);

    // Example linked list
    Tanggal tanggal1 = {1, 1, 2000};
    Pasien *pasien_list = NULL;

    // Add initial patients
    add_pasien(&pasien_list, 1, "John Doe", "123 Main St", "Anytown", "Cityville", &tanggal1, 24, 123456);
    add_pasien(&pasien_list, 2, "Jane Smith", "456 Elm St", "Othertown", "Townville", &tanggal1, 30, 654321);

    // Display initial list
    append_pasien_to_buffer(pasien_list, buffer);

    // Connect button signals
    g_signal_connect(add_button, "clicked", G_CALLBACK(show_add_pasien_dialog), &pasien_list);
    g_signal_connect(edit_button, "clicked", G_CALLBACK(show_edit_pasien_dialog), &pasien_list);
    g_signal_connect(delete_button, "clicked", G_CALLBACK(show_delete_pasien_dialog), &pasien_list);

    // Show all widgets
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();

    return 0;
}

void append_pasien_to_buffer(Pasien *head, GtkTextBuffer *buffer) {
    GtkTextIter iter;
    gtk_text_buffer_get_start_iter(buffer, &iter);

    // Clear existing text
    gtk_text_buffer_set_text(buffer, "", -1);

    // Print table header
    gtk_text_buffer_insert(buffer, &iter, "ID   | Nama                     | Alamat                   | Kota                     | Tempat Lahir             | Tanggal Lahir | Umur | BPJS\n", -1);
    gtk_text_buffer_insert(buffer, &iter, "----+-------------------------+-------------------------+-------------------------+-------------------------+---------------+------+------\n", -1);

    char line[512];
    while (head != NULL) {
        // Format the patient's data into a string
        snprintf(line, sizeof(line), "%-4d | %-24s | %-24s | %-24s | %-24s | %02d/%02d/%04d | %-4d | %-4d\n",
                 head->ID, head->nama, head->alamat, head->kota, head->tempatLahir,
                 head->tanggalLahir->hari, head->tanggalLahir->bulan, head->tanggalLahir->tahun,
                 head->umur, head->BPJS);
        gtk_text_buffer_insert(buffer, &iter, line, -1);
        head = head->next;
    }
}

void show_add_pasien_dialog(GtkButton *button, gpointer user_data) {
    GtkWidget *dialog;
    GtkWidget *content_area;
    GtkWidget *form;
    GtkWidget *entry_id, *entry_nama, *entry_alamat, *entry_kota, *entry_tempat_lahir, *entry_tanggal_lahir, *entry_umur, *entry_bpjs;
    GtkWidget *submit_button;
    Pasien **head = (Pasien **)user_data;

    // Create a new window for the dialog
    dialog = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(dialog), "Add Pasien");
    gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);
    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(window));
    gtk_window_set_default_size(GTK_WINDOW(dialog), 400, 300);

    // Create a box container for the form
    content_area = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_set_border_width(GTK_CONTAINER(content_area), 10);
    gtk_container_add(GTK_CONTAINER(dialog), content_area);

    // Create a grid for the form
    form = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(form), 5);
    gtk_grid_set_column_spacing(GTK_GRID(form), 5);
    gtk_box_pack_start(GTK_BOX(content_area), form, TRUE, TRUE, 0);

    // Create and add form elements
    entry_id = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_id), "ID");
    gtk_grid_attach(GTK_GRID(form), gtk_label_new("ID"), 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(form), entry_id, 1, 0, 1, 1);

    entry_nama = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_nama), "Nama");
    gtk_grid_attach(GTK_GRID(form), gtk_label_new("Nama"), 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(form), entry_nama, 1, 1, 1, 1);

    entry_alamat = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_alamat), "Alamat");
    gtk_grid_attach(GTK_GRID(form), gtk_label_new("Alamat"), 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(form), entry_alamat, 1, 2, 1, 1);

    entry_kota = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_kota), "Kota");
    gtk_grid_attach(GTK_GRID(form), gtk_label_new("Kota"), 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(form), entry_kota, 1, 3, 1, 1);

    entry_tempat_lahir = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_tempat_lahir), "Tempat Lahir");
    gtk_grid_attach(GTK_GRID(form), gtk_label_new("Tempat Lahir"), 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(form), entry_tempat_lahir, 1, 4, 1, 1);

    entry_tanggal_lahir = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_tanggal_lahir), "Tanggal Lahir (dd/mm/yyyy)");
    gtk_grid_attach(GTK_GRID(form), gtk_label_new("Tanggal Lahir"), 0, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(form), entry_tanggal_lahir, 1, 5, 1, 1);

    entry_umur = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_umur), "Umur");
    gtk_grid_attach(GTK_GRID(form), gtk_label_new("Umur"), 0, 6, 1, 1);
    gtk_grid_attach(GTK_GRID(form), entry_umur, 1, 6, 1, 1);

    entry_bpjs = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_bpjs), "BPJS");
    gtk_grid_attach(GTK_GRID(form), gtk_label_new("BPJS"), 0, 7, 1, 1);
    gtk_grid_attach(GTK_GRID(form), entry_bpjs, 1, 7, 1, 1);

    // Create and add submit button
    submit_button = gtk_button_new_with_label("Submit");
    g_signal_connect(submit_button, "clicked", G_CALLBACK(on_form_submit), (gpointer)dialog);
    gtk_grid_attach(GTK_GRID(form), submit_button, 1, 8, 1, 1);

    // Create form data
    FormData *form_data = g_malloc(sizeof(FormData));
    form_data->head = head;
    form_data->entry_id = entry_id;
    form_data->entry_nama = entry_nama;
    form_data->entry_alamat = entry_alamat;
    form_data->entry_kota = entry_kota;
    form_data->entry_tempat_lahir = entry_tempat_lahir;
    form_data->entry_tanggal_lahir = entry_tanggal_lahir;
    form_data->entry_umur = entry_umur;
    form_data->entry_bpjs = entry_bpjs;

    // Set form data as user data for the submit button
    g_object_set_data(G_OBJECT(submit_button), "form_data", form_data);

    // Show all widgets in the dialog
    gtk_widget_show_all(dialog);
}

void show_edit_pasien_dialog(GtkButton *button, gpointer user_data) {
    GtkWidget *dialog;
    GtkWidget *content_area;
    GtkWidget *form;
    GtkWidget *entry_id, *entry_nama, *entry_alamat, *entry_kota, *entry_tempat_lahir, *entry_tanggal_lahir, *entry_umur, *entry_bpjs;
    GtkWidget *submit_button;
    Pasien **head = (Pasien **)user_data;

    // Create a new window for the dialog
    dialog = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(dialog), "Edit Pasien");
    gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);
    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(window));
    gtk_window_set_default_size(GTK_WINDOW(dialog), 400, 300);

    // Create a box container for the form
    content_area = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_set_border_width(GTK_CONTAINER(content_area), 10);
    gtk_container_add(GTK_CONTAINER(dialog), content_area);

    // Create a grid for the form
    form = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(form), 5);
    gtk_grid_set_column_spacing(GTK_GRID(form), 5);
    gtk_box_pack_start(GTK_BOX(content_area), form, TRUE, TRUE, 0);

    // Create and add form elements
    entry_id = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_id), "ID");
    gtk_grid_attach(GTK_GRID(form), gtk_label_new("ID"), 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(form), entry_id, 1, 0, 1, 1);

    entry_nama = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_nama), "Nama");
    gtk_grid_attach(GTK_GRID(form), gtk_label_new("Nama"), 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(form), entry_nama, 1, 1, 1, 1);

    entry_alamat = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_alamat), "Alamat");
    gtk_grid_attach(GTK_GRID(form), gtk_label_new("Alamat"), 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(form), entry_alamat, 1, 2, 1, 1);

    entry_kota = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_kota), "Kota");
    gtk_grid_attach(GTK_GRID(form), gtk_label_new("Kota"), 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(form), entry_kota, 1, 3, 1, 1);

    entry_tempat_lahir = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_tempat_lahir), "Tempat Lahir");
    gtk_grid_attach(GTK_GRID(form), gtk_label_new("Tempat Lahir"), 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(form), entry_tempat_lahir, 1, 4, 1, 1);

    entry_tanggal_lahir = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_tanggal_lahir), "Tanggal Lahir (dd/mm/yyyy)");
    gtk_grid_attach(GTK_GRID(form), gtk_label_new("Tanggal Lahir"), 0, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(form), entry_tanggal_lahir, 1, 5, 1, 1);

    entry_umur = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_umur), "Umur");
    gtk_grid_attach(GTK_GRID(form), gtk_label_new("Umur"), 0, 6, 1, 1);
    gtk_grid_attach(GTK_GRID(form), entry_umur, 1, 6, 1, 1);

    entry_bpjs = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_bpjs), "BPJS");
    gtk_grid_attach(GTK_GRID(form), gtk_label_new("BPJS"), 0, 7, 1, 1);
    gtk_grid_attach(GTK_GRID(form), entry_bpjs, 1, 7, 1, 1);

    // Create and add submit button
    submit_button = gtk_button_new_with_label("Submit");
    g_signal_connect(submit_button, "clicked", G_CALLBACK(on_edit_form_submit), (gpointer)dialog);
    gtk_grid_attach(GTK_GRID(form), submit_button, 1, 8, 1, 1);

    // Create form data
    FormData *form_data = g_malloc(sizeof(FormData));
    form_data->head = head;
    form_data->entry_id = entry_id;
    form_data->entry_nama = entry_nama;
    form_data->entry_alamat = entry_alamat;
    form_data->entry_kota = entry_kota;
    form_data->entry_tempat_lahir = entry_tempat_lahir;
    form_data->entry_tanggal_lahir = entry_tanggal_lahir;
    form_data->entry_umur = entry_umur;
    form_data->entry_bpjs = entry_bpjs;

    // Set form data as user data for the submit button
    g_object_set_data(G_OBJECT(submit_button), "form_data", form_data);

    // Show all widgets in the dialog
    gtk_widget_show_all(dialog);
}

void show_delete_pasien_dialog(GtkButton *button, gpointer user_data) {
    GtkWidget *dialog;
    GtkWidget *content_area;
    GtkWidget *form;
    GtkWidget *entry_id;
    GtkWidget *submit_button;
    Pasien **head = (Pasien **)user_data;

    // Create a new window for the dialog
    dialog = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(dialog), "Delete Pasien");
    gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);
    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(window));
    gtk_window_set_default_size(GTK_WINDOW(dialog), 400, 200);

    // Create a box container for the form
    content_area = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_set_border_width(GTK_CONTAINER(content_area), 10);
    gtk_container_add(GTK_CONTAINER(dialog), content_area);

    // Create a grid for the form
    form = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(form), 5);
    gtk_grid_set_column_spacing(GTK_GRID(form), 5);
    gtk_box_pack_start(GTK_BOX(content_area), form, TRUE, TRUE, 0);

    // Create and add form elements
    entry_id = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_id), "ID");
    gtk_grid_attach(GTK_GRID(form), gtk_label_new("ID"), 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(form), entry_id, 1, 0, 1, 1);

    // Create and add submit button
    submit_button = gtk_button_new_with_label("Delete");
    g_signal_connect(submit_button, "clicked", G_CALLBACK(on_delete_confirm), (gpointer)dialog);
    gtk_grid_attach(GTK_GRID(form), submit_button, 1, 1, 1, 1);

    // Create delete data
    DeleteData *delete_data = g_malloc(sizeof(DeleteData));
    delete_data->head = head;
    delete_data->entry_id = entry_id;

    // Set delete data as user data for the submit button
    g_object_set_data(G_OBJECT(submit_button), "delete_data", delete_data);

    // Show all widgets in the dialog
    gtk_widget_show_all(dialog);
}

void on_form_submit(GtkButton *button, gpointer user_data) {
    GtkWidget *dialog = (GtkWidget *)user_data;
    FormData *form_data = (FormData *)g_object_get_data(G_OBJECT(button), "form_data");

    // Retrieve form data
    int id = atoi(gtk_entry_get_text(GTK_ENTRY(form_data->entry_id)));
    const char *nama = gtk_entry_get_text(GTK_ENTRY(form_data->entry_nama));
    const char *alamat = gtk_entry_get_text(GTK_ENTRY(form_data->entry_alamat));
    const char *kota = gtk_entry_get_text(GTK_ENTRY(form_data->entry_kota));
    const char *tempat_lahir = gtk_entry_get_text(GTK_ENTRY(form_data->entry_tempat_lahir));
    const char *tanggal_lahir_str = gtk_entry_get_text(GTK_ENTRY(form_data->entry_tanggal_lahir));
    int umur = atoi(gtk_entry_get_text(GTK_ENTRY(form_data->entry_umur)));
    int bpjs = atoi(gtk_entry_get_text(GTK_ENTRY(form_data->entry_bpjs)));

    // Parse tanggal_lahir
    Tanggal *tanggal_lahir = malloc(sizeof(Tanggal));
    sscanf(tanggal_lahir_str, "%d/%d/%d", &tanggal_lahir->hari, &tanggal_lahir->bulan, &tanggal_lahir->tahun);

    // Add the new pasien
    add_pasien(form_data->head, id, nama, alamat, kota, tempat_lahir, tanggal_lahir, umur, bpjs);

    // Update the TextView
    append_pasien_to_buffer(*(form_data->head), buffer);

    // Free form data
    free(tanggal_lahir);
    g_free(form_data);

    // Close the dialog
    gtk_widget_destroy(dialog);
}

void on_edit_form_submit(GtkButton *button, gpointer user_data) {
    GtkWidget *dialog = (GtkWidget *)user_data;
    FormData *form_data = (FormData *)g_object_get_data(G_OBJECT(button), "form_data");

    // Retrieve form data
    int id = atoi(gtk_entry_get_text(GTK_ENTRY(form_data->entry_id)));
    const char *nama = gtk_entry_get_text(GTK_ENTRY(form_data->entry_nama));
    const char *alamat = gtk_entry_get_text(GTK_ENTRY(form_data->entry_alamat));
    const char *kota = gtk_entry_get_text(GTK_ENTRY(form_data->entry_kota));
    const char *tempat_lahir = gtk_entry_get_text(GTK_ENTRY(form_data->entry_tempat_lahir));
    const char *tanggal_lahir_str = gtk_entry_get_text(GTK_ENTRY(form_data->entry_tanggal_lahir));
    int umur = atoi(gtk_entry_get_text(GTK_ENTRY(form_data->entry_umur)));
    int bpjs = atoi(gtk_entry_get_text(GTK_ENTRY(form_data->entry_bpjs)));

    // Parse tanggal_lahir
    Tanggal *tanggal_lahir = malloc(sizeof(Tanggal));
    sscanf(tanggal_lahir_str, "%d/%d/%d", &tanggal_lahir->hari, &tanggal_lahir->bulan, &tanggal_lahir->tahun);

    // Edit the pasien
    edit_pasien(*(form_data->head), id, nama, alamat, kota, tempat_lahir, tanggal_lahir, umur, bpjs);

    // Update the TextView
    append_pasien_to_buffer(*(form_data->head), buffer);

    // Free form data
    free(tanggal_lahir);
    g_free(form_data);

    // Close the dialog
    gtk_widget_destroy(dialog);
}

void on_delete_confirm(GtkButton *button, gpointer user_data) {
    GtkWidget *dialog = (GtkWidget *)user_data;
    DeleteData *delete_data = (DeleteData *)g_object_get_data(G_OBJECT(button), "delete_data");

    // Retrieve form data
    int id = atoi(gtk_entry_get_text(GTK_ENTRY(delete_data->entry_id)));

    // Delete the pasien
    delete_pasien(delete_data->head, id);

    // Update the TextView
    append_pasien_to_buffer(*(delete_data->head), buffer);

    // Free delete data
    g_free(delete_data);

    // Close the dialog
    gtk_widget_destroy(dialog);
}