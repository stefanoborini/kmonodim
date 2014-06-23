/****************************************************************************
** Form interface generated from reading ui file 'infinite.ui'
**
** Created: Tue Mar 5 15:30:05 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef INFINITEBASE_H
#define INFINITEBASE_H

#include <qvariant.h>
#include <qdialog.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QGroupBox;
class QLabel;
class QLineEdit;
class QPushButton;

class InfiniteBase : public QDialog
{ 
    Q_OBJECT

public:
    InfiniteBase( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~InfiniteBase();

    QGroupBox* GroupBox3;
    QGroupBox* GroupBox1;
    QLabel* TextLabel1;
    QLabel* TextLabel7_2;
    QLabel* TextLabel8;
    QLabel* TextLabel4;
    QLineEdit* m_eigenNumber_edit;
    QLineEdit* m_particleMass_edit;
    QLineEdit* m_numPoints_edit;
    QGroupBox* GroupBox2;
    QLabel* TextLabel5;
    QLabel* TextLabel4_2;
    QLabel* TextLabel6;
    QLabel* TextLabel5_2;
    QLineEdit* m_lowEdge_edit;
    QLineEdit* m_highEdge_edit;
    QPushButton* m_recalcButton;
    QPushButton* m_closeButton;

protected slots:
    virtual void slotClose();
    virtual void slotDoCalc();
    virtual void slotTextChanged();

protected:
    QHBoxLayout* InfiniteBaseLayout;
    QHBoxLayout* GroupBox3Layout;
    QVBoxLayout* Layout12;
    QHBoxLayout* Layout11;
    QHBoxLayout* GroupBox1Layout;
    QGridLayout* Layout10;
    QHBoxLayout* GroupBox2Layout;
    QGridLayout* Layout6;
    QHBoxLayout* Layout6_2;
};

#endif // INFINITEBASE_H
