#include <qpixmap.h>
#include <qbitmap.h>
#include "mylistviewitem.h"


/* XPM */
static const char * exclam_xpm[] = {
"18 15 4 1",
" 	c None",
".	c #FFFFFF",
"@	c #FF0000",
"#	c #FF8989",
"..................",
"..................",
"...@@@@@@@........",
"..@@@@@@@@@.......",
".@@@@..#@@@@......",
".@@@@..#@@@@......",
".@@@@..#@@@@......",
".@@@@..#@@@@......",
".@@@@..#@@@@......",
".@@@@@@@@@@@......",
".@@@@@@@@@@@......",
"..@@@..#@@@.......",
"...@@@@@@@........",
"..................",
".................."};

MyListViewItem::MyListViewItem(QListView *parent, int dataIndex,QString &str,const QColor &col, bool active, bool warn) :
	QListViewItem(parent,str) {
	QPixmap p(exclam_xpm);
	//QBitmap mask(exclam_width,exclam_height,exclam_bits);
	p.setMask(p.createHeuristicMask());

	m_dataIndex = dataIndex;
	m_color = col;
	m_active = active;
	if (warn) setPixmap(0,p);

}

MyListViewItem::MyListViewItem(QListViewItem *parent, int dataIndex,QString &str,const QColor &col, bool active, bool warn) :
	QListViewItem(parent,str) {
		
	QPixmap p(exclam_xpm);
	// QBitmap mask(exclam_width,exclam_height,exclam_bits);
	p.setMask(p.createHeuristicMask());

	m_dataIndex = dataIndex;
	m_color = col;
	m_active = active;
	if (warn) setPixmap(0,p);
}

QString	MyListViewItem::key ( int column, bool ascending ) const {
	QString out;
	double num;
	int exponent;
	int index;
	int sign;
	switch (column) {
//		case 0:
//			out.sprintf("%015i", text(column).toInt());
//			return out;
//			break;
		case 0:
			out.sprintf("%#+015.8E", text(column).toDouble());
			index = out.find('E');
			num = out.left(index).toDouble();
			exponent = out.mid(index+1).toInt();
			sign = (num<0)?1:-1;
			exponent = (num==0)?0:(1000-(exponent*sign));
			num += 10;
			out.sprintf("%+2d%04d:%011.8f", sign, exponent, num);
			return out;
			break;
		default:
			return QListViewItem::key(column, ascending);
	}
}


void MyListViewItem::paintCell(QPainter * p, const QColorGroup & cg, int column, int width, int align ) {

	int h = height();
	
	switch (column) {
		case 0:
			QListViewItem::paintCell(p, cg, column, width, align );
			break;
		case 1:
			drawColorColumn(p, cg, column, width, align );
			break;
		case 2:
			drawActiveColumn(p, cg, column, width, align );
			break;
		default:
			QListViewItem::paintCell(p, cg, column, width, align );
			break;
	}
}

void MyListViewItem::drawColorColumn(QPainter * p, const QColorGroup & cg, int column, int width, int align ) {
	int h = height();	
	
	p->fillRect( 0, 0, width, height(), cg.brush( QColorGroup::Base ) );
	
	int xfrom, yfrom, xto, yto;
	
	if (width >10) {
		xfrom = (width / 2) - 5;
		xto = 10;
	} else {
		xfrom = 0;
		xto = width;
	}
	if ( h > 10 ) {
		yfrom = (h / 2) - 5;
		yto = 10;
	} else {
		yfrom = 0;
		yto = h;
	}	
	
	p->fillRect(xfrom,yfrom,xto,yto, QBrush(m_color));
	p->setPen(QPen(QColor(0,0,0),1));
	p->drawRect(xfrom,yfrom,xto,yto);

	
}

void MyListViewItem::drawActiveColumn(QPainter * p, const QColorGroup & cg, int column, int width, int align ) {
	
	int h = height();	
	p->fillRect( 0, 0, width, height(), cg.brush( QColorGroup::Base ) );
	
	int xfrom, yfrom, xto, yto;
	
	if (width >10) {
		xfrom = (width / 2) - 5;
		xto = 10;
	} else {
		xfrom = 0;
		xto = width;
	}
	if ( h > 10 ) {
		yfrom = (h / 2) - 5;
		yto = 10;
	} else {
		yfrom = 0;
		yto = h;
	}	
	
	p->setPen(QPen(QColor(0,0,0),1));
	p->drawArc(xfrom,yfrom,xto,yto,0,5760);
	p->setBrush(QBrush(QColor(0,0,0)));
	if (m_active) p->drawPie(xfrom+2,yfrom+2,xto-4,yto-4,0,5760);

}
	

	

int MyListViewItem::width ( const QFontMetrics & fm, const QListView * lv, int c ) const {
	
	if (c == 0) { 
		return QListViewItem::width ( fm, lv, c );
	} else {
		return 10+lv->itemMargin()*2;
	}
}

