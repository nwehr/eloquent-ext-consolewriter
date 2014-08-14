#ifndef __eloquent__ConsoleWriterAttach__
#define __eloquent__ConsoleWriterAttach__

//
// Copyright 2013-2014 EvriChart, Inc. All Rights Reserved.
// See LICENSE.txt
//

// C++
#include <string>
#include <vector>

// Boost
#include <boost/smart_ptr.hpp>

// Internal
#include "ConsoleWriterFactory.h"

namespace Eloquent {
	static const std::string EXTENSION_NAME		= "console";
	static const std::string EXTENSION_VERSION	= "1.0";
	static const std::string EXTENSION_AUTHOR	= "Donald Cluck <donaldc@evrichart.com>";
	static const std::string EXTENSION_TYPE		= "write";
	
	static std::vector<std::string> EXTENSION_KEYS;
}

// Library Initialization
extern "C" void* Attach( void );

#endif /* defined(__eloquent__ConsoleWriterAttach__) */
