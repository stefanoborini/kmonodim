#include "qfile.h"

ZipFile::ZipFile()
{
    init();
}

ZipFile::ZipFile( const QString &name )
    : fn(name)
{
    init();
}

ZipFile::~ZipFile()
{
    close();
}

void ZipFile::init()
{
    setFlags( IO_Direct );
    setStatus( IO_Ok );
    fh	   = 0;
    fd	   = 0;
    length = 0;
    ioIndex = 0;
    ext_f  = FALSE;
}


void ZipFile::setName( const QString &name )
{
    if ( isOpen() ) {
	close();
    }
    fn = name;
}

bool ZipFile::exists() const
{
	return ::access( fn, F_OK );
}

bool ZipFile::exists( const QString &fileName )
{
	return ::access( fileName, F_OK );
}

bool ZipFile::remove()
{
    close();
    return remove( fn );
}

#if defined(_OS_MAC_) || defined(_OS_MSDOS_) || defined(_OS_WIN32_) || defined(_OS_OS2_)
# define HAS_TEXT_FILEMODE
#endif
#if defined(O_NONBLOCK)
# define HAS_ASYNC_FILEMODE
# define OPEN_ASYNC O_NONBLOCK
#elif defined(O_NDELAY)
# define HAS_ASYNC_FILEMODE
# define OPEN_ASYNC O_NDELAY
#endif

void QFile::flush()
{
    if ( isOpen() && fh )
	fflush( fh );
}

/*!
  Returns TRUE if the end of file has been reached, otherwise FALSE.
  \sa size()
*/

bool QFile::atEnd() const
{
    if ( !isOpen() ) {
#if defined(CHECK_STATE)
	qWarning( "QFile::atEnd: File is not open" );
#endif
	return FALSE;
    }
    if ( isDirectAccess() && !isTranslated() ) {
	if ( at() < length )
	    return FALSE;
    }
    return QIODevice::atEnd();
}

/*!
  Reads a line of text.

  Reads bytes from the file until end-of-line is reached, or up to \a
  maxlen bytes, and returns the number of bytes read, or -1 in case of
  error.  The terminating newline is not stripped.

  This function is efficient only for buffered files.  Avoid
  readLine() for files that have been opened with the \c IO_Raw
  flag.

  \sa readBlock(), QTextStream::readLine()
*/

int QFile::readLine( char *p, uint maxlen )
{
    if ( maxlen == 0 )				// application bug?
	return 0;
#if defined(CHECK_STATE)
    CHECK_PTR( p );
    if ( !isOpen() ) {				// file not open
	qWarning( "QFile::readLine: File not open" );
	return -1;
    }
    if ( !isReadable() ) {			// reading not permitted
	qWarning( "QFile::readLine: Read operation not permitted" );
	return -1;
    }
#endif
    int nread;					// number of bytes read
    if ( isRaw() ) {				// raw file
	nread = QIODevice::readLine( p, maxlen );
    } else {					// buffered file
	p = fgets( p, maxlen, fh );
	if ( p ) {
	    nread = qstrlen( p );
	    if ( !isSequentialAccess() )
		ioIndex += nread;
	} else {
	    nread = -1;
	    setStatus(IO_ReadError);
	}
    }
    return nread;
}


/*!
  Reads a line of text.

  Reads bytes from the file until end-of-line is reached, or up to \a
  maxlen bytes, and returns the number of bytes read, or -1 in case of
  error.  The terminating newline is not stripped.

  This function is efficient only for buffered files.  Avoid
  readLine() for files that have been opened with the \c IO_Raw
  flag.

  Note that the string is read as plain Latin1 bytes, not Unicode.

  \sa readBlock(), QTextStream::readLine()
*/

int QFile::readLine( QString& s, uint maxlen )
{
    QByteArray ba(maxlen);
    int l = readLine(ba.data(),maxlen);
    if ( l >= 0 ) {
	ba.truncate(l);
	s = QString(ba);
    }
    return l;
}


/*!
  Reads a single byte/character from the file.

  Returns the byte/character read, or -1 if the end of the file has been
  reached.

  \sa putch(), ungetch()
*/

int QFile::getch()
{
#if defined(CHECK_STATE)
    if ( !isOpen() ) {				// file not open
	qWarning( "QFile::getch: File not open" );
	return EOF;
    }
    if ( !isReadable() ) {			// reading not permitted
	qWarning( "QFile::getch: Read operation not permitted" );
	return EOF;
    }
#endif

    int ch;

    if ( !ungetchBuffer.isEmpty() ) {
	int len = ungetchBuffer.length();
	ch = ungetchBuffer[ len-1 ];
	ungetchBuffer.truncate( len - 1 );
	return ch;
    }

    if ( isRaw() ) {				// raw file (inefficient)
	char buf[1];
	ch = readBlock( buf, 1 ) == 1 ? buf[0] : EOF;
    } else {					// buffered file
	if ( (ch = getc( fh )) != EOF )
	    if ( !isSequentialAccess() )
		ioIndex++;
	else
	    setStatus(IO_ReadError);
    }
    return ch;
}

/*!
  \fn int QFile::writeBlock( const QByteArray& data )
  \reimp
  \internal
  Should be removed in 3.0
*/

/*!
  Writes the character \e ch to the file.

  Returns \e ch, or -1 if some error occurred.

  \sa getch(), ungetch()
*/

int QFile::putch( int ch )
{
#if defined(CHECK_STATE)
    if ( !isOpen() ) {				// file not open
	qWarning( "QFile::putch: File not open" );
	return EOF;
    }
    if ( !isWritable() ) {			// writing not permitted
	qWarning( "QFile::putch: Write operation not permitted" );
	return EOF;
    }
#endif
    if ( isRaw() ) {				// raw file (inefficient)
	char buf[1];
	buf[0] = ch;
	ch = writeBlock( buf, 1 ) == 1 ? ch : EOF;
    } else {					// buffered file
	if ( (ch = putc( ch, fh )) != EOF ) {
	    if ( !isSequentialAccess() )
		ioIndex++;
	    if ( ioIndex > length )		// update file length
		length = ioIndex;
	} else {
	    setStatus(IO_WriteError);
	}
    }
    return ch;
}

/*!
  Puts the character \e ch back into the file and decrements the index if it
  is not zero.

  This function is normally called to "undo" a getch() operation.

  Returns \e ch, or -1 if some error occurred.

  \sa getch(), putch()
*/

int QFile::ungetch( int ch )
{
#if defined(CHECK_STATE)
    if ( !isOpen() ) {				// file not open
	qWarning( "QFile::ungetch: File not open" );
	return EOF;
    }
    if ( !isReadable() ) {			// reading not permitted
	qWarning( "QFile::ungetch: Read operation not permitted" );
	return EOF;
    }
#endif
    if ( ch == EOF )				// cannot unget EOF
	return ch;

    if ( isSequentialAccess() && !fh) {
	// pipe or similar => we cannot ungetch, so do it manually
	ungetchBuffer +=ch;
	return ch;
    }

    if ( isRaw() ) {				// raw file (very inefficient)
	char buf[1];
	at( ioIndex-1 );
	buf[0] = ch;
	if ( writeBlock(buf, 1) == 1 )
	    at ( ioIndex-1 );
	else
	    ch = EOF;
    } else {					// buffered file
	if ( (ch = ungetc(ch, fh)) != EOF )
	    if ( !isSequentialAccess() )
		ioIndex--;
	else
	    setStatus( IO_ReadError );
    }
    return ch;
}


static QCString locale_encoder( const QString &fileName )
{
    return fileName.local8Bit();
}


static QFile::EncoderFn encoder = locale_encoder;

/*!
  When you use QFile, QFileInfo, and QDir to access the filesystem
  with Qt, you can use Unicode filenames.  On Unix, these filenames
  are converted to an 8-bit encoding.  If you want to do your own
  file I/O on Unix, you should convert the filename using this
  function.  On Windows NT, Unicode filenames are supported directly
  in the filesystem and this function should be avoided. On Windows 95,
  non-Latin1 locales are not supported at this time.

  By default, this function converts to the local 8-bit encoding
  determined by the user's locale.  This is sufficient for
  filenames that the user chooses.  Filenames hard-coded into the
  application should only use 7-bit ASCII filename characters.

  The conversion scheme can be changed using setEncodingFunction().
  This might be useful if you wish to give the user an option to
  store in filenames in UTF-8, etc., but beware that such filenames
  would probably then be unrecognizable when seen by other programs.

  \sa decodeName()
*/

QCString QFile::encodeName( const QString &fileName )
{
    return (*encoder)(fileName);
}

/*!
  \enum QFile::EncoderFn

  This is used by QFile::setEncodingFunction().
*/

/*!
  Sets the function for encoding Unicode filenames.
  The default encodes in the locale-specific 8-bit encoding.

  \sa encodeName()
*/
void QFile::setEncodingFunction( EncoderFn f )
{
    encoder = f;
}

static
QString locale_decoder( const QCString &localFileName )
{
    return QString::fromLocal8Bit(localFileName);
}

static QFile::DecoderFn decoder = locale_decoder;

/*!
  This does the reverse of QFile::encodeName().

  \sa setDecodingFunction()
*/
QString QFile::decodeName( const QCString &localFileName )
{
    return (*decoder)(localFileName);
}

/*!
  \enum QFile::DecoderFn

  This is used by QFile::setDecodingFunction().
*/

/*!
  Sets the function for decoding 8-bit filenames.
  The default uses the locale-specific 8-bit encoding.

  \sa encodeName(), decodeName()
*/

void QFile::setDecodingFunction( DecoderFn f )
{
    decoder = f;
}
