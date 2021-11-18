//
// Created by János Tánczos on 2021. 11. 07..
//

#ifndef MAIN_C_MENU_H
#define MAIN_C_MENU_H

#include "../rendering.h"
#include "button.h"

/// Opens the main menu and renders every related things
/// @param GameRenderer
/// @returns WindowState enum what describes what state does the user selected from the menu
enum WindowState OpenMenu(GameRenderer *renderer);


#endif //MAIN_C_MENU_H
