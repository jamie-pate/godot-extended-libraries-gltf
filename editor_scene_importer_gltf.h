/*************************************************************************/
/*  editor_scene_importer_gltf.h                                         */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2020 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2020 Godot Engine contributors (cf. AUTHORS.md).   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#ifndef EDITOR_SCENE_IMPORTER_GLTF_H
#define EDITOR_SCENE_IMPORTER_GLTF_H

#include "core/io/json.h"
#include "core/object.h"
#include "core/project_settings.h"
#include "core/vector.h"
#include "editor/import/resource_importer_scene.h"
#include "gltf_document.h"
#include "modules/csg/csg_shape.h"
#include "modules/gridmap/grid_map.h"
#include "scene/3d/mesh_instance.h"
#include "scene/3d/multimesh_instance.h"
#include "scene/3d/skeleton.h"
#include "scene/3d/spatial.h"
#include "scene/animation/animation_player.h"
#include "scene/gui/check_box.h"
#include "scene/main/node.h"
#include "scene/resources/packed_scene.h"
#include "scene/resources/surface_tool.h"

#ifndef _3D_DISABLED
class AnimationPlayer;
class BoneAttachment;
class MeshInstance;

#ifdef TOOLS_ENABLED
class EditorSceneImporterGLTF : public EditorSceneImporter {

  GDCLASS(EditorSceneImporterGLTF, EditorSceneImporter);

public:
  virtual uint32_t get_import_flags() const;
  virtual void get_extensions(List<String> *r_extensions) const;
  virtual Node *import_scene(const String &p_path, uint32_t p_flags,
                             int p_bake_fps,
                             List<String> *r_missing_deps = NULL,
                             Error *r_err = NULL);
  virtual Ref<Animation> import_animation(const String &p_path,
                                          uint32_t p_flags, int p_bake_fps);

  EditorSceneImporterGLTF();
};
#endif

class PackedSceneGLTF : public PackedScene {
  GDCLASS(PackedSceneGLTF, PackedScene);
  struct MeshInfo {
    Transform transform = Transform();
    Ref<Mesh> mesh = nullptr;
    String name = "";
    Vector<Ref<Material>> materials;
    Node *original_node = nullptr;
    Node *original_parent = nullptr;
  };
  Thread *save_thread = nullptr;
  Dictionary user_data;

protected:
  static void _bind_methods();

public:
  void save_scene(Node *p_node, const String &p_path, const String &p_src_path,
                  uint32_t p_flags, int p_bake_fps,
                  List<String> *r_missing_deps, Error *r_err = NULL);
  Error export_gltf(Node *p_root, String p_path, int32_t p_flags = 0,
                    real_t p_bake_fps = 1000.0f);
  static void _save_thread_function(void *p_user);
  Node *import_scene(const String &p_path, uint32_t p_flags, int p_bake_fps,
                     List<String> *r_missing_deps, Error *r_err);
  void pack_gltf(String p_path, int32_t p_flags = 0,
                 real_t p_bake_fps = 1000.0f);
  PackedSceneGLTF();
};

#endif // _3D_DISABLED
#endif // EDITOR_SCENE_IMPORTER_GLTF_H
