#pragma once
#ifndef __TESTCOLLECTION_H__
#define __TESTCOLLECTION_H__

#include "pch.h"
#include "testablebase.h"
#include <iostream>
#include <list>

class TestCollection
{
private:
	
	std::list<TestableBase *> Collection;

public:

	bool init(std::string t_logFileName);
	void add(TestableBase *);
	bool run();
};

#endif // !__TESTCOLLECTION_H__