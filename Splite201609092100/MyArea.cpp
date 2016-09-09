#include "MyArea.h"
#include <gtkmm.h>
#include <gdkmm.h>
#include <glibmm.h>
MyArea::MyArea(void)
{
	try {
		m_pixbufGif = Gdk::Pixbuf::create_from_file( "../res/greenball.gif" );
		m_oneImage = Gdk::Pixbuf::create_subpixbuf(m_pixbufGif, 0, 0, 16, 16);
		m_twoImage = Gdk::Pixbuf::create_subpixbuf(m_pixbufGif, 16, 0, 16, 16);
		m_oneImage = m_oneImage->scale_simple(
			m_oneImage->get_width() * 4, 
			m_oneImage->get_height() * 4, 
			Gdk::INTERP_NEAREST);
		m_twoImage = m_twoImage->scale_simple(
			m_twoImage->get_width() * 4, 
			m_twoImage->get_height() * 4, 
			Gdk::INTERP_NEAREST);
		m_nowImage = m_oneImage;
	}
	catch(...)
	{
		Glib::exception_handlers_invoke();
		exit(1);
	}
	Glib::signal_timeout().connect( sigc::mem_fun( *this, &MyArea::on_timeout ), 500 );
}
MyArea::~MyArea(void)
{
}
bool MyArea::on_expose_event( GdkEventExpose* event )
{
	const int width = this->get_width();
	const int height = this->get_height();

	Cairo::RefPtr< Cairo::Context > cr = get_window()->create_cairo_context();
	cr->set_source_rgb(0.0, 0.0, 0.0);
	cr->rectangle(0, 0, width, height);
	cr->fill();

	Gdk::Cairo::set_source_pixbuf( cr, m_nowImage, 
		width / 2 - m_nowImage->get_width() / 2 ,
		height / 2 - m_nowImage->get_height() / 2);
	cr->paint();

	return true;
}
bool MyArea::on_timeout()
{
	if (m_nowImage == m_oneImage) { m_nowImage = m_twoImage; }
	else { m_nowImage = m_oneImage; }
	queue_draw();
	return true;
}