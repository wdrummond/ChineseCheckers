#ifndef _RUBY_H_
#define _RUBY_H_

#include <ai_ccheckers.h>

namespace wsd
{
  class Ruby : public ai::Agent::AgentProgram
  {
  public:
    Ruby();
    ~Ruby();
    int Max(int player, ai::CCheckers::BasicBoard b, const std::vector<ai::CCheckers::MoveData> & moves);
    int Min(int player, ai::CCheckers::BasicBoard b);
    virtual ai::Agent::Action * Program(const ai::Agent::Percept * percept);
  protected:
  private:
  };
}


#endif /* _RUBY_H_ */