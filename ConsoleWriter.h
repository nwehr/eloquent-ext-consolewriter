#ifndef _ConsoleWriter_h
#define _ConsoleWriter_h

//
// Copyright 2013-2014 EvriChart, Inc. All Rights Reserved.
// See LICENSE.txt
//

// Boost
#include <boost/property_tree/ptree.hpp>
#include <boost/smart_ptr.hpp>

// External
#include <streamlog/streamlog.h>

// Internal
#include <Eloquent/Extensions/IOExtension.h>

namespace Eloquent {	
	///////////////////////////////////////////////////////////////////////////////
	// ConsoleWriter : IOExtension
	///////////////////////////////////////////////////////////////////////////////
	class ConsoleWriter : public IOExtension {
		ConsoleWriter();
	public:
		explicit ConsoleWriter( const boost::property_tree::ptree::value_type& i_Config
							   , std::mutex& i_LogMutex
							   , streamlog::severity_log& i_Log
							   , std::mutex& i_QueueMutex
							   , std::condition_variable& i_QueueCV
							   , std::queue<QueueItem>& i_Queue
							   , int& i_NumWriters );

		virtual ~ConsoleWriter();
		virtual void operator()();

	};

}

#endif // _ConsoleWriter_h