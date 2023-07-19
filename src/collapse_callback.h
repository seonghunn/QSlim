//
// Created by seonghun on 7/18/23.
//

#ifndef QEM_COLLAPSE_CALLBACK_H
#define QEM_COLLAPSE_CALLBACK_H

#include <igl/decimate_callback_types.h>
#include <igl/is_edge_manifold.h>
#include <igl/min_heap.h>
#include <Eigen/Core>
#include <vector>

struct QValues {
    std::vector<Eigen::Matrix4d> values;
};

extern igl::decimate_pre_collapse_callback pre_collapse;
extern igl::decimate_post_collapse_callback post_collapse;
void setup_callbacks(QValues& qvalues);

#endif //QEM_COLLAPSE_CALLBACK_H