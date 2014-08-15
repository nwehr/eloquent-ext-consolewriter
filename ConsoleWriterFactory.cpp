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
	
Eloquent::IOExtension* Eloquent::ConsoleWriterFactory::New( const boost::property_tree::ptree::value_type& i_Config
														   , std::mutex& i_LogMutex
														   , streamlog::severity_log& i_Log
														   , std::mutex& i_QueueMutex
														   , std::condition_variable& i_QueueCV
														   , std::queue<QueueItem>& i_Queue
														   , int& i_NumWriters )
{
	return new ConsoleWriter( i_Config, i_LogMutex, i_Log, i_QueueMutex, i_QueueCV, i_Queue, i_NumWriters );
}
