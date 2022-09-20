#include "wrapper.h"

void wrapper::run() 
{
	int option, score = 0;
	bool exit = false;

	importlinuxlist();
	importplayers();

	while (!exit) {
		printmenu();
		option = prompt(1, 6, "Enter an option from 1 to 6 : ");
		system("cls");

		switch (option) {
		case 1:
			printrules();
			break;
		case 2:
			playgame(score);
			break;
		case 3:
			loadprevioussave(score);
			break;
		case 4:
			add();
			break;
		case 5:
			remove();
			break;
		case 6:
			exit = true;
			if (this->modified) {
				savequestion();
			}
			saveplayers();
			break;
		}
	}
}

void wrapper::printmenu()
{
	string options[6] = { "Game Rules", "Play Game", "Load Previous Game",
		"Add Command", "Remove Command", "Exit" };

	for (int i = 1; i < 7; i++) {
		cout << "[" << i << "] " << options[i - 1] << std::endl;
	}
}


void wrapper::printrules() 
{
	cout << "To score a point you must match the linux command with the correct description. A correct answer gives you +1 points. If the answer is incorrect you will get -1 points. Note that it is possible to get a negative final score.";
	cout << endl;
}

void wrapper::importlinuxlist() 
{
	string line;
	mQuestions.clearList();
	question newData;

	std::ifstream dataline;
	dataline.open(mlinuxFile);

	dataline.clear();
	dataline.seekg(0);

	while (getline(dataline, line)) 
	{
		newData = parselinuxline(line);
		mQuestions.insertAtFront(newData);
	}
	dataline.close();
}

void wrapper::importplayers() 
{
	string line;
	for (int i = 0; i < 10; i++)
	{
		players[i].name = "";
		players[i].score = 0;
	}
	playerCount = 0;

	std::ifstream gameStream;
	gameStream.open(mGameFile);

	gameStream.clear();
	gameStream.seekg(0);

	while (getline(gameStream, line) && playerCount < 16) 
	{
		players[playerCount] = parseplayer(line);
		playerCount++;
	}

	gameStream.close();
}

question wrapper::parselinuxline(string line) 
{
	string item;
	std::stringstream dataline;
	question newData;

	dataline.str(line);

	//get question and description
	getline(dataline, item, ',');
	newData.name = item;

	if (dataline.peek() == '"') 
	{
		// get question
		getline(dataline, item, '"');
		// get description
		getline(dataline, item, '"');
	}
	else 
	{
		getline(dataline, item, ',');
	}
	newData.description = item;

	return newData;
}

player wrapper::parseplayer(string line) 
{
	string item;
	std::stringstream dataline;
	player newData;

	//get name and score
	dataline.str(line);

	// get name
	getline(dataline, item, ',');
	newData.name = item;

	// get score
	getline(dataline, item, ',');
	newData.score = stoi(item);

	return newData;
}

void wrapper::playgame(int startScore) 
{
	int score = startScore;
	int totalquestions = 0;
	string name;
	cout << "Enter your username: ";
	cin >> name;

	int questions = prompt(1, 5, "Pick between 1 and 5 randomized questions: ");
	int linuxlist[3];
	int printorder[3];
	int usedlist[5] = { 0 };

	//post 3 random commands
	for (int i = 0; i < questions; i++) {
		do {
			randomize(linuxlist, 3, 0, mQuestions.getLength() - 1);
		} while (usedlist[linuxlist[0]]);

		usedlist[linuxlist[0]] = 1;

		//randomize answers
		randomize(printorder, 3, 0, 2);

		//print linux commands
		int correct = linuxlist[0];
		cout << mQuestions.getNodeAtPosition(correct)->data.name << endl;

		int desc;
		for (int i = 0; i < 3; i++) {
			desc = printorder[i];
			cout << i << ") ";
			cout << mQuestions.getNodeAtPosition(linuxlist[desc])->data.description << endl;
		}

		// get user guess and check adjust score
		int useranswer = prompt(0, 2, "Which command does this correspond to? ");
		totalquestions++;

		system("cls");

		if (printorder[useranswer] == 0) 
		{
			//correct
			score++;
			cout << "Good! Your score is now " << score << endl;
		}
		else 
		{
			//incorrect
			score--;
			cout << "Wrong! Your score is now " << score << endl;
		}
	}
	// save score to user player
	updateplayer(name, score);
}

void wrapper::loadprevioussave(int& score) 
{
	string name;
	bool found = false;
	cout << "Enter your name: ";
	cin >> name;

	for (int i = 0; i < playerCount; i++) 
	{
		if (players[i].name == name) 
		{
			score = players[i].score;
			found = true;
			break;
		}
	}
	if (found) 
	{
		cout << "Player: " << name << ". Your current score is: " << score << "." << endl;
	}
	else 
	{
		cout << "Unable to find '" << name << "'." << endl;
	}
}

void wrapper::add() 
{
	question newData;
	bool valid = false;
	node<question>* pCurrent;

	while (!valid) 
	{
		cout << "Enter the command name to add: ";
		cin >> newData.name;

		valid = true;
		pCurrent = mQuestions.getHead();
		// ensure no duplications
		while (pCurrent != nullptr) 
		{
			if (pCurrent->data.name == newData.name) 
			{
				valid = false;
				break;
			}
			pCurrent = pCurrent->next;
		}
		if (!valid) {
			cout << "Command already exists" << endl;
		}
	}

	//add command
	cout << "Enter the command description: ";
	getline(cin, newData.description);
	getline(cin, newData.description);
	cout << "Command '" << newData.name << "' successfully added." << endl;

	mQuestions.insertAtFront(newData);
	this->modified = true;
}

void wrapper::remove() 
{
	//ensure the list is not null
	if (!mQuestions.isEmpty()) 
	{
		string name;
		bool removed = false;
		cout << "Enter the command name to remove: ";
		cin >> name;
		node<question>* pCurrent = mQuestions.getHead();
		while (pCurrent != nullptr) {
			if (pCurrent->data.name == name) 
			{
				removed = mQuestions.removeNode(pCurrent);
				break;
			}
			pCurrent = pCurrent->next;
		}
		//word exist and was removed
		if (removed) 
		{
			this->modified = true;
			cout << "Command '" << name << "' successfully removed." << endl;
		}
		else 
		{
			cout << "Unable to find command '" << name << "' to remove." << endl;
		}
	}
	else 
	{
		cout << "Command list is empty, unable to remove." << endl;
	}
}

void wrapper::updateplayer(string name, int score) 
{
	for (int i = 0; i < playerCount; i++)
	{
		if (players[i].name == name) 
		{
			players[i].score = score;
			return;
		}
	}
	if (playerCount < 20) 
	{
		players[playerCount].name = name;
		players[playerCount].score = score;
		playerCount++;
	}
	else 
	{
		cout << "Too many player profiles exist" << endl;
	}
}


void wrapper::savequestion() 
{
	std::ofstream dataline;
	dataline.open(mlinuxFile, std::ofstream::trunc);

	node<question>* pCurrent = mQuestions.getHead();
	while (pCurrent != nullptr) 
	{
		dataline << pCurrent->data.name << ",\"" << pCurrent->data.description << "\"\n";
		pCurrent = pCurrent->next;
	}

	dataline.close();
}

void wrapper::saveplayers() 
{
	std::ofstream session;
	session.open(mGameFile);

	for (int i = 0; i < playerCount; i++) {
		session << players[i].name << "," << players[i].score << "\n";
	}
	session.close();
}

void wrapper::randomize(int intArray[], int length, int min, int max) 
{
	int fill = 0;
	int newInt = 0;
	bool valid;

	while (fill < length) 
	{
		newInt = random(min, max);

		valid = true;
		for (int i = 0; i < fill; i++) 
		{
			if (intArray[i] == newInt) 
			{
				valid = false;
			}
		}

		if (valid) {
			intArray[fill] = newInt;
			fill++;
		}
	}
}

int random(int min, int max) 
{
	return (rand() % (max - min + 1)) + min;
}

int prompt(int min, int max, string message) {
	int prompt = 0;
	do {
		if (cin.fail()) 
		{
			cin.clear();
			cin.ignore(1024, '\n');
		}
		cout << message;
		cin >> prompt;
	} while (cin.fail() || (prompt < min || prompt > max));

	return prompt;
}

bool operator==(const question& lhs, const question& rhs) 
{
	return (lhs.name == rhs.name && lhs.description == rhs.description);
}