#include "pch.h"
#include "testablebase.h"
#include "TestCollection.h"

#include <list>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/File.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

using namespace std;

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace keywords = boost::log::keywords;

void TestCollection::add(TestableBase* t_testCase)
{
	//	Forming collection of test-cases.
	Collection.push_back(t_testCase);
}

bool TestCollection::init(std::string t_logFileName)
{
	logging::register_simple_formatter_factory<logging::trivial::severity_level, char>("Severity");

	logging::add_file_log
	(
		keywords::file_name = t_logFileName.c_str(),
		keywords::format = "[%TimeStamp%] [%Severity%] %Message%"
	);

	
	logging::core::get()->set_filter
	(
		logging::trivial::severity >= logging::trivial::info
	);
	
	logging::add_common_attributes();

	return true;
}

bool TestCollection::run()
{
	std::list<TestableBase *>::iterator it;
	src::severity_logger<logging::trivial::severity_level> lg;

	//	Executing all test-cases one by one.
	for (it = Collection.begin(); it != Collection.end(); ++it)
	{
		cout << endl << "=====Executing " + (*it)->getTestCaseName() + "=====" << endl;
		BOOST_LOG_TRIVIAL(info) << "=====Executing " + (*it)->getTestCaseName() + "=====";

		if ((*it)->setUp())
		{
			if (!(*it)->run())
			{
				BOOST_LOG_TRIVIAL(error) << "TestableBase::run() failed";
			}
		}
		else
		{
			BOOST_LOG_TRIVIAL(error) << "TestableBase::setUp() failed";
		}

		(*it)->tearDown();
	}

	//	Enumerate over TestResults collection to display results/statistics.
	
	return true;
}