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
    mipDistanceDrive()
*/
#include <stdio.h>
#include <unistd.h>
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
    int                result = -1;
    MiP*               pMiP = mipInit(NULL);

    printf("\tDistanceDrive.c - Use mipDistanceDrive function.\n"
           "\tDrive forward, turn 360 degrees in each direction and backward.\n");

    // Connect to first MiP robot discovered.
    result = mipConnectToRobot(pMiP, NULL);

    // Queue up multiple commands to run in sequence.
    result = mipDistanceDrive(pMiP, MIP_DRIVE_FORWARD, 30, MIP_TURN_RIGHT, 0);
    // Don't queue up multiple commands too fast.
    usleep(500 * 1000);
    result = mipDistanceDrive(pMiP, MIP_DRIVE_FORWARD, 0, MIP_TURN_LEFT, 360);
    usleep(500 * 1000);
    result = mipDistanceDrive(pMiP, MIP_DRIVE_FORWARD, 0, MIP_TURN_RIGHT, 360);
    usleep(500 * 1000);
    result = mipDistanceDrive(pMiP, MIP_DRIVE_BACKWARD, 30, MIP_TURN_RIGHT, 0);
    usleep(500 * 1000);

    mipUninit(pMiP);
}
