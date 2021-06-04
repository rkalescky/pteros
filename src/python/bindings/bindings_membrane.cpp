/*
 * This file is a part of
 *
 * ============================================
 * ###   Pteros molecular modeling library  ###
 * ============================================
 *
 * https://github.com/yesint/pteros
 *
 * (C) 2009-2021, Semen Yesylevskyy
 *
 * All works, which use Pteros, should cite the following papers:
 *
 *  1.  Semen O. Yesylevskyy, "Pteros 2.0: Evolution of the fast parallel
 *      molecular analysis library for C++ and python",
 *      Journal of Computational Chemistry, 2015, 36(19), 1480–1488.
 *      doi: 10.1002/jcc.23943.
 *
 *  2.  Semen O. Yesylevskyy, "Pteros: Fast and easy to use open-source C++
 *      library for molecular analysis",
 *      Journal of Computational Chemistry, 2012, 33(19), 1632–1636.
 *      doi: 10.1002/jcc.22989.
 *
 * This is free software distributed under Artistic License:
 * http://www.opensource.org/licenses/artistic-license-2.0.php
 *
*/





#include "bindings_util.h"
#include "pteros/extras/membrane.h"

namespace py = pybind11;
using namespace pteros;
using namespace pybind11::literals;

void make_bindings_Membrane(py::module& m){

    py::class_<Lipid_descr>(m,"Lipid_descr")
        .def(py::init<const std::string&,
             const std::string&,
             const std::string&,
             const std::string&,
             const std::string&,
             const std::vector<std::string>&>())
        .def_readonly("name",&Lipid_descr::name)
        .def_readonly("whole_sel_str",&Lipid_descr::whole_sel_str)
        .def_readonly("head_sel_str",&Lipid_descr::head_sel_str)
        .def_readonly("tail_sel_str",&Lipid_descr::tail_sel_str)
        .def_readonly("head_mid_str",&Lipid_descr::mid_sel_str)
        .def_readonly("head_mid_str",&Lipid_descr::tail_carbon_sels)
    ;

    py::class_<Splay_pair>(m,"Splay_pair")
        .def_readonly("lip1",&Splay_pair::lip1)
        .def_readonly("lip2",&Splay_pair::lip2)
        .def_readonly("splay",&Splay_pair::splay)
    ;

    py::class_<Lipid>(m,"Lipid")
            .def(py::init<const Selection&,const Lipid_descr&>())

            .def_readwrite("mid_sel",&Lipid::mid_sel)
            .def_readwrite("head_sel",&Lipid::head_sel)
            .def_readwrite("tail_sel",&Lipid::tail_sel)
            .def_readwrite("whole_sel",&Lipid::whole_sel)
            .def_readwrite("group",&Lipid::group)

            .def_readonly("name",&Lipid::name)            
            .def_readonly("normal",&Lipid::normal)
            .def_readonly("smoothed_mid_xyz",&Lipid::smoothed_mid_xyz)
            .def_readonly("tilt",&Lipid::tilt)            
            .def_readonly("quad_fit_rms",&Lipid::quad_fit_rms)
            .def_readonly("area",&Lipid::area)
            .def_readonly("leaflet",&Lipid::leaflet)
            .def_readonly("gaussian_curvature",&Lipid::gaussian_curvature)
            .def_readonly("mean_curvature",&Lipid::mean_curvature)
            .def_readonly("coord_number",&Lipid::coord_number)
            .def_readonly("order",&Lipid::order)
            .def_readonly("dipole",&Lipid::dipole)
            .def_readonly("dipole_proj",&Lipid::dipole_proj)
    ;

    py::class_<Membrane>(m,"Membrane")
        .def(py::init<System*,const std::vector<Lipid_descr>&>())
        .def(py::init<System*,const std::vector<Lipid_descr>&,int>())
        .def(py::init<System*,const std::vector<Lipid_descr>&,int,bool>())

        .def("compute_properties",&Membrane::compute_properties,
             "d"_a,
             "use_external_normal"_a=false,
             "external_pivot"_a=Eigen::Vector3f::Zero(),
             "external_dist_dim"_a=Eigen::Vector3i::Ones()
            )
        .def("compute_averages",&Membrane::compute_averages)
        .def("write_averages",&Membrane::write_averages)
        .def("write_vmd_arrows",&Membrane::write_vmd_arrows)
        .def("write_smoothed",&Membrane::write_smoothed)
        .def("num_lipids",&Membrane::num_lipids)
        .def("get_lipid",&Membrane::get_lipid,py::return_value_policy::reference_internal)        
        .def_readonly("lipids",&Membrane::lipids)
        .def_readonly("splay",&Membrane::splay)
        .def_readonly("neighbors",&Membrane::neighbors)        
    ;
}




