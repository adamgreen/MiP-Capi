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
    mipSetVolume()
    mipGetVolume()
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
    int     result = -1;
    uint8_t volume = 0;
    MiP*    pMiP = mipInit(NULL);

    printf("\tVolume.c - Use mipSet/GetVolume().\n"
           "\tSet volume level to 1 and read out afterwards.\n");

    // Connect to first MiP robot discovered.
    result = mipConnectToRobot(pMiP, NULL);

    result = mipSetVolume(pMiP, 1);
    result = mipGetVolume(pMiP, &volume);

    printf("Volume = %u\n", volume);

    mipUninit(pMiP);
}
