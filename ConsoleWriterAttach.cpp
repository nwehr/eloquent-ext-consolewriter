//
// Copyright 2013-2014 EvriChart, Inc. All Rights Reserved.
// See LICENSE.txt
//

// Internal
#include "ConsoleWriterFactory.h"

extern "C" void* Attach( void );
extern "C" void* Attach( void ) {
	return new Eloquent::ConsoleWriterFactory();
}
