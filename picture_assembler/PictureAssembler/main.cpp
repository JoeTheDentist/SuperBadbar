#include <iostream>

#include <sys/stat.h>

#include <SFML/Graphics.hpp>

using namespace std;

void usage(char *progName)
{
	cout << "usage: " << endl;
	cout << "\t" <<
			progName <<
			" path_to_set_of_images output width" <<
			endl;
}

bool FileExists(std::string strFilename) {
	struct stat stFileInfo;
	bool blnReturn;
	int intStat;

	// Attempt to get the file attributes
	intStat = stat(strFilename.c_str(),&stFileInfo);
	if(intStat == 0) {
		// We were able to get the file attributes
		// so the file obviously exists.
		blnReturn = true;
	} else {
		// We were not able to get the file attributes.
		// This may mean that we don't have permission to
		// access the folder which contains this file. If you
		// need to do that level of checking, lookup the
		// return values of stat which will give you
		// more details on why stat failed.
		blnReturn = false;
	}

	return(blnReturn);
}

int main(int argc, char *argv[])
{
	if (argc != 4) {
		usage(argv[0]);
		return 0;
	}

	char *pathToImages = argv[1];
	char *output = argv[2];
	char *size = argv[3];
	int width = atoi(size);

	string pathInput(pathToImages);
	string pathOutput(output);
	string start = "0000";
	string ext = ".png";
	string imagePath = pathInput+start+ext;
	int count=0;
	vector<sf::Image*> images;

	while (FileExists(imagePath)) {
		cout << imagePath << endl;
		sf::Image *currImg = new sf::Image();
		currImg->LoadFromFile(imagePath);
		images.push_back(currImg);
		count++;
		start.at(3) = count%10+'0';
		start.at(2) = (count/10)%10+'0';
		start.at(1) = (count/100)%10+'0';
		start.at(0) = (count/1000)%100+'0';
		imagePath = pathInput+start+ext;
	}

	if (images.size() == 0) {
		cerr << "No file found" << endl;
		return 0;
	}

	int caseHeight = images.at(0)->GetHeight();
	int caseWidth = images.at(0)->GetWidth();

	int height = images.size() / width;

	sf::Color color(255,0,255);
	sf::Image *outputImg = new sf::Image(width*(caseWidth+2),
										 height*(caseHeight+2),
										 color);

	count = 0;
	int i = 0;
	int j = 0;
	for (vector<sf::Image*>::iterator it = images.begin();
		 it < images.end();
		 ++it) {
		i = count / width;
		j = count % width;
		outputImg->Copy(*(*it),
						j*caseWidth+1+2*j,
						i*caseHeight+1+2*i);
		count++;
	}

	outputImg->SaveToFile(pathOutput+ext);

	return 0;
}

