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
    mipGetLatestRadarNotification()
*/
#include <stdio.h>
#include <string.h>
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
    int     result = -1;
    MiP*    pMiP = mipInit(NULL);

    printf("\tRadar.c - Display current radar readings to user.\n");

    // Connect to first MiP robot discovered.
    mipConnectToRobot(pMiP, NULL);

    printf("\tWaiting for robot to be standing upright.\n");
    MiPStatus status = {0, 0.0f, 0};
    while (MIP_ERROR_NONE != mipGetLatestStatusNotification(pMiP, &status) && status.position != MIP_POSITION_UPRIGHT)
    {
    }

    mipSetGestureRadarMode(pMiP, MIP_RADAR);

    static MiPRadarNotification lastRadar = { 0, -1 };
    while (1)
    {
        MiPRadarNotification currentRadar;
        result = mipGetLatestRadarNotification(pMiP, &currentRadar);
        if (result != MIP_ERROR_NONE || 0 == memcmp(&lastRadar, &currentRadar, sizeof(lastRadar)))
        {
            continue;
        }

        printf("Radar = ");
        switch (currentRadar.radar) {
          case MIP_RADAR_NONE:
            printf("None\n");
            break;
          case MIP_RADAR_10CM_30CM:
            printf("10cm - 30cm\n");
            break;
          case MIP_RADAR_0CM_10CM:
            printf("0cm - 10cm\n");
            break;
          default:
            break;
        }
        lastRadar = currentRadar;
    }

    mipUninit(pMiP);
}
