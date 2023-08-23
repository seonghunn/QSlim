//
// Created by seonghun on 8/22/23.
//

#ifndef QEM_MESHSIMPLIFY_H
#define QEM_MESHSIMPLIFY_H

#include "tree.h"
#include "AABB.hpp"
#include "collapse_callback.h"
#include <Eigen/Core>
#include <time.h>
#include <string>
#include <igl/min_heap.h>
#include <igl/writeOBJ.h>
#include <igl/collapse_edge.h>

using namespace Eigen;
namespace qslim{
    struct index_of_removed_vertices{
        int v1;
        int v2;
    };

    class MeshSimplify{
    private:
        // AABB tree
        aabb::Tree tree;
        // Min heap (priority queue) for greedy decimation
        igl::min_heap< std::tuple<double,int,int> > queue;
        // Q values table using surface normal
        std::vector<Eigen::Matrix4d> qValues;
        // viewer
        igl::opengl::glfw::Viewer viewer;
        // candidate for removing vertices
        index_of_removed_vertices RV;

        // mesh data for each timestamps
        MatrixXd V, C, N_homo;
        MatrixXi F, E, EF, EI;
        VectorXi EMAP, EQ;

        int num_input_vertices;
        int num_input_faces;
        double ratio;

        int num_collapsed;
        int stopping_condition;

        string output_filename;

        // callback functions
        igl::decimate_cost_and_placement_callback cost_and_position_callback;
        igl::decimate_pre_collapse_callback pre_collapse;
        igl::decimate_post_collapse_callback post_collapse;

    public:
        MeshSimplify(MatrixXd &OV, MatrixXi &OF, double ratio);

        // init member variable
        void init_member_variable(MatrixXd &OV, MatrixXi &OF, double ratio);

        // init homogeneous surface normal
        static void init_normal_homo_per_face(MatrixXd &V, MatrixXi &F, MatrixXd &N_homo);

        // init qvalues
        void init_qValues(MatrixXd &V, MatrixXi &F, MatrixXd &N_homo);

        // init queue
        void init_queue(MatrixXd &OV, MatrixXi &OF);

        // init callback
        void init_callback();

        // getter
        MatrixXd get_vertices();

        MatrixXi get_faces();

        igl::decimate_cost_and_placement_callback get_cost_and_position_callback();
        igl::decimate_pre_collapse_callback get_pre_collapse_callback();
        igl::decimate_post_collapse_callback get_post_collapse_callback();

        // find cost and optimal position using each qvalues
        void cost_and_position(
                const int e,
                const Eigen::MatrixXd & V,
                const Eigen::MatrixXi & /*F*/,
                const Eigen::MatrixXi & E,
                const Eigen::VectorXi & /*EMAP*/,
                const Eigen::MatrixXi & /*EF*/,
                const Eigen::MatrixXi & /*EI*/,
                double & cost,
                Eigen::RowVectorXd & p);

        bool process();
    };
}


#endif //QEM_MESHSIMPLIFY_H
