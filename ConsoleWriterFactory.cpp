//
// Copyright 2013-2014 EvriChart, Inc. All Rights Reserved.
// See LICENSE.txt
//

// Internal
#include "ConsoleWriter.h"
#include "ConsoleWriterFactory.h"

///////////////////////////////////////////////////////////////////////////////
// ConsoleWriterFactory : IOExtensionFactory
///////////////////////////////////////////////////////////////////////////////
Eloquent::ConsoleWriterFactory::ConsoleWriterFactory() {}
Eloquent::ConsoleWriterFactory::~ConsoleWriterFactory() {}
	
Eloquent::IO* Eloquent::ConsoleWriterFactory::New( const boost::property_tree::ptree::value_type& i_Config
														   , std::mutex& i_QueueMutex
														   , std::condition_variable& i_QueueCV
														   , std::queue<QueueItem>& i_Queue
														   , int& i_NumWriters )
{
	syslog( LOG_DEBUG, "returning new reader #Comment #Factory #ConsoleWriterFactory" );
	return new ConsoleWriter( i_Config, i_QueueMutex, i_QueueCV, i_Queue, i_NumWriters );
}
