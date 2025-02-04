/*
    help.c - Part of macxx, a cross assembler family for various micro-processors
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
#include "token.h"
#include "add_defs.h"

#ifdef _toupper
    #undef _toupper
    #undef _tolower
#endif

#define _toupper(c)	(char_toupper[(unsigned char)c])
#define _tolower(c)	((c) >= 'A' && (c) <= 'Z' ? (c) | 0x20:(c))

typedef struct
{
    char *ctlstr;
    int *value;
} Help_Value;
static Help_Value help_symbol_length = {"%d",&max_symbol_length};
static Help_Value help_opcode_length = {"%d",&max_opcode_length};
static char help_uppercase_mark[1],help_cmos_mark[1],help_2_pass_mark[1],help_cmos_default[1], help_jerry_mark[1], help_2_pass_default[1];
static char help_grnhill_mark[1], help_predef_mark[1];

#define UPC help_uppercase_mark

static char *help_msg[] = {
    "Usage: ",UPC,macxx_name," file1 file2 ... [",opt_delim,"","option]\n",
    "Where option is one of ([] implies optional text):\n",
    opt_delim,"[no]output", "[=name]	- name object file\n",
    opt_delim,"[no]list",   "[=name]	- select and name listing file\n",
	opt_delim,"[no]toc",    "[=name]		- enable the creation and name of table of contents file (see below)\n",
	opt_delim,"[no]ide_error_syntax",
                            "   - Output error messages in a syntax suitable for use by an IDE.\n",
    opt_delim,"[no]ignore", "	        - Ignore the assembler directives not implemented in this version\n",
#if !defined(MAC_PP)
	help_2_pass_mark,
    opt_delim,"[no]2_pass", "	        - select to assemble using two pass mode\n",
    opt_delim,"[no]debug",  "[=name]	- select and name temporary work file\n",
#if 0
    opt_delim,"[no]temp","[=name]	- select and name temporary work file\n",
#endif
    opt_delim,"[no]binary", "		- select binary or ASCII format object file\n",
    opt_delim,"[no]boff",   "		- do global branch offset testing\n",
    help_cmos_mark,
    opt_delim,"[no]cmos",   "		- use 65C02 instruction set\n",
    help_cmos_mark,
    opt_delim,"[no]816",    "		- use 65816 instruction set\n",
    help_jerry_mark,
    opt_delim,"[no]jerry",  "		- use Jaguar's Jerry opcode set\n",
    help_grnhill_mark,
    opt_delim,"[no]greenhills","         - use Green Hills assembler syntax\n",
	help_predef_mark,
	opt_delim,"[no]predefine", "          - Predefine register symbols R0-R7, PC and SP (default)\n",
    opt_delim,"[no]abbreviate","         - Abbreviate error messages\n",
#else
    opt_delim,"[no]line",  "		- place # line info in output file\n",
#endif
    opt_delim,"assem","=string		- \"string\" is assembled before anything\n",
    "			   i.e. ",opt_delim,"assem","=foo=bar will assemble as foo=bar\n",
    "			   Any number of ",opt_delim,"assem"," options may be used.\n",
    opt_delim,"include","=path		- sets path to use with .INCLUDE directives. Any number\n",
    "			  of ",opt_delim,"include"," options may be specified.\n",
    opt_delim,"symbol","=length		- set maximum length of symbols (6 <= n <= 16)\n",
    opt_delim,"opcode","=length		- set maximum length of opcodes/macros (6 <= n <= 16)\n",
    "Options may be abbreviated to 1 or more characters and are case insensitive\n",
    "Defaults are ",opt_delim,"out ",opt_delim,"nolist ",opt_delim,"notoc ",opt_delim,"sym=",
    (char *)&help_symbol_length," ",opt_delim,"opc=",(char *)&help_opcode_length," ",
	opt_delim,"noignore ",
#if !defined(MAC_PP)
    opt_delim,"notemp ",
#if !defined(VMS)
    opt_delim,"nobinary ",
#else
    opt_delim,"binary ",
#endif
	help_cmos_default,opt_delim,"nocmos ",
    help_cmos_default,opt_delim,"no816 ",
	help_2_pass_default,opt_delim,"no2_pass ",
#if defined(MAC_65) || defined(MAC_68) || defined(MAC_69) 
#endif
#else
    opt_delim,"noline ",
#endif
    " ",opt_delim,"noide_error",
    "\nAnd the ",opt_delim,"out"," filename defaults to the same name as the first input\n",
    "file with a file type of ",UPC,DEF_OUT," and the ",opt_delim,"list"," filename defaults to the\n",
    "same name as the ",
#if !defined(MAC_PP)
    "object",
#else
    "output",
#endif
    " file with a file type of ",UPC,def_lis,".\n",
	"If a ",opt_delim,"toc is provided without a ",opt_delim,"list the listing will contain only the table of contents.\n"
	"If both ",opt_delim,"list and ",opt_delim,"toc options are provided the table of contents will be included\n"
	"at the head of the listing file.\n",
    (char *)0};

int display_help(void)
{
    int i, upc = 0;
    for (i=0;help_msg[i] && i < sizeof(help_msg)/sizeof(char *);++i)
    {
        char *s;
        if (help_msg[i] == opt_delim)
        {
            fputs(opt_delim,stderr);
#if defined(VMS) || defined(MS_DOS)
            upc = 1;
#endif
            continue;
        }
        if (help_msg[i] == help_uppercase_mark)
        {
            upc = 1;
            continue;
        }
        if (help_msg[i] == (char *)&help_symbol_length ||
            help_msg[i] == (char *)&help_opcode_length)
        {
            fprintf(stderr,((Help_Value *)help_msg[i])->ctlstr,
                    *((Help_Value *)help_msg[i])->value);
            continue;
        }
        if (help_msg[i] == help_grnhill_mark)
        {
            if (! (were_mac68k || were_mac682k) )
            {
                i += 3;     /* skip the delim, option name and text */
            }
            continue;
        }
		if (help_msg[i] == help_predef_mark)
		{
			if ( !were_mac11 )
			{
				i += 3;     /* skip the delim, option name and text */
			}
			continue;
		}
        if (help_msg[i] == help_jerry_mark)
        {
            if (!were_mactj)
            {    /* If not mactj, */
                i += 3;     /* skip the delim, option name and text */
            }
            continue;
        }
        if (help_msg[i] == help_cmos_mark)
        {
            if (!were_mac65)
            {
                i += 3;     /* skip the delim, option name and text */
            }
            continue;
        }
		if (help_msg[i] == help_2_pass_mark)
		{
			if ( !(were_mac65 || were_mac68 || were_mac69 || were_mac11) )
				i += 3;     /* skip the delim, option name and text */
			continue;
		}
        if (help_msg[i] == help_cmos_default)
        {
            if (!were_mac65)
            {
                i += 2;     /* skip the delim and option name */
            }
            continue;
        }
		if ( help_msg[i] == help_2_pass_default )
		{
			if ( !(were_mac65 || were_mac68 || were_mac69) )
				i += 2;		/* skip the delim and option name */
			continue;
		}
		if ( !upc )
        {
            fputs(help_msg[i],stderr);
        }
        else
        {
            char c;
            s = help_msg[i];
            while ((c = *s++) != 0)
            {
                if (islower(c)) c = _toupper(c);
                fputc(c,stderr);
            }
            upc = 0;
        }
    }
#if defined(VMS)
    return 0x10000000;
#else
    return 1;
#endif
}

