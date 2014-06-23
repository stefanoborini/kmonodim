#include <qdom.h>
#include <qmap.h>
#include "color.h"
#include "palette.h"

Palette::Palette(QObject *parent, const char *name) : QObject(parent, name) {
	m_colors.setAutoDelete(true);
}

Color Palette::color(unsigned int index) const {

	Color *c = m_colors[index];
	
	if ( !c ) return Color::null;

	return *c;

}	

void Palette::setColor(unsigned int index, const Color &col) {

	Color *c = m_colors[index];

	if ( !c ) {
		c = new Color;
		m_colors.insert(index,c);
	}

	*c = col;

	m_changed[index] = true;

}


void Palette::reportChanges() {
	
	if (!modifiedColors()) return;
	emit signalChanged(); 
	resetChanged();

}

void Palette::resetChanged() {
	QMap<unsigned int,bool>::Iterator it;

	for (it = m_changed.begin(); it != m_changed.end(); ++it) it.data() = false;

}



unsigned int Palette::modifiedColors() {
	register unsigned int modified = 0;
	QMap<unsigned int,bool>::Iterator it;

	for (it = m_changed.begin(); it != m_changed.end(); ++it) if (it.data()) modified++;

	return modified;

}

bool Palette::changed(unsigned int index) const {
	Color *c = m_colors[index];
	
	if ( !c ) return false;

	return m_changed[index];
}

#include "palette.moc"
