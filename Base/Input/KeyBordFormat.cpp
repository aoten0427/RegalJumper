#include"pch.h"
#include"KeyBordFormat.h"

KeyBordFormat::KeyBordFormat()
{
	// ÉLÅ[Çìoò^
	AddButton("A", 'A');
	AddButton("B", 'B');
	AddButton("C", 'C');
	AddButton("D", 'D');
	AddButton("E", 'E');
	AddButton("F", 'F');
	AddButton("G", 'G');
	AddButton("H", 'H');
	AddButton("I", 'I');
	AddButton("J", 'J');
	AddButton("K", 'K');
	AddButton("L", 'L');
	AddButton("M", 'M');
	AddButton("N", 'N');
	AddButton("O", 'O');
	AddButton("P", 'P');
	AddButton("Q", 'Q');
	AddButton("R", 'R');
	AddButton("S", 'S');
	AddButton("T", 'T');
	AddButton("U", 'U');
	AddButton("V", 'V');
	AddButton("W", 'W');
	AddButton("X", 'X');
	AddButton("Y", 'Y');
	AddButton("Z", 'Z');

	AddButton("Up", VK_UP);
	AddButton("Down", VK_DOWN);
	AddButton("Left", VK_LEFT);
	AddButton("Right", VK_RIGHT);

	AddButton("Space", VK_SPACE);
	AddButton("Enter", VK_RETURN);
	AddButton("Escape", VK_ESCAPE);

	AddButton("RClick", VK_RBUTTON);
	AddButton("LClick", VK_LBUTTON);
}

const bool KeyBordFormat::CheckButtonState(char cord)
{
	return GetAsyncKeyState(cord) & 0x8000;
}
