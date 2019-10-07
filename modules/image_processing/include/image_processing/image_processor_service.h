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

#ifndef IMAGE_PROCESSING_SERVICE_H
#define IMAGE_PROCESSING_SERVICE_H

#include <klepsydra/core/service.h>
#include <klepsydra/core/subscriber.h>
#include <klepsydra/core/publisher.h>

#include <klepsydra/vision_ocv/image_event_data.h>

#include <image_processing/result_data.h>

namespace kpsr_tutorial {
class ImageProcessingService : public kpsr::Service
{
public:
    ImageProcessingService(kpsr::Environment * environment,
                 kpsr::Subscriber<kpsr::vision_ocv::ImageData> * imageDataSubscriber,
                 kpsr::Publisher<ResultData> * resultPublisher);

protected:
    void start() override;
    void stop() override;
    void execute() override;

private:
    kpsr::Subscriber<kpsr::vision_ocv::ImageData> * _imageDataSubscriber;
    kpsr::Publisher<ResultData> * _resultPublisher;

    void onImageDataReceived(const kpsr::vision_ocv::ImageData & image);
};

}

#endif
