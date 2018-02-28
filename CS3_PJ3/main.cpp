#include "game.h"
#include <iostream>
#include <fstream>
using namespace std;
int main()
{

	const int RANDOMCT = 4;
	Game g("dictionary.txt");

	g.avlTestandDisplay();
	g.play("kiss", "woof");
	g.play("cock", "numb");
	g.play("jura", "such");
	g.play("stet", "whey");
	
	
	return 0;
}
