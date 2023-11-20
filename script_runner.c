#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>

GtkWidget *output_label;

typedef struct
{
	GtkWidget *box;
	GtkWidget *entry;
	GtkWidget *button;
} ScriptRow;

static void button_clicked(GtkWidget *widget, gpointer data)
{
	ScriptRow *script_row = (ScriptRow *)data;

	// Get the text from the entry widget
	const gchar *script_path = gtk_entry_get_text(GTK_ENTRY(script_row->entry));

	// Execute the script using system() function
	int result = system(script_path);

	// Display the result in the label with color
	if (result == 0)
	{
		// Script executed successfully
		gtk_label_set_markup(GTK_LABEL(output_label), "<span foreground='green'>Success</span>");
	}
	else if (result == 256)
	{
		// Script execution failed
		gtk_label_set_markup(GTK_LABEL(output_label), "<span foreground='yellow'>Nothing to Commit</span>");
	}
	else
	{
		// Script execution failed
		gtk_label_set_markup(GTK_LABEL(output_label), "<span foreground='red'>Failure</span>");
	}
}

int main(int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *scripts_list;
	GtkWidget *scroll_window;

	gtk_init(&argc, &argv);

	// Create the main window
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Script Runner");
	gtk_window_set_default_size(GTK_WINDOW(window), 1000, 400);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	// Create a scrollable window
	scroll_window = gtk_scrolled_window_new(NULL, NULL);
	gtk_container_set_border_width(GTK_CONTAINER(scroll_window), 10);

	// Create a list box for scripts
	scripts_list = gtk_list_box_new();
	gtk_list_box_set_selection_mode(GTK_LIST_BOX(scripts_list), GTK_SELECTION_NONE);
	gtk_container_add(GTK_CONTAINER(scroll_window), scripts_list);

	// Create a label for displaying script output
	output_label = gtk_label_new(NULL);

	// Create a vertical box to organize the elements
	GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_container_add(GTK_CONTAINER(window), vbox);

	// Create dummy script data with custom names and paths
	const char *script_data[][2] = {
		{"Script 1", "/home/kelho/test.sh"},
		{"Script 2", "/path/to/script2.sh"},
		{"Script 3", "/path/to/script3.sh"},
		{"Script 4", "/path/to/script4.sh"},
		{"Script 5", "/path/to/script5.sh"},
		{"Script 5", "/path/to/script5.sh"},

	};
	size_t num_scripts = sizeof(script_data) / sizeof(script_data[0]);
	// Create script rows for each dummy script
	ScriptRow script_rows[num_scripts];

	for (int i = 0; i < 5; i++)
	{
		script_rows[i].box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

		// Label showing the script name
		GtkWidget *label = gtk_label_new(script_data[i][0]);

		// Entry widget for script path (non-editable)
		script_rows[i].entry = gtk_entry_new();
		gtk_entry_set_text(GTK_ENTRY(script_rows[i].entry), script_data[i][1]);
		gtk_widget_set_sensitive(script_rows[i].entry, FALSE);

		// Button to run the script
		script_rows[i].button = gtk_button_new_with_label("Run Script");

		g_signal_connect(script_rows[i].button, "clicked", G_CALLBACK(button_clicked), &script_rows[i]);

		// Pack elements into the box
		gtk_box_pack_start(GTK_BOX(script_rows[i].box), label, FALSE, FALSE, 5);
		gtk_box_pack_start(GTK_BOX(script_rows[i].box), script_rows[i].entry, TRUE, TRUE, 5);
		gtk_box_pack_start(GTK_BOX(script_rows[i].box), script_rows[i].button, FALSE, FALSE, 5);

		// Add the script box to the list box
		gtk_list_box_insert(GTK_LIST_BOX(scripts_list), script_rows[i].box, -1);
	}

	// Add elements to the vertical box
	gtk_box_pack_start(GTK_BOX(vbox), scroll_window, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(vbox), output_label, FALSE, FALSE, 5);

	// Show all elements
	gtk_widget_show_all(window);

	// Start the GTK main loop
	gtk_main();

	return 0;
}
