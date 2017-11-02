#include "Ruby.h"


namespace wsd 
{
	struct result 
	{
		double hueristic;
		int move_choice;
	};

  struct Sorter {
    bool operator()(const ai::CCheckers::MoveData& m1, const ai::CCheckers::MoveData& m2) const {
      int end_y1 = m1.to_y - m1.from_y;
      int end_y2 = m2.to_y - m2.from_y;

      return end_y1 < end_y2;
    }
  };

  struct Sorter1 {
    bool operator()(const ai::CCheckers::MoveData& m1, const ai::CCheckers::MoveData& m2) const {
      int end_y1 = m1.to_y - m1.from_y;
      int end_y2 = m2.to_y - m2.from_y;

      return end_y1 > end_y2;
    }
  };

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

      std::vector<ai::CCheckers::MoveData> & moves = board.DetermineLegalMoves(player);
      //std::sort(moves.begin(), moves.end(), Sorter());

      int opponent = (player == 1) ? 2 : 1;
      double alpha = -1e5;
      double beta = 1e5;
      struct result results = Max(player, opponent, board, 5, alpha, beta);  //Note this is the agents function

      if(moves.size() > 0)
        {
          move = moves[results.move_choice];
        }  

      action->SetMove(move);
      action->SetCode(ai::CCheckers::Action::MOVE);

      return action;
    }

    double Ruby::evaluate(int player, int opponent, ai::CCheckers::BasicBoard& b) {
    	double h = b.Forwardness(player) - b.Forwardness(opponent);
    	return h;
    }

    result Ruby::Max(int player,int opponent, ai::CCheckers::BasicBoard& b, int d, double alpha, double beta) {
    	if (d == 0 || b.Winner(player)) {
    		  result res;
      		res.hueristic = evaluate(player, opponent, b);
      		return res;
      	} else {
      		d -= 1;
      	}

      	result res;
      	res.hueristic = -1e5;
      	std::vector<ai::CCheckers::MoveData> & moves = b.DetermineLegalMoves(player);
      	switch(player)
        {
        	case 1:
        	std::sort(moves.begin(), moves.end(), Sorter());
        	break;
        	case 2:
        	std::sort(moves.begin(), moves.end(), Sorter1());
        	break;
        	default:
        	// FIXME add calculation for each player
        	std::sort(moves.begin(), moves.end(), Sorter());
        	break;
        }
        std::sort(moves.begin(), moves.end(), Sorter());

        // unsigned int i= 0;
        // unsigned int size = moves.size();

        // #define loop(i,size) for(i; i < size; i++);
        // loop(i, size)
        //     ai::CCheckers::BasicBoard b1(b);
        //     b1.Move(player, moves[i], 0);

        //     result o_res = Min(player, opponent, b1, d, alpha, beta);

        //     if (o_res.hueristic > res.hueristic && o_res.hueristic > alpha) 
        //     {
        //         alpha = o_res.hueristic;
        //         res.hueristic = o_res.hueristic;
        //         res.move_choice = i;
        //     }

        //     if (res.hueristic > beta) {
        //         break;
        //     }

      	for(unsigned int i=0; i<moves.size(); i++)
      	{
      		  ai::CCheckers::BasicBoard b1(b);
          	b1.Move(player, moves[i], 0);

      		result o_res = Min(player, opponent, b1, d, alpha, beta);

      		if (o_res.hueristic > res.hueristic && o_res.hueristic > alpha) {
      			alpha = o_res.hueristic;
      			res.hueristic = o_res.hueristic;
      			res.move_choice = i;
      		}

      		if (res.hueristic > beta) {
      			break;
      		}


      	}

      	return res;
    }

    result Ruby::Min(int player,int opponent, ai::CCheckers::BasicBoard& b, int d, double alpha, double beta) {
    	if (d == 0 || b.Winner(player)) {
    		  result res;
      		res.hueristic = evaluate(player, opponent, b);
      		return res;
      	} else {
      		d -= 1;
      	}

      	result res;
      	res.hueristic = 1e5;
      	std::vector<ai::CCheckers::MoveData> & o_moves = b.DetermineLegalMoves(opponent);
        //std::sort(o_moves.begin(), o_moves.end(), Sorter1());
        switch(player)
        {
        	case 1:
        	std::sort(o_moves.begin(), o_moves.end(), Sorter());
        	break;
        	case 2:
        	std::sort(o_moves.begin(), o_moves.end(), Sorter1());
        	break;
        	default:
        	// FIXME add calculation for each player
        	std::sort(o_moves.begin(), o_moves.end(), Sorter());
        	break;
        }

      	for(unsigned int i=0; i<o_moves.size(); i++) 
      	{

      		  ai::CCheckers::BasicBoard b1(b);
          	b1.Move(opponent, o_moves[i], 0);
          	result oh = Max(player, opponent, b1, d, alpha, beta);

          	if (oh.hueristic < res.hueristic && oh.hueristic < beta) {
              beta = oh.hueristic;
      			  res.hueristic = oh.hueristic;
      			  res.move_choice = i;
      		}

      		if (res.hueristic < alpha) {
      			break;
      		}     

      	}

      	return res;
    }

    // std::vector<ai::CCheckers::MoveData> & Ruby::sortmoves(std::vector<ai::CCheckers::MoveData> & moves) {
    //   for(unsigned int i=0; i<moves.size(); i++)
    //   {
    //     //
    //   }
    //   return moves;
    // }

}
