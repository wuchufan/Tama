#pragma once

class Minigame {
public:
  virtual ~Minigame() = default;

  virtual void start() = 0;
  virtual void update() = 0;
  virtual void draw() = 0;
  virtual void primaryAction() = 0; // each game decides what the one button does
  virtual void secondaryAction() {}
  virtual bool isGameOver() const = 0;
};
