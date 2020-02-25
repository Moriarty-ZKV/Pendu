#include<iostream>
#include<vector>
#include<fstream>
#include<ctime>

using namespace std;

#define ASSERT(test) if(!(test)) cout << "Test failed in file " << __FILE__ << " line " << __LINE__ << " : " #test << endl

vector<int> founded_letters;
int nombre_mots = 0;

vector<string> LireMot(string source) {
	vector<string> res;
	res = vector<string>(source.length());
	founded_letters = vector<int>(source.length());
	for (unsigned int i = 0; i < source.length(); i++) {
		founded_letters[i] = 0;
	}
	for (unsigned int i = 0; i < source.length(); i++) {
		res[i] = source[i];
		if (res[i] == "-")
			founded_letters[i] = 1;
	}

	return res;
}

bool CompareLettre(string lettre, vector<string> mot) {
	bool res = false;
	for (unsigned int i = 0; i < mot.size(); i++) {
		if (mot[i] == lettre) {
			res = true;
			founded_letters[i] = 1;
		}
	}
	return res;
}

string RandomeMot(string source) {
	string res;
	ifstream fichier;
	fichier.open(source);
	if (not fichier) {
		cout << "Assurez vous que le fichier 'Bibliotheque.txt' est dans le meme dossier que l'executable" << endl;
		system("PAUSE");
		exit(0);
	}
	fichier >> nombre_mots;
	srand(time(0));
	int n = rand() % nombre_mots + 1;
	fichier.seekg(0, ios::beg);
	for (int i = 0; i <= n; i++)
		fichier >> res;
	fichier.close();
	return res;
}

void AfficheMot(vector<string> mot, vector<int> founded_letters) {
	system("CLS");
	for (unsigned int i = 0; i < mot.size(); i++) {
		if (founded_letters[i] == 1)
			cout << mot[i] << " ";
		else
			cout << "_ ";
	}
	cout << endl;
}

void TestLireMot() {
	ASSERT(LireMot("coucou") == vector<string>({ "c","o","u","c","o","u" }));
	ASSERT(LireMot("salut") == vector<string>({ "s","a","l","u","t" }));
	ASSERT(LireMot("hello world") == vector<string>({ "h","e","l","l","o"," ","w","o","r","l","d" }));
}

void TestCompareLettre() {
	ASSERT(CompareLettre("d", LireMot("dessu")));
	ASSERT(not CompareLettre("d", LireMot("igloo")));
	ASSERT(CompareLettre("w", LireMot("hello world")));
	ASSERT(not CompareLettre("w", LireMot("bang bang")));
}

int main() {
	TestLireMot();
	TestCompareLettre();

	string m = RandomeMot("./bibliotheque.txt");
	vector<string> mot = LireMot(m);
	bool jeu = false;
	string l;
	int vie = 9;
	int compt = 0;

	while (jeu == false) {
		AfficheMot(mot, founded_letters);
		cin >> l;
		if (not CompareLettre(l, mot)) {
			cout << l << " ne fais pas parti du mot" << endl;
			vie -= 1;
			system("PAUSE");
		}
		if (vie <= 0) {
			cout << "Perdu ! le mot etait : " << m << endl;
			return EXIT_SUCCESS;
		}
		for (unsigned int i = 0; i < mot.size(); i++) {
			if (mot[i] == l)
				compt++;
		}
		if (compt == mot.size())
			jeu = true;
	}
	AfficheMot(mot, founded_letters);
	cout << "Felicitation vous avez gagne !" << endl;
	system("PAUSE");
	return EXIT_SUCCESS;
}