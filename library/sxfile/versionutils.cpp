/*
    Copyright (C) SourceXtreme, Inc. <oss@sourcextreme.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
#include "versionutils.h"
#include "xdiff.h"
#include <QFile>
#include <QTextStream>
#include <QDataStream>

#include <qdebug.h>


#define XDLT_STD_BLKSIZE (1024 * 8)

class VersionUtilsPrivate
{
public:
	memallocator_t malt;
};

static void *wrap_malloc(void *priv, unsigned int size)
{
	Q_UNUSED( priv );
        return malloc(size);
}


static void wrap_free(void *priv, void *ptr)
{
	Q_UNUSED( priv );
        free(ptr);
}


static void *wrap_realloc(void *priv, void *ptr, unsigned int size)
{
	Q_UNUSED( priv );
        return realloc(ptr, size);
}

static int xdlt_outds(void *priv, mmbuffer_t *mb, int nbuf)
{
        for (int idx = 0; idx < nbuf; idx++)
		((QDataStream*)priv)->writeRawData(mb[idx].ptr, mb[idx].size) ;
        return 0;
}

static int xdlt_outts(void *priv, mmbuffer_t *mb, int nbuf)
{
        for (int idx = 0; idx < nbuf; idx++)
		(*(QTextStream*)priv) << QByteArray(mb[idx].ptr, mb[idx].size);
        return 0;
}


int init_mmfile( QFile *file, mmfile_t *mmfile )
{
	if (xdl_init_mmfile(mmfile, XDLT_STD_BLKSIZE, XDL_MMF_ATOMIC) < 0)
	{
		qDebug("failed to init mmfile");
		return -1;
	}

	if( !file->isOpen() )
	{
		if( !file->open( QIODevice::ReadWrite ) )
		{
			qDebug("failed to read input file");
			return -2;
		}
	}

	char *blk = (char *) xdl_mmfile_writeallocate(mmfile, file->size() );
	if ( blk == 0 )
	{
		xdl_free_mmfile(mmfile);
		qDebug("Failed to allocate mmfile");
		return -3;
	}

	if (file->read( blk, (size_t) file->size() ) != (size_t) file->size() )
	{
		xdl_free_mmfile(mmfile);
		qDebug() << "Failed to memmap mmfile" << file->fileName();
		return -4;
	}

	return 0;
}

bool VersionUtils::binaryPatchQFile( QFile *input, QFile *patch, QFile *output )
{
	mmfile_t mf1,mf2;
	bool success = false;
	if( init_mmfile( input, &mf1 ) < 0 || init_mmfile( patch, &mf2 ) < 0 )
	{
		success = false;
	}
	else
	{
		if( output->isOpen() || output->open( QIODevice::ReadWrite ))
		{
			QDataStream outResult( output );
			xdemitcb_t ecb;
			ecb.priv = &outResult;
			ecb.outf = xdlt_outds;

			if( xdl_bpatch(&mf1, &mf2, &ecb) < 0)
				success = false;
			else
				success = true;
		}
		else
			success = false;
		xdl_free_mmfile(&mf2);
		xdl_free_mmfile(&mf1);
	}

// 	output->close();

	return success;
}

bool VersionUtils::binaryDiffQFiles( QFile *inputA, QFile *inputB, QFile *patch )
{
	mmfile_t mf1,mf2;
	bool success = false;

	if( init_mmfile( inputA, &mf1 ) < 0 || init_mmfile( inputB, &mf2 ) < 0 )
	{
		success = false;
	}
	else
	{
		if( patch->isOpen() || patch->open(QIODevice::ReadWrite))
		{

			QDataStream outPutStream( patch );
			xdemitcb_t ecb;
			ecb.priv = &outPutStream;
			ecb.outf = xdlt_outds;

			bdiffparam_t bdp;
			bdp.bsize = 16;

			if (xdl_bdiff(&mf1, &mf2, &bdp, &ecb) < 0)
				success = false;
			else
				success = true;
		}
		else
		{
			success = false;
		}

		xdl_free_mmfile(&mf2);
		xdl_free_mmfile(&mf1);
	}
	return success;
}

VersionUtils::VersionUtils() : d_ptr(new VersionUtilsPrivate)
{
	Q_D(VersionUtils);
	d->malt.priv = 0;
	d->malt.malloc = wrap_malloc;
	d->malt.free = wrap_free;
	d->malt.realloc = wrap_realloc;
	xdl_set_allocator( &(d->malt) );
}

VersionUtils::~VersionUtils()
{

}

bool VersionUtils::binaryPatchFile( const QString &source, const QString &patch, const QString &output )
{
	QFile sourceFile( source );
	QFile binaryPatchFiles( patch );
	QFile outputFile( output );
	return binaryPatchQFile( &sourceFile, &binaryPatchFiles, &outputFile );
}

bool VersionUtils::binaryDiffFiles( const QString &fileOne, const QString &fileTwo, const QString &output )
{
	QFile fileOneFile( fileOne );
	QFile fileTwoFile( fileTwo );
	QFile outputFile( output );
	return binaryDiffQFiles( &fileOneFile, &fileTwoFile, &outputFile );
}

bool VersionUtils::filesIdentical( const QString &fileOne, const QString &fileTwo )
{
	bool success = false;
	mmfile_t mf1,mf2;
	QFile fileOneFile( fileOne );
	QFile fileTwoFile( fileTwo );
	if( init_mmfile( &fileOneFile, &mf1 ) < 0 || init_mmfile( &fileTwoFile, &mf2 ) < 0 )
		return false;

	if( xdl_mmfile_cmp( &mf1, &mf2 ) == 0)
		success = true;
	else
		success = false;

	xdl_free_mmfile(&mf2);
	xdl_free_mmfile(&mf1);
	fileOneFile.close();
	fileTwoFile.close();

	return success;

}


bool VersionUtils::diffQFiles( QFile *inputA, QFile *inputB, QFile *patch )
{
	mmfile_t mf1,mf2;
	bool success = false;

	if( init_mmfile( inputA, &mf1 ) < 0 || init_mmfile( inputB, &mf2 ) < 0 )
	{
		success = false;
	}
	else
	{
		if( patch->isOpen() || patch->open(QIODevice::ReadWrite))
		{

			QTextStream outPutStream( patch );
			xdemitcb_t ecb;
			ecb.priv = &outPutStream;
			ecb.outf = xdlt_outts;

			xpparam_t xpp;
// 			xpp.flags = XDF_NEED_MINIMAL;

			xdemitconf_t dp;
			dp.ctxlen = 3;

			if (xdl_diff(&mf1, &mf2, &xpp, &dp, &ecb) < 0)
				success = false;
			else
				success = true;
		}
		else
		{
			success = false;
		}

		xdl_free_mmfile(&mf2);
		xdl_free_mmfile(&mf1);
	}
	return success;
}

bool VersionUtils::diffFiles( const QString &fileOne, const QString &fileTwo, const QString &output )
{
	QFile fileOneFile( fileOne );
	QFile fileTwoFile( fileTwo );
	QFile outputFile( output );
	return diffQFiles( &fileOneFile, &fileTwoFile, &outputFile );
}

bool VersionUtils::patchQFile( QFile *input, QFile *patch, QFile *output, QFile *reject )
{
	mmfile_t mf1,mf2;
	bool success = false;
	if( init_mmfile( input, &mf1 ) < 0 || init_mmfile( patch, &mf2 ) < 0 )
	{
		success = false;
	}
	else
	{
		if(( output->isOpen() || output->open( QIODevice::ReadWrite )) &&
			( reject->isOpen() || reject->open( QIODevice::ReadWrite )) )
		{

			QTextStream outResult( output );
			xdemitcb_t ecb;
			ecb.priv = &outResult;
			ecb.outf = xdlt_outts;

			QTextStream rejResult( reject );
			xdemitcb_t ecbrj;
			ecbrj.priv = &rejResult;
			ecbrj.outf = xdlt_outts;

			if( xdl_patch(&mf1, &mf2, XDL_PATCH_NORMAL, &ecb, &ecbrj) < 0)
				success = false;
			else
				success = true;
		}
		else
			success = false;
		xdl_free_mmfile(&mf2);
		xdl_free_mmfile(&mf1);
	}

	return success;
}

bool VersionUtils::patchFile( const QString &fileOne, const QString &patch, const QString &result, const QString &reject )
{
	QFile fileOneFile( fileOne );
	QFile patchFile( patch );
	QFile outputFile( result );
	QFile rejectFile( reject );
	return patchQFile( &fileOneFile, &patchFile, &outputFile, &rejectFile );
}