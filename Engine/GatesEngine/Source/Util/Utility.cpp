#include "..\..\Header\Util\Utility.h"
#include <stdio.h>
#include <Windows.h>

void GE::Utility::Printf(const char* format, ...)
{
	// Debug���̂ݎ��s
#ifdef _DEBUG
	va_list valist;
	va_start(valist, format);
	vprintf(format, valist);
	va_end(valist);
#endif
}
