/*
    token_defs.h - Part of macxx, a cross assembler family for various micro-processors
    Copyright (C) 2008 David Shepperd

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/******************************************************************************
Change Log

	05-03-2024	- TRG - Added support for TOC (Table of contents) file

******************************************************************************/

#ifndef _TOKEN_DEFS_H_
#define _TOKEN_DEFS_H_ 1

/* The following are token codes for pass2 decode */

enum tokens {
   MAX_TOKEN =2048,		/* maximum length for token strings */
   MAX_LINE  =2050,		/* maximum length for input line */

   HASH_TABLE_SIZE =3001,	/* hash table size (prime number) */

   XREF_BLOCK_SIZE =4,	/* 3 filenames/xref block + link to next */

   TOKEN_strng    =0,   /* symbol name */
   TOKEN_numb,		/* number */
   TOKEN_local,		/* local symbol name */
   TOKEN_oper,		/* expression operator follows (char) */
   TOKEN_ascs,		/* ASCII text string follows (s) */
   TOKEN_pcx,		/* just a printing character */
   TOKEN_LINK   =126,	/* link to next segment */
   TOKEN_EOF    =127	/* end of file */
};

typedef enum {
   TMP_NUM    =0x7F,	/* constant value between -64 and + 63 */
   TMP_NNUM   =0x80,	/* Not a number */
   TMP_SIZE   =0x03,	/* bit mask for size bits */
   TMP_ZERO   =0x00,	/* Value is 0 */
   TMP_B8     =0x01,	/* Value is 8 bits */
   TMP_B16    =0x02,	/* Value is 16 bits */
   TMP_B32    =0x03,	/* value is 32 bits */
   TMP_EOF    =0x80,	/* tmp file entry is end of file */
   TMP_EXPR   =0x84,	/* tmp file entry is a expression */
   TMP_ASTNG  =0x88,	/* ascii string follows */
   TMP_TEST   =0x8C,	/* test expression follows */
   TMP_FILE   =0x90,	/* new file being processed */
   TMP_ORG    =0x94,	/* change PC */
   TMP_START  =0x98,	/* set the starting address */
   TMP_BSTNG  =0x9C,	/* binary string follows */
   TMP_SCOPE  =0xE4,	/* change procedure block */
   TMP_STAB   =0xE8,	/* debug info record */
   TMP_BOFF   =0xEC,	/* branch offset out of range test */
   TMP_OOR    =0xF0,	/* tom/jerry operand value out of range test */
   TMP_LINK   =0xFF,	/* link to next temp segment */

/* Remaing code for TMP are 0xF4 to 0xFC in increments of 4...	*/

/* WARNING... These codes are actually 8 bit codes with bit 8 assumed
 * 	to be 1. Therefore these codes fit into the TMP_xxx range beginning
 *	with 0xA0 in increments of 4. The RELMD bit translates into the
 *	expression relative mode bit. It may be set in addition to all the
 *	other codes.
 */
   EXPR_RELMD =0x10,	/* relative mode bit */
   EXPR_SYM   =0x20,	/* expression component is a symbol */
   EXPR_VALUE =0x24,	/* expression component is an absolute value */
   EXPR_OPER  =0x28,	/* expression component is an operator */
   EXPR_L     =0x2C,	/* expression component is an L */
   EXPR_B     =0x40,	/* expression component is a  B */
   EXPR_TAG   =0x44,	/* expression tag follows */
   EXPR_IDENT =0x48,	/* symbol identifier follows */
   EXPR_SEG   =0x4C,	/* segment pointer follows */
   EXPR_LINK  =0x60,	/* link to another expression */

#if defined(MAC682K) || defined(MAC68K)
    EXPR_MAXSTACKS =7,	/* max number of expression stacks */
#else
    EXPR_MAXSTACKS =4,	/* max number of expression stacks */
#endif
#if M_UNIX
	EXPR_MAXDEPTH  =128	/* max number of terms in expression */
#else
	EXPR_MAXDEPTH  =48	/* max number of terms in expression */
#endif
} EXPR_codes;

enum misc {
   OUTPUT_HEX =0,	/* output mode tekhex */
   OUTPUT_OL,		/* output mode relative ascii */
   OUTPUT_VLDA,		/* output absolute binary */
   OUTPUT_OBJ,		/* output relative binary */

   OUT_FN_OBJ =0,	/* indicies into the output fn_struct table */
   OUT_FN_LIS,
   OUT_FN_TOC,		/* By TRG 20240503 to support TOC */
   OUT_FN_TMP,
   OUT_FN_DEB,
   OUT_FN_MAX,

   MSG_WARN	=0,	/* error message severities */
   MSG_SUCCESS,
   MSG_ERROR,
   MSG_INFO,
   MSG_FATAL,
   MSG_CONT,		/* continue message */
   MSG_CTRL	=8,	/* use message as control string */
   MSG_NOSTDERR =16,	/* don't output message to stderr */
   MSG_PINPSTR  =32,	/* print inp_str along with message */
   MSG_NO_EXTRA	=64,	/* Do not add anything extra to output error message */
   MSG_DONT_COUNT = 128, /* Do not count the error */
	
   ED_MOS	=0x00001,	/* enable MOS syntax */
   ED_AMA	=0x00002,	/* enable absolute address mode */
   ED_ABS	=0x00004,	/* enable absolute output */
   ED_LSB	=0x00008,	/* enable local symbol block */
   ED_USD	=0x00010,	/* enable unsigned divide */
   ED_M68	=0x00020,	/* enable 68000 word mode (big endian) */
   ED_GBL  	=0x00040,	/* enable all undefines to be global */
   ED_WRD  	=0x00080,	/* enable undefined opcodes to .word */
   ED_LC	=0x00100,	/* enable lowercase symbols */
   ED_DOL	=0x00200,	/* enable leading dollar hex constants */
   ED_DOTLCL=0x00400,	/* enable symbols starting with '.' to be local */
   ED_BYT  	=0x00800,	/* enable undefined opcodes to .byte */
   ED_CR  	=0x01000,	/* enable carriage returns in source */
   ED_TRUNC	=0x02000, 	/* enable truncation check in .byte and .word */
   ED_SIMPLE=0x04000,	/* enable simple .ifdf/.ifndf expression (technically disables the complex test for def/ndef symbols). */
   ED_CPU   =0x08000,	/* enable reporting checks for different behavior on different model CPU's (mac11) */
   ED_HEXLCL=0x10000	/* allow local symbols to be hexidecimal */
};

#endif /* _TOKEN_DEFS_H_ */
