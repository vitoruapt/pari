/**
 *       @file  mydr.h
 *      @brief  Header para projecto genérico
 *
 *     @author  Vitor Santos, vitor@ua.pt
 *
 * =====================================================================================
 */
#ifndef _MYDR_H
#define _MYDR_H

#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <cairo.h>
#include <gtk/gtk.h>

#define MAXFFBUFFER 1000

#ifdef __cplusplus
class A {};
#endif

//Data structure
typedef struct {
  int count;
  double x[MAXFFBUFFER];
  double y[MAXFFBUFFER];
} free_form;

enum my_buttons { BUTTON1=1, BUTTON2=2, BUTTON3=4};

#if defined (_MAIN_C_)
	GtkBuilder *builderG;
	double xoffG=100;
	double yoffG=120;
	free_form ffG={0};  //init count to zero
	int mouse_button_onG=0; //no button is pressed
	double fontSizeFactorG=1; //global font size factor
	double deltaFactG=0.1;  //global increment of size factor
#else
	extern GtkBuilder *builderG;
	extern double xoffG;
	extern double yoffG;
	extern free_form ffG;
	extern int mouse_button_onG;
	extern double fontSizeFactorG;
	extern double deltaFactG;
#endif

#define max(x,y) ((x)>(y) ? (x) : (y) )
#define min(x,y) ((x)<(y) ? (x) : (y) )

#include "prototypes.h"

#endif	/* _MYDR_H */

