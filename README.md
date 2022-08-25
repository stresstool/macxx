# macxx
Macro assembler for the 6502, 65C02, 65816, 68000, 68010, 68020, ASAP, PDP11, Atari Tom&Jerry DSP and a generic pre-processor

This is pretty old code. The first implementation of macxx was written by me in PDP11 assembly for RT11 with coding of it starting probably around early 1978. I re-wrote it in C probably around 1982 or 1983 first for VAX/VMS. This is that code. Since then it's been ported to lots of different O/S and had some bug fixes and features added, however, in the last 20+ years it has only been used (by me) on Linux systems. Since some old Atari game sources were posted to github recently, I thought I'd post the assembler we used to build some of them back in the old days. Note, this one is not the exact one used in 1978 so if you try to use it to build code from earlier than around 1983 you might need to make minor tweaks to the build scripts to get the exact same binary.

It needs two companion tools: LLF to link the resulting object files and MIXIT to convert the output of LLF into ROM/EPROM images. Both can be found in repositories here.
