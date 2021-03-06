/*
 * Copyrights (c):
 *     2001 - 2008 , Werner Freytag.
 *     2009, Haiku
 * Distributed under the terms of the MIT License.
 *
 * Original Author:
 *              Werner Freytag <freytag@gmx.de>
 */

#include "InputFilter.h"

#include <InterfaceDefs.h>
#include <Looper.h>
#include <Message.h>
#include <Messenger.h>
#include <OS.h>
#include <stdio.h>

//------------------------------------------------------------------------

extern "C" BInputServerFilter* instantiate_input_filter() {
	return new InputFilter();
}

//------------------------------------------------------------------------

InputFilter::InputFilter()
{
}

filter_result InputFilter::Filter(BMessage *message, BList *outList) {
	
	const int32	kControlKeys = B_COMMAND_KEY | B_SHIFT_KEY;
	
	if (message->what == B_KEY_DOWN ) {

		int32 raw;
		int32 mods;
		
		if ((message->FindInt32("raw_char", 0, (int32 *)&raw) == B_OK)
			&& (message->FindInt32("modifiers", (int32 *)&mods) == B_OK)
			&& (raw==118) // v
			&& ((mods & kControlKeys) == kControlKeys) ) {
			
			port_id port = find_port("ClipUp input port");

			if (port!=B_NAME_NOT_FOUND) {
				write_port( port, 'CtSV', NULL, 0 );
				return B_SKIP_MESSAGE;
			}
		}
	}
	
	return B_DISPATCH_MESSAGE;
}

status_t InputFilter::InitCheck() {
	return B_OK;
}
