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

#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <thread>

#include <klepsydra/core/event_emitter_middleware_provider.h>
#include <klepsydra/mem_vision_ocv/image_multiplexer_vision_ocv_provider.h>

#include <klepsydra/mem_core/mem_env.h>

#include <image_processing/image_processor_service.h>

#include "server_user_input.h"

#include "simple_write_service.h"

#include "config.h"

int main(int argc, char* argv[]) {
    std::string containerName = argc > 1 ? argv[1] : "sample1";
    std::string folderName = argc > 4 ? argv[4] : TEST_DATA;
    kpsr::mem::MemEnv environment;

    kpsr::vision_ocv::high_performance::ImageMultiplexerVisionMiddlewareProvider<128> provider(nullptr, "image_processing_feed",
                                                                                              1024, 640, 16, "body");

    kpsr::EventEmitterMiddlewareProvider<kpsr_tutorial::ResultData> eventEmitter(nullptr,
                                                                        "image_processing_results",
                                                                        0, nullptr, nullptr);

    SimpleWriteService simpleWriteService(&environment,
                                          provider.underlying->getPublisher(),
                                          folderName,
                                          true);
    kpsr_tutorial::ImageProcessingService imageProcessingService(&environment, provider.underlying->getSubscriber(), eventEmitter.getPublisher());

    imageProcessingService.startup();
    simpleWriteService.startup();

    ServerUserInput serverUserInput;

    std::thread imageProcessingServiceThread = std::thread([&]() {
        while (true) {
            simpleWriteService.runOnce();
            imageProcessingService.runOnce();
            std::this_thread::sleep_for(std::chrono::seconds(1));
            if (!serverUserInput._isRunning) {
                break;
            }
        }
    });

    serverUserInput.run();

    imageProcessingServiceThread.join();

    simpleWriteService.shutdown();
    imageProcessingService.shutdown();
}
