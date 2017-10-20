#include "Ruby.h"

namespace wsd 
{

	Ruby::Ruby()
    {
      SetName("Ruby");
    }

    Ruby::~Ruby()
    {
    }

     ai::Agent::Action * Ruby::Program(const ai::Agent::Percept * percept)
    {
      ai::CCheckers::Action *action = new ai::CCheckers::Action;
      ai::CCheckers::MoveData move;

      std::string board_str = percept->GetAtom("BASIC_BOARD").GetValue();
      ai::CCheckers::BasicBoard board(board_str);

      int player = atoi(percept->GetAtom("PLAYER_NUMBER").GetValue().c_str());

      const std::vector<ai::CCheckers::MoveData> & moves = board.DetermineLegalMoves(player);

      // move = moves[rand() % moves.size()];    

      // double       best_heuristic = -1e5;
      unsigned int best_move = Max(player, board, moves);

      // for(unsigned int i=0; i<moves.size(); i++)
      //   {
      //      ai::CCheckers::BasicBoard b(board);
      //     b.Move(player, moves[i], 0);
      //     double h = b.Forwardness(player);  //Note this is the agents function
      //     if(h>best_heuristic)
      //       {
      //         best_heuristic = h;
      //         best_move = i;
      //       }
      //     else if(h==best_heuristic && rand()%2==0)
      //       {
      //         best_heuristic = h;
      //         best_move = i;
      //       }         
      //   } // for each possible move

      if(moves.size() > 0)
        {
          move = moves[best_move];
        }  

      action->SetMove(move);
      action->SetCode(ai::CCheckers::Action::MOVE);

      return action;
    }

    int Ruby::Max(int player, ai::CCheckers::BasicBoard b, const std::vector<ai::CCheckers::MoveData> & moves) {
    	double       best_heuristic = -1e5;
    	unsigned int best_move = 0;

    	for(unsigned int i=0; i<moves.size(); i++)
        {
        	ai::CCheckers::BasicBoard b1(b);
        	b1.Move(player, moves[i], 0);
        	double h = b1.Forwardness(player);  //Note this is the agents function

        	int opponent = (player == 1) ? 2 : 1;
        	double oh = b1.Forwardness(opponent);
        	h = h - oh;
        	if(h>best_heuristic)
        	{
        		best_heuristic = h;
              	best_move = i;
            }
          	else if(h==best_heuristic && rand()%2==0)
            {
              	best_heuristic = h;
              	best_move = i;
            }         
        } // for each possible move
      	return best_move;
    }

    int Ruby::Min(int player, ai::CCheckers::BasicBoard b) {
    	double       best_heuristic = -1e5;
    	unsigned int best_move = 0;
    	const std::vector<ai::CCheckers::MoveData> & moves = b.DetermineLegalMoves(player);

    	for(unsigned int i=0; i<moves.size(); i++)
        {
        	//ai::CCheckers::BasicBoard b(board);
        	b.Move(player, moves[i], 0);
        	//need to switch player
        	player = 1 ? 2 : 1;
        	double h = b.Forwardness(player);  //Note this is the agents function

        	int opponent = 1 ? 2 : 1;
        	double oh = b.Forwardness(opponent);
        	h = h - oh;
        	h *= -1;
        	if(h>best_heuristic)
        	{
        		best_heuristic = h;
              	best_move = i;
            }
          	else if(h==best_heuristic && rand()%2==0)
            {
              	best_heuristic = h;
              	best_move = i;
            }         
        } // for each possible move
      	return best_move;
    	return 0;
    }

}
