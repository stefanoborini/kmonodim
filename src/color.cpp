#include "color.h"
	

const Color Color::null;

Color::Color() : QColor() {
	m_active = true;
}

Color::Color(int r, int g, int b, bool active) : QColor(r,g,b) {
	m_active = active;
}

Color::Color(const QColor &col, bool active) : QColor(col) {
	m_active = active;
}


Color::Color(const QString &name, bool active) : QColor(name) {
	m_active = active;
}

bool Color::operator==(const Color &c) const {

	return (QColor::operator==(c)) && (m_active == c.m_active);
}

bool Color::operator!=(const Color &c) const {
	return !operator==(c);
}

Color &Color::operator=(const Color &c) {

	QColor::operator=(c);
	m_active = c.m_active;

	return *this;
}

