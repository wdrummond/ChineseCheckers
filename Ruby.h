#ifndef _RUBY_H_
#define _RUBY_H_

#include <ai_ccheckers.h>
#include "utility"

namespace wsd
{
  class Ruby : public ai::Agent::AgentProgram
  {
  public:
    Ruby();
    ~Ruby();
    double evaluate(int player, int opponent, ai::CCheckers::BasicBoard b);
    struct result Max(int player, int opponent, ai::CCheckers::BasicBoard b, int d);
    struct result Min(int player, int opponent, ai::CCheckers::BasicBoard b, int d);
    //std::pair<int, double> Max(int player, ai::CCheckers::BasicBoard b, const std::vector<ai::CCheckers::MoveData> & moves, int d);
    //std::pair<int, double> Min(int player, ai::CCheckers::BasicBoard b, int d);
    virtual ai::Agent::Action * Program(const ai::Agent::Percept * percept);
  protected:
  private:
  };
}


#endif /* _RUBY_H_ */