/*!
@file    glapp.cpp
@author  pghali@digipen.edu
@date    10/11/2016

This file implements functionality useful and necessary to build OpenGL
applications including use of external APIs such as GLFW to create a
window and start up an OpenGL context and to extract function pointers
to OpenGL implementations.

*//*__________________________________________________________________________*/

/*                                                                   includes
----------------------------------------------------------------------------- */
#include "../include/glapp.h"
#include "../include/glhelper.h"
#include <array>

/*                                                   objects with file scope
----------------------------------------------------------------------------- */
static GLApp g_glapp;
static GLApp::GLModel mdl;

void GLApp::init() {
	// Part 1: clear colorbuffer with RGBA value in glClearColor ...
	glClearColor(1.f, 0.f, 0.f, 1.f);
	// Part 2: use the entire window as viewport ...
	GLint w = GLHelper::width, h = GLHelper::height;
	glViewport(0, 0, w, h);
	// Part 3: initialize VAO and create shader program
	mdl.setup_vao();
	mdl.setup_shdrpgm();
	// Part 4: This is related to Task 1 where OpenGL context
	// information is printed
	GLubyte const* str_ven = glGetString(GL_VENDOR);
	std::cout << "GPU Vendor: " << str_ven << std::endl;
	GLubyte const* str_ren = glGetString(GL_RENDERER);
	std::cout << "GL Renderer: " << str_ren << std::endl;
	GLubyte const* str_ver = glGetString(GL_VERSION);
	std::cout << "GL Version: " << str_ver << std::endl;
	GLubyte const* str_shalenver = glGetString(GL_SHADING_LANGUAGE_VERSION);
	std::cout << "GL Shader Version: " << str_shalenver << std::endl;
	GLint minor, major, doubleBuffer, maxVer, maxInd, tex_size, maxView[2];
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	std::cout << "GL Major Version: " << major << std::endl;
	glGetIntegerv(GL_MINOR_VERSION, &minor);
	std::cout << "GL Minor Version: " << minor << std::endl;
	glGetIntegerv(GL_DOUBLEBUFFER, &doubleBuffer);
	if (doubleBuffer == 1) // doubleBuffer가 1이면 더블 버퍼링이 지원되고 있다는 것을 의미
	{
		std::cout << "Current OpenGL Context is double buffered" << std::endl;
	}
	glGetIntegerv(GL_MAX_ELEMENTS_VERTICES, &maxVer);
	std::cout << "Maximum Vertex Count: " << maxVer << std::endl;
	glGetIntegerv(GL_MAX_ELEMENTS_INDICES, &maxInd);
	std::cout << "Maximum Indices Count: " << maxInd << std::endl;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &tex_size);
	std::cout << "Maximum texture size: " << tex_size << std::endl;
	glGetIntegerv(GL_MAX_VIEWPORT_DIMS, maxView);
	std::cout << "Maximum Viewport Dimensions:: " << maxView[0] << " x " << maxView[1] << std::endl;
}

void GLApp::update(double delta_time) {
	static bool isToggle = false;
	static int frameCount = 0;
	static GLclampf firstColor[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
	static GLclampf secondColor[4] = { 0.0f, 0.0f, 1.0f, 1.0f };

	// 목표 색깔 정의
	GLclampf* targetColor = isToggle ? secondColor : firstColor;

	frameCount++;
	if (frameCount >= GLHelper::fps && GLHelper::fps > 0) {
		isToggle = !isToggle;
		frameCount = 0;
	}

	glClearColor(targetColor[0], targetColor[1], targetColor[2], targetColor[3]);
	glClear(GL_COLOR_BUFFER_BIT);
}

void GLApp::draw() {
	// clear back buffer as before
	glClear(GL_COLOR_BUFFER_BIT);
	// now, render rectangular model from NDC coordinates to viewport
	mdl.draw();
}

void GLApp::cleanup() {
	// empty for now
}

void GLApp::GLModel::setup_vao() // VAO; Vertex Buffer Object
{
	// Initialize vertex data and color data
	std::array<glm::vec2, 4> pos_vtx; 
	pos_vtx[0] = glm::vec2(0.5f, -0.5f); pos_vtx[1] = glm::vec2(0.5f, 0.5f);
	pos_vtx[2] = glm::vec2(-0.5f, 0.5f); pos_vtx[3] = glm::vec2(-0.5f, -0.5f);
	std::array<glm::vec3, 4> clr_vtx; 
	clr_vtx[0] = glm::vec3(1.f, 0.f, 0.f); clr_vtx[1] = glm::vec3(0.f, 1.f, 0.f);
	clr_vtx[2] = glm::vec3(0.f, 0.f, 1.f); clr_vtx[3] = glm::vec3(1.f, 1.f, 1.f);

	//std::array<glm::vec2, 3> pos_vtx;
	//pos_vtx[0] = glm::vec2(0.5f, -0.5f);
	//pos_vtx[1] = glm::vec2(0.5f, 0.5f);
	//pos_vtx[2] = glm::vec2(-0.5f, 0.5f);

	//std::array<glm::vec3, 3> clr_vtx; 
	//clr_vtx[0] = glm::vec3(1.f, 0.f, 0.f);
	//clr_vtx[1] = glm::vec3(0.f, 1.f, 0.f);
	//clr_vtx[2] = glm::vec3(0.f, 0.f, 1.f);

	// Create VBO and Copy data in buffer
	GLuint vbo_hdl;
	glCreateBuffers(1, &vbo_hdl); 
	glNamedBufferStorage(vbo_hdl,
		sizeof(glm::vec2) * pos_vtx.size() + sizeof(glm::vec3) * clr_vtx.size(),
		nullptr, GL_DYNAMIC_STORAGE_BIT); 
	glNamedBufferSubData(vbo_hdl, 0,
		sizeof(glm::vec2) * pos_vtx.size(), pos_vtx.data());
	glNamedBufferSubData(vbo_hdl, sizeof(glm::vec2) * pos_vtx.size(),
		sizeof(glm::vec3) * clr_vtx.size(), clr_vtx.data()); 

	// Creating and Configuring VAO
	glCreateVertexArrays(1, &vaoid); // VAO를 생성 + vaoid 변수에 생성된 VAO의 핸들을 저장
	glEnableVertexArrayAttrib(vaoid, 0); // 속성 인덱스 0을 활성화
	glVertexArrayVertexBuffer(vaoid, 0, vbo_hdl, 0, sizeof(glm::vec2)); // 속성 인덱스 0과 위치 좌표 버퍼를 바인딩
	glVertexArrayAttribFormat(vaoid, 0, 2, GL_FLOAT, GL_FALSE, 0); // 속성 인덱스 0의 형식을 설정
	glVertexArrayAttribBinding(vaoid, 0, 0); // 속성 인덱스 0과 바인딩된 버퍼의 바인딩 인덱스를 설정

	glEnableVertexArrayAttrib(vaoid, 1); // 속성 인덱스 1을 활성화
	glVertexArrayVertexBuffer(vaoid, 1, vbo_hdl,
		sizeof(glm::vec2) * pos_vtx.size(), sizeof(glm::vec3)); // 속성 인덱스 1과 색상 값 버퍼를 바인딩
	glVertexArrayAttribFormat(vaoid, 1, 3, GL_FLOAT, GL_FALSE, 0); // 속성 인덱스 1의 형식을 설정
	glVertexArrayAttribBinding(vaoid, 1, 1); // 속성 인덱스 1과 바인딩된 버퍼의 바인딩 인덱스를 설정

	// Creating and Setting Index Buffers
	std::array<GLushort, 6> idx_vtx;
	idx_vtx[0] = 0; idx_vtx[1] = 1; idx_vtx[2] = 2;
	idx_vtx[3] = 2; idx_vtx[4] = 3; idx_vtx[5] = 0; // 사각형을 구성하는 정점들의 인덱스를 idx_vtx 배열에 저장

	/*std::array<GLushort, 3> idx_vtx;
	idx_vtx[0] = 0;
	idx_vtx[1] = 1;
	idx_vtx[2] = 2;*/

	GLuint ebo_hdl;
	glCreateBuffers(1, &ebo_hdl); // 인덱스 버퍼 객체를 생성 + ebo_hdl 변수에 생성된 인덱스 버퍼 객체의 핸들을 저장
	glNamedBufferStorage(ebo_hdl,
		sizeof(GLushort) * idx_vtx.size(),
		reinterpret_cast<GLvoid*>(idx_vtx.data()),
		GL_DYNAMIC_STORAGE_BIT); // 인덱스 버퍼에 메모리를 할당하고 데이터를 복사
	glVertexArrayElementBuffer(vaoid, ebo_hdl); // VAO에 인덱스 버퍼를 바인딩
	glBindVertexArray(0); // VAO를 언바인드
	GLModel::idx_elem_cnt = idx_vtx.size(); // idx_vtx 배열의 크기를 idx_elem_cnt 변수에 저장

}

void GLApp::GLModel::setup_shdrpgm() // VAO에 바인딩된 정정 데이터를 처리하여 렌더링하는 Shader Program
{
	std::vector<std::pair<GLenum, std::string>> shdr_files;
	shdr_files.push_back(std::make_pair(
		GL_VERTEX_SHADER,
		"../shaders/pass-thru-pos2d-clr.vert"));
	shdr_files.push_back(std::make_pair(
		GL_FRAGMENT_SHADER,
		"../shaders/basic-vtx-clr-attribute.frag"));
	shdr_pgm.CompileLinkValidate(shdr_files);
	if (GL_FALSE == shdr_pgm.IsLinked()) {
		std::cout << "Unable to compile/link/validate shader programs" <<
			std::endl;
		std::cout << shdr_pgm.GetLog() << std::endl;
		std::exit(EXIT_FAILURE);
	}

}

void GLApp::GLModel::draw()
{
	// there are many shader programs initialized - here we're saying
	// which specific shader program should be used to render geometry
	shdr_pgm.Use();
	// there are many models, each with their own initialized VAO object
	// here, we're saying which VAO's state should be used to set up the pipe
	glBindVertexArray(vaoid);
	// here, we're saying what primitive is to be rendered and how many such
	// primitives exist.
	// the graphics driver knows where to get the indices because the VAO containing
	// this state information has been made current ...
	glDrawElements(GL_TRIANGLES, idx_elem_cnt, GL_UNSIGNED_SHORT, NULL);
	// after completing the rendering, we tell the driver that the VAO vaoid
	// and the current shader program are no longer current
	glBindVertexArray(0);
	shdr_pgm.UnUse();

}


