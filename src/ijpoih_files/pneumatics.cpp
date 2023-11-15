#include "main.h"
// Helper Functions

void wingsDeploy(bool airhigh_w){
  if(airhigh_w){
    left_wing.set_value(true);
    right_wing.set_value(true);
  }
  else{
    right_wing.set_value(false);
    left_wing.set_value(false);
  }
}


void intakePneumaticsDeploy(bool airhigh_i){
  if(airhigh_i){
    left_intake.set_value(true);
    right_intake.set_value(true);
  }
  else{
    right_intake.set_value(false);
    left_intake.set_value(false);
  }
}


void blockerDeploy(bool airhigh_b){
  if(airhigh_b){
    left_blocker.set_value(true);
    right_blocker.set_value(true);
  }
  else{
    left_blocker.set_value(false);
    right_blocker.set_value(false);
  }
}
