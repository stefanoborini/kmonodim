#ifndef ZIPFILE_H
#define ZIPFILE_H

#include "qiodevice.h"
#include "qstring.h"
#include <stdio.h>

class QDir;


class ZipFile : public QIODevice
{
public:
    ZipFile();
    ZipFile( const QString &name );
   ~ZipFile();

    QString	name()	const;
    void	setName( const QString &name );

    typedef QCString (*EncoderFn)( const QString &fileName );
    typedef QString (*DecoderFn)( const QCString &localfileName );
    static QCString encodeName( const QString &fileName );
    static QString decodeName( const QCString &localFileName );
    static void setEncodingFunction( EncoderFn );
    static void setDecodingFunction( DecoderFn );

    bool	exists()   const;
    static bool exists( const QString &fileName );

    bool	remove();
    static bool remove( const QString &fileName );

    bool	open( int );
    bool	open( int, FILE * );
    bool	open( int, int );
    void	close();
    void	flush();

    uint	size()	const;
    int		at()	const;
    bool	at( int );
    bool	atEnd() const;

    int		readBlock( char *data, uint len );
    int		writeBlock( const char *data, uint len );
    int		writeBlock( const QByteArray& data )
		    { return QIODevice::writeBlock(data); }
    int		readLine( char *data, uint maxlen );
    int		readLine( QString &, uint maxlen );

    int		getch();
    int		putch( int );
    int		ungetch( int );

    int		handle() const;

protected:
    QString	fn;
    FILE       *fh;
    int		fd;
    int		length;
    bool	ext_f;
    void * 	d;

private:
    void	init();
    QCString ungetchBuffer;

private:
    QFile( const QFile & );
    QFile &operator=( const QFile & );
};


inline QString QFile::name() const
{ return fn; }

inline int QFile::at() const
{ return ioIndex; }


#endif 
