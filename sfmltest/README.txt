
Linux:

echo $LD_LIBRARY_PATH

if nothing appears: (replace x32 by x64 if you are on 64bits archi)
export LD_LIBRARY_PATH="../lib/gcc/x32"
else
export LD_LIBRARY_PATH="../lib/gcc/x32:$(LD_LIBRARY_PATH)"


qmake
make
./superbabar

