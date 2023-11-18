#include "main.h"
#include "pros/misc.h"
// Helper Functions

void wingsDeploy(bool airhigh_w){
  if(airhigh_w){
    wings.set_value(true);
  }
  else{
    wings.set_value(false);
  }
}

void blockerDeploy(bool airhigh_b){
  if(airhigh_b){
    blocker.set_value(true);
  }
  else{
    blocker.set_value(false);
  }
}