@set include=
del /q vm
mkdir vm
cd vm
set cc=..\..\..\..\bin\sof2lcc -A -DQ3_VM -DMISSIONPACK -S -Wf-target=bytecode -Wf-g -I..\..\..\gametype -I..\..\gt_elim -I..\..\..\game %1

%cc%  ../gt_main.c
@if errorlevel 1 goto quit

%cc%  ../../gt_syscalls.c
@if errorlevel 1 goto quit

%cc%  ../../../game/bg_lib.c
@if errorlevel 1 goto quit

%cc%  ../../../game/q_shared.c
@if errorlevel 1 goto quit

%cc%  ../../../game/q_math.c
@if errorlevel 1 goto quit

..\..\..\..\bin\sof2asm -f ../gt_elim
@if errorlevel 1 goto quit

mkdir "..\..\..\Debug\base\MP\vm"
copy *.map "..\..\..\Debug\base\MP\vm"
copy *.qvm "..\..\..\Debug\base\MP\vm"

:quit
cd ..
