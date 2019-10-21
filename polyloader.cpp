#include "polyloader.hpp"

#include "Geometry.h"
#include "Global.h"
#include "Image.h"

#include <fstream>
#include <filesystem>
#include <sstream>

#include "Poco/ClassLibrary.h"

POCO_BEGIN_MANIFEST(sedeen::algorithm::AlgorithmBase)
POCO_EXPORT_CLASS(sedeen::algorithm::PolyLoader)
POCO_END_MANIFEST

namespace sedeen::algorithm {

namespace {

  void writePolygon(std::vector<PointF> const &vertices, OverlayResult &result, std::string const &name) {
    if (vertices.empty()) {
      return;
    }

    Polygon poly(vertices);

    GraphicStyle style;
    Pen style_pen(RGBColor(255, 0, 0));
    style.setPen(style_pen);

    result.drawPolygon(poly, style, name);
  }
}

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

  std::string current_line;
  while (std::getline(file_stream, current_line)) {
    if (current_line.compare("-") == 0) {
      writePolygon(vertices, poly_result_, filepath_);

      vertices.clear();
    } else {
      std::stringstream ss(current_line);
      int x, y;
      if (ss >> x >> y) {
        vertices.emplace_back(x, y);
      } else {
        continue;
      }
    }
  }
  writePolygon(vertices, poly_result_, filepath_);
}

}  // namespace sedeen::algorithm