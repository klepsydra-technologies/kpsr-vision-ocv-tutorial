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

#include <klepsydra/core/event_emitter_middleware_provider.h>
#include <klepsydra/core/cache_listener.h>

#include <image_processing/image_processor_service.h>

#include "simple_write_service.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

#include "gtest/gtest.h"

#include "config.h"

TEST(ImageProcessingServiceTest, ImageProcessingServiceTest) {
    kpsr::EventEmitterMiddlewareProvider<kpsr::vision_ocv::ImageData> imageDataEventEmitter(nullptr,
                                                                                            "image_event_emitter",
                                                                                            0,
                                                                                            nullptr,
                                                                                            nullptr);

    kpsr::EventEmitterMiddlewareProvider<kpsr_tutorial::ResultData> resultDataEventEmitter(nullptr,
                                                                                  "result_data_emitter",
                                                                                  0,
                                                                                  nullptr,
                                                                                  nullptr);

    SimpleWriteService writeService(nullptr, imageDataEventEmitter.getPublisher(), TEST_DATA, true);

    kpsr_tutorial::ImageProcessingService imageProcessingServiceService(nullptr, imageDataEventEmitter.getSubscriber(), resultDataEventEmitter.getPublisher());

    kpsr::mem::TestCacheListener<kpsr_tutorial::ResultData> testListener(0);

    resultDataEventEmitter.getSubscriber()->registerListener("Test", testListener.cacheListenerFunction);

    spdlog::info("Starting services.");
    writeService.startup();
    imageProcessingServiceService.startup();

    // Publish some integers.
    for (int i = 0; i < 1; i++) {
        spdlog::info("Executing services.");
        writeService.runOnce();
        imageProcessingServiceService.runOnce();

        ASSERT_TRUE(testListener.getLastReceivedEvent()->ok);
    }

    writeService.shutdown();
    writeService.shutdown();
}

