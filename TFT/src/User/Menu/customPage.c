/*
 * Copyright (C) 2019 maxl95
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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
  {ICON_FOLDER,               LABLE_CUSTOMPAGE},
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

MENUITEMS infomenuitems = {
//  title
LABEL_READY,
// icon                       label
 {{ICON_BACKGROUND,           LABEL_BACKGROUND},
  {ICON_BACKGROUND,           LABEL_BACKGROUND},
  {ICON_BACKGROUND,           LABEL_BACKGROUND},
  {ICON_BACKGROUND,           LABEL_BACKGROUND},
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

      case KEY_ICON_6:
        infoMenu.menu[++infoMenu.cur] = infomenu;
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

const GUI_RECT progressRectinfo = {1*SPACE_X_PER_ICON, 0*ICON_HEIGHT+0*SPACE_Y+TITLE_END_Y + ICON_HEIGHT/4,
                               3*SPACE_X_PER_ICON, 0*ICON_HEIGHT+0*SPACE_Y+TITLE_END_Y + ICON_HEIGHT*3/4};

#define BED_X  (progressRectinfo.x1 - 9 * BYTE_WIDTH)
#define TEMP_Y (progressRectinfo.y1 + 3)
#define TIME_Y (TEMP_Y + 1 * BYTE_HEIGHT + 3)

void infomenu(void) {
  KEY_VALUES  key_num = KEY_IDLE;
  
  menuDrawPage(&infomenuitems);

  //GUI_DispString(progressRectinfo.x0+BYTE_WIDTH*2, TEMP_Y,(u8* )":",0);
  GUI_DispChar(progressRectinfo.x0+BYTE_WIDTH*6, TEMP_Y,'/',0);
  
  GUI_DispString(BED_X, TEMP_Y,(u8* )"Bed:",0);
  GUI_DispChar(BED_X+BYTE_WIDTH*5 + 15, TEMP_Y,'/',0);

  while(infoMenu.menu[infoMenu.cur] == infomenu)
  {
    //Read Nozzle-Temp.
    GUI_DispString(progressRectinfo.x0 - 28, TEMP_Y, (u8* )"Nozzle:", 1);
    GUI_DispDec(progressRectinfo.x0+BYTE_WIDTH*3, TEMP_Y, heatGetCurrentTemp(heatGetCurrentToolNozzle()), 3, 1, RIGHT);
    GUI_DispDec(progressRectinfo.x0+BYTE_WIDTH*7, TEMP_Y, heatGetTargetTemp(heatGetCurrentToolNozzle()),  3, 1, LEFT);
    
    //Read Bed-Temp.
    GUI_DispDec(BED_X + 2 * BYTE_WIDTH + 15, TEMP_Y, heatGetCurrentTemp(BED), 3, 1, RIGHT);
    GUI_DispDec(BED_X + 6 * BYTE_WIDTH + 15, TEMP_Y, heatGetTargetTemp(BED),  3, 1, LEFT);

    key_num = menuKeyGetValue();
    switch(key_num)
    {
      case KEY_ICON_7:
        infoMenu.cur--;
        return;
      
      default: break;
    }
    loopProcess();
  }
}