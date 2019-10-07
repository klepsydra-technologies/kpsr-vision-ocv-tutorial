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

#include <image_processing/image_processor_service.h>

kpsr_tutorial::ImageProcessingService::ImageProcessingService(kpsr::Environment * environment,
             kpsr::Subscriber<kpsr::vision_ocv::ImageData> * imageDataSubscriber,
                                 kpsr::Publisher<ResultData> * resultPublisher)
    : kpsr::Service(environment, "image_processing")
    , _imageDataSubscriber(imageDataSubscriber)
    , _resultPublisher(resultPublisher)
{}

void kpsr_tutorial::ImageProcessingService::start() {
    std::function<void(const kpsr::vision_ocv::ImageData &)> listener = std::bind(&ImageProcessingService::onImageDataReceived, this, std::placeholders::_1);
    _imageDataSubscriber->registerListener("image_processing", listener);
}

void kpsr_tutorial::ImageProcessingService::stop() {
    _imageDataSubscriber->removeListener("image_processing");
}
void kpsr_tutorial::ImageProcessingService::execute() {

}

void kpsr_tutorial::ImageProcessingService::onImageDataReceived(const kpsr::vision_ocv::ImageData & image) {
    // to access OpenCV image: image.img
    kpsr_tutorial::ResultData resultData;
    resultData.ok = true;
    _resultPublisher->publish(resultData);
}
