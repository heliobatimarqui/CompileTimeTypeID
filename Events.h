#include "TypeList.h"
#include <iostream>

class MouseEvent;
class KeyboardEvent;
class JoystickEvent;

using EngineEvents = TypeList<MouseEvent, KeyboardEvent, JoystickEvent>;


class IEvent {
  protected:
  IEvent() = default;
  public:
  virtual ~IEvent() = default;
  virtual const id_type get_id() const = 0;
};


template<typename Event>
class EngineEvent : public IEvent {
  static_assert(EngineEvents::index_of<Event>() != -1, "Event not at the EngineEvents list");
  EngineEvent() = default;
  virtual ~EngineEvent() = default;
  //If the user uses this incorrectly a compilation error will happen. It avoids two different events with the same id.
  friend Event;
public:
  const id_type get_id() const override {
    return id;
  }
  static constexpr id_type id = EngineEvents::index_of<Event>();
};



class MouseEvent : public EngineEvent<MouseEvent> {
  public:
  void do_mouse_event_stuff() const {
    std::cout << "Doing MouseEvent stuff\n";
  };
};

class KeyboardEvent : public EngineEvent<KeyboardEvent> {
  public:
  void do_keyboard_event_stuff() const {
    std::cout << "Doing KeyboardEvent stuff\n";
  };
};

class JoystickEvent : public EngineEvent<JoystickEvent> {
  public:
  void do_joystick_event_stuff() const {
    std::cout << "Doing JoystickEvent stuff\n";
  };
};
