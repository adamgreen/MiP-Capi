/* Copyright (C) 2015  Adam Green (https://github.com/adamgreen)

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
/* Example used in following API documentation:
    mipSetGestureRadarMode()
    mipGetGestureRadarMode()
*/
#include <stdio.h>
#include "mip.h"
#include "osxble.h"


int main(int argc, char *argv[])
{
    // Initialize the Core Bluetooth stack on this the main thread and start the worker robot thread to run the
    // code found in robotMain() below.
    osxMiPInitAndRun();
    return 0;
}

void robotMain(void)
{
    int                  result = -1;
    MiPGestureRadarMode  mode = MIP_GESTURE_RADAR_DISABLED;
    MiP*                 pMiP = mipInit(NULL);

    printf("\tGestureRadarMode.c - Use mipSet/GetGestureRadarMode() functions.\n"
           "\tShould switch into radar mode.\n");

    // Connect to first MiP robot discovered.
    result = mipConnectToRobot(pMiP, NULL);

    printf("Enable radar mode\n");
    do
    {
        // Keep trying until it goes through.
        result = mipSetGestureRadarMode(pMiP, MIP_RADAR);
        result = mipGetGestureRadarMode(pMiP, &mode);
    } while (mode != MIP_RADAR);
    printf("Radar mode enabled\n");

    mipUninit(pMiP);
}
