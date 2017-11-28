/**
 *       @file  main.c
 *      @brief  Example main file to create a GUI using GTK and Glade
 *
 *     @author  Vitor Santos, vitor@ua.pt
 *
 *
 * =====================================================================================
 */

#define _MAIN_C_

#include <stdlib.h>
#include "mydr.h"

int main(int argc, char *argv[])
{

	gtk_init(&argc, &argv);

	/* load the interface */
	builderG = gtk_builder_new();
	gtk_builder_add_from_file(builderG, "myda.glade", NULL);

	/* connect the signals in the interface */
	gtk_builder_connect_signals(builderG, NULL);

	/* get main window ID and connect special signals */
	GtkWidget *t = GTK_WIDGET(gtk_builder_get_object(builderG, "window1"));

	if(t)
	{
		g_signal_connect(G_OBJECT(t), "destroy", G_CALLBACK(pari_destroy), NULL);
		g_signal_connect(G_OBJECT(t), "delete_event", G_CALLBACK(pari_delete_event), NULL);
	}

	//g_signal_connect(GTK_WIDGET (gtk_builder_get_object(builderG, "drawingarea1")), "expose-event", G_CALLBACK(on_drawingarea1_expose_event), NULL);
	

	InitTimer();

	/* start the event loop */
	gtk_main();

	return 0;
}


