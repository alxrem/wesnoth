/* $Id$ */
/*
   Copyright (C) 2009 by Mark de Wever <koraq@xs4all.nl>
   Part of the Battle for Wesnoth Project http://www.wesnoth.org/

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License version 2
   or at your option any later version.
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY.

   See the COPYING file for more details.
*/

#ifndef GUI_WIDGETS_AUXILIARY_EVENT_HANDLER_HPP_INCLUDED
#define GUI_WIDGETS_AUXILIARY_EVENT_HANDLER_HPP_INCLUDED

#include <boost/mpl/set.hpp>

#include <iosfwd>

namespace gui2 {

namespace event {

class tdispatcher;

class tmanager
{
public:
	tmanager();
	~tmanager();
};

/**
 * The event send to the dispatcher.
 *
 * Events prefixed by SDL are (semi)-real SDL events. The handler does some
 * minor decoding like splitting the button down event to the proper event but
 * nothing more. Events without an SDL prefix are generated by another signal
 * eg the windows signal handler for SDL_MOUSE_MOTION can generate a
 * MOUSE_ENTER, MOUSE_MOTION and MOUSE_LEAVE event and send that to it's
 * children.
 */
enum tevent {
	  DRAW

	, SDL_MOUSE_MOTION
	, MOUSE_ENTER
	, MOUSE_MOTION
	, MOUSE_LEAVE

	, SDL_LEFT_BUTTON_DOWN
	, SDL_LEFT_BUTTON_UP

	, SDL_MIDDLE_BUTTON_DOWN
	, SDL_MIDDLE_BUTTON_UP

	, SDL_RIGHT_BUTTON_DOWN
	, SDL_RIGHT_BUTTON_UP

	, SDL_WHEEL_LEFT
	, SDL_WHEEL_RIGHT
	, SDL_WHEEL_UP
	, SDL_WHEEL_DOWN

	, SDL_KEY_DOWN
};

/**
 * Helper for catching use error of tdispatcher::connect_signal.
 *
 * This helper is needed as a user can't supply the wrong kind of callback
 * functions to tdispatcher::connect_signal. If a wrong callback would be send
 * it will never get called.
 *
 * This version is for callbacks without extra parameters.
 * NOTE some mouse functions like MOUSE_ENTER don't send the mouse coordinates
 * to the callback function so they are also in this catagory.
 */
typedef
		boost::mpl::set<
			  boost::mpl::int_<DRAW>
			, boost::mpl::int_<MOUSE_ENTER>
			, boost::mpl::int_<MOUSE_LEAVE>
			, boost::mpl::int_<SDL_WHEEL_LEFT>
			, boost::mpl::int_<SDL_WHEEL_RIGHT>
			, boost::mpl::int_<SDL_WHEEL_UP>
			, boost::mpl::int_<SDL_WHEEL_DOWN>
		>
		tset_event;

/**
 * Helper for catching use error of tdispatcher::connect_signal.
 *
 * This version is for callbacks with a coordinate as extra parameter.
 */
typedef
		boost::mpl::set<
			  boost::mpl::int_<SDL_MOUSE_MOTION>
			, boost::mpl::int_<MOUSE_MOTION>
			, boost::mpl::int_<SDL_LEFT_BUTTON_DOWN>
			, boost::mpl::int_<SDL_LEFT_BUTTON_UP>
			, boost::mpl::int_<SDL_MIDDLE_BUTTON_DOWN>
			, boost::mpl::int_<SDL_MIDDLE_BUTTON_UP>
			, boost::mpl::int_<SDL_RIGHT_BUTTON_DOWN>
			, boost::mpl::int_<SDL_RIGHT_BUTTON_UP>
		>
		tset_event_mouse;

/**
 * Helper for catching use error of tdispatcher::connect_signal.
 *
 * This version is for callbacks with the keyboard values (these haven't been
 * determined yet).
 */
typedef
		boost::mpl::set<
			boost::mpl::int_<SDL_KEY_DOWN>
		>
		tset_event_keyboard;

/**
 * Connects a dispatcher to the event handler.
 *
 * @param dispatcher              The dispatcher to connect.
 */
void connect_dispatcher(tdispatcher* dispatcher);

/**
 * Disconnects a dispatcher to the event handler.
 *
 * @param dispatcher              The dispatcher to disconnect.
 */
void disconnect_dispatcher(tdispatcher* dispatcher);


/**
 * Captures the mouse.
 *
 * A dispatcher can capture the mouse, when for example it's pressed on a
 * button, this means all mouse events after that are send to that widget.
 *
 * @param dispatcher              The dispatcher which should get the mouse
 *                                focus.
 */
void capture_mouse(tdispatcher* dispatcher);

/**
 * Releases a captured mouse.
 *
 * @param dispatcher              The dispatcher which should release the mouse
 *                                capture.
 */
void release_mouse(tdispatcher* dispatcher);


std::ostream& operator<<(std::ostream& stream, const tevent event);

} // namespace event

} // namespace gui2

#endif

