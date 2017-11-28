/**
 *       @file  aux.c
 *      @brief  file with aux funcs to create a GUI using GTK and Glade
 *
 *     @author  Vitor Santos, vitor@ua.pt
 *
 * =====================================================================================
 */

#define _AUX_C_

#include <stdlib.h>
#include "mydr.h"

/**
 * @brief  Função para detectar o fecho forçado da janela principal
 * Stop the GTK+ main loop function when the window is destroyed.
 *
 * @param  Widget and user data
 * @return boolean com ordem de ignorar ou não a continuação
 */
void pari_destroy(GtkWidget * window, gpointer data)
{
	puts("vou sair");
	gtk_main_quit();
}

/**
 * @brief  Função para detectar o fecho forçado da janela principal
 *
 * @param  Widget and user data
 * @return boolean com ordem de ignorar ou não a continuação
 * Return FALSE to destroy the widget.
 */
gboolean pari_delete_event(GtkWidget * window, GdkEvent * event, gpointer data)
{
	g_print("You should not use the OS to force leave!\n");
	return FALSE;
}

/**
 * @brief  Callback to intersect CTRL-C
 */
void InterceptCTRL_C( int a )
{
	g_print("Sair por CTRL-C\n");
	gtk_main_quit();
}


void InitTimer()
{
#if 0
    const struct itimerval vValue = { {0,500000}, //it_interval: next value (sec, usecs)  - interval of repetition (0.5 sec)
                                      {1,0}  //it_value: initial value (sec, usecs) - initial delay 
                                    };
    int a=setitimer(ITIMER_REAL, & vValue, NULL);
    if( a ) perror("Setting timer:");
    signal(SIGALRM, p_ForceRefreshDA);
#else
     GtkWidget *da=GTK_WIDGET(gtk_builder_get_object (builderG, "drawingarea1"));
     GdkWindow *w=gtk_widget_get_window(da);
     g_timeout_add (200, p_ForceRefreshDA, w);  //in milliseconds

#endif
}

