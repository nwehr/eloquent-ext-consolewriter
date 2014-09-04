#ifndef __eloquent__ConsoleWriterFactory__
#define __eloquent__ConsoleWriterFactory__

//
// Copyright 2013-2014 EvriChart, Inc. All Rights Reserved.
// See LICENSE.txt
//

// C
#include <syslog.h>

// C++
#include <string>
#include <vector>

// Boost
#include <boost/smart_ptr.hpp>
#include <boost/property_tree/ptree.hpp>

// Internal
#include "Eloquent/Extensions/IO/IOFactory.h"

namespace Eloquent {
	///////////////////////////////////////////////////////////////////////////////
	// ConsoleWriterFactory : IOFactory
	///////////////////////////////////////////////////////////////////////////////
	class ConsoleWriterFactory : public IOFactory {
	public:
		ConsoleWriterFactory();
		virtual ~ConsoleWriterFactory();
		
		virtual IO* New( const boost::property_tree::ptree::value_type& i_Config
								 , std::mutex& i_QueueMutex
								 , std::condition_variable& i_QueueCV
								 , std::queue<QueueItem>& i_Queue
								 , unsigned int& i_NumWriters );
		
	};
	
}

#endif /* defined(__eloquent__ConsoleWriterFactory__) */
