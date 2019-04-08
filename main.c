/*
 * main.c
 *
 *  Created on: 2019年4月5日
 *      Author: tom
 */
#include <X11/Xlib.h>
#include <gtk/gtk.h>

#include "MyLogo.h"


void my_custom_draw(MyLogo *self,cairo_t *cr) {
	cairo_save(cr);
	cairo_set_source_rgba(cr,1,0,0,0.5);
	cairo_arc(cr,100,100,30,0,2*G_PI);
	cairo_set_line_width(cr,5.);
	cairo_stroke(cr);

	cairo_set_source_rgba(cr,1,0.5,0,0.5);
	cairo_arc(cr,512-60-30,100,60,0,2*G_PI);
	cairo_set_line_width(cr,10.);
	cairo_stroke(cr);

	cairo_set_source_rgba(cr,0,1.,0.5,0.5);
	cairo_arc(cr,300,180,80,0,2*G_PI);
	cairo_set_line_width(cr,30.);
	cairo_stroke(cr);

	cairo_set_source_rgba(cr,0.25,0.8,0.5,0.5);
	cairo_arc(cr,412-50,412-50,100,0,2*G_PI);
	cairo_set_line_width(cr,30.);
	cairo_stroke(cr);

	cairo_set_source_rgba(cr,0.5,0,0.8,0.5);
	cairo_arc(cr,150,512-120-20,120,0,2*G_PI);
	cairo_set_line_width(cr,20.);
	cairo_stroke(cr);

	cairo_restore(cr);

}

void load_png(MyLogo *self,cairo_t *cr) {
	cairo_save(cr);
	cairo_surface_t *surf=cairo_image_surface_create_from_png("gimp.png");
	cairo_set_source_surface(cr,surf,0,0);
	cairo_paint(cr);
	cairo_surface_destroy(surf);
	cairo_restore(cr);
}



int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);
	GtkWindow *mwin=gtk_window_new(GTK_WINDOW_TOPLEVEL);


	gtk_window_set_default_size(mwin,512,512);
	gtk_window_set_decorated(mwin,FALSE);
	MyLogo *win = my_logo_new(mwin,TRUE);
	gtk_container_add(mwin,win);

	GtkButton *button = gtk_button_new_with_label("Close");
	my_logo_pack(win,button,40,100-40*100/512,20,40*100/512,TRUE);

	g_signal_connect(win,"logo_draw",my_custom_draw,NULL);
	g_signal_connect(win,"logo_draw",load_png,NULL);
	g_signal_connect(button,"clicked",gtk_main_quit,NULL);


	gtk_widget_show_all(win);
	gtk_widget_show_all(mwin);
	gtk_main();
	return 0;
}
