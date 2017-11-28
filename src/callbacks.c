/**
 *       @file  callbacks.c
 *      @brief  Callback for buttons and widgets
 *
 * Detailed description starts here.
 *
 *     @author  Vitor Santos, vitor@ua.pt
 *
 * =====================================================================================
 */

#define _CALLBACKS_C_

#include <stdlib.h>
#include "mydr.h"

/**
 * @brief  First mapping of main window
 *
 * @param  widget The usual for callbacks
 * @param  event The usual for callbacks
 * @param  user_data The usual for callbacks
 * @return boolean
 */
gboolean on_window1_map_event(GtkWidget * widget, GdkEvent * event, gpointer user_data)
{
	printf ("passei aqui\n");
	return TRUE;
}

/**
 * @brief  Callback para responder em caso de exposição da área de desenho
 *
 * @param  widget the causing widget
 * @param  event the associated event 
 * @param  user_data the usual user data
 * @return void
 */
void on_drawingarea1_draw(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
	p_RedrawFreeForm(cr);
	p_RedrawText(cr);
	//p_DrawLineLenght(widget, cr);
	
}



/**
 * @brief  Redraw text on the window
 *
 * @param  cr The cairo context
 * @return void
 */
void p_RedrawText(cairo_t *cr)
{
	const char *font="ubuntu";
	//"serif", "sans-serif", "ubuntu", "Purisa", "Courier", etc.
	//can see more fonts with command fc-list (awk -F: '{print $2}') 
	char string[200];
	cairo_text_extents_t extents;
	cairo_set_source_rgb(cr, 1, 0, 0);
	cairo_select_font_face(cr, font, CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size(cr, 20.0*fontSizeFactorG);

#if 1
	time_t timep=time(NULL);
	struct tm *tm=localtime(&timep);
	cairo_select_font_face(cr, "Courier", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
	//cairo_set_font_size(cr, 60.0);
	if(tm->tm_sec%2)
		sprintf(string,"%02d:%02d:%02d", tm->tm_hour, tm->tm_min, tm->tm_sec);
	else
		sprintf(string,"%02d %02d %02d", tm->tm_hour, tm->tm_min, tm->tm_sec);
#else
	sprintf(string,"My first cairo test");
#endif
	cairo_text_extents(cr, string, &extents);
	cairo_move_to(cr, xoffG-extents.width/2, yoffG+extents.height/2); //re-place the text on surface
	cairo_show_text(cr, string);     //draw the text on the surface
}


/**
 * @brief  Writes text with line segment count
 *
 * @param  wid the widget where this happens
 * @param  cr the cairo context
 * @return 
 */
void p_DrawLineLenght(GtkWidget *wid, cairo_t *cr)
{
	char str[40];
	GtkAllocation alloc; gtk_widget_get_allocation(wid, &alloc);
	cairo_set_source_rgb(cr, 0, 0, 1);
	cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size(cr, 10.0);
	cairo_move_to(cr, 0, alloc.height);
	sprintf(str,"line points: %04d", ffG.count);
	cairo_show_text(cr, str);    
}

/**
 * @brief  Draws the stored freeform line
 *
 * @param  wid the widget where this happens
 * @param  cr the cairo context
 * @return void
 */
void p_RedrawFreeForm(cairo_t * cr)
{
	cairo_set_source_rgb(cr, 0, 0, 0.5);
	cairo_set_line_width(cr, 9);

	int i;
	cairo_move_to(cr, ffG.x[0], ffG.y[0]);
	for(i = 1; i < ffG.count; i++)
	{
		cairo_line_to(cr, ffG.x[i], ffG.y[i]);
	}
	cairo_stroke(cr);

}

/**
 * @brief  Function to process the pressed button
 *
 * @param  widget the associated widget
 * @return void
 */
void on_button2_clicked(GtkWidget * widget, gpointer user_data)
{
	g_print("Button 2 clicked\n");
	//must enable the GDK_BUTTON_PRESS_MASK mask.
}

void on_mouse_button_on(GtkWidget *widget, GdkEventButton *event, gpointer user_data)
{
	if( event->button == 2 )
	{
	//button 2 - clear line
		ffG.count=0;
	}
        gtk_widget_queue_draw(widget);  //force draw the widget
}


void on_drawingarea1_scroll_event(GtkWidget *widget, GdkEventScroll *event, gpointer user_data)
{

	if ((event->state & (GDK_CONTROL_MASK | GDK_SHIFT_MASK))==(GDK_SHIFT_MASK| GDK_CONTROL_MASK) )
		deltaFactG=0.1;
	else
		deltaFactG=1;

	switch(event->direction)
	{
		case GDK_SCROLL_UP:
			fontSizeFactorG=min(fontSizeFactorG+deltaFactG, 10);
			break;

		case GDK_SCROLL_DOWN:
			fontSizeFactorG=max(fontSizeFactorG-deltaFactG, 0.2);
			break;

		case GDK_SCROLL_LEFT:
		case GDK_SCROLL_RIGHT:
		case GDK_SCROLL_SMOOTH:
			break;
	}
        gtk_widget_queue_draw(widget);  //make draw the widget
	//p_ForceRefreshDA(NULL); //force redrawing of area
}



void on_drawingarea1_motion_notify_event(GtkWidget *widget, GdkEventMotion *event, gpointer user_data)
{


	if( event->state & GDK_BUTTON3_MASK)
	{
		//button 3 move text
        	xoffG = event->x;  /* mouse coordinate x */
        	yoffG = event->y;  /*mouse coordinate y */
	}
	if( event->state & GDK_BUTTON1_MASK)
	{
		//button 1 - accumulate freeform path
        	if( ffG.x[ffG.count] != event->x && ffG.y[ffG.count] != event->y)
		{
        		ffG.x[ffG.count] = event->x;
        		ffG.y[ffG.count++] = event->y;
			ffG.count %= MAXFFBUFFER;
		}
	}
        //gdk_window_invalidate_rect(gtk_widget_get_window(widget), NULL, FALSE); //force redraw
        gtk_widget_queue_draw(widget);  //make draw the widget
}


gboolean p_ForceRefreshDA(gpointer user_data)
{
	GdkWindow *da;
	if( ! user_data)
	   da = gtk_widget_get_window(GTK_WIDGET(gtk_builder_get_object (builderG, "drawingarea1")));
	else
	   da=GDK_WINDOW(user_data);

    	//gdk_window_invalidate_rect (gtk_widget_get_window(da), NULL, FALSE);
    	gdk_window_invalidate_rect (da, NULL, FALSE);

	return TRUE;  //continue running
}


