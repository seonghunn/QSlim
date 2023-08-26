//
// Created by seonghun on 8/21/23.
//

#ifndef QEM_TREE_H
#define QEM_TREE_H

#include "AABB.hpp"
#include "helper.h"
#include <Eigen/Core>

using namespace Eigen;
using namespace std;
namespace qslim{
    // structure for restoring node data
    struct NodeSnapshot{
        bool isDeleted;
        int particleIdx;
        vector<double> lowerBound;
        vector<double> upperBound;
    };

    //init AABB tree
    void initialize_tree_from_mesh(const Eigen::MatrixXd &V, const Eigen::MatrixXi &F, aabb::Tree &tree);

    //update ancestors of leaf
    bool update_ancestors(aabb::Tree &tree, unsigned int triangleIdx, unsigned int dim,
                          std::unordered_map<int, NodeSnapshot> &restoreMap);

    //update tree after decimation
    bool update_tree_after_decimation(
            const Eigen::MatrixXd &V,
            const Eigen::MatrixXi &F,
            aabb::Tree &tree,
            int RV_idx1, int RV_idx2,
            int f1, int f2, std::unordered_map<int, bool> &decimatedFaces,
            std::unordered_map<int, std::vector<int>> &affectedTriangleIndices,
            std::unordered_map<int, NodeSnapshot> &restoreMap);

}


#endif //QEM_TREE_H
