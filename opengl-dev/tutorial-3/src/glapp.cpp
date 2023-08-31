/*!
@file    glapp.cpp
@author  pghali@digipen.edu
@date    10/11/2016

This file implements functionality useful and necessary to build OpenGL
applications including use of external APIs such as GLFW to create a
window and start up an OpenGL context and to extract function pointers
to OpenGL implementations.

*//*__________________________________________________________________________*/

#define _USE_MATH_DEFINES

/*                                                                   includes
----------------------------------------------------------------------------- */
#include "../include/glapp.h"
#include "../include/glhelper.h"
#include <iomanip>
#include <array>
#include <math.h>
#include <random>


/*                                                   objects with file scope
----------------------------------------------------------------------------- */
static GLApp g_glapp;
//static GLApp::GLModel mdl;
std::vector<GLApp::GLViewport> GLApp::vps;
std::vector<GLApp::GLModel> GLApp::models;

void GLApp::init() {
	// Part 1: clear colorbuffer with RGBA value in glClearColor ...
	glClearColor(1.f, 1.f, 1.f, 1.f);

	// Part 2: use the entire window as viewport ...
	GLint w{ GLHelper::width }, h{ GLHelper::height };

	// specification for viewport structure in vps ...
	vps.push_back(GLViewport(0, h / 2, w / 2, h / 2));
	vps.push_back(GLViewport(w / 2, h / 2, w / 2, h / 2));
	vps.push_back(GLViewport(0, 0, w / 2, h / 2));
	vps.push_back(GLViewport(w / 2, 0, w / 2, h / 2));

	// Part 3: create different geometries and insert them into
	// repository container GLApp::models ...
	GLApp::models.push_back(GLApp::points_model(20, 20,
		"../shaders/tutorial-2.vert",
		"../shaders/tutorial-2.frag"));

	GLApp::models.push_back(GLApp::lines_model(40, 40,
		"../shaders/tutorial-2.vert",
		"../shaders/tutorial-2.frag"));

	GLApp::models.push_back(GLApp::trifans_model(30,
		"../shaders/tutorial-2.vert",
		"../shaders/tutorial-2.frag"));

	GLApp::models.push_back(GLApp::tristrips_model(5, 10,
		"../shaders/tutorial-2.vert",
		"../shaders/tutorial-2.frag"));

	// Part 4: print GPU information ...
	GLHelper::print_specs();
}

void GLApp::update(double delta_time) {
	/*static bool isToggle = false;
	static int frameCount = 0;
	static GLclampf firstColor[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
	static GLclampf secondColor[4] = { 0.0f, 0.0f, 1.0f, 1.0f };*/

	// 목표 색깔 정의
	/*GLclampf* targetColor = isToggle ? secondColor : firstColor;

	frameCount++;
	if (frameCount >= GLHelper::fps && GLHelper::fps > 0) {
		isToggle = !isToggle;
		frameCount = 0;
	}*/

	// Erase Color Buffer
	/*static GLclampf backgroundColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glClearColor(backgroundColor[0], backgroundColor[1], backgroundColor[2], backgroundColor[3]);
	glClear(GL_COLOR_BUFFER_BIT);*/
}

void GLApp::draw() {
	/*GLint pcnt;
	glGetIntegerv(GL_POINT_C)*/
	GLHelper::title =
		"Tutorial 2";

	// clear back buffer as before
	glClear(GL_COLOR_BUFFER_BIT);
	// change single call to mdl.draw() with ...
	/*for (auto v : GLApp::vps) {
		glViewport(v.x, v.y, v.width, v.height);
		mdl.draw();
	}*/

	// render points in top-left viewport
	glViewport(vps[0].x, vps[0].y, vps[0].width, vps[0].height);
	GLApp::models[0].draw();

	// render line segments in top-right viewport
	glViewport(vps[1].x, vps[1].y, vps[1].width, vps[1].height);
	GLApp::models[1].draw();

	glViewport(vps[2].x, vps[2].y, vps[2].width, vps[2].height);
	GLApp::models[2].draw();

	glViewport(vps[3].x, vps[3].y, vps[3].width, vps[3].height);
	GLApp::models[3].draw();
}

void GLApp::cleanup() {
	// empty for now
}

//void GLApp::GLModel::setup_vao()
//{
//	// We'll define a rectangle in NDC coordinates that has one-fourth the
//	// area of the window.
//	// The NDC coordinates for a window range from [-1, 1] along both the
//	// X- and Y-axes.
//	// Therefore, the rectangle's (x, y) position coordinates are in range
//	// [-0.5, 0.5]
//	// We're using NDC coordinates, because we don't want to specify
//	// a "model-to-world-to-view-to-clip" transform to the vertex shader.
//	
//	std::array<glm::vec2, 4> pos_vtx; // 사각형의 네 개의 정점의 위치 좌표를 저장하는 배열
//	pos_vtx[0] = glm::vec2(0.5f, -0.5f); pos_vtx[1] = glm::vec2(0.5f, 0.5f);
//	pos_vtx[2] = glm::vec2(-0.5f, 0.5f); pos_vtx[3] = glm::vec2(-0.5f, -0.5f);
//	std::array<glm::vec3, 4> clr_vtx; // 각 정점의 색상 값을 저장하는 배열
//	clr_vtx[0] = glm::vec3(1.f, 0.f, 0.f); clr_vtx[1] = glm::vec3(0.f, 1.f, 0.f);
//	clr_vtx[2] = glm::vec3(0.f, 0.f, 1.f); clr_vtx[3] = glm::vec3(1.f, 1.f, 1.f);
//	//std::array<glm::vec2, 3> pos_vtx; // 삼각형의 세 개의 정점의 위치 좌표를 저장하는 배열
//	//pos_vtx[0] = glm::vec2(0.5f, -0.5f);
//	//pos_vtx[1] = glm::vec2(0.5f, 0.5f);
//	//pos_vtx[2] = glm::vec2(-0.5f, 0.5f);
//
//	//std::array<glm::vec3, 3> clr_vtx; // 각 정점의 색상 값을 저장하는 배열
//	//clr_vtx[0] = glm::vec3(1.f, 0.f, 0.f);
//	//clr_vtx[1] = glm::vec3(0.f, 1.f, 0.f);
//	//clr_vtx[2] = glm::vec3(0.f, 0.f, 1.f);
//
//	GLuint vbo_hdl;
//	glCreateBuffers(1, &vbo_hdl); // 버퍼 객체 생성 + vbo_hdl 변수에 버퍼 객체의 핸들을 저장
//	glNamedBufferStorage(vbo_hdl,
//		sizeof(glm::vec2) * pos_vtx.size() + sizeof(glm::vec3) * clr_vtx.size(),
//		nullptr, GL_DYNAMIC_STORAGE_BIT); // 버퍼에 메모리를 할당 + pos_vtx 배열과 clr_vtx 배열의 데이터를 버퍼에 복사
//	glNamedBufferSubData(vbo_hdl, 0,
//		sizeof(glm::vec2) * pos_vtx.size(), pos_vtx.data());
//	glNamedBufferSubData(vbo_hdl, sizeof(glm::vec2) * pos_vtx.size(),
//		sizeof(glm::vec3) * clr_vtx.size(), clr_vtx.data()); // 위치 좌표 데이터와 색상 값 데이터를 각각 저장
//	glCreateVertexArrays(1, &vaoid); // VAO를 생성 + vaoid 변수에 생성된 VAO의 핸들을 저장
//	glEnableVertexArrayAttrib(vaoid, 0); // 속성 인덱스 0을 활성화
//	glVertexArrayVertexBuffer(vaoid, 0, vbo_hdl, 0, sizeof(glm::vec2)); // 속성 인덱스 0과 위치 좌표 버퍼를 바인딩
//	glVertexArrayAttribFormat(vaoid, 0, 2, GL_FLOAT, GL_FALSE, 0); // 속성 인덱스 0의 형식을 설정
//	glVertexArrayAttribBinding(vaoid, 0, 0); // 속성 인덱스 0과 바인딩된 버퍼의 바인딩 인덱스를 설정
//
//	glEnableVertexArrayAttrib(vaoid, 1); // 속성 인덱스 1을 활성화
//	glVertexArrayVertexBuffer(vaoid, 1, vbo_hdl,
//		sizeof(glm::vec2) * pos_vtx.size(), sizeof(glm::vec3)); // 속성 인덱스 1과 색상 값 버퍼를 바인딩
//	glVertexArrayAttribFormat(vaoid, 1, 3, GL_FLOAT, GL_FALSE, 0); // 속성 인덱스 1의 형식을 설정
//	glVertexArrayAttribBinding(vaoid, 1, 1); // 속성 인덱스 1과 바인딩된 버퍼의 바인딩 인덱스를 설정
//
//	// represents indices of vertices that will define 2 triangles with
//	// counterclockwise winding
//	
//	std::array<GLushort, 6> idx_vtx;
//	idx_vtx[0] = 0; idx_vtx[1] = 1; idx_vtx[2] = 2;
//	idx_vtx[3] = 2; idx_vtx[4] = 3; idx_vtx[5] = 0; // 사각형을 구성하는 정점들의 인덱스를 idx_vtx 배열에 저장
//
//	/*std::array<GLushort, 3> idx_vtx;
//	idx_vtx[0] = 0;
//	idx_vtx[1] = 1;
//	idx_vtx[2] = 2;*/
//
//	GLuint ebo_hdl;
//	glCreateBuffers(1, &ebo_hdl); // 인덱스 버퍼 객체를 생성 + ebo_hdl 변수에 생성된 인덱스 버퍼 객체의 핸들을 저장
//	glNamedBufferStorage(ebo_hdl,
//		sizeof(GLushort) * idx_vtx.size(),
//		reinterpret_cast<GLvoid*>(idx_vtx.data()),
//		GL_DYNAMIC_STORAGE_BIT); // 인덱스 버퍼에 메모리를 할당하고 데이터를 복사
//	glVertexArrayElementBuffer(vaoid, ebo_hdl); // VAO에 인덱스 버퍼를 바인딩
//	glBindVertexArray(0); // VAO를 언바인드
//	GLModel::idx_elem_cnt = idx_vtx.size(); // idx_vtx 배열의 크기를 idx_elem_cnt 변수에 저장
//
//}


void GLApp::GLModel::setup_shdrpgm(std::string vtx_shdr,
	std::string frg_shdr) {
	std::vector<std::pair<GLenum, std::string>> shdr_files;
	shdr_files.push_back(std::make_pair(GL_VERTEX_SHADER, vtx_shdr));
	shdr_files.push_back(std::make_pair(GL_FRAGMENT_SHADER, frg_shdr));
	shdr_pgm.CompileLinkValidate(shdr_files);
	if (GL_FALSE == shdr_pgm.IsLinked()) {
		std::cout << "Unable to compile/link/validate shader programs\n";
		std::cout << shdr_pgm.GetLog() << "\n";
		std::exit(EXIT_FAILURE);
	}
}

//void GLApp::GLModel::setup_shdrpgm()
//{
//	std::vector<std::pair<GLenum, std::string>> shdr_files;
//	shdr_files.push_back(std::make_pair(
//		GL_VERTEX_SHADER,
//		"../shaders/pass-thru-pos2d-clr.vert"));
//	shdr_files.push_back(std::make_pair(
//		GL_FRAGMENT_SHADER,
//		"../shaders/basic-vtx-clr-attribute.frag"));
//	shdr_pgm.CompileLinkValidate(shdr_files);
//	if (GL_FALSE == shdr_pgm.IsLinked()) {
//		std::cout << "Unable to compile/link/validate shader programs" <<
//			std::endl;
//		std::cout << shdr_pgm.GetLog() << std::endl;
//		std::exit(EXIT_FAILURE);
//	}
//
//}

void GLApp::GLModel::draw()
{
	shdr_pgm.Use();
	glBindVertexArray(vaoid);
	if (primitive_type == GL_POINTS) 
	{
		glPointSize(10.f);
		glVertexAttrib3f(1, 1.f, 0.0f, 0.f); // red color for points
		glDrawArrays(GL_POINTS, 0, draw_cnt);
		glPointSize(1.f);
	}
	else if (primitive_type == GL_LINES) 
	{
		glLineWidth(1.f);
		glVertexAttrib3f(1, 0.f, 0.f, 1.f); // blue color for lines
		glDrawArrays(GL_LINES, 0, draw_cnt);
		glLineWidth(1.f);
	}
	else if (primitive_type == GL_TRIANGLE_FAN)
	{
		glDrawElements(GL_TRIANGLE_FAN, draw_cnt, GL_UNSIGNED_SHORT, 0);
	}
	else if (primitive_type == GL_TRIANGLE_STRIP)
	{
		glDrawElements(GL_TRIANGLE_STRIP, draw_cnt, GL_UNSIGNED_SHORT, 0);
	}
	glBindVertexArray(0);
	shdr_pgm.UnUse();
}

GLApp::GLModel GLApp::points_model(int slices, int stacks,
	std::string vtx_shdr, std::string frg_shdr)
{
	int const count{ (stacks + 1) * (slices + 1) };
	std::vector<glm::vec2> pos_vtx(count);
	std::vector<glm::vec3> clr_vtx(count); // new for task 4b
	float const u{ 2.f / static_cast<float>(slices) };
	float const v{ 2.f / static_cast<float>(stacks) };
	for (int row{ 0 }, index{ 0 }; row <= stacks; ++row) {
		for (int col{ 0 }; col <= slices; ++col) {
			pos_vtx[index] = glm::vec2(u * static_cast<float>(col) - 1.f,
				v * static_cast<float>(row) - 1.f);
			// randomly generate r, g, b values for vertex color attribute
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<float> dis(0.0f, 1.0f); // 0.0부터 1.0 사이의 균일한 분포를 갖는 난수 생성

			float r = dis(gen);
			float g = dis(gen);
			float b = dis(gen);

			clr_vtx[index++] = glm::vec3(r, g, b);
		}
	}

	GLuint vbo_hdl;
	glCreateBuffers(1, &vbo_hdl);
	glNamedBufferStorage(vbo_hdl, sizeof(glm::vec2) * pos_vtx.size(),
		pos_vtx.data(), GL_DYNAMIC_STORAGE_BIT);
	GLuint vao_hdl;
	glCreateVertexArrays(1, &vao_hdl);
	glEnableVertexArrayAttrib(vao_hdl, 0);
	glVertexArrayVertexBuffer(vao_hdl, 0, vbo_hdl, 0, sizeof(glm::vec2));
	glVertexArrayAttribFormat(vao_hdl, 0, 2, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vao_hdl, 0, 0);
	glBindVertexArray(0);

	GLApp::GLModel mdl;
	mdl.vaoid = vao_hdl;
	mdl.primitive_type = GL_POINTS;
	mdl.setup_shdrpgm(vtx_shdr, frg_shdr);
	mdl.draw_cnt = pos_vtx.size();
	mdl.primitive_cnt = pos_vtx.size();
	return mdl;
}

// ignore parameter stacks for now ...
GLApp::GLModel GLApp::lines_model(int slices, int stacks,
	std::string vtx_shdr,
	std::string frg_shdr)
{
	int const count{ (stacks + 1) * 2 + (slices + 1) * 2 };

	std::vector<glm::vec2> pos_vtx(count);

	float const u{ 2.f / static_cast<float>(slices) };
	float const v{ 2.f / static_cast<float>(stacks) };

	for (int col{ 0 }, index{ 0 }; col <= slices; col++)
	{
		float x{ u * static_cast<float>(col) - 1.f };
		pos_vtx[index++] = glm::vec2(x, -1.f);
		pos_vtx[index++] = glm::vec2(x, 1.f);
	}

	for (int row{ 0 }, index{ (slices + 1) * 2 }; row <= stacks; row++) // index를 vertical line을 다 그린 후로 설정
	{
		float y{ v * static_cast<float>(row) - 1.f };
		pos_vtx[index++] = glm::vec2(-1.f, y);
		pos_vtx[index++] = glm::vec2(1.f, y);
	}

	// set up VAO as in GLApp::points_model
	GLuint vbo_hdl;
	glCreateBuffers(1, &vbo_hdl);
	glNamedBufferStorage(vbo_hdl, sizeof(glm::vec2) * pos_vtx.size(),
		pos_vtx.data(), GL_DYNAMIC_STORAGE_BIT);
	GLuint vao_hdl;
	glCreateVertexArrays(1, &vao_hdl);
	glEnableVertexArrayAttrib(vao_hdl, 0);
	glVertexArrayVertexBuffer(vao_hdl, 0, vbo_hdl, 0, sizeof(glm::vec2));
	glVertexArrayAttribFormat(vao_hdl, 0, 2, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vao_hdl, 0, 0);
	glBindVertexArray(0);

	GLApp::GLModel mdl;
	mdl.vaoid = vao_hdl; // set up VAO same as in GLApp::points_model
	mdl.primitive_type = GL_LINES;
	mdl.setup_shdrpgm(vtx_shdr, frg_shdr);
	mdl.draw_cnt = count; // number of vertices
	mdl.primitive_cnt = count / 2; // number of GL_LINES
	return mdl;
}

GLApp::GLModel GLApp::trifans_model(int slices, std::string vtx_shdr,
	std::string frg_shdr)
{
	// Step 1: Generate the (slices+1) count of vertices required to
	// render a triangle fan parameterization of a circle with unit
	// radius and centered at (0, 0)

	int const count{ slices + 1 };
	
	float const angle = 0.0f;
	double const conversionValue{ (M_PI * 2) / slices };


	std::vector<glm::vec2> vertices(count);
	std::vector<glm::vec3> clr_vtx(count);
	vertices[0] = glm::vec2(0, 0);

	for (int i = 1; i <= slices; ++i) {
		for (int j = 0, index = 0; j <= slices; ++j)
		{
			float theta = angle + (i - 1) * conversionValue;
			float x = std::cos(theta);
			float y = std::sin(theta);
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<float> dis(0.0f, 1.0f); // 0.0부터 1.0 사이의 균일한 분포를 갖는 난수 생성
			float r = dis(gen);
			float g = dis(gen);
			float b = dis(gen);
			vertices[i] = glm::vec2(x, y);
			clr_vtx[j] = glm::vec3(r, g, b);
		}
	}

	std::vector<GLushort> idx_vtx;
	idx_vtx.push_back(0); // Pivot vertex
	for (GLushort i = 1; i <= slices; ++i) {
		idx_vtx.push_back(i);
	}
	idx_vtx.push_back(1);

	GLuint vbo_hdl;
	glCreateBuffers(1, &vbo_hdl); // 버퍼 객체 생성 + vbo_hdl 변수에 버퍼 객체의 핸들을 저장
	glNamedBufferStorage(vbo_hdl,
		sizeof(glm::vec2) * vertices.size() + sizeof(glm::vec3) * clr_vtx.size(),
		nullptr, GL_DYNAMIC_STORAGE_BIT); // 버퍼에 메모리를 할당 + pos_vtx 배열과 clr_vtx 배열의 데이터를 버퍼에 복사
	glNamedBufferSubData(vbo_hdl, 0,
		sizeof(glm::vec2) * vertices.size(), vertices.data());
	glNamedBufferSubData(vbo_hdl, sizeof(glm::vec2) * vertices.size(),
		sizeof(glm::vec3) * clr_vtx.size(), clr_vtx.data()); // 위치 좌표 데이터와 색상 값 데이터를 각각 저장
	GLuint vao_hdl;
	glCreateVertexArrays(1, &vao_hdl); // VAO를 생성 + vaoid 변수에 생성된 VAO의 핸들을 저장
	glEnableVertexArrayAttrib(vao_hdl, 0); // 속성 인덱스 0을 활성화
	glVertexArrayVertexBuffer(vao_hdl, 0, vbo_hdl, 0, sizeof(glm::vec2)); // 속성 인덱스 0과 위치 좌표 버퍼를 바인딩
	glVertexArrayAttribFormat(vao_hdl, 0, 2, GL_FLOAT, GL_FALSE, 0); // 속성 인덱스 0의 형식을 설정
	glVertexArrayAttribBinding(vao_hdl, 0, 0); // 속성 인덱스 0과 바인딩된 버퍼의 바인딩 인덱스를 설정

	glEnableVertexArrayAttrib(vao_hdl, 1); // 속성 인덱스 1을 활성화
	glVertexArrayVertexBuffer(vao_hdl, 1, vbo_hdl,
		sizeof(glm::vec2) * vertices.size(), sizeof(glm::vec3)); // 속성 인덱스 1과 색상 값 버퍼를 바인딩
	glVertexArrayAttribFormat(vao_hdl, 1, 3, GL_FLOAT, GL_FALSE, 0); // 속성 인덱스 1의 형식을 설정
	glVertexArrayAttribBinding(vao_hdl, 1, 1); // 속성 인덱스 1과 바인딩된 버퍼의 바인딩 인덱스를 설정

	GLuint ebo_hdl;
	glCreateBuffers(1, &ebo_hdl); // 인덱스 버퍼 객체를 생성 + ebo_hdl 변수에 생성된 인덱스 버퍼 객체의 핸들을 저장
	glNamedBufferStorage(ebo_hdl,
		sizeof(GLushort) * idx_vtx.size(),
		reinterpret_cast<GLvoid*>(idx_vtx.data()),
		GL_DYNAMIC_STORAGE_BIT); // 인덱스 버퍼에 메모리를 할당하고 데이터를 복사
	glVertexArrayElementBuffer(vao_hdl, ebo_hdl); // VAO에 인덱스 버퍼를 바인딩
	glBindVertexArray(0); // VAO를 언바인드


	GLApp::GLModel mdl;
	mdl.vaoid = vao_hdl; // set up VAO same as in GLApp::points_model
	mdl.primitive_type = GL_TRIANGLE_FAN;
	mdl.setup_shdrpgm(vtx_shdr, frg_shdr);
	mdl.draw_cnt = idx_vtx.size(); // number of vertices
	mdl.primitive_cnt = slices; // number of GL_LINES
	return mdl;

	// Step 2: In addition to vertex position coordinates, generate vertex
	// color coordinates. Each RGB component must be randomly computed.

	// Step 3: Generate the triangle fan's index or element list.

	// Step 4: Generate a VAO handle to encapsulate the VBO(s) and
	// state of this triangle mesh

	// Return an appropriately initialized instance of GLApp::GLModel
}

GLApp::GLModel GLApp::tristrips_model(int slices, int stacks, std::string vtx_shdr, std::string frg_shdr)
{
	int const verticesPerStrip = slices + 1;
	int const vertexCount = verticesPerStrip * (stacks + 1);
	std::vector<glm::vec2> pos_vtx(vertexCount);
	std::vector<glm::vec3> clr_vtx(vertexCount);

	float const u{ 2.f / static_cast<float>(slices) };
	float const v{ 2.f / static_cast<float>(stacks) };

	for (int row = 0, index = 0; row <= stacks; ++row)
	{
		for (int col = 0; col <= slices; ++col)
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<float> dis(0.0f, 1.0f);
			float r = dis(gen);
			float g = dis(gen);
			float b = dis(gen);
			pos_vtx[index] = glm::vec2(u * static_cast<float>(col) - 1.f, v * static_cast<float>(row) - 1.f);
			clr_vtx[index] = glm::vec3(r, g, b);
			index++;
		}
	}

	std::vector<GLushort> idx_vtx;

	for (int row = 0; row < stacks; ++row)
	{
		// 아래쪽 삼각형 스트립에 해당하는 인덱스를 추가
		for (int col = 0; col <= slices; ++col)
		{
			idx_vtx.push_back(static_cast<GLushort>(row * verticesPerStrip + col));
			idx_vtx.push_back(static_cast<GLushort>((row + 1) * verticesPerStrip + col));
		}

		// 아래쪽 삼각형 스트립의 끝점을 따라가지 않는(degenerate) 삼각형으로 연결
		if (row < stacks - 1)
		{
			idx_vtx.push_back(static_cast<GLushort>((row + 1) * verticesPerStrip + slices));
			idx_vtx.push_back(static_cast<GLushort>((row + 1) * verticesPerStrip));
		}
	}


	GLuint vbo_hdl;
	glCreateBuffers(1, &vbo_hdl);
	glNamedBufferStorage(vbo_hdl,
		sizeof(glm::vec2) * pos_vtx.size() + sizeof(glm::vec3) * clr_vtx.size(),
		nullptr, GL_DYNAMIC_STORAGE_BIT);
	glNamedBufferSubData(vbo_hdl, 0, sizeof(glm::vec2) * pos_vtx.size(), pos_vtx.data());
	glNamedBufferSubData(vbo_hdl, sizeof(glm::vec2) * pos_vtx.size(), sizeof(glm::vec3) * clr_vtx.size(), clr_vtx.data());

	GLuint vao_hdl;
	glCreateVertexArrays(1, &vao_hdl);
	glEnableVertexArrayAttrib(vao_hdl, 0);
	glVertexArrayVertexBuffer(vao_hdl, 0, vbo_hdl, 0, sizeof(glm::vec2));
	glVertexArrayAttribFormat(vao_hdl, 0, 2, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vao_hdl, 0, 0);

	glEnableVertexArrayAttrib(vao_hdl, 1);
	glVertexArrayVertexBuffer(vao_hdl, 1, vbo_hdl, sizeof(glm::vec2) * pos_vtx.size(), sizeof(glm::vec3));
	glVertexArrayAttribFormat(vao_hdl, 1, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vao_hdl, 1, 1);

	GLuint ebo_hdl;
	glCreateBuffers(1, &ebo_hdl);
	glNamedBufferStorage(ebo_hdl, sizeof(GLushort) * idx_vtx.size(), reinterpret_cast<GLvoid*>(idx_vtx.data()), GL_DYNAMIC_STORAGE_BIT);
	glVertexArrayElementBuffer(vao_hdl, ebo_hdl);

	glBindVertexArray(0);

	GLApp::GLModel mdl;
	mdl.vaoid = vao_hdl;
	mdl.primitive_type = GL_TRIANGLE_STRIP;
	mdl.setup_shdrpgm(vtx_shdr, frg_shdr);
	mdl.draw_cnt = idx_vtx.size();
	mdl.primitive_cnt = slices;

	return mdl;
}


