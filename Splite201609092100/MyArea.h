#pragma once
#include <gtkmm/drawingarea.h>
class MyArea : public Gtk::DrawingArea
{
public:
	MyArea();
	virtual ~MyArea();
protected:
	bool on_expose_event( GdkEventExpose* event );
private:
	int m_value;
	Pango::FontDescription m_font;
	Cairo::FontOptions m_fontOption;
	Glib::RefPtr< Gdk::Pixbuf > m_pixbufGif;
	Glib::RefPtr< Gdk::Pixbuf > m_oneImage;
	Glib::RefPtr< Gdk::Pixbuf > m_twoImage;
	Glib::RefPtr< Gdk::Pixbuf > m_nowImage;
	bool on_timeout();
};
