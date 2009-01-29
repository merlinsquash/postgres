/*-------------------------------------------------------------------------
 *
 *	  JOHAB <--> UTF-8
 *
 * Portions Copyright (c) 1996-2003, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * IDENTIFICATION
 *	  $Header: /cvsroot/pgsql/src/backend/utils/mb/conversion_procs/utf8_and_johab/utf8_and_johab.c,v 1.6.4.2 2009/01/29 19:25:14 tgl Exp $
 *
 *-------------------------------------------------------------------------
 */

#include "postgres.h"
#include "fmgr.h"
#include "mb/pg_wchar.h"
#include "../../Unicode/johab_to_utf8.map"
#include "../../Unicode/utf8_to_johab.map"

PG_FUNCTION_INFO_V1(johab_to_utf8);
PG_FUNCTION_INFO_V1(utf8_to_johab);

extern Datum johab_to_utf8(PG_FUNCTION_ARGS);
extern Datum utf8_to_johab(PG_FUNCTION_ARGS);

/* ----------
 * conv_proc(
 *		INTEGER,	-- source encoding id
 *		INTEGER,	-- destination encoding id
 *		CSTRING,	-- source string (null terminated C string)
 *		CSTRING,	-- destination string (null terminated C string)
 *		INTEGER		-- source string length
 * ) returns VOID;
 * ----------
 */
Datum
johab_to_utf8(PG_FUNCTION_ARGS)
{
	unsigned char *src = PG_GETARG_CSTRING(2);
	unsigned char *dest = PG_GETARG_CSTRING(3);
	int			len = PG_GETARG_INT32(4);

	CHECK_ENCODING_CONVERSION_ARGS(PG_JOHAB, PG_UTF8);

	LocalToUtf(src, dest, LUmapJOHAB,
			sizeof(LUmapJOHAB) / sizeof(pg_local_to_utf), PG_JOHAB, len);

	PG_RETURN_VOID();
}

Datum
utf8_to_johab(PG_FUNCTION_ARGS)
{
	unsigned char *src = PG_GETARG_CSTRING(2);
	unsigned char *dest = PG_GETARG_CSTRING(3);
	int			len = PG_GETARG_INT32(4);

	CHECK_ENCODING_CONVERSION_ARGS(PG_UTF8, PG_JOHAB);

	UtfToLocal(src, dest, ULmapJOHAB,
			   sizeof(ULmapJOHAB) / sizeof(pg_utf_to_local), PG_JOHAB, len);

	PG_RETURN_VOID();
}
