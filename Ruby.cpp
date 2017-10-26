#include "Ruby.h"


namespace wsd 
{
	struct result 
	{
		double hueristic;
		int move_choice;
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

      const std::vector<ai::CCheckers::MoveData> & moves = board.DetermineLegalMoves(player);

      // move = moves[rand() % moves.size()];    

      //double       best_heuristic = -1e5;
      //int best_move = 0;
      //std::pair<int, double> bests = Max(player, board, moves, 3);
      //int best_move = bests.first;

      int opponent = (player == 1) ? 2 : 1;
      struct result results = Max(player, opponent, board, 3);  //Note this is the agents function

      if(moves.size() > 0)
        {
          move = moves[results.move_choice];
        }  

      action->SetMove(move);
      action->SetCode(ai::CCheckers::Action::MOVE);

      return action;
    }

    double Ruby::evaluate(int player, int opponent, ai::CCheckers::BasicBoard b) {
    	double h = b.Forwardness(player) - b.Forwardness(opponent);
    	return h;
    }

    result Ruby::Max(int player,int opponent, ai::CCheckers::BasicBoard b, int d) {
    	if (d > 0) {
    		d -= 1;
      	} else {
      		result res;
      		res.hueristic = evaluate(player, opponent, b);
      		return res;
      	}

      	result res;
      	res.hueristic = -1e5;
      	const std::vector<ai::CCheckers::MoveData> & moves = b.DetermineLegalMoves(player);

      	for(unsigned int i=0; i<moves.size(); i++)
      	{
      		ai::CCheckers::BasicBoard b1(b);
          	b1.Move(player, moves[i], 0);

      		result o_res = Min(player, opponent, b1, d);

      		if (o_res.hueristic > res.hueristic) {
      			res.hueristic = o_res.hueristic;
      			res.move_choice = i;
      		} 

      	}

      	return res;
    }

    result Ruby::Min(int player,int opponent, ai::CCheckers::BasicBoard b, int d) {
    	if (d > 0) {
    		d -= 1;
      	} else {
      		result res;
      		res.hueristic = evaluate(player, opponent, b);
      		return res;
      	}

      	result res;
      	res.hueristic = 1e5;
      	const std::vector<ai::CCheckers::MoveData> & o_moves = b.DetermineLegalMoves(opponent);

      	for(unsigned int i=0; i<o_moves.size(); i++) 
      	{

      		ai::CCheckers::BasicBoard b1(b);
          	b1.Move(opponent, o_moves[i], 0);
          	result oh = Max(player, opponent, b1, d);

          	if (oh.hueristic < res.hueristic) {
      			res.hueristic = oh.hueristic;
      			res.move_choice = i;
      		}     

      	}

      	return res;
    }

    // std::pair<int, double> Ruby::Max(int player, ai::CCheckers::BasicBoard b, const std::vector<ai::CCheckers::MoveData> & moves, int d) {
    //   	if (d >= 0) {
    //     	d -= 1;
    //   	} 
    //   	else {
    //   		std::pair<int, double> bests;
    //   		bests.first = 0;
    //   		bests.second = b.Forwardness(player);
    //     	return bests;
    //   	}

    // 	double       best_heuristic = -1e5;
    // 	unsigned int best_move = 0;

    // 	for(unsigned int i=0; i<moves.size(); i++)
    //     {
    //     	ai::CCheckers::BasicBoard b1(b);

    //     	b1.Move(player, moves[i], 0);
    //     	double h = b1.Forwardness(player);  //Note this is the agents function

    //     	int opponent = (player == 1) ? 2 : 1;
    //     	double oh = b1.Forwardness(opponent);
    //     	h = h - oh;
        	
    //     	if(h>best_heuristic)
    //     	{
    //     		best_heuristic = h;
    //         	best_move = i;
    //       	}
    //       	else if(h==best_heuristic && rand()%2==0)
    //       	{
    //         	best_heuristic = h;
    //         	best_move = i;
    //       	}

    //         std::pair<int, double> opp_best = Min(player, b, d);
    //         if (opp_best.second > best_heuristic) 
    //         {
    //          	best_move = opp_best.first;
    //         }         
    //     } // for each possible move

    //     std::pair<int, double> bests;
    //     bests.first = best_move;
    //     bests.second = best_heuristic;
    //   	return bests;
    // }

    // std::pair<int, double> Ruby::Min(int player, ai::CCheckers::BasicBoard b, int d) {
    // 	if (d >= 0) {
    // 		d -= 1;
    //   	} 
    //   	else {
    //     	std::pair<int, double> bests;
    //   		bests.first = 0;
    //   		bests.second = b.Forwardness(player);
    //     	return bests;
    //   	}

    //   	int opponent = (player == 1) ? 2 : 1;
    // 	double       best_heuristic = -1e5;
    // 	unsigned int best_move = 0;
    // 	const std::vector<ai::CCheckers::MoveData> & moves = b.DetermineLegalMoves(opponent);

    // 	for(unsigned int i=0; i<moves.size(); i++)
    //     {
    //     	ai::CCheckers::BasicBoard b1(b);
    //     	b1.Move(player, moves[i], 0);

    //     	double h = b1.Forwardness(player);  //Note this is the agents function

    //     	double oh = b1.Forwardness(opponent);
    //     	h = h - oh;
    //     	//h *= -1;
    //     	if(h<best_heuristic)
    //     	{
    //     		best_heuristic = h;
    //         	best_move = i;
    //       	}
    //       	else if(h==best_heuristic && rand()%2==0)
    //       	{
    //           	best_heuristic = h;
    //           	best_move = i;
    //       	}

    //       	const std::vector<ai::CCheckers::MoveData> & movess = b.DetermineLegalMoves(player);
    //       	std::pair<int, double> opp_best = Max(player, b, movess, d);
    //       	if (opp_best.second < best_heuristic) 
    //       	{
    //        	 	best_move = opp_best.first;
    //       	}          
    //     } // for each possible move
    //     std::pair<int, double> bests;
    //     bests.first = best_move;
    //     bests.second = best_heuristic;
    //   	return bests;
    // }

}
