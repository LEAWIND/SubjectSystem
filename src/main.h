#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cui.h"

// us: UI style settings
const int us_width = 54;
const int us_height = 23;

char page_getUserType();
int startStudentModule();
int startTeatureModule();
int startAdminModule();