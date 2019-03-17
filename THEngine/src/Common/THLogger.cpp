#include <fstream>
#include "THLogger.h"

using namespace THEngine;

Logger::Logger()
{
	logFile.open("THLog.txt", std::ios::binary);
	char unicodeBom[3] = { (char)0xff, (char)0xfe, (char)0x00 };
	logFile.write(unicodeBom, 2);
}

Logger::~Logger()
{
	if (logFile.is_open())
		logFile.close();
}

Logger* Logger::GetInstance()
{
	static Logger instance;
	return &instance;
}

void Logger::WriteLine(String message)
{
	logFile.write((char*)message.GetBuffer(), message.GetLength() * 2);
	logFile.write((char*)L"\r\n", 4);
}