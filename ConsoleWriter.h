#ifndef _ConsoleWriter_h
#define _ConsoleWriter_h

//
// Copyright 2013-2014 EvriChart, Inc. All Rights Reserved.
// See LICENSE.txt
//

// C
#include <syslog.h>

// Boost
#include <boost/property_tree/ptree.hpp>
#include <boost/smart_ptr.hpp>

// Internal
#include <Eloquent/Extensions/IO/IO.h>

namespace Eloquent {	
	///////////////////////////////////////////////////////////////////////////////
	// ConsoleWriter : IO
	///////////////////////////////////////////////////////////////////////////////
	class ConsoleWriter : public IO {
		ConsoleWriter();
	public:
		explicit ConsoleWriter( const boost::property_tree::ptree::value_type& i_Config
							   , std::mutex& i_QueueMutex
							   , std::condition_variable& i_QueueCV
							   , std::queue<QueueItem>& i_Queue
							   , int& i_NumWriters );

		virtual ~ConsoleWriter();
		virtual void operator()();

	};

}

#endif // _ConsoleWriter_h