#include "pch.h"
#include "testablebase.h"
#include <boost/log/trivial.hpp>

using namespace std;

std::string TestableBase::s_drvName("");
bool TestableBase::s_isDriverLoaded = false;

TestableBase::TestableBase(std::string& t_name) : m_testCaseName(t_name) { }

void TestableBase::setDrvName(const char* t_drvName)
{
	TestableBase::s_drvName.assign(t_drvName);
}

std::string TestableBase::getTestCaseName()
{
	return this->m_testCaseName;
}

bool TestableBase::loadDriver()
{
	if (!s_isDriverLoaded)
	{
		std::string load_cmd("fltmc load ");	
		load_cmd.append(TestableBase::s_drvName);
		
		if (-1 == system(load_cmd.c_str()))
		{
			BOOST_LOG_TRIVIAL(error) << "Failed to load the driver";
			return false;
		}

		s_isDriverLoaded = true;
	}

	return true;
}

bool TestableBase::unloadDriver()
{
	if (s_isDriverLoaded)
	{
		std::string unload_cmd("fltmc unload ");
		unload_cmd.append(TestableBase::s_drvName);

		if (-1 == system(unload_cmd.c_str()))
		{
			BOOST_LOG_TRIVIAL(error) << "Failed to unload the driver";
			return false;
		}

		s_isDriverLoaded = false;
	}

	return true;
}