/****************************************************************************
*
*                           Klepsydra Core Modules
*              Copyright (C) 2019-2020  Klepsydra Technologies GmbH
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <functional>
#include <iostream>

#include <klepsydra/core/time_utils.h>

#include "server_user_input.h"

ServerUserInput::ServerUserInput()
    : _isRunning(false)
{
    _serverThread = std::thread([this]() {
        initializeServer();
        printTestHelp();

        _isRunning = true;
        while(_isRunning) {
            updateServer();
        }
        exitServer();
    });
}

void ServerUserInput::run() {
    _serverThread.join();
}

void ServerUserInput::printTestHelp() {
    std::cout << "Keys:" << std::endl;
    std::cout << "  q   : Quit" << std::endl;
    std::cout << "  p   : Print help" << std::endl;
}

void ServerUserInput::initializeServer() {

    /*tcgetattr gets the parameters of the current terminal
    STDIN_FILENO will tell tcgetattr that it should write the settings
    of stdin to initial_settings*/
    tcgetattr( STDIN_FILENO, &initial_settings);
    /*now the settings will be copied*/
    new_settings = initial_settings;

    /*ICANON normally takes care that one line at a time will be processed
    that means it will return if it sees a "\n" or an EOF or an EOL*/
    new_settings.c_lflag &= ~(ICANON);
    new_settings.c_lflag &= ~ECHO;

    /*Those new settings will be set to STDIN
    TCSANOW tells tcsetattr to change attributes immediately. */
    tcsetattr( STDIN_FILENO, TCSANOW, &new_settings);
}

void ServerUserInput::updateServer() {
    char input = getchar();

    if(input > 0) {
        switch(input) {
        case 'p':
            printTestHelp();
            break;
        case 3: // <CTRL-C>
            std::cout << "Keyboard caught exit signal ..." << std::endl;
            _isRunning = false;
        case 'q':
            std::cout << "Keyboard caught exit signal ..." << std::endl;
            _isRunning = false;
            break;

        default:
            break;
        }
        input = 0;
    } else {
        clearerr(stdin);
    }
}

void ServerUserInput::exitServer() {
    tcsetattr(STDIN_FILENO, TCSANOW, &initial_settings);
}
