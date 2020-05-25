#include "state.h"

#include <iostream>
#include <memory>
#include <cassert>

State::State() : state_(STATE_RUNNING), next_(nullptr)
{
#ifdef DEBUG
  std::cout << "[State] ctor" << std::endl;
#endif
}
State::~State()
{
#ifdef DEBUG
  std::cout << "[State] dtor" << std::endl;
#endif
}


void State::exitState(std::unique_ptr<State> next)
{
  if (next) {
    next_ = std::move(next);
  }
  else {
    assert(!next_);
  }
  state_ = STATE_EXIT;
}

void State::pushState(std::unique_ptr<State> next)
{
  assert(next);
  next_ = std::move(next);
  state_ = STATE_PAUSE;
}
