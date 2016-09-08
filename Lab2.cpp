#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>

#define ROUNDS 100
using namespace std;

int flip() {
  return rand() % 2;
}

void run(string filename) {
  ifstream ifs(filename);

  string line = "";
  getline(ifs, line);
  istringstream iss(line);
  int nV;
  int nE;
  iss >> nV >> nE;

  vector<vector<pair<int, int> > > graph(nV + 1);
  while (getline(ifs, line)) {
    istringstream iss(line);
    int v1;
    int v2;
    int w;
    iss >> v1 >> v2 >> w;

    graph[v1].push_back(make_pair(v2, w));
  }
  size_t cutSum = 0;
  vector<int> cutsizes(ROUNDS);
  
  for (int r = 0; r < ROUNDS; ++r) {
    vector<bool> nodes(nV + 1, false);
  
    for (int i = 1; i <= nV; ++i) {
      if (flip()) {
	nodes[i] = true;
      }
    }
    int cutSize = 0;
    for (int i = 1; i <= nV; ++i) {
      if (nodes[i]) {
	for (const pair<int, int>& p : graph[i]) {
	  if (!nodes[p.first]) {
	    cutSize += p.second;
	  }
	}
      }
    }
    cutsizes[r] = cutSize;
    cutSum += cutSize;
  }
  ofstream ofs(filename.substr(0, filename.size() - 4) + "output.txt");
  ofs << "Average cut size: " << (double)cutSum / ROUNDS << endl;
  ofs << "cut sizes: " << endl;
  for (int s : cutsizes) {
    ofs << s << endl;
  }
}

int main() {
  run("/h/d2/i/tpi11nfa/Documents/EDAN55/pw09_100.9.txt");
  run("/h/d2/i/tpi11nfa/Documents/EDAN55/matching_1000.txt");
}
