#include "main.h"
// Helper Functions

void wingsDeploy(bool airhigh){
  if(airhigh){
    left_wing.set_value(true);
    right_wing.set_value(true);
  }
  else{
    right_wing.set_value(false);
    left_wing.set_value(false);
  }
}