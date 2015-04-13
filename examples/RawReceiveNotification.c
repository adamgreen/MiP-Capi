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
    mipRawReceiveNotification()
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
    int     result = -1;
    size_t  responseLength = 0;
    uint8_t response[MIP_RESPONSE_MAX_LEN];
    MiP*    pMiP = mipInit(NULL);

    printf("\tRawReceiveNotification.c - Use mipRawReceiveNotification() functions.\n"
           "\tIn less than half a minute, a notification should be displayed.\n");

    // Connect to first MiP robot discovered.
    result = mipConnectToRobot(pMiP, NULL);

    // Wait for first out of band notification to arrive.
    while (MIP_ERROR_EMPTY == mipRawReceiveNotification(pMiP, response, sizeof(response), &responseLength))
    {
    }

    // Display notification contents.
    printf("notification -> ");
    for (int i = 0 ; i < responseLength ; i++)
    {
        printf("%02X", response[i]);
    }
    printf("\n");

    mipUninit(pMiP);
}
