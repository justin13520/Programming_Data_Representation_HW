//Justin Liu, jl8wf     Date:10/30/2020       Filename: hNode.cpp

#include "hNode.h"


hNode::hNode() {
  frequency = 0;
  left = NULL;
  right = NULL;
}

hNode::hNode(string val,int fre) {
  frequency = fre;
  value = val;
  left = NULL;
  right = NULL;
}

string hNode::getValue(){
  return value;
}

unsigned int hNode::getFrequency(){
  return frequency;
}

void hNode::setLeft(hNode* l){
  left = l;
}

void hNode::setRight(hNode* r){
  right = r;
}
