/*
    pst11.c - Part of macxx, a cross assembler family for various micro-processors
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
#ifndef MAC_11
#define MAC_11 1
#endif

#include "pst_tokens.h"

#define DIRDEF(name,func,flags) extern int func();
#include "dirdefs.h"
#undef DIRDEF

#define OPDEF(name,class,val,bwl) {name,val,OP_CLASS_OPC+class,bwl},

Opcpst perm_opcpst[] = {
#include "opcs11.h"
   	{ 0,0,0,0 }
};

#define DIRDEF(name,func,flags) {name,func,flags},

Dirpst perm_dirpst[] = {
#include "dirdefs.h"
   	{ 0,0,0 }
};
