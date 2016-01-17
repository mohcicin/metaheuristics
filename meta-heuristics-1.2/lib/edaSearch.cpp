#include "edaSearch.h"

edaSearch::edaSearch()
  : Timeout(0), Epsilon(1e-3), Power (0), TaskID(-1), ProcID(-1)
{
  strcpy( Protocol, "" );
}

edaSearch::edaSearch(int _power, const char *prot)
  : Timeout(0), Epsilon(1e-3), Power (_power), TaskID(-1), ProcID(-1)
{
  strcpy( Protocol, prot );
}

edaSearch::edaSearch(const edaSearch &search) 
  : Timeout(search.Timeout), Epsilon(search.Epsilon), Power(search.Power)
        , TaskID(search.TaskID), ProcID(search.ProcID)
{
  strcpy( Protocol, search.Protocol );
}

  
edaSearch::edaSearch(int _timeout, int _power) 
 : Timeout(_timeout), Epsilon(1e-3), Power (_power), TaskID(-1), ProcID(-1) 
{
    strcpy( Protocol, "" );
}

edaSearch::~edaSearch() {}

void edaSearch::Serialize(edaBuffer &buf, bool pack)
{
  if (pack)
  {
    buf.Pack( &Power, 1 );
    buf.Pack( &Timeout, 1 );
    buf.Pack( &Epsilon, 1 );
    buf.Pack( Protocol, 1024 );
    buf.Pack( &TaskID, 1 );
    buf.Pack( &ProcID, 1 );
  }
  else
  {
    buf.UnPack( &Power, 1 );
    buf.UnPack( &Timeout, 1 );
    buf.UnPack( &Epsilon, 1 );
    buf.UnPack( Protocol, 1024 );
    buf.UnPack( &TaskID, 1 );
    buf.UnPack( &ProcID, 1 );
  }
}
