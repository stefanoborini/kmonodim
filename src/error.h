#include <qmessagebox.h>

class QWidget;

class Error {
public:
	Error() { m_central = NULL; }
	Error(QWidget *central) { m_central = central; }
	inline void setCentralWidget(QWidget *central) { m_central = central; }
	inline void error(QString title, QString message) { if (m_central) QMessageBox::warning(m_central,title,message); }
protected:
	QWidget *m_central;
};

