/* !
@file    glapp.h
@author  pghali@digipen.edu
@date    10/11/2016

This file contains the declaration of namespace GLApp that encapsulates the
functionality required to implement an OpenGL application including 
compiling, linking, and validating shader programs
setting up geometry and index buffers, 
configuring VAO to present the buffered geometry and index data to
vertex shaders,
configuring textures (in later labs),
configuring cameras (in later labs), 
and transformations (in later labs).
*//*__________________________________________________________________________*/

/*                                                                      guard
----------------------------------------------------------------------------- */
#ifndef GLAPP_H
#define GLAPP_H

/*                                                                   includes
----------------------------------------------------------------------------- */
#include <GL/glew.h> // for access to OpenGL API declarations 
#include <GLFW/glfw3.h>
#include "../include/glhelper.h"
#include "../include/glslshader.h"

struct GLApp {

  static void init();
  static void update(double delta_time);
  static void draw();
  static void cleanup();

  // encapsulates state required to render a geometrical model
  struct GLModel {
	  GLenum primitive_type;
	  GLSLShader shdr_pgm;
	  GLuint vaoid;
	  GLuint idx_elem_cnt;
	  // member functions defined in glapp.cpp
	  void setup_vao();
	  void setup_shdrpgm();
	  void draw();
  };

};

#endif /* GLAPP_H */
