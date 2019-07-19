#include "polyloader.hpp"

#include "Geometry.h"
#include "Global.h"

#include "Poco/ClassLibrary.h"

POCO_BEGIN_MANIFEST(sedeen::algorithm::AlgorithmBase)
POCO_EXPORT_CLASS(sedeen::algorithm::PolyLoader)
POCO_END_MANIFEST

namespace sedeen::algorithm {

PolyLoader::PolyLoader()
    : open_file_dialog_()
    , poly_result_() {}

void PolyLoader::init(const image::ImageHandle &image) {
  poly_result_ = createOverlayResult(*this);
  open_file_dialog_ = createOpenFileDialogParameter(*this, "Polygon File", "File containing list of polygon points");
}

void PolyLoader::run() {
  if (open_file_dialog_.isChanged()) {
    std::vector<file::Location> file_locations = open_file_dialog_;



    std::vector<PointF> vertices;
    vertices.emplace_back(0.0, 0.0);
    vertices.emplace_back(0.0, 100.0);
    vertices.emplace_back(100.0, 100.0);
    vertices.emplace_back(100.0, 0.0);

    Polygon poly(vertices);

    poly_result_.drawPolygon(poly);
  }
}

}  // namespace sedeen::algorithm