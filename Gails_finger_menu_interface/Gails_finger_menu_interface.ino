#include "U8glib.h"
#include "M2tk.h"
#include "utility/m2ghu8g.h"

extern char z_homing_28_bits[];
extern char pre_approach_28_bits[];
extern char approach_28_bits[];
extern char retract_28_bits[];
extern char general_movement_28_bits[];
extern char configuration_28_bits[];

uint32_t height2dp = 11500;

U8GLIB_ST7920_128X64_4X u8g(17, 15, 16);  // SPI Com: SCK = en = 18, MOSI = rw = 16, CS = di = 17

M2_EXTERN_ALIGN(el_top);  // forward declaration of the top level element
M2_EXTERN_ALIGN(el_z_homing_course);
M2_EXTERN_LABEL(el_z_homing_course_label);
M2_EXTERN_HLIST(el_preapp_course);
M2_EXTERN_HLIST(el_app_course);
M2_EXTERN_HLIST(el_ret_course);


//------------------------------------------------------------------------------------------------

/* ===== Home first Message ===== */

M2_LABEL(el_z_home_first_label, NULL, "Home First");
M2_ALIGN(el_z_home_first, NULL, &el_z_home_first_label);  

//------------------------------------------------------------------------------------------------

/* ===== Z homing menu ===== */

void zh_cb(m2_el_fnarg_p fnarg){
    m2_SetRoot(&el_z_homing_course_label);
}

    /* ______ Z homing selection menu ______ */
M2_LABEL(el_z_homing_label, NULL, "Fancy homming Z?");
M2_BUTTON(el_z_homing_yes, "f4", " Yes, please ", zh_cb);
M2_ROOT(el_z_homing_no, "f4", " No, thanks ", &el_top);
M2_LIST(list_z_homing) = { &el_z_homing_label, &el_z_homing_yes, &el_z_homing_no };
M2_VLIST(el_z_homing_vl, NULL, list_z_homing);
M2_ALIGN(el_z_homing, NULL, &el_z_homing_vl);  

    /* ______ Z homing in course menu ______ */

M2_LABEL(el_z_homing_course_label, NULL, "Z homing...");

    /* ______ Z homing successful ______ */

M2_LABEL(el_z_homing_success_label, NULL, "Z homing successful");

    /* ______ Z homing failed ______ */

M2_LABEL(el_z_homing_fail_label, NULL, "Z homing failed");

//------------------------------------------------------------------------------------------------

/* ===== Pre approach menu ===== */

uint8_t preapph = 50;

void pr_app(m2_el_fnarg_p fnarg){
  //add if it is homed proceed but if it is not go to main menu again
  m2_SetRoot(&el_preapp_course);  // go to pre approach function
}

    /* ______ Set pre approach hight menu ______ */

M2_LABEL(el_preapph_input_label1, NULL, "Pre approach ");
M2_LABEL(el_preapph_input_label2, NULL, "");
M2_LABEL(el_preapph_input_label3, NULL, "Height = ");
M2_U8NUM(el_preapph_input_u8, "c3", 0, 115, &preapph);
M2_BUTTON(el_preapph_input_ok, "", "Ok", pr_app);
M2_ROOT(el_preapph_input_back, "", "Back", &el_top);
M2_LIST(list_preapph_input) = { 
  &el_preapph_input_label1,&el_preapph_input_label2,
  &el_preapph_input_label3, &el_preapph_input_u8,
  &el_preapph_input_ok, &el_preapph_input_back
  };
M2_GRIDLIST(el_preapph_input_g1, "c2", list_preapph_input);
M2_ALIGN(el_preapph_input, NULL, &el_preapph_input_g1);

    /* ______ Pre approach in course menu ______ */

M2_LABEL(el_preapp_course_label, NULL, "Pre apprx... ");
M2_U32NUM(el_preapp_course_label_height, "c5r1.2", &height2dp);
M2_LIST(el_preapp_list) = { &el_preapp_course_label, &el_preapp_course_label_height };
M2_HLIST(el_preapp_course, NULL, el_preapp_list);

//------------------------------------------------------------------------------------------------

/* ===== Approach menu ===== */

uint32_t feedrate = 1000;

void app(m2_el_fnarg_p fnarg){
  //add if it is homed proceed but if it is not go to main menu again
  m2_SetRoot(&el_app_course);  // go to approach function
}

    /* ______ Set approach feedrate menu ______ */

M2_LABEL(el_appf_input_label1, NULL, "Approach ");
M2_LABEL(el_appf_input_label2, NULL, "");
M2_LABEL(el_appf_input_label3, NULL, "Feedrate = ");
M2_U32NUM(el_appf_input_u32, "a1c4", &feedrate);
M2_BUTTON(el_appf_input_ok, "", "Ok", app);
M2_ROOT(el_appf_input_back, "", "Back", &el_top);
M2_LIST(list_appf_input) = { 
  &el_appf_input_label1,&el_appf_input_label2,
  &el_appf_input_label3, &el_appf_input_u32,
  &el_appf_input_ok, &el_appf_input_back
  };
M2_GRIDLIST(el_appf_input_g1, "c2", list_appf_input);
M2_ALIGN(el_appf_input, NULL, &el_appf_input_g1);

    /* ______ Approach in course menu ______ */

M2_LABEL(el_app_course_label, NULL, "Approach... ");
M2_U32NUM(el_app_course_label_height, "c5r1.2", &height2dp);
M2_LIST(el_app_list) = { &el_app_course_label, &el_app_course_label_height };
M2_HLIST(el_app_course, NULL, el_app_list);

    /* ______ Approach successful ______ */

M2_LABEL(el_approach_success_label, NULL, "Approach successful");

    /* ______ Approach failed ______ */

M2_LABEL(el_approach_fail_label, NULL, "Approach failed");

//------------------------------------------------------------------------------------------------

/* ===== Retract menu ===== */

uint8_t rdistance = 20;

void ret(m2_el_fnarg_p fnarg){
  //add if it is homed proceed but if it is not go to main menu again
  m2_SetRoot(&el_ret_course);  // go to approach function
}

    /* ______ Set Retract feedrate menu ______ */

M2_LABEL(el_retf_input_label1, NULL, "Retract ");
M2_LABEL(el_retf_input_label2, NULL, "");
M2_LABEL(el_retf_input_label3, NULL, "Feedrate = ");
M2_U32NUM(el_retf_input_u32, "a1c4", &feedrate);
M2_LABEL(el_retf_input_label4, NULL, "Distance = ");
M2_U8NUM(el_retd_input_u8, "c3",0,115, &rdistance);
M2_BUTTON(el_retf_input_ok, "", "Ok", ret);
M2_ROOT(el_retf_input_back, "", "Back", &el_top);
M2_LIST(list_retf_input) = { 
  &el_retf_input_label1,&el_retf_input_label2,
  &el_retf_input_label3, &el_retf_input_u32,
  &el_retf_input_label4, &el_retd_input_u8,
  &el_retf_input_ok, &el_retf_input_back
  };
M2_GRIDLIST(el_retf_input_g1, "c2", list_retf_input);
M2_ALIGN(el_retf_input, NULL, &el_retf_input_g1);

    /* ______ Retract in course menu ______ */

M2_LABEL(el_ret_course_label, NULL, "Retract... ");
M2_U32NUM(el_ret_course_label_height, "c5r1.2", &height2dp);
M2_LIST(el_ret_list) = { &el_ret_course_label, &el_ret_course_label_height };
M2_HLIST(el_ret_course, NULL, el_ret_list);

//------------------------------------------------------------------------------------------------

/* ===== General Movement menu ===== */

void mov(m2_el_fnarg_p fnarg){
  //add if it is homed proceed but if it is not go to main menu again
  m2_SetRoot(&el_top);  // go to approach function
}

    /* ______ Set movement menu ______ */

M2_LABEL(el_mov_input_label1, NULL, "Z pos = ");
M2_U32NUM(el_movz_input_u32, "a1c5.2", &height2dp);
M2_LABEL(el_mov_input_label2, NULL, "Feedrate = ");
M2_U32NUM(el_movf_input_u32, "a1c4", &feedrate);
M2_BUTTON(el_mov_input_ok, "", "Move", mov);
M2_ROOT(el_mov_input_back, "", "Back", &el_top);
M2_LIST(list_mov_input) = { 
  &el_mov_input_label1, &el_movz_input_u32,
  &el_mov_input_label2, &el_movf_input_u32,
  &el_mov_input_ok, &el_mov_input_back
  };
M2_GRIDLIST(el_mov_input_g1, "c2", list_mov_input);
M2_ALIGN(el_mov_input, NULL, &el_mov_input_g1);



//------------------------------------------------------------------------------------------------

/* ===== No configuration Message ===== */

M2_LABEL(el_nopem_label, NULL, "Configuration?");
M2_ROOT(el_nopemr, "" , "Nope :3" , &el_top);
M2_LIST(list_nopem) = { &el_nopem_label, &el_nopemr};
M2_VLIST(el_nopem_v1, NULL, list_nopem);
M2_ALIGN(el_nopem, NULL, &el_nopem_v1);

//------------------------------------------------------------------------------------------------

/* ===== Main Menu ===== */

M2_XBMROOTP(el_xbm_z_homming, "w32h29", 27, 27, z_homing_28_bits, &el_z_homing);
M2_XBMROOTP(el_xbm_pre_approach,  "w32h29", 27, 27, pre_approach_28_bits, &el_preapph_input);
M2_XBMROOTP(el_xbm_approach,  "w32h29",  27, 27, approach_28_bits, &el_appf_input);
M2_XBMROOTP(el_xbm_retract,  "w32h29",  27, 27, retract_28_bits, &el_retf_input);
M2_XBMROOTP(el_xbm_general_movement,  "w32h29",  27, 27, general_movement_28_bits, &el_mov_input);
M2_XBMROOTP(el_xbm_configuration,  "w32h29",  27, 27, configuration_28_bits, &el_nopem);
M2_LIST(el_xbm_list) = {
  &el_xbm_z_homming, &el_xbm_pre_approach, &el_xbm_approach,
  &el_xbm_retract, &el_xbm_general_movement, &el_xbm_configuration,
  };
M2_GRIDLIST(el_xbm_hlist, "c3", el_xbm_list);
M2_ALIGN(el_top, NULL, &el_xbm_hlist);



//------------------------------------------------------------------------------------------------
  
//void set_next_state(void) {
//  switch(state) {
//    case MAIN_MENU: r = rand(); r&=15; state = SETUP_NUM_INPUT; break;
//    case ZHOME: break;
//    case ZHOMING:
//    case PREAPPROACH:
//
//  }
//}


M2tk m2(&el_top, m2_es_arduino_rotary_encoder, m2_eh_4bd, m2_gh_u8g_ffs);

// U8glib draw procedure: Just call the M2tklib draw procedure
void draw(void) {
    m2.draw();
}

// Arduino setup procedure (called only once)
void setup() {
  // Connect u8glib with m2tklib
  m2_SetU8g(u8g.getU8g(), m2_u8g_box_icon);

  // Assign u8g font to index 0
  m2.setFont(0, u8g_font_6x13);

  // Setup keys
  m2.setPin(M2_KEY_SELECT, 4);
  m2.setPin(M2_KEY_ROT_ENC_A, 3);
  m2.setPin(M2_KEY_ROT_ENC_B, 2);
}

// Arduino loop procedure
void loop() {
  height2dp = millis()/10;
  m2.checkKey();
  if ( m2.handleKey() || newFrame() ) {
    u8g.firstPage();  
    do {
      draw();
    } while( u8g.nextPage() );
  }
}

  
