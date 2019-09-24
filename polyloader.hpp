#pragma once

#include "algorithm/AlgorithmBase.h"
#include "algorithm/Parameters.h"
#include "algorithm/Results.h"

namespace sedeen::algorithm {

class PolyLoader : public AlgorithmBase {

 public:
  PolyLoader();

 private:
  void init(const image::ImageHandle &image) final;
  void run() final;

 private:
  algorithm::OverlayResult poly_result_;

  std::string filepath_;
};

}  // namespace sedeen::algorithm