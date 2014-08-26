//
// Copyright 2013-2014 EvriChart, Inc. All Rights Reserved.
// See LICENSE.txt
//

// C++
#include <string>
#include <mutex>
#include <iostream>

// Boost
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

// Internal
#include "Eloquent/Logging.h"
#include "ConsoleWriter.h"

///////////////////////////////////////////////////////////////////////////////
// ConsoleWriter : Extension
///////////////////////////////////////////////////////////////////////////////
Eloquent::ConsoleWriter::ConsoleWriter( const boost::property_tree::ptree::value_type& i_Config
									   , std::mutex& i_LogMutex
									   , streamlog::severity_log& i_Log
									   , std::mutex& i_QueueMutex
									   , std::condition_variable& i_QueueCV
									   , std::queue<QueueItem>& i_Queue
									   , int& i_NumWriters )
: IO( i_Config, i_LogMutex, i_Log, i_QueueMutex, i_QueueCV, i_Queue, i_NumWriters )
{
	std::unique_lock<std::mutex> LogLock( m_LogMutex );
	m_Log( Eloquent::LogSeverity::SEV_INFO ) << TimeAndSpace() << "setting up a writer #Comment #Writer #ConsoleWriter" << std::endl;
	
}

Eloquent::ConsoleWriter::~ConsoleWriter() {
	std::unique_lock<std::mutex> LogLock( m_LogMutex );
	m_Log( Eloquent::LogSeverity::SEV_INFO ) << TimeAndSpace() << "shutting down #Comment #Writer #ConsoleWriter" << std::endl;
	
}

void Eloquent::ConsoleWriter::operator()() {
	boost::optional<int> Batch = m_Config.second.get_optional<int>( "batch" );
	boost::optional<std::string> Filter = m_Config.second.get_optional<std::string>( "filter" );
	
	std::string BatchData	= "";
	int			BatchCount	= 0;
	
	while( true ) {
		try {
			QueueItem& Item = NextQueueItem();
			
			std::cout << Item.Data();
			
			PopQueueItem();
			
		} catch( const std::exception& e ) {
			std::unique_lock<std::mutex> LogLock( m_LogMutex );
			m_Log( Eloquent::LogSeverity::SEV_ERROR ) << TimeAndSpace() << e.what() << "#Error #Writer #ConsoleWriter" << std::endl;
			
		} catch( ... ) {
			std::unique_lock<std::mutex> LogLock( m_LogMutex );
			m_Log( Eloquent::LogSeverity::SEV_ERROR ) << TimeAndSpace() << "unknown exception #Error #Attention #Writer #ConsoleWriter" << std::endl;
			
		}
		
	}
	
	delete this;
	
}