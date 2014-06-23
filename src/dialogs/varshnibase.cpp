/****************************************************************************
** Form implementation generated from reading ui file 'varshni.ui'
**
** Created: Wed Feb 13 14:03:56 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "varshnibase.h"

#include <qgroupbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qvariant.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/* 
 *  Constructs a VarshniBase which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
VarshniBase::VarshniBase( QWidget* parent,  const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "VarshniBase" );
    resize( 659, 348 ); 
    setCaption( tr( "Varshni potential" ) );
    VarshniBaseLayout = new QVBoxLayout( this ); 
    VarshniBaseLayout->setSpacing( 6 );
    VarshniBaseLayout->setMargin( 11 );

    GroupBox3 = new QGroupBox( this, "GroupBox3" );
    GroupBox3->setTitle( tr( "Varshni" ) );
    GroupBox3->setColumnLayout(0, Qt::Vertical );
    GroupBox3->layout()->setSpacing( 0 );
    GroupBox3->layout()->setMargin( 0 );
    GroupBox3Layout = new QVBoxLayout( GroupBox3->layout() );
    GroupBox3Layout->setAlignment( Qt::AlignTop );
    GroupBox3Layout->setSpacing( 6 );
    GroupBox3Layout->setMargin( 11 );

    Layout14 = new QVBoxLayout; 
    Layout14->setSpacing( 6 );
    Layout14->setMargin( 0 );

    Layout13 = new QHBoxLayout; 
    Layout13->setSpacing( 6 );
    Layout13->setMargin( 0 );

    GroupBox1 = new QGroupBox( GroupBox3, "GroupBox1" );
    GroupBox1->setTitle( tr( "Data" ) );
    GroupBox1->setColumnLayout(0, Qt::Vertical );
    GroupBox1->layout()->setSpacing( 0 );
    GroupBox1->layout()->setMargin( 0 );
    GroupBox1Layout = new QVBoxLayout( GroupBox1->layout() );
    GroupBox1Layout->setAlignment( Qt::AlignTop );
    GroupBox1Layout->setSpacing( 6 );
    GroupBox1Layout->setMargin( 11 );

    Layout11 = new QGridLayout; 
    Layout11->setSpacing( 6 );
    Layout11->setMargin( 0 );

    TextLabel3_2 = new QLabel( GroupBox1, "TextLabel3_2" );
    TextLabel3_2->setText( tr( "bohr" ) );

    Layout11->addWidget( TextLabel3_2, 4, 2 );

    TextLabel3 = new QLabel( GroupBox1, "TextLabel3" );
    TextLabel3->setText( tr( "Higher integration limit" ) );

    Layout11->addWidget( TextLabel3, 4, 0 );

    m_highIntegration_edit = new QLineEdit( GroupBox1, "m_highIntegration_edit" );
    m_highIntegration_edit->setCursor( QCursor( 0 ) );

    Layout11->addWidget( m_highIntegration_edit, 4, 1 );

    TextLabel4 = new QLabel( GroupBox1, "TextLabel4" );
    TextLabel4->setText( tr( "Number of eigenvalues" ) );

    Layout11->addWidget( TextLabel4, 1, 0 );

    TextLabel8 = new QLabel( GroupBox1, "TextLabel8" );
    TextLabel8->setText( tr( "Particle mass" ) );

    Layout11->addWidget( TextLabel8, 0, 0 );

    m_lowIntegration_edit = new QLineEdit( GroupBox1, "m_lowIntegration_edit" );
    m_lowIntegration_edit->setCursor( QCursor( 0 ) );

    Layout11->addWidget( m_lowIntegration_edit, 3, 1 );

    m_particleMass_edit = new QLineEdit( GroupBox1, "m_particleMass_edit" );
    m_particleMass_edit->setCursor( QCursor( 0 ) );

    Layout11->addWidget( m_particleMass_edit, 0, 1 );

    TextLabel2_2 = new QLabel( GroupBox1, "TextLabel2_2" );
    TextLabel2_2->setText( tr( "bohr" ) );

    Layout11->addWidget( TextLabel2_2, 3, 2 );

    TextLabel1 = new QLabel( GroupBox1, "TextLabel1" );
    TextLabel1->setText( tr( "Number of points" ) );

    Layout11->addWidget( TextLabel1, 2, 0 );

    TextLabel2 = new QLabel( GroupBox1, "TextLabel2" );
    TextLabel2->setText( tr( "Lower integration limit" ) );

    Layout11->addWidget( TextLabel2, 3, 0 );

    m_numPoints_edit = new QLineEdit( GroupBox1, "m_numPoints_edit" );
    m_numPoints_edit->setCursor( QCursor( 0 ) );
    QToolTip::add(  m_numPoints_edit, tr( "" ) );

    Layout11->addWidget( m_numPoints_edit, 2, 1 );

    m_eigenNumber_edit = new QLineEdit( GroupBox1, "m_eigenNumber_edit" );
    m_eigenNumber_edit->setCursor( QCursor( 0 ) );

    Layout11->addWidget( m_eigenNumber_edit, 1, 1 );

    TextLabel1_3 = new QLabel( GroupBox1, "TextLabel1_3" );
    TextLabel1_3->setText( tr( "em" ) );

    Layout11->addWidget( TextLabel1_3, 0, 2 );
    GroupBox1Layout->addLayout( Layout11 );
    Layout13->addWidget( GroupBox1 );

    GroupBox2 = new QGroupBox( GroupBox3, "GroupBox2" );
    GroupBox2->setTitle( tr( "Potential" ) );
    GroupBox2->setColumnLayout(0, Qt::Vertical );
    GroupBox2->layout()->setSpacing( 0 );
    GroupBox2->layout()->setMargin( 0 );
    GroupBox2Layout = new QVBoxLayout( GroupBox2->layout() );
    GroupBox2Layout->setAlignment( Qt::AlignTop );
    GroupBox2Layout->setSpacing( 6 );
    GroupBox2Layout->setMargin( 11 );

    Layout12 = new QGridLayout; 
    Layout12->setSpacing( 6 );
    Layout12->setMargin( 0 );

    TextLabel1_2 = new QLabel( GroupBox2, "TextLabel1_2" );
    TextLabel1_2->setText( tr( "Rot. factor" ) );

    Layout12->addWidget( TextLabel1_2, 3, 0 );

    TextLabel6_2 = new QLabel( GroupBox2, "TextLabel6_2" );
    TextLabel6_2->setText( tr( "bohr" ) );

    Layout12->addWidget( TextLabel6_2, 2, 2 );

    TextLabel5_2 = new QLabel( GroupBox2, "TextLabel5_2" );
    TextLabel5_2->setText( tr( "1/bohr^2" ) );

    Layout12->addWidget( TextLabel5_2, 1, 2 );

    TextLabel5 = new QLabel( GroupBox2, "TextLabel5" );
    TextLabel5->setText( tr( "De" ) );

    Layout12->addWidget( TextLabel5, 0, 0 );

    TextLabel7 = new QLabel( GroupBox2, "TextLabel7" );
    TextLabel7->setText( tr( "Eq. distance" ) );

    Layout12->addWidget( TextLabel7, 2, 0 );

    TextLabel4_2 = new QLabel( GroupBox2, "TextLabel4_2" );
    TextLabel4_2->setText( tr( "hartree" ) );

    Layout12->addWidget( TextLabel4_2, 0, 2 );

    m_rotFactor_edit = new QLineEdit( GroupBox2, "m_rotFactor_edit" );

    Layout12->addWidget( m_rotFactor_edit, 3, 1 );

    m_eqDistance_edit = new QLineEdit( GroupBox2, "m_eqDistance_edit" );
    m_eqDistance_edit->setCursor( QCursor( 0 ) );

    Layout12->addWidget( m_eqDistance_edit, 2, 1 );

    m_alpha_edit = new QLineEdit( GroupBox2, "m_alpha_edit" );
    m_alpha_edit->setCursor( QCursor( 0 ) );

    Layout12->addWidget( m_alpha_edit, 1, 1 );

    TextLabel6 = new QLabel( GroupBox2, "TextLabel6" );
    TextLabel6->setText( tr( "Alpha" ) );

    Layout12->addWidget( TextLabel6, 1, 0 );

    m_de_edit = new QLineEdit( GroupBox2, "m_de_edit" );
    m_de_edit->setCursor( QCursor( 0 ) );

    Layout12->addWidget( m_de_edit, 0, 1 );
    GroupBox2Layout->addLayout( Layout12 );
    Layout13->addWidget( GroupBox2 );
    Layout14->addLayout( Layout13 );
    QSpacerItem* spacer = new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding );
    Layout14->addItem( spacer );

    Layout6 = new QHBoxLayout; 
    Layout6->setSpacing( 6 );
    Layout6->setMargin( 0 );
    QSpacerItem* spacer_2 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout6->addItem( spacer_2 );

    m_recalcButton = new QPushButton( GroupBox3, "m_recalcButton" );
    m_recalcButton->setCursor( QCursor( 0 ) );
    m_recalcButton->setText( tr( "Recalc" ) );
    m_recalcButton->setDefault( TRUE );
    m_recalcButton->setFlat( FALSE );
    QToolTip::add(  m_recalcButton, tr( "Start recalculation" ) );
    Layout6->addWidget( m_recalcButton );
    QSpacerItem* spacer_3 = new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum );
    Layout6->addItem( spacer_3 );

    m_closeButton = new QPushButton( GroupBox3, "m_closeButton" );
    m_closeButton->setCursor( QCursor( 0 ) );
    m_closeButton->setText( tr( "Close" ) );
    m_closeButton->setAutoDefault( FALSE );
    QToolTip::add(  m_closeButton, tr( "Close the dialog" ) );
    Layout6->addWidget( m_closeButton );
    Layout14->addLayout( Layout6 );
    GroupBox3Layout->addLayout( Layout14 );
    VarshniBaseLayout->addWidget( GroupBox3 );

    // signals and slots connections
    connect( m_numPoints_edit, SIGNAL( textChanged(const QString&) ), this, SLOT( slotTextChanged() ) );
    connect( m_lowIntegration_edit, SIGNAL( textChanged(const QString&) ), this, SLOT( slotTextChanged() ) );
    connect( m_highIntegration_edit, SIGNAL( textChanged(const QString&) ), this, SLOT( slotTextChanged() ) );
    connect( m_eigenNumber_edit, SIGNAL( textChanged(const QString&) ), this, SLOT( slotTextChanged() ) );
    connect( m_de_edit, SIGNAL( textChanged(const QString&) ), this, SLOT( slotTextChanged() ) );
    connect( m_alpha_edit, SIGNAL( textChanged(const QString&) ), this, SLOT( slotTextChanged() ) );
    connect( m_eqDistance_edit, SIGNAL( textChanged(const QString&) ), this, SLOT( slotTextChanged() ) );
    connect( m_particleMass_edit, SIGNAL( textChanged(const QString&) ), this, SLOT( slotTextChanged() ) );
    connect( m_recalcButton, SIGNAL( clicked() ), this, SLOT( slotDoCalc() ) );
    connect( m_closeButton, SIGNAL( clicked() ), this, SLOT( slotClose() ) );
    connect( m_rotFactor_edit, SIGNAL( textChanged(const QString&) ), this, SLOT( slotTextChanged() ) );

    // tab order
    setTabOrder( m_particleMass_edit, m_eigenNumber_edit );
    setTabOrder( m_eigenNumber_edit, m_numPoints_edit );
    setTabOrder( m_numPoints_edit, m_lowIntegration_edit );
    setTabOrder( m_lowIntegration_edit, m_highIntegration_edit );
    setTabOrder( m_highIntegration_edit, m_de_edit );
    setTabOrder( m_de_edit, m_alpha_edit );
    setTabOrder( m_alpha_edit, m_eqDistance_edit );
    setTabOrder( m_eqDistance_edit, m_rotFactor_edit );
    setTabOrder( m_rotFactor_edit, m_recalcButton );
    setTabOrder( m_recalcButton, m_closeButton );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
VarshniBase::~VarshniBase()
{
    // no need to delete child widgets, Qt does it all for us
}

void VarshniBase::slotClose()
{
    qWarning( "VarshniBase::slotClose(): Not implemented yet!" );
}

void VarshniBase::slotDoCalc()
{
    qWarning( "VarshniBase::slotDoCalc(): Not implemented yet!" );
}

void VarshniBase::slotTextChanged()
{
    qWarning( "VarshniBase::slotTextChanged(): Not implemented yet!" );
}

