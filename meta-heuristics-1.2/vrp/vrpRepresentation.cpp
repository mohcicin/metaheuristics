/* 
 * File:   vrpRepresentation.cpp
 * Author: Tieu Minh
 * 
 * Created on October 8, 2013, 4:03 PM
 */

#include "vrpRepresentation.h"
#include "vrpProblem.h"
#include "vrpSolution.h"
#include "vrpGenne.h"

vrpRepresentation::vrpRepresentation() 
  : pro(NULL), con(NULL) {}

vrpRepresentation::vrpRepresentation(const vrpProblem &pro, const vrpConst &con) 
  : pro( pro.clone() ), con (con.clone()) {}
vrpRepresentation::vrpRepresentation(const vrpRepresentation& orig) 
  : pro( orig.pro->clone() ), con( orig.con->clone()) {}

vrpRepresentation::~vrpRepresentation() {
  easer();
}

vrpRepresentation* vrpRepresentation::clone() const {
  return new vrpRepresentation(*this);
}

void vrpRepresentation::easer() {
  if(pro != NULL) 
  { 
    delete pro;
    pro = NULL;
  }
  if(con != NULL) 
  { 
    delete con;
    con = NULL;
  }
}

void vrpRepresentation::Serialize( edaBuffer &buf, bool pack ) {

  if(pack) {
    pro->doSerialize(buf, pack);
    con->doSerialize(buf, pack);
  }
  else {
    easer();
    pro = (vrpProblem*) classGenerateFromBuffer(buf);
    con = (vrpConst*) classGenerateFromBuffer(buf);
  }
}

void vrpRepresentation::init(const edaSolutionList &list, edaPopulation &pop) const {
  for(unsigned int i = 0; i < list.size(); i++) {
    edaChromosome *chro = new edaChromosome();
    encode(list[i], chro);  
    pop[i] = chro; 
  }
  for(unsigned int i = list.size(); i < pop.size(); i++) {
    edaChromosome *chro = new edaChromosome();
    vrpSolution *vrpSol = new vrpSolution();
    vrpSol->init();
    encode(vrpSol, chro);     
    pop[i] = chro; 
  }
}

void vrpRepresentation::decode(const edaPopulation &pop, edaSolutionList &list) const{
  list.easer();
  for(unsigned int i = 0; i < pop.size(); i++) {
    edaChromosome *chro = pop[i];
    vrpSolution *vrpSol = new vrpSolution();
    decode(chro, vrpSol);
    list.push_back(vrpSol);
  }
}

void vrpRepresentation::encode(const edaSolutionList &list, edaPopulation &pop) const {
  pop.easer();
  for(unsigned int i = 0; i < list.size(); i++) {
    edaSolution *sol = list[i];
    edaChromosome *chro = new edaChromosome();
    encode(sol, chro);
    pop.push_back(chro);
  }
}

void vrpRepresentation::decode(const edaChromosome *chro, edaSolution *sol) const {
  vrpSolution *vrpSol = (vrpSolution*)sol;  
  vector<unsigned int> list;
  for(unsigned int i = 0; i < chro->getLength(); i++) {
      vrpGenne* genne = (vrpGenne*)chro->getGenne(i);
      unsigned int value = genne->getValue();
      list.push_back(value); 
  }

  vrpSol->setProblem(pro->clone());
  vrpSol->setParameter(con->clone());
  vrpProblem* problem = vrpSol->getProblem();
  vrpConst* con = vrpSol->getParameter();
  
  vrpRoute *route; 
  vrpSubRoute *sub;
  double res_dist;
  double coming_time;
  vrpStop* ref;
  unsigned int id;
//  vrpStop* _stop = problem->getListStops();
  vrpStop* _depot = problem->getDepot();
    
INIT_ROUTE:
    route = new vrpRoute();
    ref = _depot;
    res_dist =  problem->getMaxTotalDist();
    coming_time = ref->EarlyTime;
    
INIT_SUB: 
    sub = createSubRouteFormList(ref, res_dist, coming_time, list, problem, con); 
    if(sub != NULL) {
        id = list.back();
        vrpStop* stop = problem->getStop(id);
        while(list.size() > 0 && sub->canInsert(stop, sub->size() - 2)) {        
            sub->insertStop(stop->ID, sub->size() - 2);
            list.pop_back();
            id = list.back();
            stop = problem->getStop(id);
        }  
        sub->removeStop(_depot->ID);   
        ref = problem->getStop( sub->at(sub->size()-1) );
        coming_time = sub->getComingTime(sub->size()-1);
        res_dist = sub->getRestDist();
 
        route->push_back(sub);   
        goto INIT_SUB;
    }
    else {
        if(route->size() > 0) {
            vrpSubRoute* last = route->at(route->size() - 1);
            last->pushStop(_depot);        
            vrpSol->push_back(route);            
            goto INIT_ROUTE;
        }
        else {
            vrpSol->improveLandfill();
            vrpSol->update();
            return;
        }
    }
}

void vrpRepresentation::encode(const edaSolution *sol, edaChromosome *chro) const {
  vrpSolution *vrpSol = (vrpSolution*)sol;
  vector<unsigned int> route =  vrpSol->getListRoute();
  for(unsigned int i = 0; i < route.size() ; i++) {   
    if(pro->getStop(route[i])->Type == REGULAR_STOP) {
      vrpGenne genne(route[i]);
      chro->addGenne(genne);
    }
  }
  chro->setFitness( vrpSol->evaluate() );
}

vrpSubRoute* vrpRepresentation::createSubRouteFormList(vrpStop* ref, double rest_dist, 
  double coming_time, vector<unsigned int> &list, vrpProblem* _problem, vrpConst* _const) const {  
    if(list.size() > 0) {
        unsigned int id = list.back();
        vrpStop* stop = _problem->getStop(id);    
        vrpStop* _depot = _problem->getDepot();
        vector<vrpStop*> _landfill = _problem->getLandfill();
        vrpSubRoute *result = new vrpSubRoute(rest_dist, coming_time);
        result->setProblem(_problem);
        result->setConst(_const);
        result->insertStop(ref->ID,0);
        result->insertStop(stop->ID,1);  
        result->insertStop(_depot->ID,2);
        for(unsigned int i = 0; i < _landfill.size(); i++) {
            if(result->canInsert(_landfill[i], 2)) {
                result->insertStop(_landfill[i]->ID, 2);
                list.pop_back();
                return result;              
            }
        }
        delete result;        
    }    
    return NULL; 
}
