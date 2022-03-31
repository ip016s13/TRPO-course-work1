#include <iostream>
#include <windows.h>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class GameLife {

private:
	std::vector<std::vector<bool> > ArrayFirst;
	std::vector<std::vector<bool> > ArraySecond;
	bool isFirst;
	char keyYES;
	char keyNO;
	int Gen;

	byte calc(const int& x, const int& y, const vector<vector<bool> >& Array) 
	{
		byte buffer = 0;

		if (x >= 1 && y >= 1 && x < Array.size() - 1 && y < Array[0].size() - 1)
		{
			if (Array[x - 1][y - 1]) buffer++;
			if (Array[x][y - 1]) buffer++;
			if (Array[x + 1][y - 1]) buffer++;

			if (Array[x - 1][y]) buffer++;
			if (Array[x + 1][y]) buffer++;

			if (Array[x - 1][y + 1]) buffer++;
			if (Array[x][y + 1]) buffer++;
			if (Array[x + 1][y + 1]) buffer++;
		}
		else
		{
			if (y - 1 <= Array[0].size() && y - 1 >= 0)
			{
				if (x - 1 >= 0)
					if (Array[x - 1][y - 1]) buffer++;

				if (Array[x][y - 1]) buffer++;

				if (x + 1 < Array.size())
					if (Array[x + 1][y - 1]) buffer++;
			}

			if (y <= Array[0].size() && y >= 0)
			{
				if (x - 1 >= 0)
					if (Array[x - 1][y]) buffer++;

				if (x + 1 < Array.size())
					if (Array[x + 1][y]) buffer++;
			}

			if (y + 1 < Array[0].size() && y + 1 >= 0)
			{
				if (x - 1 >= 0)
					if (Array[x - 1][y + 1]) buffer++;

				if (Array[x][y + 1]) buffer++;

				if (x + 1 < Array.size())
					if (Array[x + 1][y + 1]) buffer++;

			}
		}

		return buffer;
	}

	bool rule(const int& x, const int& y)
	{
		byte sum;
		bool status;

		if (isFirst)
		{
			status = ArraySecond[x][y];
			sum = calc(x, y, ArraySecond);

		}
		else
		{
			status = ArrayFirst[x][y];
			sum = calc(x, y, ArrayFirst);
		}

		if (status)
		{
			return (sum == 2 || sum == 3);
		}
		else
		{
			return (sum == 3);
		}
	}

public:
	GameLife()
	{
		int chance = 70; //1 - 100
		int sizeH = 20; //Height
		int sizeW = 40; //Width
		ArrayFirst.resize(sizeH);
		ArraySecond.resize(sizeH);
		isFirst = true;

		srand(static_cast<unsigned int>(time(0)));
		for (int i = 0; i < sizeH; i++)
		{
			ArrayFirst[i].resize(sizeW);
			ArraySecond[i].resize(sizeW);
			for (int j = 0; j < sizeW; j++)
			{
				if ((100 - chance) < rand() % 100) ArrayFirst[i][j] = true;
				else ArrayFirst[i][j] = false;

				ArraySecond[i][j] = ArrayFirst[i][j];
			}
		}

		keyYES = (char)219;
		keyNO = (char)176;
		Gen = 0;
	}

	void PrintPlus()
	{
		if (!isFirst) ArrayFirst = ArraySecond;

		std::cout << (char)201;

		for (int j = 0; j < ArrayFirst[0].size(); j++)
			std::cout << (char)205;

		std::cout << (char)187;

		std::cout << std::endl;

		for (int i = 0; i < ArrayFirst.size();i++)
		{
			std::cout << (char)186;

			for (int j = 0; j < ArrayFirst[0].size(); j++)
				if (isFirst)
				{
					if (ArrayFirst[i][j]) std::cout << keyYES;
					else std::cout << keyNO;
				}
				else
				{
					if (ArraySecond[i][j]) std::cout << keyYES;
					else std::cout << keyNO;
				}
			std::cout << (char)186 << std::endl;
		}

		std::cout << (char)200;

		for (int j = 0; j < ArrayFirst[0].size(); j++)
			std::cout << (char)205;

		std::cout << (char)188;

		std::cout << endl << ArrayFirst.size() << "x" << ArrayFirst[0].size() << "; isFirst = " << isFirst << "; Gen = " << Gen << endl;
	}

	void Print()
	{
		for (int i = 0; i < ArrayFirst.size(); i++)
		{
			for (int j = 0; j < ArrayFirst[0].size(); j++)
				if (isFirst)
				{
					if (ArrayFirst[i][j]) std::cout << keyYES;
					else std::cout << keyNO;
				}
				else
				{
					if (ArraySecond[i][j]) std::cout << keyYES;
					else std::cout << keyNO;
				}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	void Update()
	{
		Gen++;

		for (int i = 0; i < ArrayFirst.size(); i++)
			for (int j = 0; j < ArrayFirst[0].size(); j++)
			{
				if (isFirst) ArrayFirst[i][j] = rule(i, j);
				else ArraySecond[i][j] = rule(i, j);
			}

		isFirst = !isFirst;
	}

	bool isUpdated()
	{
		return!(ArrayFirst == ArraySecond);
	}
};

int main()
{
	srand(100);
	int i = 0;
	GameLife demo;
	demo.PrintPlus(); 

	bool play = true;
	while (play)
	{
		std::system("cls");
		demo.PrintPlus();
		demo.Update();

		if (i % 10 == 0) play = demo.isUpdated();
		Sleep(100);
		i++;
	}
}

