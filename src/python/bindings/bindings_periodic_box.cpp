/*
 *
 *                This source code is part of
 *                    ******************
 *                    ***   Pteros   ***
 *                    ******************
 *                 molecular modeling library
 *
 * Copyright (c) 2009-2013, Semen Yesylevskyy
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of Artistic License:
 *
 * Please note, that Artistic License is slightly more restrictive
 * then GPL license in terms of distributing the modified versions
 * of this software (they should be approved first).
 * Read http://www.opensource.org/licenses/artistic-license-2.0.php
 * for details. Such license fits scientific software better then
 * GPL because it prevents the distribution of bugged derivatives.
 *
*/

#include "bindings_periodic_box.h"
#include "pteros/core/system.h"
#include "pteros/python/bindings_util.h"

using namespace pteros;
using namespace Eigen;
using namespace boost::python;

void Periodic_box_modify(Periodic_box* b, PyObject* arr){
    MAP_EIGEN_TO_PYARRAY(m,Matrix3f,arr)
    b->modify(m);
}

PyObject* Periodic_box_get_box(Periodic_box* b){
    CREATE_PYARRAY_2D(p,3,3)
    MAP_EIGEN_TO_PYARRAY(m,Matrix3f,p)
    m = b->get_box();
    return boost::python::incref(p);
}

PyObject* Periodic_box_to_box(Periodic_box* b, PyObject* point){
    CREATE_PYARRAY_1D(ret,3)
    MAP_EIGEN_TO_PYARRAY(v,Vector3f,ret)
    MAP_EIGEN_TO_PYARRAY(p,Vector3f,point)
    v = b->to_box(p);
    return boost::python::incref(ret);
}

PyObject* Periodic_box_to_lab(Periodic_box* b, PyObject* point){
    CREATE_PYARRAY_1D(ret,3)
    MAP_EIGEN_TO_PYARRAY(v,Vector3f,ret)
    MAP_EIGEN_TO_PYARRAY(p,Vector3f,point)
    v = b->to_lab(p);
    return boost::python::incref(ret);
}

PyObject* Periodic_box_to_box_matrix(Periodic_box* b){
    CREATE_PYARRAY_2D(ret,3,3)
    MAP_EIGEN_TO_PYARRAY(m,Matrix3f,ret)
    m = b->to_box_matrix();
    return boost::python::incref(ret);
}

PyObject* Periodic_box_to_lab_matrix(Periodic_box* b){
    CREATE_PYARRAY_2D(ret,3,3)
    MAP_EIGEN_TO_PYARRAY(m,Matrix3f,ret)
    m = b->to_lab_matrix();
    return boost::python::incref(ret);
}

PyObject* Periodic_box_extents(Periodic_box* b){
    CREATE_PYARRAY_1D(ret,3)
    MAP_EIGEN_TO_PYARRAY(v,Vector3f,ret)
    v = b->extents();
    return boost::python::incref(ret);
}

float Periodic_box_distance1(Periodic_box* b, PyObject* point1, PyObject* point2,
                             bool do_wrap, boost::python::list periodic_dims){
    MAP_EIGEN_TO_PYARRAY(p1,Vector3f,point1)
    MAP_EIGEN_TO_PYARRAY(p2,Vector3f,point2)
    Vector3i dims;
    for(int i=0;i<3;++i) dims(i) = extract<int>(periodic_dims[i]);

    float dist = b->distance(p1,p2,do_wrap,dims);
    return dist;
}

float Periodic_box_distance2(Periodic_box* b, PyObject* point1, PyObject* point2, bool do_wrap){
    MAP_EIGEN_TO_PYARRAY(p1,Vector3f,point1)
    MAP_EIGEN_TO_PYARRAY(p2,Vector3f,point2)

    float dist = b->distance(p1,p2,do_wrap);
    return dist;
}

float Periodic_box_distance3(Periodic_box* b, PyObject* point1, PyObject* point2){
    MAP_EIGEN_TO_PYARRAY(p1,Vector3f,point1)
    MAP_EIGEN_TO_PYARRAY(p2,Vector3f,point2)

    float dist = b->distance(p1,p2);
    return dist;
}

void Periodic_box_wrap_point1(Periodic_box* b, PyObject* point, boost::python::list dims_to_wrap){
    MAP_EIGEN_TO_PYARRAY(p,Vector3f,point)

    Vector3i dims;
    for(int i=0;i<3;++i) dims(i) = extract<int>(dims_to_wrap[i]);

    b->wrap_point(p,dims);
}

void Periodic_box_wrap_point2(Periodic_box* b, PyObject* point){
    MAP_EIGEN_TO_PYARRAY(p,Vector3f,point)    
    b->wrap_point(p);
}

PyObject* Periodic_box_get_closest_image1(Periodic_box* b, PyObject* point, PyObject* target,
                             bool do_wrap, boost::python::list dims_to_wrap){
    MAP_EIGEN_TO_PYARRAY(p,Vector3f,point)
    MAP_EIGEN_TO_PYARRAY(t,Vector3f,target)

    CREATE_PYARRAY_1D(ret,3)
    MAP_EIGEN_TO_PYARRAY(v,Vector3f,ret)

    Vector3i dims;
    for(int i=0;i<3;++i) dims(i) = extract<int>(dims_to_wrap[i]);

    v = b->get_closest_image(p,t,do_wrap,dims);
    return boost::python::incref(ret);
}

PyObject* Periodic_box_get_closest_image2(Periodic_box* b, PyObject* point, PyObject* target,
                             bool do_wrap){
    MAP_EIGEN_TO_PYARRAY(p,Vector3f,point)
    MAP_EIGEN_TO_PYARRAY(t,Vector3f,target)

    CREATE_PYARRAY_1D(ret,3)
    MAP_EIGEN_TO_PYARRAY(v,Vector3f,ret)

    v = b->get_closest_image(p,t,do_wrap);
    return boost::python::incref(ret);
}

PyObject* Periodic_box_get_closest_image3(Periodic_box* b, PyObject* point, PyObject* target){
    MAP_EIGEN_TO_PYARRAY(p,Vector3f,point)
    MAP_EIGEN_TO_PYARRAY(t,Vector3f,target)

    CREATE_PYARRAY_1D(ret,3)
    MAP_EIGEN_TO_PYARRAY(v,Vector3f,ret)

    v = b->get_closest_image(p,t);
    return boost::python::incref(ret);
}


void make_bindings_Periodic_box(){
    import_array();

    class_<Periodic_box>("Periodic_box", init<>())
        .def("modify",&Periodic_box_modify)
        .def("get_box",&Periodic_box_get_box)
        .def("to_box",&Periodic_box_to_box)
        .def("to_box_matrix",&Periodic_box_to_box_matrix)
        .def("to_lab",&Periodic_box_to_lab)
        .def("to_lab_matrix",&Periodic_box_to_lab_matrix)
        .def("extent",&Periodic_box::extent)
        .def("extents",&Periodic_box_extents)
        .def("is_triclinic",&Periodic_box::is_triclinic)
        .def("is_periodic",&Periodic_box::is_periodic)
        .def("distance",&Periodic_box_distance1)
        .def("distance",&Periodic_box_distance2)
        .def("distance",&Periodic_box_distance3)
        .def("wrap_point",&Periodic_box_wrap_point1)
        .def("wrap_point",&Periodic_box_wrap_point2)
        .def("get_closest_image",&Periodic_box_get_closest_image1)
        .def("get_closest_image",&Periodic_box_get_closest_image2)
        .def("get_closest_image",&Periodic_box_get_closest_image3)
        .def("is_periodic",&Periodic_box::volume)
    ;
}