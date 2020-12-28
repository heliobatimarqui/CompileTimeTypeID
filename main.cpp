#include "Events.h"

void handle_event(const IEvent& e) {
  switch(e.get_id()) {
    case MouseEvent::id:
      static_cast<const MouseEvent&>(e).do_mouse_event_stuff();
      break;
    case KeyboardEvent::id:
      static_cast<const KeyboardEvent&>(e).do_keyboard_event_stuff();
      break;
    case JoystickEvent::id:
      static_cast<const JoystickEvent&>(e).do_joystick_event_stuff();
      break;
    default:
      std::cout << "Event not recognized.\n";
  }
}

int main() {
  MouseEvent m;
  KeyboardEvent k;
  JoystickEvent j;

  handle_event(m);
  handle_event(k);
  handle_event(j);
  
  return 0;
}

