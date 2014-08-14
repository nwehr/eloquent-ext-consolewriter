//
// Copyright 2013-2014 EvriChart, Inc. All Rights Reserved.
// See LICENSE.txt
//

// Internal
#include "ConsoleWriterAttach.h"

extern "C" void* Attach( void ) {
	return new Eloquent::ConsoleWriterFactory( Eloquent::EXTENSION_NAME, Eloquent::EXTENSION_VERSION, Eloquent::EXTENSION_AUTHOR, Eloquent::EXTENSION_TYPE, Eloquent::EXTENSION_KEYS );
}
