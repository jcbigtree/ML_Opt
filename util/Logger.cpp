#include <cstdio>
#include "Logger.hpp"

using namespace Util;

#ifdef FILE_LOG_TO_FILE
	FILE* pFile = fopen("My.log", "w");
	FILE* OutputToFile::m_pStream = pFile;
#else
	FILE* OutputToFile::m_pStream = stdout;
#endif

