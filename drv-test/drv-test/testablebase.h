#pragma once

#ifndef __TESTABLEBASE_H__
#define __TESTABLEBASE_H__

#include "pch.h"
#include <iostream>
#include <string>

class TestableBase
{
private:
	
	std::string m_testCaseName;

	static std::string s_drvName;
	static bool s_isDriverLoaded;

public:
	TestableBase(std::string&);

	//	TODO: Make this guy inline.
	std::string getTestCaseName();

	static void setDrvName(const char *);
	static bool loadDriver();
	static bool unloadDriver();

	virtual bool setUp() = 0;
	virtual bool run() = 0;
	virtual void tearDown() = 0;
};

#endif	//	__TESTABLEBASE_H__