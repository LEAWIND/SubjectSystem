#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "administrator.h"
#include "cui.h"
#include "datastruct.h"
#include "student.h"
#include "teacher.h"

// us: UI style settings
const int us_width = 54;
const int us_height = 23;

char page_getUserType();

int startStudentModule();
int startTeatureModule();
int startAdminModule();