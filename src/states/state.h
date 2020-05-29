#ifndef SRC_STATES_STATE_H_
#define SRC_STATES_STATE_H_

#include <memory>

#include <SFML/Graphics.hpp>

enum {
  STATE_RUNNING = 0,
  STATE_PAUSE,
  STATE_EXIT,
};

class State {
 public:
  State();
  virtual ~State();

  virtual void handleInput() = 0;
  virtual void update(sf::Time delta) = 0;
  virtual void render(sf::RenderWindow *window = nullptr) = 0;

  void resume() { state_ = STATE_RUNNING; }
  int getState() const { return state_; }
  std::unique_ptr<State>& getNext() { return next_; }

  void exitState(std::unique_ptr<State> next = nullptr);
  void pushState(std::unique_ptr<State> next);

 private:
  int state_;
  std::unique_ptr<State> next_;
};

#endif  // SRC_STATES_STATE_H_
