#include "Home.h"
#include "includes.h"

//1��title(����), ITEM_PER_PAGE��item(ͼ��+��ǩ)
const MENUITEMS homeItems = {
//   title
LABEL_HOME,
// icon                       label
#ifdef CNC_MENU //if CNC menu is selected
  {{ICON_HOME,                 LABEL_XY},
    {ICON_Z_HOME,               LABEL_Z},
    {ICON_Z_PROBE,              LABEL_PROBE_Z},
    {ICON_BACKGROUND,           LABEL_BACKGROUND},
    {ICON_ZERO_X,               LABEL_ZERO_X},
    {ICON_ZERO_Y,               LABEL_ZERO_Y},
    {ICON_ZERO_Z,               LABEL_ZERO_Z},
    {ICON_BACK,                 LABEL_BACK},}
#else
  {{ICON_HOME,                 LABEL_HOME},
    {ICON_X_HOME,               LABEL_X},
    {ICON_Y_HOME,               LABEL_Y},
    {ICON_Z_HOME,               LABEL_Z},
    {ICON_BACKGROUND,           LABEL_BACKGROUND},
    {ICON_BACKGROUND,           LABEL_BACKGROUND},
    {ICON_BACKGROUND,           LABEL_BACKGROUND},
    {ICON_BACK,                 LABEL_BACK},}
#endif
  
};

void menuHome(void)
{
  KEY_VALUES key_num = KEY_IDLE;
  menuDrawPage(&homeItems);
  update_gantry();
  float v;
  float ov;
  char c;
  while(infoMenu.menu[infoMenu.cur] == menuHome)
  {
    key_num = menuKeyGetValue();
    switch(key_num)
    {
    	#ifdef CNC_MENU //if CNC menu is selected
        case KEY_ICON_0: storeCmd("G28 XY\n");   break;
        case KEY_ICON_1: storeCmd("G28 Z\n"); break;
        case KEY_ICON_2: storeCmd("G54\nG92 Z0\nG38.2 Z-20 F50\nG92 Z25.4\nG0 Z30 F1000\n"); break;
        case KEY_ICON_4: 
        case KEY_ICON_5: 
        case KEY_ICON_6: 
          c = (int)'X' + (key_num - KEY_ICON_4); //X, Y or Z?
          ov = getAxisLocation(key_num - KEY_ICON_4) + 0.000001; //Out of band data. If num_pad() truncates this, user pressed OK, otherwise user pressed CANCEL
          v = num_pad(ov,true);
          if(v != ov) {
            storeCmd("G54\nG92 %c%f\n",c,v); 
          }
          menuDrawPage(&homeItems);
          break;
      #else
        case KEY_ICON_0: storeCmd("G28\n");   break;
        case KEY_ICON_1: storeCmd("G28 X\n"); break;
        case KEY_ICON_2: storeCmd("G28 Y\n"); break;
        case KEY_ICON_3: storeCmd("G28 Z\n"); break;
      #endif
      case KEY_ICON_7: infoMenu.cur--;      break;
      default:break;
    }
    loopProcess();
    update_gantry();
  }
}

