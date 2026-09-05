#pragma once

class Minigame {
public:
  virtual ~Minigame() = default;

  virtual void start() = 0;
  virtual void update() = 0;
  virtual void draw() = 0;
  virtual void primaryAction() = 0; // each game decides what the one button does
  virtual void secondaryAction() {}
  virtual int getScore() const { return 0; } // optional; default 0, override if the game tracks one
  virtual bool isGameOver() const = 0;
};
