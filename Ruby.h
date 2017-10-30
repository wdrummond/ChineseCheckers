#ifndef _RUBY_H_
#define _RUBY_H_

#include <ai_ccheckers.h>
#include <algorithm>
#include "utility"

namespace wsd
{
  class Ruby : public ai::Agent::AgentProgram
  {
  public:
    Ruby();
    ~Ruby();
    double evaluate(int player, int opponent, ai::CCheckers::BasicBoard& b);
    struct result Max(int player, int opponent, ai::CCheckers::BasicBoard& b, int d, double alpha, double beta);
    struct result Min(int player, int opponent, ai::CCheckers::BasicBoard& b, int d, double alpha, double beta);
    std::vector<ai::CCheckers::MoveData> & sortmoves(std::vector<ai::CCheckers::MoveData> & moves);
    virtual ai::Agent::Action * Program(const ai::Agent::Percept * percept);
  protected:
  private:
  };
}


#endif /* _RUBY_H_ */