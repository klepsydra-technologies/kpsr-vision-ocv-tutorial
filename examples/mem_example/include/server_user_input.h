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

#ifndef BST_SERVER_USER_INPUT_H
#define BST_SERVER_USER_INPUT_H

#include <termios.h>
#include <thread>
#include <atomic>

class ServerUserInput {
public:

    ServerUserInput();

    void run();

private:

    void printTestHelp(void);
    void exitServer(void);
    void initializeServer(void);
    void updateServer(void);

    termios initial_settings, new_settings;

public:
    std::atomic_bool _isRunning;

private:
    std::thread _serverThread;
};

#endif //BST_SERVER_USER_INPUT_H
