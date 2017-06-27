#include <nimble/common.h>
#include <nimble/app.h>

#include <GL/glew.h>
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#endif
#define GLFW_INCLUDE_GLEXT
#include <GLFW/glfw3.h>

#include <nanovg.h>
#define NANOVG_GL3
#include <nanovg_gl.h>

#include <layout.h>

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	//
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	//
}

na::Application::Application()
{
	InitializeLayout();
}

na::Application::~Application()
{
	CleanupLayout();
	CleanupRendering();
}

void na::Application::Run()
{
	InitializeRendering();
	InitializeWindow();

	while (!glfwWindowShouldClose(m_window)) {
		if (IsInvalidated()) {
			Frame();
		}

		if (IsInvalidated()) {
			glfwPollEvents();
		} else {
			glfwWaitEvents(); // interrupt using glfwPostEmptyEvent
		}
	}
}

void na::Application::DoLayout()
{
	lay_reset_context(m_layout);
	lay_id root = lay_item(m_layout);

	if (m_root != nullptr) {
		m_root->DoLayout(m_layout, root);
	}

	lay_run_context(m_layout);
}

void na::Application::Frame()
{
	if (m_invalidatedLayout) {
		static int _layoutCount = 0;
		printf("Layout %d\n", _layoutCount++);

		m_invalidatedLayout = false;
		DoLayout();
		m_invalidatedRendering = true;
	}

	if (!m_invalidatedRendering) {
		return;
	}
	m_invalidatedRendering = false;

	static int _renderCount = 0;
	printf("Render %d\n", _renderCount++);

	glClear(GL_COLOR_BUFFER_BIT);

	nvgBeginFrame(m_nvg, 1024, 768, 1.0f);

	if (m_root != nullptr) {
		m_root->Draw(m_nvg);
	}

	nvgEndFrame(m_nvg);

	glfwSwapBuffers(m_window);
}

void na::Application::InvalidateLayout()
{
	m_invalidatedLayout = true;
}

void na::Application::InvalidateRendering()
{
	m_invalidatedRendering = true;
}

bool na::Application::IsInvalidated()
{
	return m_invalidatedLayout || m_invalidatedRendering;
}

void na::Application::InitializeLayout()
{
	m_layout = new lay_context;
	lay_init_context(m_layout);
	m_initializedLayout = true;
}

void na::Application::InitializeRendering()
{
	if (!glfwInit()) {
		printf("Glfw failed\n");
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	m_initializedRendering = true;
}

void na::Application::InitializeWindow()
{
	m_window = glfwCreateWindow(1024, 768, "Nimble App", nullptr, nullptr);
	if (m_window == nullptr) {
		printf("No window\n");
		CleanupRendering();
		return;
	}

	glfwSetCursorPosCallback(m_window, cursor_position_callback);
	glfwSetMouseButtonCallback(m_window, mouse_button_callback);
	glfwMakeContextCurrent(m_window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		printf("Glew failed\n");
		CleanupRendering();
		return;
	}
	glGetError();

	m_nvg = nvgCreateGL3(/*NVG_ANTIALIAS | */NVG_STENCIL_STROKES);
	if (m_nvg == nullptr) {
		printf("Nvg failed\n");
		CleanupRendering();
		return;
	}

	m_initializedWindow = true;
}

void na::Application::CleanupLayout()
{
	if (!m_initializedLayout) {
		return;
	}

	lay_destroy_context(m_layout);
	delete m_layout;
	m_layout = nullptr;

	m_initializedLayout = false;
}

void na::Application::CleanupRendering()
{
	if (!m_initializedRendering) {
		return;
	}

	glfwTerminate();

	m_initializedRendering = false;
	m_initializedWindow = false;
}
