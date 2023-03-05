/********************************************************************************
 *  This file is part of CinoLib * Copyright(C) 2016: Marco Livesu *
 *                                                                               *
 *  The MIT License *
 *                                                                               *
 *  Permission is hereby granted, free of charge, to any person obtaining a *
 *  copy of this software and associated documentation files (the "Software"), *
 *  to deal in the Software without restriction, including without limitation *
 *  the rights to use, copy, modify, merge, publish, distribute, sublicense, *
 *  and/or sell copies of the Software, and to permit persons to whom the *
 *  Software is furnished to do so, subject to the following conditions: *
 *                                                                               *
 *  The above copyright notice and this permission notice shall be included in *
 *  all copies or substantial portions of the Software. *
 *                                                                               *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR *
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, *
 *  FITNESS FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL THE
 ** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER *
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING *
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 ** IN THE SOFTWARE. *
 *                                                                               *
 *  Author(s): *
 *                                                                               *
 *     Marco Livesu (marco.livesu@gmail.com) *
 *     http://pers.ge.imati.cnr.it/livesu/ *
 *                                                                               *
 *     Italian National Research Council (CNR) * Institute for Applied
 *Mathematics and Information Technologies (IMATI)    * Via de Marini, 6 * 16149
 *Genoa,                                                              * Italy *
 *********************************************************************************/
#ifndef CINO_POLYGONMESH_H
#define CINO_POLYGONMESH_H

#include <cinolib/meshes/abstract_polygonmesh.h>
#include <sys/types.h>
#include <vector>

#include <range/v3/range/concepts.hpp>

namespace cinolib {

template <class M = Mesh_std_attributes, // default template arguments
          class V = Vert_std_attributes, class E = Edge_std_attributes,
          class P = Polygon_std_attributes>
class Polygonmesh : public AbstractPolygonMesh<M, V, E, P> {
public:
  explicit Polygonmesh() {}

  explicit Polygonmesh(const char *filename);

  explicit Polygonmesh(const std::vector<vec3d> &verts);

  explicit Polygonmesh(const std::vector<vec3d> &verts,
                       const std::vector<std::vector<uint>> &polys);

  template <typename RngCoords, typename RngPolys>
    requires(
        ranges::input_range<RngCoords> CPP_and ranges::input_range<RngPolys>)
  explicit Polygonmesh(const RngCoords &coords, const RngPolys &polys);

  explicit Polygonmesh(const std::vector<double> &coords,
                       const std::vector<std::vector<uint>> &polys);

  //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  MeshType mesh_type() const override { return POLYGONMESH; }
};

} // namespace cinolib

#ifndef CINO_STATIC_LIB
#include "polygonmesh.cpp"
#endif

#endif // CINO_POLYGONMESH_H
