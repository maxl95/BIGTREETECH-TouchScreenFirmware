#include "MainPage.h"
#include "includes.h"

//1��title(����), ITEM_PER_PAGE��item(ͼ��+��ǩ) 
const MENUITEMS mainPageItems = {
//   title
LABEL_READY,
// icon                       label
 {{ICON_HEAT,                 LABEL_HEAT},
  {ICON_MOVE,                 LABEL_MOVE},
  {ICON_HOME,                 LABEL_HOME},
  {ICON_PRINT,                LABEL_PRINT},
  {ICON_EXTRUDE,              LABEL_EXTRUDE},
  {ICON_FAN,                  LABEL_FAN},
  {ICON_SETTINGS,             LABEL_SETTINGS},
  #ifndef MOREMENU
  {ICON_LEVELING,             LABEL_LEVELING},
  #else
  {ICON_FOLDER,             LABLE_CUSTOMPAGE},
  #endif
  }
};

void menuMain(void)
{
  KEY_VALUES key_num=KEY_IDLE;

  menuDrawPage(&mainPageItems);

  while(infoMenu.menu[infoMenu.cur] == menuMain)
  {
    key_num = menuKeyGetValue();
    switch(key_num)
    {
      case KEY_ICON_0: infoMenu.menu[++infoMenu.cur] = menuHeat;      break;
      case KEY_ICON_1: infoMenu.menu[++infoMenu.cur] = menuMove;      break;
      case KEY_ICON_2: infoMenu.menu[++infoMenu.cur] = menuHome;      break;
      case KEY_ICON_3: infoMenu.menu[++infoMenu.cur] = menuPrint;     break;      
      case KEY_ICON_4: infoMenu.menu[++infoMenu.cur] = menuExtrude;   break;
      case KEY_ICON_5: infoMenu.menu[++infoMenu.cur] = menuFan;       break;
      case KEY_ICON_6: infoMenu.menu[++infoMenu.cur] = menuSettings;  break;

      #ifndef MOREMENU
      case KEY_ICON_7: storeCmd("G28\n"); storeCmd("G29\n");          break;
      #else
      case KEY_ICON_7: infoMenu.menu[++infoMenu.cur] = menuCustom;    break;
      #endif

      default:break;
    }		
    loopProcess();
  }
}

