/*
 *
 *                This source code is part of
 *                    ******************
 *                    ***   Pteros   ***
 *                    ******************
 *                 molecular modeling library
 *
 * Copyright (c) 2009, Semen Yesylevskyy
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


#include "pteros/analysis/bilayer.h"
#include "pteros/core/pteros_error.h"
#include <boost/lexical_cast.hpp>
#include <boost/phoenix.hpp>

using namespace std;
using namespace pteros;

Bilayer::Bilayer(Selection &sel, std::string head_marker_atom, float d){
    create(sel,head_marker_atom,d);
}

void Bilayer::create(Selection &sel, std::string head_marker_atom, float d){
    spot_size = 10;
    bilayer_ptr = &sel;    
    Selection(*sel.get_system(),"("+sel.get_text()+") and "+head_marker_atom)
            .split_by_connectivity(d,surf);
    if(surf.size()!=2) throw Pteros_error("Passed selection is not a bilayer!");

    // Select monolayers
    vector<int> ind;
    string str;

    // Monolayer 1
    ind = surf[0].get_unique_resindex();
    str = "resindex";
    for(int i=0; i<ind.size(); ++i) str += " "+boost::lexical_cast<string>(ind[i]);
    mono1.modify(*sel.get_system(),str);
    cout << "Monolayer 1 contains " << mono1.size() << " atoms in " << surf[0].size() << " lipids " << endl;

    // Monolayer 2
    ind = surf[1].get_unique_resindex();
    str = "resindex";
    for(int i=0; i<ind.size(); ++i) str += " "+boost::lexical_cast<string>(ind[i]);
    mono2.modify(*sel.get_system(),str);
    cout << "Monolayer 2 contains " << mono1.size() << " atoms in " << surf[1].size() << " lipids " << endl;
}

bool dist_sorter(int a ,int b, vector<float>& d){ return d[a]<d[b]; }

Bilayer_point_info Bilayer::point_info(Eigen::Vector3f &point){    
    // Get periodic distances to all markers in both monolayers
    int i;
    vector<float> dist1(surf[0].size()), dist2(surf[1].size());
    vector<int> aux1(surf[0].size()), aux2(surf[1].size());

    for(i=0;i<surf[0].size();++i){
        aux1[i] = i;
        dist1[i] = bilayer_ptr->get_system()
                ->distance(point,surf[0].XYZ(i),bilayer_ptr->get_frame(),true);
    }

    for(i=0;i<surf[1].size();++i){
        aux2[i] = i;
        dist2[i] = bilayer_ptr->get_system()
                ->distance(point,surf[1].XYZ(i),bilayer_ptr->get_frame(),true);
    }

    // Sort distances
    sort(aux1.begin(),aux1.end(),boost::bind(dist_sorter,_1,_2,dist1));
    sort(aux2.begin(),aux2.end(),boost::bind(dist_sorter,_1,_2,dist2));

    // Start filling output fields
    Bilayer_point_info ret;

    // Now take 10 closest markers in each monolayer and make selections for them
    ret.spot1_ptr = boost::shared_ptr<Selection>( new Selection(*bilayer_ptr->get_system()) );
    ret.spot2_ptr = boost::shared_ptr<Selection>( new Selection(*bilayer_ptr->get_system()) );

    for(i=0;i<spot_size;++i){
        ret.spot1_ptr->append(surf[0].Index(aux1[i]));
        ret.spot2_ptr->append(surf[1].Index(aux2[i]));
        //spot1.set_chain('P');
        //spot2.set_chain('Q');
    }

    ret.proj1 = ret.spot1_ptr->center();
    ret.proj2 = ret.spot2_ptr->center();
    // We use get_closest_image to bring projections close to the point according to pbc
    ret.proj1 = bilayer_ptr->get_system()->get_closest_image(ret.proj1,point,bilayer_ptr->get_frame());
    ret.proj2 = bilayer_ptr->get_system()->get_closest_image(ret.proj2,point,bilayer_ptr->get_frame());

    ret.center = (ret.proj1+ret.proj2)/2.0;
    ret.normal = (ret.proj2-ret.proj1).normalized();
    ret.thickness = (ret.proj2-ret.proj1).norm();
    ret.center_dist = (ret.center-point).norm();
    ret.surf_dist1 = (ret.proj1-point).norm();
    ret.surf_dist2 = (ret.proj2-point).norm();
    ret.monolayer = ret.surf_dist1<ret.surf_dist2 ? 1 : 2;

    return ret;
}

void Bilayer_point_info::print(){
    cout << endl << "Information for bilayer point:" << endl;
    cout << "Bilayer center:\t" << center.transpose() << endl;
    cout << "Bilayer thickness:\t" << thickness << endl;
    cout << "Bilayer normal:\t" << normal.transpose() << endl;
    cout << "Distance from center:\t" << center_dist << endl;
    cout << "Distance from the surface of monolayer 1:\t" << surf_dist1 << endl;
    cout << "Distance from the surface of monolayer 2:\t" << surf_dist2 << endl;
    cout << "Distance from the center:\t" << center_dist << endl;
    cout << "Projection to the surface of monolayer 1:\t" << proj1.transpose() << endl;
    cout << "Projection to the surface of monolayer 2:\t" << proj2.transpose() << endl;
    cout << "Belongs to monolayer:\t" << monolayer << endl;
}
