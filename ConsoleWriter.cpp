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
#include "ConsoleWriter.h"

///////////////////////////////////////////////////////////////////////////////
// ConsoleWriter : Extension
///////////////////////////////////////////////////////////////////////////////
Eloquent::ConsoleWriter::ConsoleWriter( const boost::property_tree::ptree::value_type& i_Config
									   , std::mutex& i_QueueMutex
									   , std::condition_variable& i_QueueCV
									   , std::queue<QueueItem>& i_Queue
									   , int& i_NumWriters )
: IO( i_Config, i_QueueMutex, i_QueueCV, i_Queue, i_NumWriters )
{
	syslog( LOG_INFO, "setting up a writer #Comment #Writer #ConsoleWriter" );
}

Eloquent::ConsoleWriter::~ConsoleWriter() {
	syslog( LOG_INFO, "shutting down a writer #Comment #Writer #ConsoleWriter" );
}

void Eloquent::ConsoleWriter::operator()() {
	while( true ) {
		try {
			QueueItem& Item = NextQueueItem();
			std::cout << Item.Data();
			PopQueueItem();
			
		} catch( const std::exception& e ) {
			syslog( LOG_ERR, "%s #Error #Writer #ConsoleWriter", e.what() );
		} catch( ... ) {
			syslog( LOG_ERR, "unknown exception #Error #Attention #Writer #ConsoleWriter" );
			
			delete this;
			
		}
		
	}
	
}