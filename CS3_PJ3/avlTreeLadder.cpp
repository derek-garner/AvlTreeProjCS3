#include "avlTreeLadder.h"

ostream & operator<<(ostream & ss, const WordLadderState &gs)
{
	for (int i = 0; i < gs.wordLadder.size(); i++) {
		ss << gs.wordLadder[i]<<" ";
	}
	return ss;
}
