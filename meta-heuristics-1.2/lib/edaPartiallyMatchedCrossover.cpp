/* 
 * File:   edaPartiallyMatchedCrossover.cpp
 * Author: tieuminh
 * 
 * Created on April 20, 2012, 2:48 PM
 */

#include "edaPartiallyMatchedCrossover.h"
#include "edaRNG.h"
#include <cstdlib>
#include <math.h>
#include <algorithm>
#include <stdio.h>

edaPartiallyMatchedCrossover::
    edaPartiallyMatchedCrossover(double rate, unsigned int num) {
    this->num = num;
    this->rate = rate;
}

edaPartiallyMatchedCrossover::
    edaPartiallyMatchedCrossover(const edaPartiallyMatchedCrossover& cross):
    num(cross.num),
    rate(cross.rate) {}

edaPartiallyMatchedCrossover::
    ~edaPartiallyMatchedCrossover() {
}

edaPartiallyMatchedCrossover
    *edaPartiallyMatchedCrossover::clone() const {
    return new edaPartiallyMatchedCrossover(*this);            
}

void edaPartiallyMatchedCrossover::Serialize(edaBuffer &buf, bool pack) {
  if (pack)
  {
    buf.Pack(&num, 1);
    buf.Pack(&rate, 1);
  }
  else
  {
    buf.UnPack(&num, 1);
    buf.UnPack(&rate, 1);
  }
}

void edaPartiallyMatchedCrossover::update(edaPopulation &pop) {
    vector<edaChromosome*> trash;  
    unsigned int length = pop[0]->getLength();
    num = num <=0 ? 0 : num;
    num = num > length/2 ? length/2 : num;
    
    unsigned int* cross_point = new unsigned int[num + 1];
    unsigned int size = pop.size();
    
    for(unsigned int i = 1; i < size; i++) {
        double p = rnd.uniform();
        if(p <= rate) {            
//            printDebug(5, "  + Prob = " << p << " < Rate , select ");
//            printDebug(5, "    " << *pop[i])
            trash.push_back(pop[i]);           
            if(trash.size() == 2) {               
                edaChromosome* A = trash[0];
                edaChromosome* B = trash[1];
                bool update = false;
                for(unsigned int j = 0; j < num; j++) {
                  cross_point[j] = rnd.random( (length - 1) + 1 );                
                }
                cross_point[num] = length;
                sort(cross_point, cross_point + num + 1);
                string strPoint = "";
                for(unsigned int i = 0; i < num; i++) {
                  char str[16];
                  sprintf(str, "%d", num);         
                  strPoint += str;
                  if(i != num - 1)
                    strPoint += " ";
                }
//                printDebug(5, "  + Crossover points = " << strPoint << ", update: ")
                for(unsigned int j = 0; j < num; j+= 2) {
                    for(unsigned int k = cross_point[j]; k < cross_point[j+1]; k++) {
                      edaGenne *a = A->getGenne(k);
                      edaGenne *b = B->getGenne(k);
                      if(*a != *b) {
                          a->swap(b);
                          update = true;
                      }
                  }                
                }
                vector<unsigned int> stack_1;
                bool *flag_1 = new bool[length]; 
                fill(flag_1,flag_1+length,0);
                for(unsigned int k = 0; k < length - 1; k++) 
                    if(!flag_1[k]) {
                        edaGenne *a1 =  A->getGenne(k);
                        for(unsigned int j = k + 1; j < length; j++) 
                            if(!flag_1[j]) {
                                edaGenne *a2 =  A->getGenne(j);
                                if(*a1 == *a2) {
                                    stack_1.push_back(j);
                                    flag_1[j] = true;
                                    break;
                                }
                            }                
                       }

                vector<unsigned int> stack_2;
                bool *flag_2 = new bool[length];
                fill(flag_2,flag_2+length,0);    
                for(unsigned int k = 0; k < length - 1; k++) {
                    if(!flag_2[k]) {
                        edaGenne *b1 =  B->getGenne(k);
                        for(unsigned int j = k + 1; j < length; j++) {
                            if(!flag_2[j]) {
                                edaGenne *b2 =  B->getGenne(j);
                                if(*b1 == *b2) {
                                    stack_2.push_back(j);
                                    flag_2[j] = true;
                                    break;
                                }
                            }
                        }
                    }
                }
                
                if(stack_1.size() != stack_2.size()) {
                    cerr << "Error: The solution is not Permutation route !" << endl;
                    exit(1);
                }
                
                for(unsigned int k = 0; k < stack_1.size();k++) {
                    edaGenne *a = A->getGenne(stack_1[k]);
                    edaGenne *b = B->getGenne(stack_2[k]);
                    a->swap(b);
                }

                delete[] flag_1;
                delete[] flag_2;


                if(update) {
                    A->setFitness(NAN);
                    B->setFitness(NAN);
                }
//                printDebug(5, "    " << *A);
//                printDebug(5, "    " << *B);
                trash.pop_back();
                trash.pop_back();
              }
          }
      }
    delete[] cross_point;
}

void edaPartiallyMatchedCrossover::setNumPoint(unsigned int num) {
    this->num = num;
}

void edaPartiallyMatchedCrossover::setRate(double value) {
    rate = value;
}

void edaPartiallyMatchedCrossover::printOn(ostream& os) const {
  os << "Rate = " << rate << ", Number of crossover points = " << num;
}
