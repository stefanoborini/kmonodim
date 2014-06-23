/****************************************************************************
** Form interface generated from reading ui file 'varshni.ui'
**
** Created: Wed Feb 13 14:03:56 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef VARSHNIBASE_H
#define VARSHNIBASE_H

#include <qvariant.h>
#include <qdialog.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QGroupBox;
class QLabel;
class QLineEdit;
class QPushButton;

class VarshniBase : public QDialog
{ 
    Q_OBJECT

public:
    VarshniBase( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~VarshniBase();

    QGroupBox* GroupBox3;
    QGroupBox* GroupBox1;
    QLabel* TextLabel3_2;
    QLabel* TextLabel3;
    QLineEdit* m_highIntegration_edit;
    QLabel* TextLabel4;
    QLabel* TextLabel8;
    QLineEdit* m_lowIntegration_edit;
    QLineEdit* m_particleMass_edit;
    QLabel* TextLabel2_2;
    QLabel* TextLabel1;
    QLabel* TextLabel2;
    QLineEdit* m_numPoints_edit;
    QLineEdit* m_eigenNumber_edit;
    QLabel* TextLabel1_3;
    QGroupBox* GroupBox2;
    QLabel* TextLabel1_2;
    QLabel* TextLabel6_2;
    QLabel* TextLabel5_2;
    QLabel* TextLabel5;
    QLabel* TextLabel7;
    QLabel* TextLabel4_2;
    QLineEdit* m_rotFactor_edit;
    QLineEdit* m_eqDistance_edit;
    QLineEdit* m_alpha_edit;
    QLabel* TextLabel6;
    QLineEdit* m_de_edit;
    QPushButton* m_recalcButton;
    QPushButton* m_closeButton;

protected slots:
    virtual void slotClose();
    virtual void slotDoCalc();
    virtual void slotTextChanged();

protected:
    QVBoxLayout* VarshniBaseLayout;
    QVBoxLayout* GroupBox3Layout;
    QVBoxLayout* Layout14;
    QHBoxLayout* Layout13;
    QVBoxLayout* GroupBox1Layout;
    QGridLayout* Layout11;
    QVBoxLayout* GroupBox2Layout;
    QGridLayout* Layout12;
    QHBoxLayout* Layout6;
};

#endif // VARSHNIBASE_H
