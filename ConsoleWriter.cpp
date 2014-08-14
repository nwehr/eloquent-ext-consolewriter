//
// Copyright 2013-2014 EvriChart, Inc. All Rights Reserved.
// See LICENSE.txt
//

// C++
#include <string>
#include <mutex>

// Boost
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

// Internal
#include "Eloquent/Global/Logging.h"
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
: IOExtension( i_Config, i_LogMutex, i_Log, i_QueueMutex, i_QueueCV, i_Queue, i_NumWriters )
{
	//boost::this_thread::disable_interruption DI;
	
	std::unique_lock<std::mutex> LogLock( m_LogMutex );
	m_Log( Eloquent::LogSeverity::SEV_INFO ) << "ConsoleWriter::ConsoleWriter() - info - setting up a writer" << std::endl;
	
}

Eloquent::ConsoleWriter::~ConsoleWriter() {
	std::unique_lock<std::mutex> LogLock( m_LogMutex );
	m_Log( Eloquent::LogSeverity::SEV_INFO ) << "ConsoleWriter::ConsoleWriter() - info - shutting down" << std::endl;
	
}

void Eloquent::ConsoleWriter::operator()() {
	boost::optional<int> Batch = m_Config.second.get_optional<int>( "batch" );
	boost::optional<std::string> Filter = m_Config.second.get_optional<std::string>( "filter" );
	
	std::string BatchData	= "";
	int			BatchCount	= 0;
	
	while( true ) {
		try {
			QueueItem& Item = NextQueueItem();
			
			{
				if( Batch.is_initialized() ) {
					{
						std::unique_lock<std::mutex> QueueLock( m_QueueMutex );
						
						if( Filter.is_initialized() )
							BatchData.append( m_FilterCoordinator->FilterData( Item.Data() ) );
						else BatchData.append( Item.Data() );
						
					}
					
					if( *Batch == (BatchCount + 1)  ) {
						std::cout << BatchData;
						
						BatchData	= "";
						BatchCount	= 0;
						
					} else ++BatchCount;
					
				} else {
					if( Filter.is_initialized() ) {
						std::unique_lock<std::mutex> QueueLock( m_QueueMutex );
						std::cout << m_FilterCoordinator->FilterData( Item.Data() );
						
					} else {
						std::unique_lock<std::mutex> QueueLock( m_QueueMutex );
						std::cout << Item.Data();
						
					}
					
				}
				
			}
			
			PopQueueItem();
			
		} catch( const std::exception& e ) {
			std::unique_lock<std::mutex> LogLock( m_LogMutex );
			m_Log( Eloquent::LogSeverity::SEV_ERROR ) << "ConsoleWriter::operator()() - error - " << e.what() << std::endl;
			
		} catch( ... ) {
			std::unique_lock<std::mutex> LogLock( m_LogMutex );
			m_Log( Eloquent::LogSeverity::SEV_ERROR ) << " - ConsoleWriter::operator()() - error - unknown exception" << std::endl;
			
		}
		
	}
	
	delete this;
	
}