#ifndef __eloquent__ConsoleWriterFactory__
#define __eloquent__ConsoleWriterFactory__

//
// Copyright 2013-2014 EvriChart, Inc. All Rights Reserved.
// See LICENSE.txt
//

// C++
#include <string>
#include <vector>

// Boost
#include <boost/smart_ptr.hpp>
#include <boost/property_tree/ptree.hpp>

// Internal
#include "eloquent/Extensions/IOExtensionFactory.h"

namespace Eloquent {
	///////////////////////////////////////////////////////////////////////////////
	// ConsoleWriterFactory : IOExtensionFactory
	///////////////////////////////////////////////////////////////////////////////
	class ConsoleWriterFactory : public IOExtensionFactory {
		ConsoleWriterFactory();
	public:
		explicit ConsoleWriterFactory( const std::string& i_Name
									  , const std::string& i_Version
									  , const std::string& i_Author
									  , const std::string& i_Type
									  , const std::vector<std::string>& i_Keys );
		
		virtual IOExtension* New( const boost::property_tree::ptree::value_type& i_Config
								 , std::mutex& i_LogMutex
								 , streamlog::severity_log& i_Log
								 , std::mutex& i_QueueMutex
								 , std::condition_variable& i_QueueCV
								 , std::queue<QueueItem>& i_Queue
								 , int& i_NumWriters );
		
	};
	
}

#endif /* defined(__eloquent__ConsoleWriterFactory__) */
