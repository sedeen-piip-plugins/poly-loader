#include "polyloader.hpp"

#include "Geometry.h"
#include "Global.h"

#include <fstream>

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
    std::vector<file::Location> const file_locations = open_file_dialog_;

    if (file_locations.size() > 0) {
      auto const &file_location = file_locations[0];

      std::ifstream file_stream(file_location.getFilename());
      
      std::vector<PointF> vertices;
      int x, y;
      while (file_stream >> x >> y) {
        vertices.emplace_back(x, y);
      }

      Polygon poly(vertices);

      GraphicStyle style;
      Pen style_pen(RGBColor(255, 0, 0));
      style.setPen(style_pen);

      poly_result_.drawPolygon(poly, style);
    }
  }
}

}  // namespace sedeen::algorithm