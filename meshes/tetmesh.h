/*********************************************************************************
*  Copyright(C) 2016: Marco Livesu                                               *
*  All rights reserved.                                                          *
*                                                                                *
*  This file is part of CinoLib                                                  *
*                                                                                *
*  CinoLib is dual-licensed:                                                     *
*                                                                                *
*   - For non-commercial use you can redistribute it and/or modify it under the  *
*     terms of the GNU General Public License as published by the Free Software  *
*     Foundation; either version 3 of the License, or (at your option) any later *
*     version.                                                                   *
*                                                                                *
*   - If you wish to use it as part of a commercial software, a proper agreement *
*     with the Author(s) must be reached, based on a proper licensing contract.  *
*                                                                                *
*  This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE       *
*  WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.     *
*                                                                                *
*  Author(s):                                                                    *
*                                                                                *
*     Marco Livesu (marco.livesu@gmail.com)                                      *
*     http://pers.ge.imati.cnr.it/livesu/                                        *
*                                                                                *
*     Italian National Research Council (CNR)                                    *
*     Institute for Applied Mathematics and Information Technologies (IMATI)     *
*     Via de Marini, 6                                                           *
*     16149 Genoa,                                                               *
*     Italy                                                                      *
**********************************************************************************/
#ifndef CINO_TETMESH_H
#define CINO_TETMESH_H

#include <sys/types.h>
#include <vector>

#include <cinolib/cinolib.h>
#include <cinolib/bbox.h>
#include <cinolib/geometry/vec3.h>
#include <cinolib/meshes/trimesh.h>
#include <cinolib/meshes/mesh_attributes.h>
#include <cinolib/meshes/abstract_polyhedralmesh.h>

namespace cinolib
{

template<class M = Mesh_std_attributes, // default template arguments
         class V = Vert_std_attributes,
         class E = Edge_std_attributes,
         class F = Polygon_std_attributes,
         class P = Polyhedron_std_attributes>
class Tetmesh : public AbstractPolyhedralMesh<M,V,E,F,P>
{
    public:

        Tetmesh(){}

        Tetmesh(const char * filename);

        Tetmesh(const std::vector<double> & coords,
                const std::vector<uint>   & polys);

        Tetmesh(const std::vector<vec3d> & verts,
                const std::vector<uint>  & polys);

        Tetmesh(const std::vector<vec3d>             & verts,
                const std::vector<std::vector<uint>> & polys);

        Tetmesh(const std::vector<vec3d>             & verts,
                const std::vector<std::vector<uint>> & faces,
                const std::vector<std::vector<uint>> & polys,
                const std::vector<std::vector<bool>> & polys_face_winding);

        //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

        MeshType mesh_type() const { return TETMESH; }

        //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

        void init();
        void load(const char * filename);
        void save(const char * filename) const;

        //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

        void update_normals();
        void update_tet_quality(const uint pid);
        void update_tet_quality();

        //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

        uint verts_per_poly(const uint) const { return  4; }
        uint verts_per_poly()           const { return  4; }
        uint edges_per_poly(const uint) const { return  6; }
        uint edges_per_poly()           const { return  6; }
        uint faces_per_poly(const uint) const { return  4; }
        uint faces_per_poly()           const { return  4; }
        uint verts_per_face(const uint) const { return  3; }
        uint verts_per_face()           const { return  3; }

        //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

        Trimesh<M,V,E,F> export_surface() const { return Trimesh<M,V,E,F>(this->verts,this->faces); }
        Trimesh<M,V,E,F> export_surface(std::map<uint,uint> & c2f_map,
                                        std::map<uint,uint> & f2c_map) const;

        //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

        std::vector<uint> face_tessellation(const uint fid) const;

        //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

        vec3d  poly_face_normal          (const uint pid, const uint face_offset) const;
        double poly_face_area            (const uint pid, const uint face_offset) const;
        double poly_dihedral_angle       (const uint pid, const uint face_offset1, const uint face_offset2) const;
        uint   poly_vert_opposite_to     (const uint pid, const uint face_offset) const;
        uint   poly_edge_opposite_to     (const uint pid, const uint vid0, const uint vid1) const;
        uint   poly_face_opposite_to     (const uint pid, const uint vid) const;
        double poly_edge_length          (const uint pid, const uint edge_offset) const;
        int    poly_shared_vert          (const uint pid, const std::vector<uint> & incident_edges) const;
        int    poly_adjacent_through_face(const uint pid, const uint face_offset) const;
        bool   poly_bary_coords          (const uint pid, const vec3d & p, std::vector<double> & wgts) const;
        double poly_volume               (const uint pid) const;
};

}

#ifndef  CINO_STATIC_LIB
#include "tetmesh.cpp"
#endif

#endif // CINO_TETMESH_H
