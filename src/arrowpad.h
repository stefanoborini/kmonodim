#ifndef ARROWPAD_H
#define ARROWPAD_H

#include "arrowpadbase.h" 
#include "control.h"


class ArrowPad : public ArrowPadBase {
Q_OBJECT;

public:
	ArrowPad(QWidget *, const char *);

	void northClick()			{ emit signalAction( Control::North ); }
	void eastClick()			{ emit signalAction( Control::East ); }
	void southClick()			{ emit signalAction( Control::South ); }
	void westClick()          { emit signalAction( Control::West ); }
	void zoomInClick()		{ emit signalAction( Control::ZoomIn ); }
	void zoomOutClick()		{ emit signalAction( Control::ZoomOut ); }

signals:

	void signalAction( Control::Command );

};

#endif
	
	
