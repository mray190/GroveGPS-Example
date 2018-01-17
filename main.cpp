// ----------------------------------------------------------------------------
// Copyright 2016-2017 ARM Ltd.
//
// SPDX-License-Identifier: Apache-2.0
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ----------------------------------------------------------------------------

#include "mbed.h"

#include "GroveGPS.h"

Serial gps_serial(D1, D0, 9600);

Thread gpsThread;
GroveGPS gps;

// Runs at 1Hz and updates the GPS location every second
void gps_updater_thread() {
    while(true) {
        char latBuffer[16], lonBuffer[16];
        gps.getLatitude(latBuffer);
        gps.getLongitude(lonBuffer);

        // Utilize latitude and longitude values here
        printf("Latitude: %f\n, Longitude: %f\n", latBuffer, lonBuffer);
        wait(1);
    }
}

int main() {

    // Start a thread to get updated GPS values
    gpsThread.start(gps_updater_thread);

    // Read the serial bus to get NMEA GPS details
    while (true) {
        if (gps_serial.readable()) {
            gps.readCharacter(gps_serial.getc());
        }
    }

    return 0;
}