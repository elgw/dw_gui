#ifndef __DWAPPWIN_H
#define __DWAPPWIN_H

#include <gtk/gtk.h>
#include <ctype.h>
#include "dw_app.h"



#define DW_APP_WINDOW_TYPE (dw_app_window_get_type ())
G_DECLARE_FINAL_TYPE (DwAppWindow, dw_app_window, DW, APP_WINDOW, GtkApplicationWindow)

DwAppWindow *dw_app_window_new (DwApp *app);
void dw_app_window_open (DwAppWindow *win, GFile *file);


void edit_selected_channel();

gboolean file_tree_keypress (GtkWidget *tree_view, GdkEventKey *event, gpointer data);
void del_selected_file();

// Channel
typedef struct {
    char * name;
    char * alias;
    float lambda;
    int niter;
} DwChannel;

// Remove selected items from the treeviews:
void del_selected_channel();
// Callback from buttons in channel tab
gboolean del_channel_cb(GtkWidget * w, gpointer p);
gboolean save_channels_cb(GtkWidget * w, gpointer p);
gboolean edit_channel_cb(GtkWidget * w, gpointer p);
DwChannel * dw_channel_new();
void dw_channels_free(DwChannel **);
void dw_channel_free(DwChannel*);
/* Write down NULL-terminated array of channels to a ini file */
void dw_channels_to_disk(DwChannel ** , char *);
/* Look trough an array of channels and return the first where alias matches  */
DwChannel * dw_channel_get_by_alias(DwChannel ** , char * alias);
/* Get all channels from gui as a null-terminated array */
DwChannel ** dw_channels_get_from_gui(void);
/* Read channels from file */
DwChannel ** dw_channels_from_disk(char * fname);

// Microscope
typedef struct {
    char * name;
    float NA;
    float ni;
    float xy_nm;
    float z_nm;
} DwScope;

DwScope * dw_scope_new();
void dw_scope_free(DwScope *);
void dw_scopes_free(DwScope ** );
// Get NULL-terminated list of microscopes from the GUI
DwScope ** dw_scopes_get_from_gui();
//
DwScope * dw_scope_get_from_model(GtkTreeModel * model, GtkTreeIter * iter);

// Edit button in scope view
gboolean edit_scope_cb(GtkWidget * w, gpointer p);
// Delete selected scope
gboolean del_scope_cb(GtkWidget * w, gpointer p);
gboolean save_scopes_cb(GtkWidget * w, gpointer p);
/* Read channels from file */
DwScope ** dw_scopes_from_disk(char * fname);

//
void edit_selected_scope();
void del_selected_scope();
void dw_scopes_to_disk(DwScope **, char *);
void dw_scope_to_key_file(DwScope *, GKeyFile *);

// deconwolf
typedef struct {
    int nthreads;
    int tilesize;
    gboolean overwrite;
} dwconf;

#endif
