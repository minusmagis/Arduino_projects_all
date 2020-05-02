#include "Header_file.h"

#define Calibration_Delay 50                                      //(we give 50 segonds so that the needle stabilizes properly)

extern int photoState_Vacuum_L;
extern int photoState_Vacuum_R;
extern int photoState_Full_L;
extern int photoState_Full_R;

boolean Gauge_Calibration_Sequence() {
  servo_move(Servo_Vacuum);
  delay(Calibration_Delay);
  photoRead(false , Vacuum_position);
  servo_move(Servo_Refill);
  delay(Calibration_Delay);
  photoRead(false , Full_position);
  if (photoState_Vacuum_L + Gauge_Read_Threshold < photoState_Full_L || photoState_Full_L < photoState_Vacuum_L - Gauge_Read_Threshold) {
    if (Move_and_Wait(Full_Vacuum_1) == false) return false;
  }
  else{
    Serial.println("Error, the gauge needle seems to not have moved during the calibration process on the vacuum stage");
    return false;
  }
  if (photoState_Vacuum_R + Gauge_Read_Threshold < photoState_Full_R || photoState_Full_R < photoState_Vacuum_R - Gauge_Read_Threshold) {
    if (Move_and_Wait(Atmosphere) == false) return false;
  }
  else{
    Serial.println("Error, the gauge needle seems to not have moved during the calibration process on the refill stage");
    return false;
  }
  if (Move_and_Wait(Half_Vacuum_05) == false) return false;
  if (Move_and_Wait(Clean_Vacuum_02) == false) return false;
  //EEprom write the values if the calibration has been succesful
  return true;

}
