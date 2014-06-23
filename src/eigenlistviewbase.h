/****************************************************************************
** Form interface generated from reading ui file 'eigenlistview.ui'
**
** Created: Mon Nov 18 16:48:10 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef EIGENLISTVIEWBASE_H
#define EIGENLISTVIEWBASE_H

#include <qvariant.h>
#include <qwidget.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QLabel;
class QListView;
class QListViewItem;
class QPushButton;

class EigenListViewBase : public QWidget
{ 
    Q_OBJECT

public:
    EigenListViewBase( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~EigenListViewBase();

    QListView* m_listView;
    QPushButton* m_setUniqueColorButton;
    QPushButton* m_setActiveButton;
    QLabel* m_meanKinetic_label;
    QLabel* m_meanPosition_label;
    QLabel* TextLabel1;
    QLabel* TextLabel4;
    QLabel* m_extrapolatedEigenvalue_label;
    QLabel* m_meanPotential_label;
    QLabel* m_extrapolatedEigenvalue_name_label;
    QLabel* TextLabel3;
    QLabel* m_eigenvalue_label;
    QLabel* TextLabel2;
    QLabel* m_wrongLimits_label;

protected:
    QVBoxLayout* EigenListViewBaseLayout;
    QVBoxLayout* Layout6;
    QVBoxLayout* Layout4;
    QHBoxLayout* Layout3;
    QHBoxLayout* Layout8;
    QGridLayout* Layout7;
};

#endif // EIGENLISTVIEWBASE_H
