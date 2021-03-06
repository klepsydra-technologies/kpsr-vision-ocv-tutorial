#****************************************************************************
#
#                           Klepsydra Core Modules
#              Copyright (C) 2019-2020  Klepsydra Technologies GmbH
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#****************************************************************************

SET(PROJ_NAME kpsr_${PROJ_MAIN_NAME})
PROJECT(${PROJ_NAME})

# Include directories with headers
#---------------------------------------------------#
INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/include )
INCLUDE_DIRECTORIES( ${KLEPSYDRA_INCLUDE_DIRECTORIES} )

# Source
#---------------------------------------------------#
FILE(GLOB ${PROJ_NAME}_SRC
    "src/*.cpp"
)

FILE(GLOB_RECURSE ${PROJ_NAME}_HEADERS
    "include/*.h"
)

# Create Library
#---------------------------------------------------#
LINK_DIRECTORIES()

ADD_LIBRARY(${PROJ_NAME} ${${PROJ_MAIN_NAME}_LIB_TYPE} ${${PROJ_NAME}_HEADERS} ${${PROJ_NAME}_SRC} )

# Link libraries with Project
#---------------------------------------------------#
TARGET_LINK_LIBRARIES(${PROJ_NAME} ${OpenCV_LIBS})

# Install
#---------------------------------------------------#
INSTALL(TARGETS ${PROJ_NAME}
    DESTINATION "${${PROJ_MAIN_NAME}_PATH_INSTALL}/lib/"
)
INSTALL(DIRECTORY "include/klepsydra"
    DESTINATION "${${PROJ_MAIN_NAME}_PATH_INSTALL}/include"
)

#PRINTBASICINFO(${PROJ_NAME})

