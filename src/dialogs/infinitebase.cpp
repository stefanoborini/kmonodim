/****************************************************************************
** Form implementation generated from reading ui file 'infinite.ui'
**
** Created: Tue Mar 5 15:30:05 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "infinitebase.h"

#include <qgroupbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qvariant.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/* 
 *  Constructs a InfiniteBase which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
InfiniteBase::InfiniteBase( QWidget* parent,  const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "InfiniteBase" );
    resize( 556, 346 ); 
    setCaption( tr( "Infinite Well" ) );
    InfiniteBaseLayout = new QHBoxLayout( this ); 
    InfiniteBaseLayout->setSpacing( 6 );
    InfiniteBaseLayout->setMargin( 11 );

    GroupBox3 = new QGroupBox( this, "GroupBox3" );
    GroupBox3->setTitle( tr( "Infinite well" ) );
    GroupBox3->setColumnLayout(0, Qt::Vertical );
    GroupBox3->layout()->setSpacing( 0 );
    GroupBox3->layout()->setMargin( 0 );
    GroupBox3Layout = new QHBoxLayout( GroupBox3->layout() );
    GroupBox3Layout->setAlignment( Qt::AlignTop );
    GroupBox3Layout->setSpacing( 6 );
    GroupBox3Layout->setMargin( 11 );

    Layout12 = new QVBoxLayout; 
    Layout12->setSpacing( 6 );
    Layout12->setMargin( 0 );

    Layout11 = new QHBoxLayout; 
    Layout11->setSpacing( 6 );
    Layout11->setMargin( 0 );

    GroupBox1 = new QGroupBox( GroupBox3, "GroupBox1" );
    GroupBox1->setTitle( tr( "Data" ) );
    GroupBox1->setColumnLayout(0, Qt::Vertical );
    GroupBox1->layout()->setSpacing( 0 );
    GroupBox1->layout()->setMargin( 0 );
    GroupBox1Layout = new QHBoxLayout( GroupBox1->layout() );
    GroupBox1Layout->setAlignment( Qt::AlignTop );
    GroupBox1Layout->setSpacing( 6 );
    GroupBox1Layout->setMargin( 11 );

    Layout10 = new QGridLayout; 
    Layout10->setSpacing( 6 );
    Layout10->setMargin( 0 );

    TextLabel1 = new QLabel( GroupBox1, "TextLabel1" );
    TextLabel1->setText( tr( "Number of points" ) );

    Layout10->addWidget( TextLabel1, 2, 0 );

    TextLabel7_2 = new QLabel( GroupBox1, "TextLabel7_2" );
    TextLabel7_2->setText( tr( "em" ) );

    Layout10->addWidget( TextLabel7_2, 0, 2 );

    TextLabel8 = new QLabel( GroupBox1, "TextLabel8" );
    TextLabel8->setText( tr( "Particle mass" ) );

    Layout10->addWidget( TextLabel8, 0, 0 );

    TextLabel4 = new QLabel( GroupBox1, "TextLabel4" );
    TextLabel4->setText( tr( "Number of eigenvalues" ) );

    Layout10->addWidget( TextLabel4, 1, 0 );

    m_eigenNumber_edit = new QLineEdit( GroupBox1, "m_eigenNumber_edit" );
    m_eigenNumber_edit->setCursor( QCursor( 0 ) );

    Layout10->addWidget( m_eigenNumber_edit, 1, 1 );

    m_particleMass_edit = new QLineEdit( GroupBox1, "m_particleMass_edit" );
    m_particleMass_edit->setCursor( QCursor( 0 ) );

    Layout10->addWidget( m_particleMass_edit, 0, 1 );

    m_numPoints_edit = new QLineEdit( GroupBox1, "m_numPoints_edit" );
    m_numPoints_edit->setCursor( QCursor( 0 ) );
    QToolTip::add(  m_numPoints_edit, tr( "" ) );

    Layout10->addWidget( m_numPoints_edit, 2, 1 );
    GroupBox1Layout->addLayout( Layout10 );
    Layout11->addWidget( GroupBox1 );

    GroupBox2 = new QGroupBox( GroupBox3, "GroupBox2" );
    GroupBox2->setTitle( tr( "Potential" ) );
    GroupBox2->setColumnLayout(0, Qt::Vertical );
    GroupBox2->layout()->setSpacing( 0 );
    GroupBox2->layout()->setMargin( 0 );
    GroupBox2Layout = new QHBoxLayout( GroupBox2->layout() );
    GroupBox2Layout->setAlignment( Qt::AlignTop );
    GroupBox2Layout->setSpacing( 6 );
    GroupBox2Layout->setMargin( 11 );

    Layout6 = new QGridLayout; 
    Layout6->setSpacing( 6 );
    Layout6->setMargin( 0 );

    TextLabel5 = new QLabel( GroupBox2, "TextLabel5" );
    TextLabel5->setText( tr( "Lower edge" ) );

    Layout6->addWidget( TextLabel5, 0, 0 );

    TextLabel4_2 = new QLabel( GroupBox2, "TextLabel4_2" );
    TextLabel4_2->setText( tr( "bohr" ) );

    Layout6->addWidget( TextLabel4_2, 0, 2 );

    TextLabel6 = new QLabel( GroupBox2, "TextLabel6" );
    TextLabel6->setText( tr( "Higher edge" ) );

    Layout6->addWidget( TextLabel6, 1, 0 );

    TextLabel5_2 = new QLabel( GroupBox2, "TextLabel5_2" );
    TextLabel5_2->setText( tr( "bohr" ) );

    Layout6->addWidget( TextLabel5_2, 1, 2 );

    m_lowEdge_edit = new QLineEdit( GroupBox2, "m_lowEdge_edit" );
    m_lowEdge_edit->setCursor( QCursor( 0 ) );

    Layout6->addWidget( m_lowEdge_edit, 0, 1 );

    m_highEdge_edit = new QLineEdit( GroupBox2, "m_highEdge_edit" );
    m_highEdge_edit->setCursor( QCursor( 0 ) );

    Layout6->addWidget( m_highEdge_edit, 1, 1 );
    GroupBox2Layout->addLayout( Layout6 );
    Layout11->addWidget( GroupBox2 );
    Layout12->addLayout( Layout11 );
    QSpacerItem* spacer = new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding );
    Layout12->addItem( spacer );

    Layout6_2 = new QHBoxLayout; 
    Layout6_2->setSpacing( 6 );
    Layout6_2->setMargin( 0 );
    QSpacerItem* spacer_2 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout6_2->addItem( spacer_2 );

    m_recalcButton = new QPushButton( GroupBox3, "m_recalcButton" );
    m_recalcButton->setCursor( QCursor( 0 ) );
    m_recalcButton->setText( tr( "Recalc" ) );
    m_recalcButton->setDefault( TRUE );
    m_recalcButton->setFlat( FALSE );
    QToolTip::add(  m_recalcButton, tr( "Start recalculation" ) );
    Layout6_2->addWidget( m_recalcButton );
    QSpacerItem* spacer_3 = new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum );
    Layout6_2->addItem( spacer_3 );

    m_closeButton = new QPushButton( GroupBox3, "m_closeButton" );
    m_closeButton->setCursor( QCursor( 0 ) );
    m_closeButton->setText( tr( "Close" ) );
    m_closeButton->setAutoDefault( FALSE );
    QToolTip::add(  m_closeButton, tr( "Close the dialog" ) );
    Layout6_2->addWidget( m_closeButton );
    Layout12->addLayout( Layout6_2 );
    GroupBox3Layout->addLayout( Layout12 );
    InfiniteBaseLayout->addWidget( GroupBox3 );

    // signals and slots connections
    connect( m_numPoints_edit, SIGNAL( textChanged(const QString&) ), this, SLOT( slotTextChanged() ) );
    connect( m_eigenNumber_edit, SIGNAL( textChanged(const QString&) ), this, SLOT( slotTextChanged() ) );
    connect( m_lowEdge_edit, SIGNAL( textChanged(const QString&) ), this, SLOT( slotTextChanged() ) );
    connect( m_highEdge_edit, SIGNAL( textChanged(const QString&) ), this, SLOT( slotTextChanged() ) );
    connect( m_particleMass_edit, SIGNAL( textChanged(const QString&) ), this, SLOT( slotTextChanged() ) );
    connect( m_recalcButton, SIGNAL( clicked() ), this, SLOT( slotDoCalc() ) );
    connect( m_closeButton, SIGNAL( clicked() ), this, SLOT( slotClose() ) );

    // tab order
    setTabOrder( m_particleMass_edit, m_eigenNumber_edit );
    setTabOrder( m_eigenNumber_edit, m_numPoints_edit );
    setTabOrder( m_numPoints_edit, m_lowEdge_edit );
    setTabOrder( m_lowEdge_edit, m_highEdge_edit );
    setTabOrder( m_highEdge_edit, m_recalcButton );
    setTabOrder( m_recalcButton, m_closeButton );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
InfiniteBase::~InfiniteBase()
{
    // no need to delete child widgets, Qt does it all for us
}

void InfiniteBase::slotClose()
{
    qWarning( "InfiniteBase::slotClose(): Not implemented yet!" );
}

void InfiniteBase::slotDoCalc()
{
    qWarning( "InfiniteBase::slotDoCalc(): Not implemented yet!" );
}

void InfiniteBase::slotTextChanged()
{
    qWarning( "InfiniteBase::slotTextChanged(): Not implemented yet!" );
}

