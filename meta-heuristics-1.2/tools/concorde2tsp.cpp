#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

using namespace std;

int main(int argc, char** argv)
{
  ifstream concordeFile;
  ofstream tspFile;

  if (argc != 3)
  {
    cout << "Usage:" << endl;
    cout << "\tconcorde2tsp <concorde file> <tsp file>" << endl;
    return 0;
  }

  try
  {
    concordeFile.open(argv[1]);
  } catch(...) {
    cerr << "File " << argv[1] << " open error" << endl;
  }

  try
  {
    tspFile.open(argv[2]);
  } catch(...) {
    cerr << "File " << argv[2] << " write error" << endl;
  }

  int c;
  char buffer[256];
  vector< pair<double, double> > outBuf;

  while (concordeFile.good())
  {
    c = concordeFile.get();
    if (c > '9' || c < '0')
    {
      concordeFile.unget();
      concordeFile.getline(buffer, 256);
      continue;
    }

    concordeFile.unget();

    int seqNo;
    double x, y;

    concordeFile >> seqNo >> x >> y;

    pair<double, double> cord;
    cord.first = x;
    cord.second = y;

    outBuf.push_back(cord);
  }

  concordeFile.close();

  vector< pair<double, double> >::iterator outBufIter;

  tspFile << outBuf.size() << endl;

  for (outBufIter = outBuf.begin(); outBufIter != outBuf.end(); outBufIter++)
  {
    pair<double, double> cord;
    cord = *outBufIter;

    tspFile << cord.first << " " << cord.second << endl;
  }
  tspFile.close();
}
