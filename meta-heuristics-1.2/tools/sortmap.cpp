#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

using namespace std;

int main(int argc, char** argv)
{
  ifstream keyFile;
  ifstream plotFile;

  if (argc != 3)
  {
    cout << "Usage:" << endl;
    cout << "\tsortmap <keyfile> <plotfile>" << endl;
    return 0;
  }

  try
  {
    keyFile.open(argv[1]);
  } catch(...) {
    cerr << "File " << argv[1] << " open error" << endl;
  }

  try
  {
    plotFile.open(argv[2]);
  } catch(...) {
    cerr << "File " << argv[2] << " open error" << endl;
  }

  int c;
  char buffer[256];
  vector< pair<double, double> > valueBuf;
//  vector< pair<double, double> > outBuf;
  vector< int > keyBuf;

  while (keyFile.good())
  {
    keyFile >> c;
    keyBuf.push_back(c);
  }

  keyFile.close();

  while (plotFile.good())
  {
    pair<double, double> cord;

    plotFile >> cord.first >> cord.second;
    valueBuf.push_back(cord);
  }

  plotFile.close();

  vector<int>::iterator keyIter;
  for (keyIter = keyBuf.begin(); keyIter != keyBuf.end(); keyIter++)
  {
    pair<double, double> cord;

    cord = valueBuf[*keyIter];
    cout << cord.first << " " << cord.second << endl;
  }
}
