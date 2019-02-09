//
// Created by matth on 05/01/2019.
//

#ifndef NOVELRT_NOVELIMAGERECT_H
#define NOVELRT_NOVELIMAGERECT_H

#include "NovelObject.h"
#include "RGBAConfig.h"
#include <string>
#include "../lib/nanovg/nanovg.h"

namespace NovelRT {

    class NovelImageRect : public NovelObject {
    public:
        NovelImageRect(const GeoVector<float>& position, NVGcontext* context, const std::string& imageDir, const float& rotation = 0, const GeoVector<float>& scale = GeoVector<float>(1, 1));

        void drawObject() const override;
        void setScale(const GeoVector<float>& value) override;

    private:
        std::string _imageDir;
        int _imageHandle;
        NVGpaint _paint;
        int _width;
        int _height;

    };

}
#endif //NOVELRT_NOVELIMAGERECT_H
