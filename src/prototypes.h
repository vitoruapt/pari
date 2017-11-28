/*File generated automatically in robotica5 by vitor on Ter Nov 28 15:58:08 WET 2017*/
#ifdef __cplusplus
extern "C" {
#endif
/* aux.c */
void InitTimer();
void InterceptCTRL_C(int a);
gboolean pari_delete_event(GtkWidget * window, GdkEvent * event, gpointer data);
void pari_destroy(GtkWidget * window, gpointer data);
/* callbacks.c */
void on_button2_clicked(GtkWidget * widget, gpointer user_data);
void on_drawingarea1_draw(GtkWidget * widget, cairo_t * cr, gpointer user_data);
void on_drawingarea1_motion_notify_event(GtkWidget * widget, GdkEventMotion * event, gpointer user_data);
void on_drawingarea1_scroll_event(GtkWidget * widget, GdkEventScroll * event, gpointer user_data);
void on_mouse_button_on(GtkWidget * widget, GdkEventButton * event, gpointer user_data);
gboolean on_window1_map_event(GtkWidget * widget, GdkEvent * event, gpointer user_data);
void p_DrawLineLenght(GtkWidget * wid, cairo_t * cr);
gboolean p_ForceRefreshDA(gpointer user_data);
void p_RedrawFreeForm(cairo_t * cr);
void p_RedrawText(cairo_t * cr);
/* main.c */
int main(int argc, char *argv[]);
#ifdef __cplusplus
}
#endif
