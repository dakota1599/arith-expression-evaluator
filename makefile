OUT=math
main:
	cl /EHsc /Fe$(OUT) main.cpp parser.cpp scanner.cpp

del:
	del *.exe
	del *.obj