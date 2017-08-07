/******************************************************************************
 * Copyright 2017 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

/**
 *   @file: st_graph_boundary.h
 **/

#ifndef MODULES_PLANNING_OPTIMIZER_ST_GRAPH_ST_GRAPH_BOUNDARY_H_
#define MODULES_PLANNING_OPTIMIZER_ST_GRAPH_ST_GRAPH_BOUNDARY_H_

#include <memory>
#include <vector>

#include "modules/planning/proto/planning.pb.h"

#include "modules/common/math/polygon2d.h"
#include "modules/planning/common/path_obstacle.h"
#include "modules/planning/optimizer/st_graph/st_graph_point.h"

namespace apollo {
namespace planning {

class StGraphBoundary : public common::math::Polygon2d {
 public:
  explicit StGraphBoundary(const PathObstacle* path_obstacle);
  // boundary points go counter clockwise.
  explicit StGraphBoundary(const PathObstacle* path_obstacle,
                           const std::vector<STPoint>& points);

  // boundary points go counter clockwise.
  explicit StGraphBoundary(const PathObstacle* path_obstacle,
                           const std::vector<common::math::Vec2d>& points);
  // if you need to add boundary type, make sure you modify
  // GetUnblockSRange accordingly.
  enum class BoundaryType {
    UNKNOWN,
    STOP,
    FOLLOW,
    YIELD,
    OVERTAKE,
  };

  ~StGraphBoundary() = default;

  bool IsPointInBoundary(const StGraphPoint& st_graph_point) const;
  bool IsPointInBoundary(const STPoint& st_point) const;

  common::math::Vec2d point(const uint32_t index) const;
  const std::vector<common::math::Vec2d>& points() const;

  BoundaryType boundary_type() const;
  const std::string& id() const;
  double characteristic_length() const;

  void set_id(const std::string& id);
  void SetBoundaryType(const BoundaryType& boundary_type);
  void SetCharacteristicLength(const double characteristic_length);

  bool GetUnblockSRange(const double curr_time, double* s_upper,
                        double* s_lower) const;

  bool GetBoundarySRange(const double curr_time, double* s_upper,
                         double* s_lower) const;

  void GetBoundaryTimeScope(double* start_t, double* end_t) const;

  const PathObstacle* path_obstacle() const;

 private:
  const PathObstacle* path_obstacle_ = nullptr;
  BoundaryType boundary_type_ = BoundaryType::UNKNOWN;
  std::string id_;
  double characteristic_length_ = 1.0;
  double s_high_limit_ = 200.0;
};

}  // namespace planning
}  // namespace apollo

#endif  // MODULES_PLANNING_OPTIMIZER_ST_GRAPH_ST_GRAPH_BOUNDARY_H_
