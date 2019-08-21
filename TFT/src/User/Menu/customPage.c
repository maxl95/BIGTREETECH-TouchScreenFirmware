#include "customPage.h"
#include "includes.h"

MENUITEMS customPageitems = {
//  title
LABLE_CUSTOMPAGE,
// icon                       label
 {{ICON_CUSTOM_1,             LABLE_CUSTOM_1},
  {ICON_CUSTOM_2,             LABLE_CUSTOM_2},
  {ICON_CUSTOM_3,             LABEL_BACKGROUND},
  {ICON_CUSTOM_4,             LABEL_BACKGROUND},
  {ICON_LEVELING,             LABEL_LEVELING},
  {ICON_BACKGROUND,           LABEL_BACKGROUND},
  {ICON_BACKGROUND,           LABEL_BACKGROUND},
  {ICON_BACK,                 LABEL_BACK},}
};

MENUITEMS Bedlevelitems = {
//  title
LABEL_LEVELING,
// icon                       label
 {{ICON_BED_LEVEL_1,          LABEL_BACKGROUND},
  {ICON_BED_LEVEL_2,          LABEL_BACKGROUND},
  {ICON_BED_LEVEL_3,          LABEL_BACKGROUND},
  {ICON_BED_LEVEL_4,          LABEL_BACKGROUND},
  {ICON_BACKGROUND,           LABEL_BACKGROUND},
  {ICON_BACKGROUND,           LABEL_BACKGROUND},
  {ICON_BACKGROUND,           LABEL_BACKGROUND},
  {ICON_BACK,                 LABEL_BACK},}
};

void menubedleveling(void) {
  KEY_VALUES  key_num = KEY_IDLE;

  menuDrawPage(&Bedlevelitems);
  while(infoMenu.menu[infoMenu.cur] == menubedleveling) {
    key_num = menuKeyGetValue();
    switch(key_num) {
      case KEY_ICON_0:
      storeCmd("G1 Z10 F1000\n");
      storeCmd(LEVELPONIT_1);
      storeCmd("G1 Z0 F500\n");
      goto selectEnd;

      case KEY_ICON_1:
      storeCmd("G1 Z10 F1000\n");
      storeCmd(LEVELPONIT_2);
      storeCmd("G1 Z0 F500\n");
      goto selectEnd;

      case KEY_ICON_2:
      storeCmd("G1 Z10 F1000\n");
      storeCmd(LEVELPONIT_3);
      storeCmd("G1 Z0 F500\n");
      goto selectEnd;

      case KEY_ICON_3:
      storeCmd("G1 Z10 F1000\n");
      storeCmd(LEVELPONIT_4);
      storeCmd("G1 Z0 F500\n");
      goto selectEnd;

      case KEY_ICON_7:
        storeCmd("G28\n");
        infoMenu.cur--;
        return;
      
      default: break;
    }
    loopProcess();
  }
  selectEnd:  
  resetInfoFile();
  powerFailedSetDriverSource(getCurFileSource());
}

void menuCustom(void)
{
  KEY_VALUES  key_num = KEY_IDLE;
  
  menuDrawPage(&customPageitems);
  while(infoMenu.menu[infoMenu.cur] == menuCustom)
  {
    key_num = menuKeyGetValue();
    switch(key_num)
    {
      case KEY_ICON_0:
        storeCmd("M140 S75\n"); 
        storeCmd("M104 S215 T0\n");       
        goto selectEnd;
      
      case KEY_ICON_1:
        storeCmd("M140 S55\n"); 
        storeCmd("M104 S190 T0\n");
        goto selectEnd;
      
      
      case KEY_ICON_2:
        storeCmd("G90\n");
        storeCmd("G1 X60 Y220 F9000\n");
        goto selectEnd;


      case KEY_ICON_3:
        storeCmd("G90\n");
        storeCmd("G1 X0 Y0 F9000\n");
        goto selectEnd;


      case KEY_ICON_4:
        storeCmd("G28\n");
        storeCmd("G1 Z10 F1000\n");
        infoMenu.menu[++infoMenu.cur] = menubedleveling;
        goto selectEnd;  
      
      
      case KEY_ICON_7:
        infoMenu.cur--;
        return;
      
      default: break;
    }
    loopProcess();
  }
  
selectEnd:  
  resetInfoFile();
  powerFailedSetDriverSource(getCurFileSource());
}