#include "polyloader.hpp"

#include "Geometry.h"
#include "Global.h"
#include "Image.h"

#include <fstream>
#include <filesystem>

#include "Poco/ClassLibrary.h"

POCO_BEGIN_MANIFEST(sedeen::algorithm::AlgorithmBase)
POCO_EXPORT_CLASS(sedeen::algorithm::PolyLoader)
POCO_END_MANIFEST

namespace sedeen::algorithm {

PolyLoader::PolyLoader() : poly_result_() {}

void PolyLoader::init(const image::ImageHandle &image) {
  poly_result_ = createOverlayResult(*this);

  // get image filepath
  auto metadata = image->getMetaData();
  filepath_ = metadata->get(image::StringTags::SOURCE_DESCRIPTION, 0);
}

void PolyLoader::run() {
  namespace fs = std::filesystem;

  // get the path of the overlay from the filepath
  auto overlay_filepath = fs::path(filepath_);
  overlay_filepath.replace_extension(".txt");

  std::ifstream file_stream(overlay_filepath.string());

  std::vector<PointF> vertices;
  int x, y;
  while (file_stream >> x >> y) {
    vertices.emplace_back(x, y);
  }

  Polygon poly(vertices);

  GraphicStyle style;
  Pen style_pen(RGBColor(255, 0, 0));
  style.setPen(style_pen);

  poly_result_.drawPolygon(poly, style, filepath_);
}

}  // namespace sedeen::algorithm