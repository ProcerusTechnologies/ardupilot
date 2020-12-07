#include "Copter.h"

bool ModePlanckLand::init(bool ignore_checks){

    //If we are already landed this makes no sense
    if(copter.ap.land_complete)
      return false;

    if(!copter.planck_interface.ready_for_land()) {
      return false;
    }

    ModeGuided::set_angle(Quaternion(),0,true,0);
    if(ModeGuidedNoGPS::init(ignore_checks)) {
        float land_velocity = abs((copter.g.land_speed > 0 ?
            copter.g.land_speed : copter.pos_control->get_max_speed_down()))/100.;
      copter.planck_interface.request_land(land_velocity);
      return true;
    }
    return false;
}

void ModePlanckLand::run(){
    if(copter.planck_interface.teth_just_locked())
    {
      //TODO make the value a param
      copter.pos_control->get_pos_z_p().kP(0.3);
    }
    else if(copter.planck_interface.teth_just_unlocked())
    {
      //TODO make the value a param
      copter.pos_control->get_pos_z_p().kP(1);
    }
    copter.mode_plancktracking.run();
}
