/****************************************************************************
** Form implementation generated from reading ui file 'eigenlistview.ui'
**
** Created: Mon Nov 18 16:49:11 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "eigenlistviewbase.h"

#include <qheader.h>
#include <qlabel.h>
#include <qlistview.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qvariant.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/* 
 *  Constructs a EigenListViewBase which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 */
EigenListViewBase::EigenListViewBase( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "EigenListViewBase" );
    resize( 242, 450 ); 
    setCaption( tr( "Form1" ) );
    EigenListViewBaseLayout = new QVBoxLayout( this ); 
    EigenListViewBaseLayout->setSpacing( 6 );
    EigenListViewBaseLayout->setMargin( 11 );

    Layout6 = new QVBoxLayout; 
    Layout6->setSpacing( 6 );
    Layout6->setMargin( 0 );

    Layout4 = new QVBoxLayout; 
    Layout4->setSpacing( 6 );
    Layout4->setMargin( 0 );

    m_listView = new QListView( this, "m_listView" );
    m_listView->addColumn( tr( "Eigenvalue" ) );
    m_listView->addColumn( tr( "Color" ) );
    m_listView->header()->setClickEnabled( FALSE, m_listView->header()->count() - 1 );
    m_listView->header()->setResizeEnabled( FALSE, m_listView->header()->count() - 1 );
    m_listView->addColumn( tr( "Active" ) );
    m_listView->header()->setClickEnabled( FALSE, m_listView->header()->count() - 1 );
    m_listView->header()->setResizeEnabled( FALSE, m_listView->header()->count() - 1 );
    m_listView->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, m_listView->sizePolicy().hasHeightForWidth() ) );
    m_listView->setMouseTracking( FALSE );
    m_listView->setFrameShape( QListView::StyledPanel );
    m_listView->setFrameShadow( QListView::Sunken );
    m_listView->setResizePolicy( QScrollView::Manual );
    m_listView->setSelectionMode( QListView::Multi );
    Layout4->addWidget( m_listView );

    Layout3 = new QHBoxLayout; 
    Layout3->setSpacing( 6 );
    Layout3->setMargin( 0 );

    m_setUniqueColorButton = new QPushButton( this, "m_setUniqueColorButton" );
    m_setUniqueColorButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, m_setUniqueColorButton->sizePolicy().hasHeightForWidth() ) );
    m_setUniqueColorButton->setText( tr( "Set unique color" ) );
    Layout3->addWidget( m_setUniqueColorButton );

    m_setActiveButton = new QPushButton( this, "m_setActiveButton" );
    m_setActiveButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, m_setActiveButton->sizePolicy().hasHeightForWidth() ) );
    m_setActiveButton->setText( tr( "dummy" ) );
    Layout3->addWidget( m_setActiveButton );
    Layout4->addLayout( Layout3 );
    Layout6->addLayout( Layout4 );

    Layout8 = new QHBoxLayout; 
    Layout8->setSpacing( 6 );
    Layout8->setMargin( 0 );

    Layout7 = new QGridLayout; 
    Layout7->setSpacing( 6 );
    Layout7->setMargin( 0 );

    m_meanKinetic_label = new QLabel( this, "m_meanKinetic_label" );
    m_meanKinetic_label->setText( tr( "dummy" ) );

    Layout7->addWidget( m_meanKinetic_label, 3, 1 );

    m_meanPosition_label = new QLabel( this, "m_meanPosition_label" );
    m_meanPosition_label->setText( tr( "dummy" ) );

    Layout7->addWidget( m_meanPosition_label, 2, 1 );

    TextLabel1 = new QLabel( this, "TextLabel1" );
    TextLabel1->setText( tr( "Mean Position" ) );

    Layout7->addWidget( TextLabel1, 2, 0 );

    TextLabel4 = new QLabel( this, "TextLabel4" );
    TextLabel4->setText( tr( "Mean Potential" ) );

    Layout7->addWidget( TextLabel4, 4, 0 );

    m_extrapolatedEigenvalue_label = new QLabel( this, "m_extrapolatedEigenvalue_label" );
    m_extrapolatedEigenvalue_label->setText( tr( "dummy" ) );

    Layout7->addWidget( m_extrapolatedEigenvalue_label, 1, 1 );

    m_meanPotential_label = new QLabel( this, "m_meanPotential_label" );
    m_meanPotential_label->setText( tr( "dummy" ) );

    Layout7->addWidget( m_meanPotential_label, 4, 1 );

    m_extrapolatedEigenvalue_name_label = new QLabel( this, "m_extrapolatedEigenvalue_name_label" );
    m_extrapolatedEigenvalue_name_label->setText( tr( "Extrapolated" ) );

    Layout7->addWidget( m_extrapolatedEigenvalue_name_label, 1, 0 );

    TextLabel3 = new QLabel( this, "TextLabel3" );
    TextLabel3->setText( tr( "Eigenvalue" ) );

    Layout7->addWidget( TextLabel3, 0, 0 );

    m_eigenvalue_label = new QLabel( this, "m_eigenvalue_label" );
    m_eigenvalue_label->setText( tr( "dummy" ) );

    Layout7->addWidget( m_eigenvalue_label, 0, 1 );

    TextLabel2 = new QLabel( this, "TextLabel2" );
    TextLabel2->setText( tr( "Mean Kinetic" ) );

    Layout7->addWidget( TextLabel2, 3, 0 );
    Layout8->addLayout( Layout7 );
    QSpacerItem* spacer = new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum );
    Layout8->addItem( spacer );
    Layout6->addLayout( Layout8 );

    m_wrongLimits_label = new QLabel( this, "m_wrongLimits_label" );
    m_wrongLimits_label->setText( tr( "<qt>\n"
"<b><i><font color=\"red\">Warning</font></i></b><br/>\n"
"These data could be faked.<br/>\n"
"The eigenfunction integral is <br/>\n"
"not approx. zero in a small <br/>\n"
"range near the integration limits.<br/>\n"
"<b><i><font color=\"blue\">Solution</font></i></b><br/>\n"
"- Increase the integration range<br/>\n"
"</qt>" ) );
    m_wrongLimits_label->setTextFormat( QLabel::RichText );
    Layout6->addWidget( m_wrongLimits_label );
    QSpacerItem* spacer_2 = new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum );
    Layout6->addItem( spacer_2 );
    EigenListViewBaseLayout->addLayout( Layout6 );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
EigenListViewBase::~EigenListViewBase()
{
    // no need to delete child widgets, Qt does it all for us
}

