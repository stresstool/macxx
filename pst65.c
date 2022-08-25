/*
    pst65.c - Part of macxx, a cross assembler family for various micro-processors
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
#define MAC_65
#include "pst_tokens.h"
#include "psttkn65.h"

#define DIRDEF(name,func,flags) extern int func();

#include "dirdefs.h"

#undef DIRDEF

#define OPCDEF(name,clas,value,am,aam,aaam) {name,value,OP_CLASS_OPC+(clas),am,aam,aaam},

enum opc2hex { OPCa,OPCb,OPCc,OPCd,OPCe,OPCf,OPCg,OPCh,OPCi,OPCj,OPCk,
OPCl,OPCm,OPCn,OPCo,OPCp,OPCq,OPCr,OPCs,OPCt,OPCu,OPCv,OPCw,OPCx,OPCy,
OPCz,OPCaa,OPCab };

Opcpst perm_opcpst[] = {
OPCDEF("ADC",	02,		OPCa,	MOST65,	MOST65|ND, MOST816	)
OPCDEF("AND",	02,		OPCb,	MOST65,	MOST65|ND, MOST816	)
OPCDEF("ANDA",	02,		OPCb,	MOST65,	MOST65|ND, MOST816	)
OPCDEF("ASL",	02,		OPCc,	SHFTAM,	SHFTAM,   SHFTAM	)
OPCDEF("BCC",	03,		0x90,	R,	R,	R	)
OPCDEF("BCS",	03,		0xB0,	R,	R,	R	)
OPCDEF("BEQ",	03,		0xF0,	R,	R,	R	)
OPCDEF("BIT",	02,		OPCd,	BITAM,	BITAM816, BITAM816	)
OPCDEF("BMI",	03,		0x30,	R,	R,	R	)
OPCDEF("BNE",	03,		0xD0,	R,	R,	R	)
OPCDEF("BPL",	03,		0x10,	R,	R,	R	)
OPCDEF("BRA",	03,		0x80,	R,	R,	R	)
OPCDEF("BRK",	00,		0x00,	IMP,	IMP,	IMP	)
OPCDEF("BRL",	03,		0x82,	0,	0,	RL	)
OPCDEF("BVC",	03,		0x50,	R,	R,	R	)
OPCDEF("BVS",	03,		0x70,	R,	R,	R	)
OPCDEF("CLC",	00,		0x18,	IMP,	IMP,	IMP	)
OPCDEF("CLD",	00,		0xD8,	IMP,	IMP,	IMP	)
OPCDEF("CLI",	00,		0x58,	IMP,	IMP,	IMP	)
OPCDEF("CLV",	00,		0xB8,	IMP,	IMP,	IMP	)
OPCDEF("CMP",	02,		OPCe,	MOST65,	MOST65|ND, MOST816 )
OPCDEF("COP",	00,		0x02,	IMP,	IMP,	IMP	)
OPCDEF("CPX",	02|OPCLINDX,	OPCf,	XYAM,	XYAM,	XYAM	)
OPCDEF("CPY",	02|OPCLINDX,	OPCg,	XYAM,	XYAM,	XYAM	)
OPCDEF("DEC",	02,		OPCh,	INCAM,	INCAM|AC, INCAM816	)
OPCDEF("DEX",	00,		0xCA,	IMP,	IMP,	IMP	)
OPCDEF("DEY",	00,		0x88,	IMP,	IMP,	IMP	)
OPCDEF("EOR",	02,		OPCi,	MOST65,	MOST65|ND, MOST816	)
OPCDEF("INC",	02,		OPCj,	INCAM,	INCAM|AC, INCAM816	)
OPCDEF("INX",	00,		0xE8,	IMP,	IMP,	IMP	)
OPCDEF("INY",	00,		0xC8,	IMP,	IMP,	IMP	)
OPCDEF("JML",	02|OPCLPBR,	OPCk,	0,	0, 	NND )
OPCDEF("JMP",	02|OPCLPBR,	OPCl,	A|N, A|N, A|AL|N|NND|NAX )
OPCDEF("JSL",	01|OPCLPBR,	0x22,	0,	0,	AL	)
OPCDEF("JSR",	02|OPCLPBR,	OPCm,	A,	A,	A|AL|NAX )
OPCDEF("LDA",	02,		OPCn,	MOST65,	MOST65|ND, MOST816	)
OPCDEF("LDX",	02|OPCLINDX,	OPCo,	XYAM|ZY|AY,	XYAM|ZY|AY,	XYAM|ZY|AY )
OPCDEF("LDY",	02|OPCLINDX,	OPCp,	XYAM|ZX|AX,	XYAM|ZX|AX,	XYAM|ZX|AX )
OPCDEF("LSR",	02,		OPCq,	SHFTAM,	SHFTAM,	SHFTAM	)
OPCDEF("MVN",	01,		0x54,	0,	0,	XYC )
OPCDEF("MVP",	01,		0x44,	0,	0,	XYC )
OPCDEF("NOP",	00,		0xEA,	IMP,	IMP,	IMP )
OPCDEF("ORA",	02,		OPCr,	MOST65,	MOST65|ND, MOST816 )
OPCDEF("PEA",	01,		0xF4,	0,	0,	A )
OPCDEF("PEI",	02,		OPCv,	0,	0,	D|ND )
OPCDEF("PER",	03,		0x62,	0,	0,	RL )
OPCDEF("PHA",	00,		0x48,	IMP,	IMP,	IMP )
OPCDEF("PHB",	00,		0x8B,	0,	0,	IMP )
OPCDEF("PHD",	00,		0x0B,	0,	0,	IMP )
OPCDEF("PHK",	00,		0x4B,	0,	0,	IMP )
OPCDEF("PHP",	00,		0x08,	IMP,	IMP,	IMP )
OPCDEF("PHX",	00,		0xDA,	0,	IMP,	IMP )
OPCDEF("PHY",	00,		0x5A,	0,	IMP,	IMP )
OPCDEF("PLA",	00,		0x68,	IMP,	IMP,	IMP )
OPCDEF("PLB",	00,		0xAB,	0,	0,	IMP )
OPCDEF("PLD",	00,		0x2B,	0,	0,	IMP )
OPCDEF("PLP",	00,		0x28,	IMP,	IMP,	IMP )
OPCDEF("PLX",	00,		0xfA,	0,	IMP,	IMP )
OPCDEF("PLY",	00,		0x7A,	0,	IMP,	IMP )
OPCDEF("REP",	01,		0xC2,	0,	0,	I )
OPCDEF("ROL",	02,		OPCs,	SHFTAM,	SHFTAM,	SHFTAM )
OPCDEF("ROR",	02,		OPCt,	SHFTAM,	SHFTAM,	SHFTAM )
OPCDEF("RTI",	00,		0x40,	IMP,	IMP,	IMP )
OPCDEF("RTL",	00,		0x6B,	0,	0,	IMP )
OPCDEF("RTS",	00,		0x60,	IMP,	IMP,	IMP )
OPCDEF("SBC",	02,		OPCu,	MOST65,	MOST65|ND, MOST816 )
OPCDEF("SEC",	00,		0x38,	IMP,	IMP,	IMP )
OPCDEF("SED",	00,		0xF8,	IMP,	IMP,	IMP )
OPCDEF("SEI",	00,		0x78,	IMP,	IMP,	IMP )
OPCDEF("SEP",	01,		0xE2,	0,	0,	I )
OPCDEF("STA",	02,		OPCw,	(MOST65-I)|DES,	(MOST65-I)|DES, (MOST816-I)|DES )
OPCDEF("STP",	00,		0xDB,	0,	IMP,	IMP )
OPCDEF("STX",	02,		OPCx,	(XYAM-I)|ZY|DES,	(XYAM-I)|ZY|DES, (XYAM-I)|ZY|DES )
OPCDEF("STY",	02,		OPCy,	(XYAM-I)|ZX|DES,	(XYAM-I)|ZX|DES, (XYAM-I)|ZX|DES )
OPCDEF("STZ",	02,		OPCz,	0,	A|Z|ZX|AX|DES, A|Z|ZX|AX|DES )
OPCDEF("SWA",	00,		0xEB,	0,	0,	IMP )
OPCDEF("TAD",	00,		0x5B,	0,	0,	IMP )
OPCDEF("TAS",	00,		0x1B,	0,	0,	IMP )
OPCDEF("TAX",	00,		0xAA,	IMP,	IMP,	IMP )
OPCDEF("TAY",	00,		0xA8,	IMP,	IMP,	IMP )
OPCDEF("TCD",	00,		0x5B,	0,	0,	IMP )
OPCDEF("TCS",	00,		0x1B,	0,	0,	IMP )
OPCDEF("TDA",	00,		0x7B,	0,	0,	IMP )
OPCDEF("TDC",	00,		0x7B,	0,	0,	IMP )
OPCDEF("TRB",	02,		OPCaa,	0,	A|Z|DES, A|Z|DES )
OPCDEF("TSA",	00,		0x3B,	0,	0,	IMP )
OPCDEF("TSB",	02,		OPCab,	0,	A|Z|DES, A|Z|DES )
OPCDEF("TSC",	00,		0x3B,	0,	0,	IMP )
OPCDEF("TSX",	00,		0xBA,	IMP,	IMP,	IMP )
OPCDEF("TXA",	00,		0x8A,	IMP,	IMP,	IMP )
OPCDEF("TXS",	00,		0x9A,	IMP,	IMP,	IMP )
OPCDEF("TXY",	00,		0x9B,	0,	0,	IMP )
OPCDEF("TYA",	00,		0x98,	IMP,	IMP,	IMP )
OPCDEF("TYX",	00,		0xBB,	0,	0,	IMP )
OPCDEF("WAI",	00,		0xCB,	0,	IMP,	IMP )
OPCDEF("WDM",	00,		0x42,	0,	0,	IMP )
OPCDEF("XBA",	00,		0xEB,	0,	0,	IMP )
OPCDEF("XCE",	00,		0xFB,	0,	0,	IMP )
   	{ 0,0,0,0,0,0 }
};

unsigned char opc_to_hex[][OP_TO_HEX_SIZE] = {
/*   imm  abs  absl drct  acc (d)y [d]y (dx)  d,x  d,y  a,x al,x  a,y  (a)  (d)  [d] (ax)  d,s (ds)y  */
   { 0x69,0x6d,0x6F,0x65,0x00,0x71,0x77,0x61,0x75,0x00,0x7d,0x7F,0x79,0x00,0x72,0x67,0x00,0x63,0x73 },	/* OPCa - adc */
   { 0x29,0x2d,0x2F,0x25,0x00,0x31,0x37,0x21,0x35,0x00,0x3d,0x3f,0x39,0x00,0x32,0x27,0x00,0x23,0x33 },	/* OPCb - and */
   { 0x00,0x0e,0x00,0x06,0x0a,0x00,0x00,0x00,0x16,0x00,0x1e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },	/* OPCc - asl */
   { 0x89,0x2c,0x00,0x24,0x00,0x00,0x00,0x00,0x34,0x00,0x3c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },	/* OPCd - bit */
   { 0xc9,0xcd,0xcf,0xc5,0x00,0xd1,0xd7,0xc1,0xd5,0x00,0xdd,0xdf,0xd9,0x00,0xd2,0xc7,0x00,0xc3,0xd3 },	/* OPCe - cmp */
   { 0xe0,0xec,0x00,0xe4,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },	/* OPCf - cpx */
   { 0xc0,0xcc,0x00,0xc4,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },	/* OPCg - cpy */
   { 0x00,0xce,0x00,0xc6,0x3a,0x00,0x00,0x00,0xd6,0x00,0xde,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },	/* OPCh - dec */
   { 0x49,0x4d,0x4f,0x45,0x00,0x51,0x57,0x41,0x55,0x00,0x5d,0x5f,0x59,0x00,0x52,0x47,0x00,0x43,0x53 },	/* OPCi - eor */
   { 0x00,0xee,0x00,0xe6,0x1a,0x00,0x00,0x00,0xf6,0x00,0xfe,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },	/* OPCj - inc */
   { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xdc,0x00,0x00,0x00 },	/* OPCk - jml */
   { 0x00,0x4c,0x5c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x6c,0x00,0xdc,0x7c,0x00,0x00 },	/* OPCl - jmp */
   { 0x00,0x20,0x22,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xfc,0x00,0x00 },	/* OPCm - jsr */
   { 0xa9,0xad,0xaf,0xa5,0x00,0xb1,0xb7,0xa1,0xb5,0x00,0xbd,0xbf,0xb9,0x00,0xb2,0xa7,0x00,0xa3,0xb3 },	/* OPCn - lda */
   { 0xa2,0xae,0x00,0xa6,0x00,0x00,0x00,0x00,0x00,0xb6,0x00,0x00,0xbe,0x00,0x00,0x00,0x00,0x00,0x00 },	/* OPCo - ldx */
   { 0xa0,0xac,0x00,0xa4,0x00,0x00,0x00,0x00,0xb4,0x00,0xbc,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },	/* OPCp - ldy */
   { 0x00,0x4e,0x00,0x46,0x4a,0x00,0x00,0x00,0x56,0x00,0x5e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },	/* OPCq - lsr */
   { 0x09,0x0d,0x0f,0x05,0x00,0x11,0x17,0x01,0x15,0x00,0x1d,0x1f,0x19,0x00,0x12,0x07,0x00,0x03,0x13 },	/* OPCr - ora */
   { 0x00,0x2e,0x00,0x26,0x2a,0x00,0x00,0x00,0x36,0x00,0x3e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },	/* OPCs - rol */
   { 0x00,0x6e,0x00,0x66,0x6a,0x00,0x00,0x00,0x76,0x00,0x7e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },	/* OPCt - ror */
   { 0xe9,0xed,0xef,0xe5,0x00,0xf1,0xf7,0xe1,0xf5,0x00,0xfd,0xff,0xf9,0x00,0xf2,0xe7,0x00,0xe3,0xf3 },	/* OPCu - sbc */
   { 0x00,0x00,0x00,0xd4,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xd4,0x00,0x00,0x00,0x00 },	/* OPCv - pei */
   { 0x00,0x8d,0x8f,0x85,0x00,0x91,0x97,0x81,0x95,0x00,0x9d,0x9f,0x99,0x00,0x92,0x87,0x00,0x83,0x93 },	/* OPCw - sta */
   { 0x00,0x8e,0x00,0x86,0x00,0x00,0x00,0x00,0x00,0x96,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },	/* OPCx - stx */
   { 0x00,0x8c,0x00,0x84,0x00,0x00,0x00,0x00,0x94,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },	/* OPCy - sty */
   { 0x00,0x9c,0x00,0x64,0x00,0x00,0x00,0x00,0x74,0x00,0x9e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },	/* OPCz - stz */
   { 0x00,0x1c,0x00,0x14,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },	/* OPCaa- trb */
   { 0x00,0x0c,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 }	/* OPCab- tsb */
};	

#define DIRDEF(name,func,flags) {name,func,flags},

Dirpst perm_dirpst[] = {

#include "dirdefs.h"

   	{ 0,0,0 }
};
