#include "edaSA.h"

edaSA::edaSA()
  : edaSearch(),
    move(NULL),
    moveRandom(NULL),
    con(NULL),
    initTemperature(1e100),
    coolingSchedule(NULL)
{
}

edaSA::edaSA(int _power)
  : edaSearch(_power),
    move(NULL),
    moveRandom(NULL),
    con(NULL),
    initTemperature(1e100),
    coolingSchedule(NULL)
{
}

edaSA::edaSA( edaMove *_move, 
	      edaMoveGen *_moveRandom, 
	      edaContinue *_continueCriteria,
	      double _initTemperature, 
	      edaCoolingSchedule *_coolingSchedule,
              int _timeout,
              int _power )
  : edaSearch(_timeout, _power), initTemperature (_initTemperature)
{
  move = _move->clone();
  moveRandom = _moveRandom->clone();
  con = _continueCriteria->clone();
  coolingSchedule = _coolingSchedule->clone();
}
edaSA::edaSA( const edaSA &sa )
  : edaSearch(sa), initTemperature (sa.initTemperature)
{
  move = sa.move->clone();
  moveRandom = sa.moveRandom->clone();
  con = sa.con->clone();
  coolingSchedule = sa.coolingSchedule->clone();
}

edaSA *edaSA::clone() const {
  return new edaSA(*this);
}

edaSA::~edaSA()
{
  delete move;
  delete moveRandom;
  delete con;
  delete coolingSchedule;
}

bool edaSA::search(edaSolutionList &list) 
{  
  for (unsigned int i = 0; i < list.size(); i++) 
  {
    edaSolution &sol = *list[i];  
    edaSolution *newSol = sol.clone();     
    
    move->init(sol);
    con->init();
//    cout << "F: " << sol.evaluate() << endl;
    printCSVLog("SA", TaskID, ProcID, "S", i, *con, list);
    
    do
    {
      double temp = initTemperature;
      do
      {      

        if( moveRandom->generate(move, sol) )
        {
          
          double newFitness = move->incrEval(sol);
          double fitnessDiff = newFitness - sol.evaluate();
//          cout << "P: " << newFitness << endl;
          // Better solution OR worse solution (in some case)
          double prob = rnd.uniform();
          double energy = exp(fitnessDiff / temp);
          
//          cout << "Diff: " << fitnessDiff << endl;
//          cout << "Temp: " << temp << endl;
//          cout << "Energy: " << energy << endl;          
//          cout << "Prob: " << prob << endl;
          if ((fitnessDiff > Epsilon) || ( prob < energy) )
          {

            move->update(sol);            
            move->init(sol);          
            // Update best solution found      
            if( newSol->evaluate() < sol.evaluate() )            
              *newSol = sol;  
//            cout << "A: " << newFitness << endl;
          }
        }
      } while (coolingSchedule->check(temp)); 

      printCSVLog("SA", TaskID, ProcID, "P", i, *con, list);
      
    } while (con->check(list));   
    
    sol = *newSol;
    delete newSol;  
        
    printCSVLog("SA", TaskID, ProcID, "F", i, *con, list);
  }
  return true;
}

void edaSA::Serialize( edaBuffer &buf, bool pack )
{
  edaSearch::Serialize(buf, pack);

  if ( pack ){
    move->doSerialize( buf, pack );
    moveRandom->doSerialize( buf, pack );
    con->doSerialize( buf, pack );
    coolingSchedule->doSerialize( buf, pack );
    buf.Pack( &initTemperature, 1 );
  } else {
    move = (edaMove*)classGenerateFromBuffer( buf );
    moveRandom = (edaMoveGen*)classGenerateFromBuffer( buf );
    con = (edaContinue*)classGenerateFromBuffer( buf );
    coolingSchedule = (edaCoolingSchedule*)classGenerateFromBuffer( buf );
    buf.UnPack( &initTemperature, 1 );
  }
}
